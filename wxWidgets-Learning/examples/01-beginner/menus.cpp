/*
 * wxWidgets 菜单和工具栏示例
 * 
 * 展示：
 * - 菜单栏（MenuBar）
 * - 工具栏（ToolBar）
 * - 状态栏（StatusBar）
 * - 快捷键
 * - 图标
 * 
 * 编译：g++ -o menus menus.cpp `wx-config --cxxflags --libs`
 */

#include <wx/wx.h>
#include <wx/artprov.h>  // 提供标准图标

class MyApp : public wxApp {
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame {
public:
    MyFrame();

private:
    // 控件
    wxTextCtrl* m_textCtrl;
    
    // 菜单项 ID
    enum {
        ID_NEW = wxID_HIGHEST + 1,
        ID_BOLD,
        ID_ITALIC,
        ID_UNDERLINE
    };
    
    // 事件处理器
    void OnNew(wxCommandEvent& event);
    void OnOpen(wxCommandEvent& event);
    void OnSave(wxCommandEvent& event);
    void OnSaveAs(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    
    void OnCut(wxCommandEvent& event);
    void OnCopy(wxCommandEvent& event);
    void OnPaste(wxCommandEvent& event);
    
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
    : wxFrame(NULL, wxID_ANY, "菜单和工具栏示例", wxDefaultPosition, wxSize(700, 500)) {
    
    // ==================== 创建菜单栏 ====================
    
    // 文件菜单
    wxMenu* menuFile = new wxMenu;
    menuFile->Append(ID_NEW, "新建(&N)\tCtrl-N", "创建新文档");
    menuFile->Append(wxID_OPEN, "打开(&O)\tCtrl-O", "打开文件");
    menuFile->Append(wxID_SAVE, "保存(&S)\tCtrl-S", "保存文件");
    menuFile->Append(ID_SAVE_AS, "另存为(&A)\tCtrl-Shift-S", "另存为");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT, "退出(&X)\tAlt-F4", "退出程序");
    
    // 编辑菜单
    wxMenu* menuEdit = new wxMenu;
    menuEdit->Append(wxID_UNDO, "撤销(&U)\tCtrl-Z", "撤销操作");
    menuEdit->Append(wxID_REDO, "重做(&R)\tCtrl-Y", "重做操作");
    menuEdit->AppendSeparator();
    menuEdit->Append(wxID_CUT, "剪切(&T)\tCtrl-X", "剪切选中内容");
    menuEdit->Append(wxID_COPY, "复制(&C)\tCtrl-C", "复制选中内容");
    menuEdit->Append(wxID_PASTE, "粘贴(&P)\tCtrl-V", "粘贴内容");
    menuEdit->AppendSeparator();
    menuEdit->Append(wxID_SELECTALL, "全选(&A)\tCtrl-A", "选择全部内容");
    
    // 格式菜单（带复选框）
    wxMenu* menuFormat = new wxMenu;
    menuFormat->AppendCheckItem(ID_BOLD, "粗体(&B)\tCtrl-B", "设置粗体");
    menuFormat->AppendCheckItem(ID_ITALIC, "斜体(&I)\tCtrl-I", "设置斜体");
    menuFormat->AppendCheckItem(ID_UNDERLINE, "下划线(&U)\tCtrl-U", "设置下划线");
    
    // 视图菜单（带单选项）
    wxMenu* menuView = new wxMenu;
    menuView->AppendRadioItem(wxID_ANY, "普通视图\tF5", "普通视图模式");
    menuView->AppendRadioItem(wxID_ANY, "紧凑视图\tF6", "紧凑视图模式");
    menuView->AppendRadioItem(wxID_ANY, "全屏视图\tF11", "全屏视图模式");
    menuView->Check(menuView->GetMenuItems()[0]->GetId(), true);  // 默认选中第一项
    
    // 帮助菜单
    wxMenu* menuHelp = new wxMenu;
    menuHelp->Append(wxID_HELP, "帮助主题\tF1", "查看帮助");
    menuHelp->AppendSeparator();
    menuHelp->Append(wxID_ABOUT, "关于(&A)", "关于此程序");
    
    // 创建菜单栏
    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "文件(&F)");
    menuBar->Append(menuEdit, "编辑(&E)");
    menuBar->Append(menuFormat, "格式(&O)");
    menuBar->Append(menuView, "视图(&V)");
    menuBar->Append(menuHelp, "帮助(&H)");
    
    SetMenuBar(menuBar);
    
    // ==================== 创建工具栏 ====================
    wxToolBar* toolBar = CreateToolBar();
    
    // 使用系统提供的标准图标
    toolBar->AddTool(ID_NEW, "新建",
                    wxArtProvider::GetBitmap(wxART_NEW, wxART_TOOLBAR),
                    "创建新文档");
    
    toolBar->AddTool(wxID_OPEN, "打开",
                    wxArtProvider::GetBitmap(wxART_FILE_OPEN, wxART_TOOLBAR),
                    "打开文件");
    
    toolBar->AddTool(wxID_SAVE, "保存",
                    wxArtProvider::GetBitmap(wxART_FILE_SAVE, wxART_TOOLBAR),
                    "保存文件");
    
    toolBar->AddSeparator();  // 分隔线
    
    toolBar->AddTool(wxID_CUT, "剪切",
                    wxArtProvider::GetBitmap(wxART_CUT, wxART_TOOLBAR),
                    "剪切");
    
    toolBar->AddTool(wxID_COPY, "复制",
                    wxArtProvider::GetBitmap(wxART_COPY, wxART_TOOLBAR),
                    "复制");
    
    toolBar->AddTool(wxID_PASTE, "粘贴",
                    wxArtProvider::GetBitmap(wxART_PASTE, wxART_TOOLBAR),
                    "粘贴");
    
    toolBar->AddSeparator();
    
    toolBar->AddTool(wxID_UNDO, "撤销",
                    wxArtProvider::GetBitmap(wxART_UNDO, wxART_TOOLBAR),
                    "撤销");
    
    toolBar->AddTool(wxID_REDO, "重做",
                    wxArtProvider::GetBitmap(wxART_REDO, wxART_TOOLBAR),
                    "重做");
    
    // 实现工具栏
    toolBar->Realize();
    
    // ==================== 创建状态栏 ====================
    CreateStatusBar(2);  // 2 个字段
    SetStatusText("就绪", 0);
    SetStatusText("行 1, 列 1", 1);
    
    // 设置状态栏字段宽度（-1 表示自动拉伸）
    int widths[2] = {-1, 100};
    SetStatusWidths(2, widths);
    
    // ==================== 创建文本编辑器 ====================
    m_textCtrl = new wxTextCtrl(this, wxID_ANY, "",
                               wxDefaultPosition, wxDefaultSize,
                               wxTE_MULTILINE | wxTE_RICH2);
    
    // 设置初始文本
    m_textCtrl->SetValue("欢迎使用文本编辑器！\n\n"
                        "尝试使用菜单和工具栏的各种功能：\n"
                        "- 文件操作（新建、打开、保存）\n"
                        "- 编辑操作（剪切、复制、粘贴）\n"
                        "- 格式设置（粗体、斜体、下划线）\n\n"
                        "快捷键也可以使用，例如 Ctrl-C 复制。");
    
    // ==================== 绑定事件 ====================
    Bind(wxEVT_MENU, &MyFrame::OnNew, this, ID_NEW);
    Bind(wxEVT_MENU, &MyFrame::OnOpen, this, wxID_OPEN);
    Bind(wxEVT_MENU, &MyFrame::OnSave, this, wxID_SAVE);
    Bind(wxEVT_MENU, &MyFrame::OnSaveAs, this, ID_SAVE_AS);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
    
    Bind(wxEVT_MENU, &MyFrame::OnCut, this, wxID_CUT);
    Bind(wxEVT_MENU, &MyFrame::OnCopy, this, wxID_COPY);
    Bind(wxEVT_MENU, &MyFrame::OnPaste, this, wxID_PASTE);
    
    Bind(wxEVT_MENU, &MyFrame::OnBold, this, ID_BOLD);
    Bind(wxEVT_MENU, &MyFrame::OnItalic, this, ID_ITALIC);
    Bind(wxEVT_MENU, &MyFrame::OnUnderline, this, ID_UNDERLINE);
    
    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
    
    Centre();
}

void MyFrame::OnNew(wxCommandEvent& event) {
    if (wxMessageBox("当前内容将被清空。继续吗？", "确认",
                    wxYES_NO | wxICON_QUESTION) == wxYES) {
        m_textCtrl->Clear();
        SetStatusText("新建文档", 0);
    }
}

void MyFrame::OnOpen(wxCommandEvent& event) {
    wxFileDialog openFileDialog(this, "打开文件", "", "",
                               "文本文件 (*.txt)|*.txt|所有文件 (*.*)|*.*",
                               wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    
    if (openFileDialog.ShowModal() == wxID_CANCEL) {
        return;
    }
    
    wxString filename = openFileDialog.GetPath();
    m_textCtrl->LoadFile(filename);
    SetStatusText("已打开: " + filename, 0);
}

void MyFrame::OnSave(wxCommandEvent& event) {
    SetStatusText("文件已保存（模拟）", 0);
    wxMessageBox("保存功能（本示例仅模拟）", "信息", wxOK | wxICON_INFORMATION);
}

void MyFrame::OnSaveAs(wxCommandEvent& event) {
    wxFileDialog saveFileDialog(this, "另存为", "", "",
                               "文本文件 (*.txt)|*.txt",
                               wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    
    if (saveFileDialog.ShowModal() == wxID_CANCEL) {
        return;
    }
    
    wxString filename = saveFileDialog.GetPath();
    m_textCtrl->SaveFile(filename);
    SetStatusText("已保存: " + filename, 0);
}

void MyFrame::OnExit(wxCommandEvent& event) {
    Close(true);
}

void MyFrame::OnCut(wxCommandEvent& event) {
    m_textCtrl->Cut();
    SetStatusText("已剪切", 0);
}

void MyFrame::OnCopy(wxCommandEvent& event) {
    m_textCtrl->Copy();
    SetStatusText("已复制", 0);
}

void MyFrame::OnPaste(wxCommandEvent& event) {
    m_textCtrl->Paste();
    SetStatusText("已粘贴", 0);
}

void MyFrame::OnBold(wxCommandEvent& event) {
    wxTextAttr attr;
    attr.SetFontWeight(event.IsChecked() ? wxFONTWEIGHT_BOLD : wxFONTWEIGHT_NORMAL);
    
    long from, to;
    m_textCtrl->GetSelection(&from, &to);
    m_textCtrl->SetStyle(from, to, attr);
    
    SetStatusText(event.IsChecked() ? "已设置粗体" : "已取消粗体", 0);
}

void MyFrame::OnItalic(wxCommandEvent& event) {
    wxTextAttr attr;
    attr.SetFontStyle(event.IsChecked() ? wxFONTSTYLE_ITALIC : wxFONTSTYLE_NORMAL);
    
    long from, to;
    m_textCtrl->GetSelection(&from, &to);
    m_textCtrl->SetStyle(from, to, attr);
    
    SetStatusText(event.IsChecked() ? "已设置斜体" : "已取消斜体", 0);
}

void MyFrame::OnUnderline(wxCommandEvent& event) {
    wxTextAttr attr;
    attr.SetFontUnderlined(event.IsChecked());
    
    long from, to;
    m_textCtrl->GetSelection(&from, &to);
    m_textCtrl->SetStyle(from, to, attr);
    
    SetStatusText(event.IsChecked() ? "已设置下划线" : "已取消下划线", 0);
}

void MyFrame::OnAbout(wxCommandEvent& event) {
    wxMessageBox("菜单和工具栏示例程序\n\n"
                "演示了 wxWidgets 的菜单、工具栏和状态栏功能。",
                "关于",
                wxOK | wxICON_INFORMATION);
}

wxIMPLEMENT_APP(MyApp);

/*
 * 功能说明：
 * 
 * 1. 菜单类型
 *    - Append: 普通菜单项
 *    - AppendCheckItem: 复选菜单项
 *    - AppendRadioItem: 单选菜单项
 *    - AppendSeparator: 分隔线
 * 
 * 2. 快捷键
 *    - \t 后面是快捷键描述
 *    - 自动处理（不需要额外绑定）
 * 
 * 3. 工具栏
 *    - CreateToolBar() 创建
 *    - AddTool() 添加按钮
 *    - AddSeparator() 添加分隔线
 *    - Realize() 实现工具栏
 * 
 * 4. 状态栏
 *    - CreateStatusBar(n) 创建 n 个字段
 *    - SetStatusText(text, field) 设置文本
 *    - SetStatusWidths() 设置字段宽度
 * 
 * 5. wxArtProvider
 *    - 提供跨平台的标准图标
 *    - 常用：wxART_NEW, wxART_FILE_OPEN, wxART_SAVE 等
 * 
 * 练习：
 * 1. 添加更多菜单项和工具栏按钮
 * 2. 实现真正的文件保存功能
 * 3. 添加最近文件列表
 * 4. 实现搜索和替换功能
 * 5. 添加自定义图标
 */
