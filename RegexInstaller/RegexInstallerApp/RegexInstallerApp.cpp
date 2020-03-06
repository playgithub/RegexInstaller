#include "pch.h"
#include <UI/MainFrame.h>
#include "RegexInstallerApp.h"

IMPLEMENT_APP(RegexInstallerApp)

bool RegexInstallerApp::OnInit()
{
    MainFrame * pMF = new MainFrame(nullptr, wxID_ANY, "Install Tool", wxDefaultPosition, wxSize(800, 600));

    pMF->Center();
    
    pMF->Show();

    return true;
}

int RegexInstallerApp::OnExit()
{
    return wxApp::OnExit();
}