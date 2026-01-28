/*
 * wxWidgets 菜单和工具栏示例（简化版）
 * 
 * 展示：
 * - 基本文件操作（新建、打开、保存）
 * - 基本格式设置（粗体、斜体、下划线）
 * 
 * 编译：g++ -o menus menus.cpp `wx-config --cxxflags --libs`
 */

#include <wx/wx.h>
#include <wx/artprov.h>

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
    wxTextCtrl* m_textCtrl;
    enum 
    {
        ID_NEW = wxID_HIGHEST + 1,
        ID_BOLD,
        ID_ITALIC,
        ID_UNDERLINE
    };
    
    void OnNew(wxCommandEvent& event);
    void OnOpen(wxCommandEvent& event);
    void OnSave(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    
    void OnBold(wxCommandEvent& event);
    void OnItalic(wxCommandEvent& event);
    void OnUnderline(wxCommandEvent& event);
    
    void OnAbout(wxCommandEvent& event);
};

bool MyApp::OnInit() {
    MyFrame* frame = new MyFrame();
    frame->Show(true);
    return true;
}

MyFrame::MyFrame()
    : wxFrame(NULL, wxID_ANY, "Simple Text Editor", wxDefaultPosition, wxSize(700, 500)) {
    
    // ==================== 创建菜单栏 ====================
    
    // 文件菜单
    wxMenu* menuFile = new wxMenu;
    menuFile->Append(ID_NEW, "&New\tCtrl-N", "Create new document");
    menuFile->Append(wxID_OPEN, "&Open\tCtrl-O", "Open file");
    menuFile->Append(wxID_SAVE, "&Save\tCtrl-S", "Save file");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT, "E&xit\tAlt-F4", "Quit program");
    
    // 格式菜单
    wxMenu* menuFormat = new wxMenu;
    menuFormat->AppendCheckItem(ID_BOLD, "&Bold\tCtrl-B", "Set bold");
    menuFormat->AppendCheckItem(ID_ITALIC, "&Italic\tCtrl-I", "Set italic");
    menuFormat->AppendCheckItem(ID_UNDERLINE, "&Underline\tCtrl-U", "Set underline");
    
    // 帮助菜单
    wxMenu* menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT, "&About", "About this program");
    
    // 创建菜单栏
    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuFormat, "F&ormat");
    menuBar->Append(menuHelp, "&Help");
    
    SetMenuBar(menuBar);
    
    // ==================== 创建工具栏 ====================
    wxToolBar* toolBar = CreateToolBar();
    
    toolBar->AddTool(ID_NEW, "New",
                    wxArtProvider::GetBitmap(wxART_NEW, wxART_TOOLBAR),
                    "Create new document");
    
    toolBar->AddTool(wxID_OPEN, "Open",
                    wxArtProvider::GetBitmap(wxART_FILE_OPEN, wxART_TOOLBAR),
                    "Open file");
    
    toolBar->AddTool(wxID_SAVE, "Save",
                    wxArtProvider::GetBitmap(wxART_FILE_SAVE, wxART_TOOLBAR),
                    "Save file");
    
    toolBar->Realize();
    
    // ==================== 创建状态栏 ====================
    CreateStatusBar();
    SetStatusText("Ready");
    
    // ==================== 创建文本编辑器 ====================
    m_textCtrl = new wxTextCtrl(this, wxID_ANY, "",
                               wxDefaultPosition, wxDefaultSize,
                               wxTE_MULTILINE | wxTE_RICH2);
    
    m_textCtrl->SetValue("Welcome to the simple text editor!\n\n"
                        "File operations:\n"
                        "- New (Ctrl-N)\n"
                        "- Open (Ctrl-O)\n"
                        "- Save (Ctrl-S)\n\n"
                        "Format settings:\n"
                        "- Bold (Ctrl-B)\n"
                        "- Italic (Ctrl-I)\n"
                        "- Underline (Ctrl-U)");
    
    // ==================== 绑定事件 ====================
    Bind(wxEVT_MENU, &MyFrame::OnNew, this, ID_NEW);
    Bind(wxEVT_MENU, &MyFrame::OnOpen, this, wxID_OPEN);
    Bind(wxEVT_MENU, &MyFrame::OnSave, this, wxID_SAVE);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
    
    Bind(wxEVT_MENU, &MyFrame::OnBold, this, ID_BOLD);
    Bind(wxEVT_MENU, &MyFrame::OnItalic, this, ID_ITALIC);
    Bind(wxEVT_MENU, &MyFrame::OnUnderline, this, ID_UNDERLINE);
    
    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
    
    Centre();
}

void MyFrame::OnNew(wxCommandEvent& event) {
    if (wxMessageBox("Current content will be cleared. Continue?", "Confirm",
                    wxYES_NO | wxICON_QUESTION) == wxYES) {
        m_textCtrl->Clear();
        SetStatusText("New document");
    }
}

void MyFrame::OnOpen(wxCommandEvent& event) {
    wxFileDialog openFileDialog(this, "Open File", "", "",
                               "Text files (*.txt)|*.txt|All files (*.*)|*.*",
                               wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    
    if (openFileDialog.ShowModal() == wxID_CANCEL) {
        return;
    }
    
    wxString filename = openFileDialog.GetPath();
    m_textCtrl->LoadFile(filename);
    SetStatusText("Opened: " + filename);
}

void MyFrame::OnSave(wxCommandEvent& event) {
    wxFileDialog saveFileDialog(this, "Save File", "", "",
                               "Text files (*.txt)|*.txt",
                               wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    
    if (saveFileDialog.ShowModal() == wxID_CANCEL) {
        return;
    }
    
    wxString filename = saveFileDialog.GetPath();
    m_textCtrl->SaveFile(filename);
    SetStatusText("Saved: " + filename);
}

void MyFrame::OnExit(wxCommandEvent& event) {
    Close(true);
}

void MyFrame::OnBold(wxCommandEvent& event) {
    wxTextAttr attr;
    attr.SetFontWeight(event.IsChecked() ? wxFONTWEIGHT_BOLD : wxFONTWEIGHT_NORMAL);
    
    long from, to;
    m_textCtrl->GetSelection(&from, &to);
    m_textCtrl->SetStyle(from, to, attr);
    
    SetStatusText(event.IsChecked() ? "Bold set" : "Bold cleared");
}

void MyFrame::OnItalic(wxCommandEvent& event) {
    wxTextAttr attr;
    attr.SetFontStyle(event.IsChecked() ? wxFONTSTYLE_ITALIC : wxFONTSTYLE_NORMAL);
    
    long from, to;
    m_textCtrl->GetSelection(&from, &to);
    m_textCtrl->SetStyle(from, to, attr);
    
    SetStatusText(event.IsChecked() ? "Italic set" : "Italic cleared");
}

void MyFrame::OnUnderline(wxCommandEvent& event) {
    wxTextAttr attr;
    attr.SetFontUnderlined(event.IsChecked());
    
    long from, to;
    m_textCtrl->GetSelection(&from, &to);
    m_textCtrl->SetStyle(from, to, attr);
    
    SetStatusText(event.IsChecked() ? "Underline set" : "Underline cleared");
}

void MyFrame::OnAbout(wxCommandEvent& event) {
    wxMessageBox("Simple Text Editor\n\n"
                "A basic text editor with file operations and text formatting.",
                "About",
                wxOK | wxICON_INFORMATION);
}

wxIMPLEMENT_APP(MyApp);
