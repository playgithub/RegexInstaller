#include "pch.h"
#include "RegexFileCopy.h"

namespace fs = std::filesystem;

void RegexFileCopy::Copy(const fs::path & source_root,
                         const fs::path & destination_root,
                         const std::regex & relative_path_regex,
                         std::filesystem::copy_options copy_options)
{
    if (!fs::exists(source_root))
        throw std::invalid_argument("source root not exist");

    if (!fs::is_directory(source_root))
        throw std::invalid_argument("source root is not a directory");

    _source_root = source_root;

    _destination_root = destination_root;

    _relative_path_regex = relative_path_regex;

    _copy_options = copy_options;

    std::list<fs::path> path_list;

    CollectRelativePathsRecursively(fs::directory_entry(_source_root), path_list);
    CopyByRelativePaths(path_list.cbegin(), path_list.cend());
}

void RegexFileCopy::CollectRelativePathsRecursively(const fs::directory_entry & de,
                                                    std::list<fs::path> & path_list)
{
    if (de.is_regular_file())
    {
        const fs::path & path = de.path();
        const fs::path relative_path = fs::relative(path, _source_root);
        if (std::regex_match(relative_path.string(), _relative_path_regex))
            path_list.push_back(relative_path);
    }
    else if (de.is_directory())
    {
        const fs::path & path = de.path();
        const fs::path relative_path = fs::relative(path, _source_root);
        if (std::regex_match(relative_path.string(), _relative_path_regex))
            path_list.push_back(relative_path);

        for (const auto & de : fs::directory_iterator(path))
            CollectRelativePathsRecursively(de, path_list);
    }
}

template<class ForwardIterator>
void RegexFileCopy::CopyByRelativePaths(ForwardIterator it_begin_path,
                                        ForwardIterator it_end_path)
{
    for (auto it = it_begin_path;
         it != it_end_path;
         ++it)
    {
        const fs::path relative_path = *it;

        fs::path source_path = _source_root / relative_path;

        if (!fs::exists(source_path))
        {
            std::ostringstream oss;
            oss << "source path not exist (" << source_path << ")";
            throw oss.str();
        }

        const fs::path destination_path = _destination_root / relative_path;


        if (fs::is_regular_file(source_path))
        {
            const auto parent_path = destination_path.parent_path();
            CreateDirectoriesIfNotExist(parent_path);

            fs::copy(source_path, destination_path, _copy_options);
        }
        else if (fs::is_directory(source_path))
            CreateDirectoriesIfNotExist(destination_path);
    }
}

void RegexFileCopy::CreateDirectoriesIfNotExist(const std::filesystem::path & path)
{
    if (!fs::exists(path))
        fs::create_directories(path);
    else if (!fs::is_directory(path))
        throw std::runtime_error("directory can not be created (directory name conflicats with existing file name)");
}
