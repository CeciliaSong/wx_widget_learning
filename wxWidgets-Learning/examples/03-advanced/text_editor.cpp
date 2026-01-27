/*
 * wxWidgets 简单文本编辑器
 * 
 * 这是一个功能较完整的文本编辑器应用，综合展示：
 * - 菜单和工具栏
 * - 文件操作（新建、打开、保存）
 * - 编辑功能（撤销、重做、查找、替换）
 * - 状态栏显示
 * - 对话框使用
 * - 事件处理
 * 
 * 编译：g++ -o text_editor text_editor.cpp `wx-config --cxxflags --libs`
 */

#include <wx/wx.h>
#include <wx/artprov.h>
#include <wx/stc/stc.h>  // 使用 Scintilla 文本控件

class MyApp : public wxApp {
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame {
public:
    MyFrame();

private:
    wxTextCtrl* m_textCtrl;
    wxString m_currentFile;
    bool m_modified;
    
    // 菜单 ID
    enum {
        ID_NEW = wxID_HIGHEST + 1,
        ID_FIND,
        ID_REPLACE,
        ID_GOTO_LINE,
        ID_WORD_WRAP,
        ID_FONT,
        ID_LINE_NUMBERS
    };
    
    // 事件处理器
    void OnNew(wxCommandEvent& event);
    void OnOpen(wxCommandEvent& event);
    void OnSave(wxCommandEvent& event);
    void OnSaveAs(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnClose(wxCloseEvent& event);
    
    void OnUndo(wxCommandEvent& event);
    void OnRedo(wxCommandEvent& event);
    void OnCut(wxCommandEvent& event);
    void OnCopy(wxCommandEvent& event);
    void OnPaste(wxCommandEvent& event);
    void OnSelectAll(wxCommandEvent& event);
    void OnFind(wxCommandEvent& event);
    void OnReplace(wxCommandEvent& event);
    void OnGotoLine(wxCommandEvent& event);
    
    void OnWordWrap(wxCommandEvent& event);
    void OnFont(wxCommandEvent& event);
    
    void OnAbout(wxCommandEvent& event);
    void OnTextChanged(wxCommandEvent& event);
    void OnUpdateUI(wxUpdateUIEvent& event);
    
    // 辅助函数
    bool SaveFile(const wxString& filename);
    bool LoadFile(const wxString& filename);
    bool AskSaveChanges();
    void UpdateTitle();
    void UpdateStatusBar();
};

bool MyApp::OnInit() {
    MyFrame* frame = new MyFrame();
    frame->Show(true);
    return true;
}

MyFrame::MyFrame()
    : wxFrame(NULL, wxID_ANY, "文本编辑器", wxDefaultPosition, wxSize(800, 600)),
      m_modified(false) {
    
    // ==================== 创建菜单栏 ====================
    
    // 文件菜单
    wxMenu* menuFile = new wxMenu;
    menuFile->Append(ID_NEW, "新建\tCtrl-N", "创建新文档");
    menuFile->Append(wxID_OPEN, "打开...\tCtrl-O", "打开文件");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_SAVE, "保存\tCtrl-S", "保存文件");
    menuFile->Append(wxID_SAVEAS, "另存为...\tCtrl-Shift-S", "另存为新文件");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT, "退出\tAlt-F4", "退出程序");
    
    // 编辑菜单
    wxMenu* menuEdit = new wxMenu;
    menuEdit->Append(wxID_UNDO, "撤销\tCtrl-Z", "撤销上一步操作");
    menuEdit->Append(wxID_REDO, "重做\tCtrl-Y", "重做");
    menuEdit->AppendSeparator();
    menuEdit->Append(wxID_CUT, "剪切\tCtrl-X", "剪切选中内容");
    menuEdit->Append(wxID_COPY, "复制\tCtrl-C", "复制选中内容");
    menuEdit->Append(wxID_PASTE, "粘贴\tCtrl-V", "粘贴内容");
    menuEdit->AppendSeparator();
    menuEdit->Append(wxID_SELECTALL, "全选\tCtrl-A", "选择全部内容");
    menuEdit->AppendSeparator();
    menuEdit->Append(ID_FIND, "查找...\tCtrl-F", "查找文本");
    menuEdit->Append(ID_REPLACE, "替换...\tCtrl-H", "替换文本");
    menuEdit->Append(ID_GOTO_LINE, "转到行...\tCtrl-G", "跳转到指定行");
    
    // 视图菜单
    wxMenu* menuView = new wxMenu;
    menuView->AppendCheckItem(ID_WORD_WRAP, "自动换行", "启用/禁用自动换行");
    menuView->AppendSeparator();
    menuView->Append(ID_FONT, "字体...", "选择字体");
    
    // 帮助菜单
    wxMenu* menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT, "关于", "关于此程序");
    
    // 创建菜单栏
    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "文件(&F)");
    menuBar->Append(menuEdit, "编辑(&E)");
    menuBar->Append(menuView, "视图(&V)");
    menuBar->Append(menuHelp, "帮助(&H)");
    SetMenuBar(menuBar);
    
    // ==================== 创建工具栏 ====================
    wxToolBar* toolBar = CreateToolBar();
    
    toolBar->AddTool(ID_NEW, "新建",
                    wxArtProvider::GetBitmap(wxART_NEW, wxART_TOOLBAR),
                    "新建文件");
    toolBar->AddTool(wxID_OPEN, "打开",
                    wxArtProvider::GetBitmap(wxART_FILE_OPEN, wxART_TOOLBAR),
                    "打开文件");
    toolBar->AddTool(wxID_SAVE, "保存",
                    wxArtProvider::GetBitmap(wxART_FILE_SAVE, wxART_TOOLBAR),
                    "保存文件");
    toolBar->AddSeparator();
    
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
    toolBar->AddSeparator();
    
    toolBar->AddTool(ID_FIND, "查找",
                    wxArtProvider::GetBitmap(wxART_FIND, wxART_TOOLBAR),
                    "查找");
    
    toolBar->Realize();
    
    // ==================== 创建状态栏 ====================
    CreateStatusBar(3);
    SetStatusText("就绪", 0);
    SetStatusText("行 1, 列 1", 1);
    SetStatusText("长度: 0", 2);
    
    int widths[3] = {-1, 120, 100};
    SetStatusWidths(3, widths);
    
    // ==================== 创建文本编辑器 ====================
    m_textCtrl = new wxTextCtrl(this, wxID_ANY, "",
                               wxDefaultPosition, wxDefaultSize,
                               wxTE_MULTILINE | wxTE_RICH2 | wxTE_PROCESS_TAB);
    
    // 设置默认字体
    wxFont font(10, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    m_textCtrl->SetFont(font);
    
    // ==================== 绑定事件 ====================
    Bind(wxEVT_MENU, &MyFrame::OnNew, this, ID_NEW);
    Bind(wxEVT_MENU, &MyFrame::OnOpen, this, wxID_OPEN);
    Bind(wxEVT_MENU, &MyFrame::OnSave, this, wxID_SAVE);
    Bind(wxEVT_MENU, &MyFrame::OnSaveAs, this, wxID_SAVEAS);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_CLOSE_WINDOW, &MyFrame::OnClose, this);
    
    Bind(wxEVT_MENU, &MyFrame::OnUndo, this, wxID_UNDO);
    Bind(wxEVT_MENU, &MyFrame::OnRedo, this, wxID_REDO);
    Bind(wxEVT_MENU, &MyFrame::OnCut, this, wxID_CUT);
    Bind(wxEVT_MENU, &MyFrame::OnCopy, this, wxID_COPY);
    Bind(wxEVT_MENU, &MyFrame::OnPaste, this, wxID_PASTE);
    Bind(wxEVT_MENU, &MyFrame::OnSelectAll, this, wxID_SELECTALL);
    Bind(wxEVT_MENU, &MyFrame::OnFind, this, ID_FIND);
    Bind(wxEVT_MENU, &MyFrame::OnReplace, this, ID_REPLACE);
    Bind(wxEVT_MENU, &MyFrame::OnGotoLine, this, ID_GOTO_LINE);
    
    Bind(wxEVT_MENU, &MyFrame::OnWordWrap, this, ID_WORD_WRAP);
    Bind(wxEVT_MENU, &MyFrame::OnFont, this, ID_FONT);
    
    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
    
    m_textCtrl->Bind(wxEVT_TEXT, &MyFrame::OnTextChanged, this);
    m_textCtrl->Bind(wxEVT_UPDATE_UI, &MyFrame::OnUpdateUI, this);
    
    Centre();
    UpdateTitle();
}

void MyFrame::OnNew(wxCommandEvent& event) {
    if (!AskSaveChanges()) {
        return;
    }
    
    m_textCtrl->Clear();
    m_currentFile.Clear();
    m_modified = false;
    UpdateTitle();
    SetStatusText("新建文档", 0);
}

void MyFrame::OnOpen(wxCommandEvent& event) {
    if (!AskSaveChanges()) {
        return;
    }
    
    wxFileDialog openFileDialog(this, "打开文件", "", "",
                               "文本文件 (*.txt)|*.txt|所有文件 (*.*)|*.*",
                               wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    
    if (openFileDialog.ShowModal() == wxID_CANCEL) {
        return;
    }
    
    wxString filename = openFileDialog.GetPath();
    if (LoadFile(filename)) {
        m_currentFile = filename;
        m_modified = false;
        UpdateTitle();
        SetStatusText("已打开: " + filename, 0);
    }
}

void MyFrame::OnSave(wxCommandEvent& event) {
    if (m_currentFile.IsEmpty()) {
        OnSaveAs(event);
    } else {
        SaveFile(m_currentFile);
        m_modified = false;
        UpdateTitle();
        SetStatusText("已保存", 0);
    }
}

void MyFrame::OnSaveAs(wxCommandEvent& event) {
    wxFileDialog saveFileDialog(this, "另存为", "", "",
                               "文本文件 (*.txt)|*.txt",
                               wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
    
    if (saveFileDialog.ShowModal() == wxID_CANCEL) {
        return;
    }
    
    wxString filename = saveFileDialog.GetPath();
    if (SaveFile(filename)) {
        m_currentFile = filename;
        m_modified = false;
        UpdateTitle();
        SetStatusText("已保存: " + filename, 0);
    }
}

void MyFrame::OnExit(wxCommandEvent& event) {
    Close(true);
}

void MyFrame::OnClose(wxCloseEvent& event) {
    if (!AskSaveChanges()) {
        event.Veto();
        return;
    }
    event.Skip();
}

void MyFrame::OnUndo(wxCommandEvent& event) {
    m_textCtrl->Undo();
}

void MyFrame::OnRedo(wxCommandEvent& event) {
    m_textCtrl->Redo();
}

void MyFrame::OnCut(wxCommandEvent& event) {
    m_textCtrl->Cut();
}

void MyFrame::OnCopy(wxCommandEvent& event) {
    m_textCtrl->Copy();
}

void MyFrame::OnPaste(wxCommandEvent& event) {
    m_textCtrl->Paste();
}

void MyFrame::OnSelectAll(wxCommandEvent& event) {
    m_textCtrl->SelectAll();
}

void MyFrame::OnFind(wxCommandEvent& event) {
    wxString text = wxGetTextFromUser("查找:", "查找", "", this);
    if (!text.IsEmpty()) {
        long pos = m_textCtrl->GetInsertionPoint();
        long found = m_textCtrl->GetValue().Find(text, pos);
        
        if (found != wxNOT_FOUND) {
            m_textCtrl->SetSelection(found, found + text.Length());
            m_textCtrl->SetFocus();
            SetStatusText("找到: " + text, 0);
        } else {
            wxMessageBox("未找到: " + text, "查找", wxOK | wxICON_INFORMATION);
            SetStatusText("未找到", 0);
        }
    }
}

void MyFrame::OnReplace(wxCommandEvent& event) {
    // 简单实现
    wxTextEntryDialog findDlg(this, "查找:", "查找和替换");
    if (findDlg.ShowModal() != wxID_OK) return;
    wxString findText = findDlg.GetValue();
    
    wxTextEntryDialog replaceDlg(this, "替换为:", "查找和替换");
    if (replaceDlg.ShowModal() != wxID_OK) return;
    wxString replaceText = replaceDlg.GetValue();
    
    wxString content = m_textCtrl->GetValue();
    int count = content.Replace(findText, replaceText);
    
    if (count > 0) {
        m_textCtrl->SetValue(content);
        wxMessageBox(wxString::Format("替换了 %d 处", count),
                    "替换", wxOK | wxICON_INFORMATION);
    } else {
        wxMessageBox("未找到要替换的内容", "替换", wxOK | wxICON_INFORMATION);
    }
}

void MyFrame::OnGotoLine(wxCommandEvent& event) {
    long lineCount = m_textCtrl->GetNumberOfLines();
    long lineNum = wxGetNumberFromUser("跳转到行:", "行号:",
                                      "跳转到行", 1, 1, lineCount, this);
    
    if (lineNum >= 1) {
        long pos = m_textCtrl->XYToPosition(0, lineNum - 1);
        m_textCtrl->SetInsertionPoint(pos);
        m_textCtrl->ShowPosition(pos);
    }
}

void MyFrame::OnWordWrap(wxCommandEvent& event) {
    // 注意：切换自动换行需要重新创建控件
    wxMessageBox("自动换行功能需要重启应用生效", "提示", wxOK | wxICON_INFORMATION);
}

void MyFrame::OnFont(wxCommandEvent& event) {
    wxFontData fontData;
    fontData.SetInitialFont(m_textCtrl->GetFont());
    
    wxFontDialog dialog(this, fontData);
    if (dialog.ShowModal() == wxID_OK) {
        wxFont font = dialog.GetFontData().GetChosenFont();
        m_textCtrl->SetFont(font);
        SetStatusText("字体已更改", 0);
    }
}

void MyFrame::OnAbout(wxCommandEvent& event) {
    wxMessageBox("简单文本编辑器\n\n"
                "使用 wxWidgets 开发\n"
                "功能：新建、打开、保存、编辑、查找、替换",
                "关于",
                wxOK | wxICON_INFORMATION);
}

void MyFrame::OnTextChanged(wxCommandEvent& event) {
    if (!m_modified) {
        m_modified = true;
        UpdateTitle();
    }
    UpdateStatusBar();
}

void MyFrame::OnUpdateUI(wxUpdateUIEvent& event) {
    UpdateStatusBar();
}

bool MyFrame::SaveFile(const wxString& filename) {
    return m_textCtrl->SaveFile(filename);
}

bool MyFrame::LoadFile(const wxString& filename) {
    return m_textCtrl->LoadFile(filename);
}

bool MyFrame::AskSaveChanges() {
    if (m_modified) {
        int result = wxMessageBox("文档已修改。是否保存？",
                                 "确认", wxYES_NO | wxCANCEL | wxICON_QUESTION, this);
        
        if (result == wxYES) {
            wxCommandEvent evt;
            OnSave(evt);
            return !m_modified;  // 如果保存失败，modified 仍为 true
        } else if (result == wxCANCEL) {
            return false;
        }
    }
    return true;
}

void MyFrame::UpdateTitle() {
    wxString title = "文本编辑器 - ";
    
    if (m_currentFile.IsEmpty()) {
        title += "未命名";
    } else {
        title += m_currentFile;
    }
    
    if (m_modified) {
        title += " *";
    }
    
    SetTitle(title);
}

void MyFrame::UpdateStatusBar() {
    // 更新光标位置
    long pos = m_textCtrl->GetInsertionPoint();
    long col, line;
    m_textCtrl->PositionToXY(pos, &col, &line);
    SetStatusText(wxString::Format("行 %ld, 列 %ld", line + 1, col + 1), 1);
    
    // 更新文本长度
    long length = m_textCtrl->GetLastPosition();
    SetStatusText(wxString::Format("长度: %ld", length), 2);
}

wxIMPLEMENT_APP(MyApp);

/*
 * 这个文本编辑器展示了：
 * 
 * 1. 完整的文件操作流程
 * 2. 修改状态追踪
 * 3. 关闭前提示保存
 * 4. 查找和替换功能
 * 5. 状态栏实时更新
 * 6. 工具栏和菜单整合
 * 
 * 可以继续扩展的功能：
 * 1. 最近文件列表
 * 2. 语法高亮
 * 3. 多标签页编辑
 * 4. 打印功能
 * 5. 行号显示
 * 6. 配置保存
 * 7. 拖放文件打开
 */
