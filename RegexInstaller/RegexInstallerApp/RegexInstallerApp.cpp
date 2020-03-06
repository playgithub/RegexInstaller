#include "pch.h"
#include <RegexInstaller/RegexInstaller.h>
#include <UI/MainFrame.h>
#include "RegexInstallerApp.h"

IMPLEMENT_APP(RegexInstallerApp)

RegexInstallerApp::RegexInstallerApp() :
    _is_console_mode(false)
{
}

bool RegexInstallerApp::OnInit()
{
    if (!wxApp::OnInit())
    {
        wxLogDebug(wxT("wxApp::OnInit failed"));
        return false;
    }

    if (!_is_console_mode)
    {
        MainFrame * pMF = new MainFrame(nullptr, wxID_ANY, "Install Tool", wxDefaultPosition, wxSize(800, 600));
        pMF->Center();
        pMF->Show();
    }

    return true;
}

int RegexInstallerApp::OnRun()
{
    if (_is_console_mode)
    {
        try
        {
            RegexInstaller installer;
            installer.Install(_install_file_path_in_console_mode.ToStdString());
            return 0;
        }
        catch (std::exception & ex)
        {
            wxLogDebug("RegexInstaller::Install failed (%s)", ex.what());
            return -1;
        }
    }
    else
    {
        return wxApp::OnRun();
    }
}

int RegexInstallerApp::OnExit()
{
    return wxApp::OnExit();
}

void RegexInstallerApp::OnInitCmdLine(wxCmdLineParser & parser)
{
    parser.AddLongSwitch("console-mode", "run in console mode", wxCMD_LINE_VAL_NONE);
    parser.AddLongOption("install-file-path", "install file path", wxCMD_LINE_VAL_STRING);
}

bool RegexInstallerApp::OnCmdLineParsed(wxCmdLineParser & parser)
{
    _is_console_mode = parser.FoundSwitch("console-mode");
    if (_is_console_mode)
    {
        if (!parser.Found("install-file-path", &_install_file_path_in_console_mode))
        {
            wxLogDebug(L"no install-file-path");
            return false;
        }
    }

    return true;
}