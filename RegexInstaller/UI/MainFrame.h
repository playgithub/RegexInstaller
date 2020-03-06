#pragma once

#include <RegexInstaller/RegexInstaller.h>

class InstallInfoListView;

class MainFrame : public wxFrame
{
    DECLARE_EVENT_TABLE()
public:
    MainFrame(wxWindow * parent,
              wxWindowID id,
              const wxString & title,
              const wxPoint & pos = wxDefaultPosition,
              const wxSize & size = wxDefaultSize,
              long style = wxDEFAULT_FRAME_STYLE,
              const wxString & name = wxFrameNameStr);
private: // event handlers
    void OnBtnLocateInstallationFile(wxCommandEvent & event);
    void OnBtnInstall(wxCommandEvent & event);
    void OnShow(wxShowEvent & event);
private:
    wxTextCtrl * _ptcInstallationFilePath;
    InstallInfoListView * _plvInstallInfo;
private:
    RegexInstaller _installer;
};

