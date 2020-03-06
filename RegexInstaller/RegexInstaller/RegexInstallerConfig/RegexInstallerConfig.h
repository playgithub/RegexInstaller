#pragma once

class RegexInstallerConfig
{
public:
    bool LoadFromFile(const std::string & path, const std::string & os);
public:
    void GetLibPath(const char * pLibName,
                    std::filesystem::path * pInc,
                    std::filesystem::path * pLib,
                    std::filesystem::path * pBin) const;
    void GetLibPath(std::string & sLibName,
                    std::filesystem::path * pInc,
                    std::filesystem::path * pLib,
                    std::filesystem::path * pBin) const;
private:
    rapidjson::Document _jdConfigByOS;
};
