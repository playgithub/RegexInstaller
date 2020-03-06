#pragma once

class InstallInfoListView : public wxListView
{
public:
    InstallInfoListView(wxWindow * parent,
                        wxWindowID winid = wxID_ANY,
                        const wxPoint & pos = wxDefaultPosition,
                        const wxSize & size = wxDefaultSize,
                        long style = wxLC_REPORT,
                        const wxValidator & validator = wxDefaultValidator,
                        const wxString & name = wxListCtrlNameStr);
public:
    void Prepend(const wxString & info);
private:
};
