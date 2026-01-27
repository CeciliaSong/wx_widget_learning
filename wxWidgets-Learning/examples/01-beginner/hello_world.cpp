#include <wx/wx.h>

class MyApp : public wxApp 
{
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame 
{
public:
    MyFrame();

private:
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
};


bool MyApp::OnInit() 
{
    MyFrame* frame = new MyFrame();
    frame->Show(true);
    return true;
}

enum 
{
    ID_HELLO = 1
};

MyFrame::MyFrame()
    : wxFrame(NULL, wxID_ANY, "Hello World - wxWidgets First Program") 
    {
    
    SetSize(wxSize(450, 350));
    Centre();
    
    wxMenu* menuFile = new wxMenu;
    menuFile->Append(ID_HELLO, "&Hello...\tCtrl-H",
                    "Show greeting message");
    menuFile->AppendSeparator();  
    menuFile->Append(wxID_EXIT, "E&xit\tAlt-F4",
                    "Quit this application");
    
    wxMenu* menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT, "&About\tF1",
                    "About this program");
    
    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
    
    SetMenuBar(menuBar);
    
    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");
    

    Bind(wxEVT_MENU, &MyFrame::OnHello, this, ID_HELLO);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
}

void MyFrame::OnHello(wxCommandEvent& event) 
{
    wxMessageBox("This is a wxWidgets Hello World example!\n\n"
                "Congratulations on running your first wxWidgets program.",
                "Hello",
                wxOK | wxICON_INFORMATION);
}

void MyFrame::OnExit(wxCommandEvent& event) 
{
    
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& event) 
{
    wxString message = wxString::Format
    (
        "This is a program written with wxWidgets cross-platform GUI framework.\n\n"
        "wxWidgets version: %s\n"
        "Platform: %s",
        wxVERSION_STRING,
        wxPlatformInfo::Get().GetOperatingSystemIdName()
    );
    
    wxMessageBox(message, "About Hello World", wxOK | wxICON_INFORMATION);
}

wxIMPLEMENT_APP(MyApp);
