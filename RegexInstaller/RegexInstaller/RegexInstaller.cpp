#include "pch.h"
#include <RegexFileCopy/RegexFileCopy.h>
#include "RegexInstaller.h"

namespace fs = std::filesystem;

void RegexInstaller::LoadConfig(const std::string & sConfigFilePath, const std::string & os)
{
    if (!_config.LoadFromFile(sConfigFilePath, os))
        throw std::runtime_error("InstallerConfig::LoadFromFile failed");
}

void RegexInstaller::Install(const std::string & sInstallFilePath)
{
    std::ifstream ifs;
    ifs.open(sInstallFilePath);
    if (ifs.fail())
        throw std::runtime_error("Failed to open application installer config file");

    rapidjson::IStreamWrapper isw(ifs);

    rapidjson::Document jd;
    jd.ParseStream(isw);
    if (jd.HasParseError())
    {
        auto ec = jd.GetParseError();
        const char * es = rapidjson::GetParseError_En(ec);
        throw std::runtime_error(es);
    }

    if (!jd.IsObject())
        throw std::runtime_error("root is not a json object");
    
    rapidjson::Value::MemberIterator it = jd.FindMember("InstallItems");
    if (it == jd.MemberEnd())
        throw std::runtime_error("no json member for InstallItems");

    const rapidjson::Value & jvInstallItems = it->value;
    if (!jvInstallItems.IsArray())
        throw std::runtime_error("not a json array for InstallItems");


    fs::path path(sInstallFilePath);
    _install_file_directory_path = path.parent_path();

    for (rapidjson::Value::ConstValueIterator it = jvInstallItems.Begin();
         it != jvInstallItems.End();
         ++it)
        InstallItem(*it);
}

void RegexInstaller::InstallItem(const rapidjson::Value & jvInstallItem) const
{
    if (!jvInstallItem.IsObject())
        throw std::runtime_error("Invalid install file (not a json object for InstallItem)");

    rapidjson::Value::ConstMemberIterator it;

    it = jvInstallItem.FindMember("SourceRoot");
    if (it == jvInstallItem.MemberEnd())
        throw std::runtime_error("Invalid install file (no SourceRoot)");
    fs::path source_root(it->value.GetString());
    if (source_root.is_relative())
    {
        source_root = _install_file_directory_path / source_root;
        source_root = fs::canonical(source_root);
    }

    it = jvInstallItem.FindMember("DestinationRoot");
    if (it == jvInstallItem.MemberEnd())
        throw std::runtime_error("Invalid install file (no DestinationRoot)");
    fs::path destination_root(it->value.GetString());
    if (destination_root.is_relative())
    {
        destination_root = _install_file_directory_path / destination_root;
        destination_root = fs::canonical(destination_root);
    }

    it = jvInstallItem.FindMember("RelativePathRegex");
    if (it == jvInstallItem.MemberEnd())
        throw std::runtime_error("Invalid install file (no RelativePathRegex)");
    std::string relative_path_regex(it->value.GetString(), it->value.GetStringLength());

    RegexFileCopy c;
    c.Copy(source_root, destination_root, std::regex(relative_path_regex), std::filesystem::copy_options::update_existing);
}
