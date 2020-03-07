#pragma once

#include "RegexInstallerConfig/RegexInstallerConfig.h"

class RegexInstaller
{
public:
    void LoadConfig(const std::string & sConfigFilePath, const std::string & os);

    /*
     * Install file sample (json):
     * {
     *     "InstallItems":
     *     [
     *         {
     *             "SourceRoot": "SampleApp",
     *             "DestinationRoot" : "C:\\Users\\disc\\Apps\\SampleApp",
     *             "RelativePathRegex" : ".*\\.txt$"
     *         }
     *     ]
     * }
     */
    //  If SourceRoot/DestinationRoot is a relative path, it'll be relative to the parent path of the install file.
    void Install(const std::string & sInstallFilePath);
public:
    const RegexInstallerConfig & GetConfig() const { return _config; }
private:
    void InstallItem(const rapidjson::Value & jvInstallItem) const;
private:
    RegexInstallerConfig _config;
    std::filesystem::path _install_file_directory_path;
};

