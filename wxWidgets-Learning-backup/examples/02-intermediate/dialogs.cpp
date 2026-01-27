/*
 * wxWidgets 对话框示例
 * 
 * 展示：
 * - 标准对话框（文件、颜色、字体、消息框）
 * - 自定义对话框
 * - 模态和非模态对话框
 * 
 * 编译：g++ -o dialogs dialogs.cpp `wx-config --cxxflags --libs`
 */

#include <wx/wx.h>
#include <wx/colordlg.h>
#include <wx/fontdlg.h>

// 自定义对话框
class CustomDialog : public wxDialog {
public:
    CustomDialog(wxWindow* parent);
    
    wxString GetName() const { return m_name; }
    wxString GetEmail() const { return m_email; }

private:
    wxTextCtrl* m_textName;
    wxTextCtrl* m_textEmail;
    wxString m_name;
    wxString m_email;
    
    void OnOK(wxCommandEvent& event);
};

class MyApp : public wxApp {
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame {
public:
    MyFrame();

private:
    wxTextCtrl* m_textCtrl;
    wxPanel* m_colorPanel;
    wxStaticText* m_fontLabel;
    
    // 事件处理器
    void OnMessageBox(wxCommandEvent& event);
    void OnFileOpen(wxCommandEvent& event);
    void OnFileSave(wxCommandEvent& event);
    void OnColorDialog(wxCommandEvent& event);
    void OnFontDialog(wxCommandEvent& event);
    void OnCustomDialog(wxCommandEvent& event);
    void OnProgressDialog(wxCommandEvent& event);
    void OnTextEntry(wxCommandEvent& event);
    
    enum {
        ID_MESSAGE_BOX = 1,
        ID_FILE_OPEN,
        ID_FILE_SAVE,
        ID_COLOR,
        ID_FONT,
        ID_CUSTOM,
        ID_PROGRESS,
        ID_TEXT_ENTRY
    };
};

// ==================== CustomDialog 实现 ====================

CustomDialog::CustomDialog(wxWindow* parent)
    : wxDialog(parent, wxID_ANY, "自定义对话框", wxDefaultPosition, wxSize(400, 200)) {
    
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    
    // 表单布局
    wxFlexGridSizer* formSizer = new wxFlexGridSizer(2, 10, 10);
    formSizer->AddGrowableCol(1, 1);
    
    // 姓名
    formSizer->Add(new wxStaticText(this, wxID_ANY, "姓名:"),
                  0, wxALIGN_CENTER_VERTICAL);
    m_textName = new wxTextCtrl(this, wxID_ANY);
    formSizer->Add(m_textName, 1, wxEXPAND);
    
    // 邮箱
    formSizer->Add(new wxStaticText(this, wxID_ANY, "邮箱:"),
                  0, wxALIGN_CENTER_VERTICAL);
    m_textEmail = new wxTextCtrl(this, wxID_ANY);
    formSizer->Add(m_textEmail, 1, wxEXPAND);
    
    mainSizer->Add(formSizer, 1, wxEXPAND | wxALL, 10);
    
    // 按钮
    wxSizer* buttonSizer = CreateButtonSizer(wxOK | wxCANCEL);
    mainSizer->Add(buttonSizer, 0, wxEXPAND | wxALL, 10);
    
    SetSizer(mainSizer);
    
    // 绑定确定按钮
    Bind(wxEVT_BUTTON, &CustomDialog::OnOK, this, wxID_OK);
    
    Centre();
}

void CustomDialog::OnOK(wxCommandEvent& event) {
    m_name = m_textName->GetValue();
    m_email = m_textEmail->GetValue();
    
    // 验证
    if (m_name.IsEmpty()) {
        wxMessageBox("请输入姓名！", "错误", wxOK | wxICON_ERROR, this);
        return;
    }
    
    if (m_email.IsEmpty() || !m_email.Contains("@")) {
        wxMessageBox("请输入有效的邮箱地址！", "错误", wxOK | wxICON_ERROR, this);
        return;
    }
    
    // 验证通过，关闭对话框
    EndModal(wxID_OK);
}

// ==================== MyApp 实现 ====================

bool MyApp::OnInit() {
    MyFrame* frame = new MyFrame();
    frame->Show(true);
    return true;
}

// ==================== MyFrame 实现 ====================

MyFrame::MyFrame()
    : wxFrame(NULL, wxID_ANY, "对话框示例", wxDefaultPosition, wxSize(600, 500)) {
    
    wxPanel* panel = new wxPanel(this);
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    
    // 标题
    wxStaticText* title = new wxStaticText(panel, wxID_ANY,
                                          "点击按钮打开不同类型的对话框：");
    mainSizer->Add(title, 0, wxALL, 10);
    
    // 按钮网格
    wxGridSizer* gridSizer = new wxGridSizer(2, 5, 5);
    
    wxButton* btnMessage = new wxButton(panel, ID_MESSAGE_BOX, "消息框");
    wxButton* btnOpen = new wxButton(panel, ID_FILE_OPEN, "打开文件");
    wxButton* btnSave = new wxButton(panel, ID_FILE_SAVE, "保存文件");
    wxButton* btnColor = new wxButton(panel, ID_COLOR, "颜色选择");
    wxButton* btnFont = new wxButton(panel, ID_FONT, "字体选择");
    wxButton* btnCustom = new wxButton(panel, ID_CUSTOM, "自定义对话框");
    wxButton* btnProgress = new wxButton(panel, ID_PROGRESS, "进度对话框");
    wxButton* btnTextEntry = new wxButton(panel, ID_TEXT_ENTRY, "文本输入");
    
    gridSizer->Add(btnMessage, 0, wxEXPAND);
    gridSizer->Add(btnOpen, 0, wxEXPAND);
    gridSizer->Add(btnSave, 0, wxEXPAND);
    gridSizer->Add(btnColor, 0, wxEXPAND);
    gridSizer->Add(btnFont, 0, wxEXPAND);
    gridSizer->Add(btnCustom, 0, wxEXPAND);
    gridSizer->Add(btnProgress, 0, wxEXPAND);
    gridSizer->Add(btnTextEntry, 0, wxEXPAND);
    
    mainSizer->Add(gridSizer, 0, wxEXPAND | wxALL, 10);
    
    // 分隔线
    mainSizer->Add(new wxStaticLine(panel), 0, wxEXPAND | wxALL, 5);
    
    // 颜色显示面板
    wxBoxSizer* colorSizer = new wxBoxSizer(wxHORIZONTAL);
    colorSizer->Add(new wxStaticText(panel, wxID_ANY, "选择的颜色:"),
                   0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);
    m_colorPanel = new wxPanel(panel, wxID_ANY, wxDefaultPosition, wxSize(100, 30));
    m_colorPanel->SetBackgroundColour(*wxWHITE);
    colorSizer->Add(m_colorPanel, 0);
    mainSizer->Add(colorSizer, 0, wxALL, 10);
    
    // 字体显示
    m_fontLabel = new wxStaticText(panel, wxID_ANY, "选择的字体将显示在这里");
    mainSizer->Add(m_fontLabel, 0, wxALL, 10);
    
    // 文本区域
    m_textCtrl = new wxTextCtrl(panel, wxID_ANY, "",
                               wxDefaultPosition, wxDefaultSize,
                               wxTE_MULTILINE | wxTE_READONLY);
    m_textCtrl->SetValue("对话框操作的结果将显示在这里...\n");
    mainSizer->Add(m_textCtrl, 1, wxEXPAND | wxALL, 10);
    
    panel->SetSizer(mainSizer);
    
    // 绑定事件
    Bind(wxEVT_BUTTON, &MyFrame::OnMessageBox, this, ID_MESSAGE_BOX);
    Bind(wxEVT_BUTTON, &MyFrame::OnFileOpen, this, ID_FILE_OPEN);
    Bind(wxEVT_BUTTON, &MyFrame::OnFileSave, this, ID_FILE_SAVE);
    Bind(wxEVT_BUTTON, &MyFrame::OnColorDialog, this, ID_COLOR);
    Bind(wxEVT_BUTTON, &MyFrame::OnFontDialog, this, ID_FONT);
    Bind(wxEVT_BUTTON, &MyFrame::OnCustomDialog, this, ID_CUSTOM);
    Bind(wxEVT_BUTTON, &MyFrame::OnProgressDialog, this, ID_PROGRESS);
    Bind(wxEVT_BUTTON, &MyFrame::OnTextEntry, this, ID_TEXT_ENTRY);
    
    Centre();
}

void MyFrame::OnMessageBox(wxCommandEvent& event) {
    // 不同类型的消息框
    int choice = wxMessageBox(
        "wxMessageBox 可以显示各种类型的消息。\n\n"
        "这是一个带图标和按钮的示例。\n"
        "点击 Yes 查看更多示例，点击 No 返回。",
        "消息框示例",
        wxYES_NO | wxICON_QUESTION,
        this
    );
    
    if (choice == wxYES) {
        // 信息框
        wxMessageBox("这是一个信息框。", "信息", wxOK | wxICON_INFORMATION, this);
        
        // 警告框
        wxMessageBox("这是一个警告框。", "警告", wxOK | wxICON_WARNING, this);
        
        // 错误框
        wxMessageBox("这是一个错误框。", "错误", wxOK | wxICON_ERROR, this);
    }
    
    m_textCtrl->AppendText("消息框已显示\n");
}

void MyFrame::OnFileOpen(wxCommandEvent& event) {
    wxFileDialog openFileDialog(
        this,
        "选择文件",
        "",  // 默认目录
        "",  // 默认文件名
        "文本文件 (*.txt)|*.txt|所有文件 (*.*)|*.*",
        wxFD_OPEN | wxFD_FILE_MUST_EXIST | wxFD_MULTIPLE  // 可多选
    );
    
    if (openFileDialog.ShowModal() == wxID_CANCEL) {
        m_textCtrl->AppendText("取消打开文件\n");
        return;
    }
    
    wxArrayString paths;
    openFileDialog.GetPaths(paths);
    
    m_textCtrl->AppendText("选择的文件:\n");
    for (size_t i = 0; i < paths.GetCount(); i++) {
        m_textCtrl->AppendText("  " + paths[i] + "\n");
    }
}

void MyFrame::OnFileSave(wxCommandEvent& event) {
    wxFileDialog saveFileDialog(
        this,
        "保存文件",
        "",
        "untitled.txt",
        "文本文件 (*.txt)|*.txt",
        wxFD_SAVE | wxFD_OVERWRITE_PROMPT
    );
    
    if (saveFileDialog.ShowModal() == wxID_CANCEL) {
        m_textCtrl->AppendText("取消保存文件\n");
        return;
    }
    
    wxString path = saveFileDialog.GetPath();
    m_textCtrl->AppendText("保存到: " + path + "\n");
}

void MyFrame::OnColorDialog(wxCommandEvent& event) {
    wxColourData colorData;
    colorData.SetColour(m_colorPanel->GetBackgroundColour());
    
    wxColourDialog dialog(this, &colorData);
    
    if (dialog.ShowModal() == wxID_OK) {
        wxColour color = dialog.GetColourData().GetColour();
        m_colorPanel->SetBackgroundColour(color);
        m_colorPanel->Refresh();
        
        m_textCtrl->AppendText(wxString::Format(
            "选择的颜色: RGB(%d, %d, %d)\n",
            color.Red(), color.Green(), color.Blue()
        ));
    }
}

void MyFrame::OnFontDialog(wxCommandEvent& event) {
    wxFontData fontData;
    fontData.SetInitialFont(m_fontLabel->GetFont());
    
    wxFontDialog dialog(this, fontData);
    
    if (dialog.ShowModal() == wxID_OK) {
        wxFont font = dialog.GetFontData().GetChosenFont();
        m_fontLabel->SetFont(font);
        
        m_textCtrl->AppendText(wxString::Format(
            "选择的字体: %s, 大小: %d\n",
            font.GetFaceName(), font.GetPointSize()
        ));
    }
}

void MyFrame::OnCustomDialog(wxCommandEvent& event) {
    CustomDialog dialog(this);
    
    if (dialog.ShowModal() == wxID_OK) {
        wxString name = dialog.GetName();
        wxString email = dialog.GetEmail();
        
        m_textCtrl->AppendText(wxString::Format(
            "自定义对话框返回:\n  姓名: %s\n  邮箱: %s\n",
            name, email
        ));
    } else {
        m_textCtrl->AppendText("取消自定义对话框\n");
    }
}

void MyFrame::OnProgressDialog(wxCommandEvent& event) {
    wxProgressDialog dialog(
        "处理中",
        "正在处理，请稍候...",
        100,  // 最大值
        this,
        wxPD_AUTO_HIDE | wxPD_APP_MODAL | wxPD_CAN_ABORT
    );
    
    for (int i = 0; i <= 100; i++) {
        wxString message = wxString::Format("处理中... %d%%", i);
        
        if (!dialog.Update(i, message)) {
            m_textCtrl->AppendText("进度对话框被取消\n");
            break;
        }
        
        wxMilliSleep(30);  // 模拟工作
        
        if (i == 100) {
            m_textCtrl->AppendText("处理完成！\n");
        }
    }
}

void MyFrame::OnTextEntry(wxCommandEvent& event) {
    wxString value = wxGetTextFromUser(
        "请输入你的名字:",
        "文本输入",
        "默认值",
        this
    );
    
    if (!value.IsEmpty()) {
        m_textCtrl->AppendText("输入的文本: " + value + "\n");
    } else {
        m_textCtrl->AppendText("取消文本输入\n");
    }
}

wxIMPLEMENT_APP(MyApp);

/*
 * 对话框说明：
 * 
 * 1. wxMessageBox - 消息框
 *    - 图标：wxICON_INFORMATION, wxICON_WARNING, wxICON_ERROR, wxICON_QUESTION
 *    - 按钮：wxOK, wxCANCEL, wxYES_NO, wxYES | wxNO | wxCANCEL
 * 
 * 2. wxFileDialog - 文件对话框
 *    - wxFD_OPEN: 打开文件
 *    - wxFD_SAVE: 保存文件
 *    - wxFD_MULTIPLE: 多选
 *    - wxFD_FILE_MUST_EXIST: 文件必须存在
 *    - wxFD_OVERWRITE_PROMPT: 覆盖提示
 * 
 * 3. wxColourDialog - 颜色选择对话框
 *    - 返回 wxColour 对象
 * 
 * 4. wxFontDialog - 字体选择对话框
 *    - 返回 wxFont 对象
 * 
 * 5. 自定义对话框
 *    - 继承 wxDialog
 *    - ShowModal() 显示模态对话框
 *    - EndModal(returnCode) 关闭对话框
 * 
 * 6. wxProgressDialog - 进度对话框
 *    - Update(value, message) 更新进度
 *    - wxPD_CAN_ABORT 允许取消
 * 
 * 7. 便捷函数
 *    - wxGetTextFromUser() 快速文本输入
 *    - wxGetPasswordFromUser() 密码输入
 *    - wxGetNumberFromUser() 数字输入
 * 
 * 练习：
 * 1. 创建一个设置对话框
 * 2. 实现非模态对话框
 * 3. 添加对话框验证逻辑
 * 4. 创建向导式对话框（多页）
 */
