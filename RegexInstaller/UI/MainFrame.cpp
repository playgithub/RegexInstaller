#include "pch.h"
#include <UI/InstallInfoListView/InstallInfoListView.h>
#include "MainFrame.h"

#define ID_BTN_LOCATE_INSTALLATION_FILE (wxID_HIGHEST + 1)
#define ID_BTN_INSTALL (wxID_HIGHEST + 2)

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
EVT_BUTTON(ID_BTN_LOCATE_INSTALLATION_FILE, MainFrame::OnBtnLocateInstallationFile)
EVT_BUTTON(ID_BTN_INSTALL, MainFrame::OnBtnInstall)
EVT_SHOW(MainFrame::OnShow)
END_EVENT_TABLE()

MainFrame::MainFrame(wxWindow * parent,
                     wxWindowID id,
                     const wxString & title,
                     const wxPoint & pos,
                     const wxSize & size,
                     long style,
                     const wxString & name) :
    wxFrame(parent, id, title, pos, size, style, name)
{
    SetBackgroundColour(*wxWHITE);

    wxBoxSizer * sizer_1 = new wxBoxSizer(wxVERTICAL);
    {
        wxBoxSizer * sizer_2 = new wxBoxSizer(wxHORIZONTAL);
        {
            sizer_2->Add(new wxStaticText(this, wxID_ANY, L"Installation File"), 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);

            _ptcInstallationFilePath = new wxTextCtrl(this, wxID_ANY);
            sizer_2->Add(_ptcInstallationFilePath, 1, wxALIGN_CENTER_VERTICAL);

            sizer_2->Add(new wxButton(this, ID_BTN_LOCATE_INSTALLATION_FILE, wxT("&Open")),
                         0,
                         wxLEFT | wxALIGN_CENTER_VERTICAL, 5);

            sizer_2->Add(new wxButton(this, ID_BTN_INSTALL, wxT("&Install")),
                         0,
                         wxLEFT | wxRIGHT | wxALIGN_CENTER_VERTICAL, 5);
        }
        sizer_1->Add(sizer_2, 0, wxEXPAND);

        _plvInstallInfo = new InstallInfoListView(this, wxID_ANY);
        sizer_1->Add(_plvInstallInfo, 1, wxEXPAND | wxALL, 5);
    }
    SetSizer(sizer_1);
}

void MainFrame::OnBtnLocateInstallationFile(wxCommandEvent & event)
{
    wxFileDialog dlg(this,
                     wxT("Open Installation File"),
                     wxEmptyString,
                     wxEmptyString,
                     "Installation Files (*.json)|*.json", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (dlg.ShowModal() == wxID_OK)
    {
        _ptcInstallationFilePath->SetValue(dlg.GetPath());
    }
}

void MainFrame::OnBtnInstall(wxCommandEvent & event)
{
    try
    {
        _installer.Install("C:\\Users\\disc\\Dev\\Tool\\RegexInstaller\\RegexInstaller\\Sample\\InstallFile.json");
        wxMessageBox("Install Completed");
    }
    catch (std::exception & ex)
    {
        wxMessageBox(ex.what());
    }
    
    return;
}

void MainFrame::OnShow(wxShowEvent & event)
{
    event.Skip();

    if (event.IsShown())
    {
        try
        {
            _installer.LoadConfig("Config/InstallerConfig.json", "Windows");
        }
        catch (std::exception & ex)
        {
            wxMessageBox(ex.what());
        }
    }
}