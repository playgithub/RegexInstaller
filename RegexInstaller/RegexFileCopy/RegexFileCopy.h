#pragma once

class RegexFileCopy
{
public:
    void Copy(const std::filesystem::path & source_root,
              const std::filesystem::path & destination_root,
              const std::regex & relative_path_regex, // relative to source_root & destination_root, match literally
              std::filesystem::copy_options copy_options);
private:
    void CollectRelativePathsRecursively(const std::filesystem::directory_entry & de,
                                         std::list<std::filesystem::path> & path_list);
    template<class ForwardIterator>
    void CopyByRelativePaths(ForwardIterator it_begin_path,
                             ForwardIterator it_end_path);
    void CreateDirectoriesIfNotExist(const std::filesystem::path & path);
private:
    std::filesystem::path _source_root;
    std::filesystem::path _destination_root;
    std::regex _relative_path_regex;
    std::filesystem::copy_options _copy_options;
};
