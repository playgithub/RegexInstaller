#pragma once

#include "RegexInstallerConfig/RegexInstallerConfig.h"

class RegexInstaller
{
public:
    void LoadConfig(const std::string & sConfigFilePath, const std::string & os);
    void Install(const std::string & sInstallFilePath) const;
public:
    const RegexInstallerConfig & GetConfig() const { return _config; }
private:
    void InstallItem(const rapidjson::Value & jvInstallItem) const;
private:
    RegexInstallerConfig _config;
};

