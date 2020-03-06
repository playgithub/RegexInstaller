#include "pch.h"
#include <RegexFileCopy/RegexFileCopy.h>
#include "RegexInstaller.h"

void RegexInstaller::LoadConfig(const std::string & sConfigFilePath, const std::string & os)
{
    if (!_config.LoadFromFile(sConfigFilePath, os))
        throw std::runtime_error("InstallerConfig::LoadFromFile failed");
}

void RegexInstaller::Install(const std::string & sInstallFilePath) const
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

    for (rapidjson::Value::ConstValueIterator it = jvInstallItems.Begin();
         it != jvInstallItems.End();
         ++it)
        InstallItem(*it);
}

void RegexInstaller::InstallItem(const rapidjson::Value & jvInstallItem) const
{
    if (!jvInstallItem.IsObject())
        throw std::runtime_error("Invalid file format (file group)");

    rapidjson::Value::ConstMemberIterator it;

    it = jvInstallItem.FindMember("SourceRoot");
    if (it == jvInstallItem.MemberEnd())
        throw std::runtime_error("invalid install file (no SourceRoot)");
    std::string source_root(it->value.GetString(), it->value.GetStringLength());

    it = jvInstallItem.FindMember("DestinationRoot");
    if (it == jvInstallItem.MemberEnd())
        throw std::runtime_error("invalid install file (no DestinationRoot)");
    std::string destination_root(it->value.GetString(), it->value.GetStringLength());

    it = jvInstallItem.FindMember("RelativePathRegex");
    if (it == jvInstallItem.MemberEnd())
        throw std::runtime_error("invalid install file (no RelativePathRegex)");
    std::string relative_path_regex(it->value.GetString(), it->value.GetStringLength());

    RegexFileCopy c;
    c.Copy(source_root, destination_root, std::regex(relative_path_regex), std::filesystem::copy_options::update_existing);
}
