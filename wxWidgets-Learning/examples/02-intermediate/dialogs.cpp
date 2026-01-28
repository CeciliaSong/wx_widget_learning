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

// Custom dialog
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
    
    // Event handlers
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

// ==================== CustomDialog Implementation ====================

CustomDialog::CustomDialog(wxWindow* parent)
    : wxDialog(parent, wxID_ANY, "Custom Dialog", wxDefaultPosition, wxSize(400, 200)) {
    
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    
    // Form layout
    wxFlexGridSizer* formSizer = new wxFlexGridSizer(2, 10, 10);
    formSizer->AddGrowableCol(1, 1);
    
    // Name
    formSizer->Add(new wxStaticText(this, wxID_ANY, "Name:"),
                  0, wxALIGN_CENTER_VERTICAL);
    m_textName = new wxTextCtrl(this, wxID_ANY);
    formSizer->Add(m_textName, 1, wxEXPAND);
    
    // Email
    formSizer->Add(new wxStaticText(this, wxID_ANY, "Email:"),
                  0, wxALIGN_CENTER_VERTICAL);
    m_textEmail = new wxTextCtrl(this, wxID_ANY);
    formSizer->Add(m_textEmail, 1, wxEXPAND);
    
    mainSizer->Add(formSizer, 1, wxEXPAND | wxALL, 10);
    
    // Buttons
    wxSizer* buttonSizer = CreateButtonSizer(wxOK | wxCANCEL);
    mainSizer->Add(buttonSizer, 0, wxEXPAND | wxALL, 10);
    
    SetSizer(mainSizer);
    
    // Bind OK button
    Bind(wxEVT_BUTTON, &CustomDialog::OnOK, this, wxID_OK);
    
    Centre();
}

void CustomDialog::OnOK(wxCommandEvent& event) {
    m_name = m_textName->GetValue();
    m_email = m_textEmail->GetValue();
    
    // Validation
    if (m_name.IsEmpty()) {
        wxMessageBox("Please enter name!", "Error", wxOK | wxICON_ERROR, this);
        return;
    }
    
    if (m_email.IsEmpty() || !m_email.Contains("@")) {
        wxMessageBox("Please enter valid email address!", "Error", wxOK | wxICON_ERROR, this);
        return;
    }
    
    // Validation passed, close dialog
    EndModal(wxID_OK);
}

// ==================== MyApp Implementation ====================

bool MyApp::OnInit() {
    MyFrame* frame = new MyFrame();
    frame->Show(true);
    return true;
}

// ==================== MyFrame Implementation ====================

MyFrame::MyFrame()
    : wxFrame(NULL, wxID_ANY, "Dialog Examples", wxDefaultPosition, wxSize(600, 500)) {
    
    wxPanel* panel = new wxPanel(this);
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    
    // Title
    wxStaticText* title = new wxStaticText(panel, wxID_ANY,
                                          "Click buttons to open different types of dialogs:");
    mainSizer->Add(title, 0, wxALL, 10);
    
    // Button grid
    wxGridSizer* gridSizer = new wxGridSizer(2, 5, 5);
    
    wxButton* btnMessage = new wxButton(panel, ID_MESSAGE_BOX, "Message Box");
    wxButton* btnOpen = new wxButton(panel, ID_FILE_OPEN, "Open File");
    wxButton* btnSave = new wxButton(panel, ID_FILE_SAVE, "Save File");
    wxButton* btnColor = new wxButton(panel, ID_COLOR, "Color Picker");
    wxButton* btnFont = new wxButton(panel, ID_FONT, "Font Picker");
    wxButton* btnCustom = new wxButton(panel, ID_CUSTOM, "Custom Dialog");
    wxButton* btnProgress = new wxButton(panel, ID_PROGRESS, "Progress Dialog");
    wxButton* btnTextEntry = new wxButton(panel, ID_TEXT_ENTRY, "Text Input");
    
    gridSizer->Add(btnMessage, 0, wxEXPAND);
    gridSizer->Add(btnOpen, 0, wxEXPAND);
    gridSizer->Add(btnSave, 0, wxEXPAND);
    gridSizer->Add(btnColor, 0, wxEXPAND);
    gridSizer->Add(btnFont, 0, wxEXPAND);
    gridSizer->Add(btnCustom, 0, wxEXPAND);
    gridSizer->Add(btnProgress, 0, wxEXPAND);
    gridSizer->Add(btnTextEntry, 0, wxEXPAND);
    
    mainSizer->Add(gridSizer, 0, wxEXPAND | wxALL, 10);
    
    // Separator
    mainSizer->Add(new wxStaticLine(panel), 0, wxEXPAND | wxALL, 5);
    
    // Color display panel
    wxBoxSizer* colorSizer = new wxBoxSizer(wxHORIZONTAL);
    colorSizer->Add(new wxStaticText(panel, wxID_ANY, "Selected color:"),
                   0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);
    m_colorPanel = new wxPanel(panel, wxID_ANY, wxDefaultPosition, wxSize(100, 30));
    m_colorPanel->SetBackgroundColour(*wxWHITE);
    colorSizer->Add(m_colorPanel, 0);
    mainSizer->Add(colorSizer, 0, wxALL, 10);
    
    // Font display
    m_fontLabel = new wxStaticText(panel, wxID_ANY, "Selected font will be displayed here");
    mainSizer->Add(m_fontLabel, 0, wxALL, 10);
    
    // Text area
    m_textCtrl = new wxTextCtrl(panel, wxID_ANY, "",
                               wxDefaultPosition, wxDefaultSize,
                               wxTE_MULTILINE | wxTE_READONLY);
    m_textCtrl->SetValue("Dialog results will be displayed here...\n");
    mainSizer->Add(m_textCtrl, 1, wxEXPAND | wxALL, 10);
    
    panel->SetSizer(mainSizer);
    
    // Bind events
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
    // Different types of message boxes
    int choice = wxMessageBox(
        "wxMessageBox can display various types of messages.\n\n"
        "This is an example with icons and buttons.\n"
        "Click Yes for more examples, No to return.",
        "Message Box Example",
        wxYES_NO | wxICON_QUESTION,
        this
    );
    
    if (choice == wxYES) {
        // Info box
        wxMessageBox("This is an info box.", "Info", wxOK | wxICON_INFORMATION, this);
        
        // Warning box
        wxMessageBox("This is a warning box.", "Warning", wxOK | wxICON_WARNING, this);
        
        // Error box
        wxMessageBox("This is an error box.", "Error", wxOK | wxICON_ERROR, this);
    }
    
    m_textCtrl->AppendText("Message box displayed\n");
}

void MyFrame::OnFileOpen(wxCommandEvent& event) {
    wxFileDialog openFileDialog(
        this,
        "Select file",
        "",  // Default directory
        "",  // Default filename
        "Text files (*.txt)|*.txt|All files (*.*)|*.*",
        wxFD_OPEN | wxFD_FILE_MUST_EXIST | wxFD_MULTIPLE  // Allow multiple selection
    );
    
    if (openFileDialog.ShowModal() == wxID_CANCEL) {
        m_textCtrl->AppendText("Cancelled opening file\n");
        return;
    }
    
    wxArrayString paths;
    openFileDialog.GetPaths(paths);
    
    m_textCtrl->AppendText("Selected files:\n");
    for (size_t i = 0; i < paths.GetCount(); i++) {
        m_textCtrl->AppendText("  " + paths[i] + "\n");
    }
}

void MyFrame::OnFileSave(wxCommandEvent& event) {
    wxFileDialog saveFileDialog(
        this,
        "Save file",
        "",
        "untitled.txt",
        "Text files (*.txt)|*.txt",
        wxFD_SAVE | wxFD_OVERWRITE_PROMPT
    );
    
    if (saveFileDialog.ShowModal() == wxID_CANCEL) {
        m_textCtrl->AppendText("Cancelled saving file\n");
        return;
    }
    
    wxString path = saveFileDialog.GetPath();
    m_textCtrl->AppendText("Saved to: " + path + "\n");
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
            "Selected color: RGB(%d, %d, %d)\n",
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
            "Selected font: %s, size: %d\n",
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
            "Custom dialog returned:\n  Name: %s\n  Email: %s\n",
            name, email
        ));
    } else {
        m_textCtrl->AppendText("Cancelled custom dialog\n");
    }
}

void MyFrame::OnProgressDialog(wxCommandEvent& event) {
    wxProgressDialog dialog(
        "Processing",
        "Processing, please wait...",
        100,  // Max value
        this,
        wxPD_AUTO_HIDE | wxPD_APP_MODAL | wxPD_CAN_ABORT
    );
    
    for (int i = 0; i <= 100; i++) {
        wxString message = wxString::Format("Processing... %d%%", i);
        
        if (!dialog.Update(i, message)) {
            m_textCtrl->AppendText("Progress dialog cancelled\n");
            break;
        }
        
        wxMilliSleep(30);  // Simulate work
        
        if (i == 100) {
            m_textCtrl->AppendText("Processing completed!\n");
        }
    }
}

void MyFrame::OnTextEntry(wxCommandEvent& event) {
    wxString value = wxGetTextFromUser(
        "Please enter your name:",
        "Text Input",
        "Default value",
        this
    );
    
    if (!value.IsEmpty()) {
        m_textCtrl->AppendText("Entered text: " + value + "\n");
    } else {
        m_textCtrl->AppendText("Cancelled text input\n");
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
