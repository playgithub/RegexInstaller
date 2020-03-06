#pragma once

class RegexInstallerApp : public wxApp
{
public:
    RegexInstallerApp();
public:
    virtual bool OnInit() wxOVERRIDE;
    virtual int OnRun() wxOVERRIDE;
    virtual int OnExit() wxOVERRIDE;
    virtual void OnInitCmdLine(wxCmdLineParser & parser) wxOVERRIDE;
    virtual bool OnCmdLineParsed(wxCmdLineParser & parser) wxOVERRIDE;
private:
    bool _is_console_mode;
    wxString _install_file_path_in_console_mode;
};

DECLARE_APP(RegexInstallerApp)
