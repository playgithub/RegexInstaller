#include "pch.h"
#include "InstallInfoListView.h"

InstallInfoListView::InstallInfoListView(wxWindow * parent,
                                         wxWindowID winid,
                                         const wxPoint & pos,
                                         const wxSize & size,
                                         long style,
                                         const wxValidator & validator,
                                         const wxString & name) :
    wxListView(parent, winid, pos, size, style, validator, name)
{
    InsertColumn(0, wxT("Time"), 0, 200);
    InsertColumn(1, wxT("Info"), 0, 500);
}

void InstallInfoListView::Prepend(const wxString & info)
{
    wxString now = wxDateTime::Now().Format(wxT("%F %T"));
    long n = InsertItem(0, now);
    if (n >= 0)
    {
        SetItem(n, 1, info);
    }
    else
    {
        wxLogDebug(wxT("InsertItem failed"));
    }
}
