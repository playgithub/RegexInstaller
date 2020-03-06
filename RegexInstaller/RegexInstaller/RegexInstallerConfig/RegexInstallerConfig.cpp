#include "pch.h"
#include "RegexInstallerConfig.h"

bool RegexInstallerConfig::LoadFromFile(const std::string & path, const std::string & os)
{
    std::ifstream ifs;
    ifs.open(path);
    if (ifs.fail())
    {
        wxLogDebug(wxT("Failed to open config file"));
        return false;
    }

    rapidjson::IStreamWrapper isw(ifs);

    rapidjson::Document jd;
    jd.ParseStream(isw);
    if (jd.HasParseError())
    {
        auto ec = jd.GetParseError();
        const char * es = rapidjson::GetParseError_En(ec);
        wxLogDebug(es);
        return false;
    }

    if (!jd.IsObject())
    {
        wxLogDebug(wxT("json root is not a json object"));
        return false;
    }

    rapidjson::Value::MemberIterator it = jd.FindMember(os.c_str());
    if (it == jd.MemberEnd())
    {
        wxLogDebug("no config for %s", os.c_str());
        return false;
    }

    if (!it->value.IsObject())
    {
        wxLogDebug("config for %s is not a json object ", os.c_str());
        return false;
    }

    _jdConfigByOS.CopyFrom(it->value, _jdConfigByOS.GetAllocator());

    return true;
}

void RegexInstallerConfig::GetLibPath(const char * pLibName,
                                      std::filesystem::path * pInc,
                                      std::filesystem::path * pLib,
                                      std::filesystem::path * pBin) const
{
    std::string sLibName(pLibName);
    GetLibPath(sLibName, pInc, pLib, pBin);
}

void RegexInstallerConfig::GetLibPath(std::string & sLibName,
                                      std::filesystem::path * pInc,
                                      std::filesystem::path * pLib,
                                      std::filesystem::path * pBin) const
{
    if (pInc != nullptr)
        pInc->clear();

    if (pLib != nullptr)
        pLib->clear();

    if (pBin != nullptr)
        pBin->clear();

    if (!_jdConfigByOS.IsObject())
    {
        wxLogDebug(wxT("not a json object for installer config"));
        return;
    }

    rapidjson::Value::ConstMemberIterator it = _jdConfigByOS.FindMember(sLibName.c_str());
    if (it == _jdConfigByOS.MemberEnd())
    {
        wxLogDebug(wxT("lib not found"));
        return;
    }

    const rapidjson::Value & jv = it->value;
    if (!jv.IsObject())
    {
        wxLogDebug(wxT("not a json object for lib values"));
        return;
    }

    it = jv.FindMember("root");
    if (it == jv.MemberEnd())
    {
        wxLogDebug(wxT("no root for lib"));
        return;
    }

    std::filesystem::path rootPath = it->value.GetString();

    if (pInc != nullptr)
    {
        it = jv.FindMember("inc");
        if (it != jv.MemberEnd())
        {
            *pInc = rootPath / it->value.GetString();
            pInc->make_preferred();
        }
    }

    if (pLib != nullptr)
    {
        it = jv.FindMember("lib");
        if (it != jv.MemberEnd())
        {
            *pLib = rootPath / it->value.GetString();
            pLib->make_preferred();
        }
    }

    if (pBin != nullptr)
    {
        it = jv.FindMember("bin");
        if (it != jv.MemberEnd())
        {
            *pBin = rootPath / it->value.GetString();
            pBin->make_preferred();
        }
    }
}
