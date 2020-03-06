#pragma once

class RegexInstallerApp : public wxApp
{
public:
    virtual bool OnInit();
    virtual int OnExit();
};

DECLARE_APP(RegexInstallerApp)
