/*
 * wxWidgets 对话框示例（简化版）
 * 
 * 展示：
 * - 消息框
 * - 文件对话框
 * - 颜色选择
 * - 自定义对话框
 * 
 * 编译：g++ -o dialogs dialogs.cpp `wx-config --cxxflags --libs`
 */

#include <wx/wx.h>
#include <wx/colordlg.h>

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
    
    void OnMessageBox(wxCommandEvent& event);
    void OnFileOpen(wxCommandEvent& event);
    void OnFileSave(wxCommandEvent& event);
    void OnColorDialog(wxCommandEvent& event);
    void OnCustomDialog(wxCommandEvent& event);
    
    enum {
        ID_MESSAGE_BOX = 1,
        ID_FILE_OPEN,
        ID_FILE_SAVE,
        ID_COLOR,
        ID_CUSTOM
    };
};

// ==================== CustomDialog Implementation ====================

CustomDialog::CustomDialog(wxWindow* parent)
    : wxDialog(parent, wxID_ANY, "Custom Dialog") {
    
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    
    wxFlexGridSizer* formSizer = new wxFlexGridSizer(2, 10, 10);
    formSizer->AddGrowableCol(1, 1);
    
    formSizer->Add(new wxStaticText(this, wxID_ANY, "Name:"),
                  0, wxALIGN_CENTER_VERTICAL);
    m_textName = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(280, -1));
    formSizer->Add(m_textName, 1, wxEXPAND);
    
    formSizer->Add(new wxStaticText(this, wxID_ANY, "Email:"),
                  0, wxALIGN_CENTER_VERTICAL);
    m_textEmail = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxSize(280, -1));
    formSizer->Add(m_textEmail, 1, wxEXPAND);
    
    mainSizer->Add(formSizer, 0, wxEXPAND | wxALL, 15);
    
    wxSizer* buttonSizer = CreateButtonSizer(wxOK | wxCANCEL);
    mainSizer->Add(buttonSizer, 0, wxALIGN_RIGHT | wxALL, 10);
    
    SetSizerAndFit(mainSizer);  // 自动调整大小
    Centre();
}

void CustomDialog::OnOK(wxCommandEvent& event) {
    m_name = m_textName->GetValue();
    m_email = m_textEmail->GetValue();
    
    // 去除首尾空格
    m_name.Trim().Trim(false);
    m_email.Trim().Trim(false);
    
    if (m_name.IsEmpty()) {
        wxMessageBox("Please enter name!", "Error", wxOK | wxICON_ERROR, this);
        m_textName->SetFocus();
        return;
    }
    
    // 更严格的邮箱验证
    if (m_email.IsEmpty()) {
        wxMessageBox("Please enter email!", "Error", wxOK | wxICON_ERROR, this);
        m_textEmail->SetFocus();
        return;
    }
    
    if (!m_email.Contains("@") || !m_email.Contains(".")) {
        wxMessageBox("Please enter a valid email address!\nExample: user@example.com", 
                     "Error", wxOK | wxICON_ERROR, this);
        m_textEmail->SetFocus();
        return;
    }
    
    // 检查 @ 位置
    int atPos = m_email.Find('@');
    if (atPos == 0 || atPos == (int)m_email.Length() - 1) {
        wxMessageBox("Invalid email format!", "Error", wxOK | wxICON_ERROR, this);
        m_textEmail->SetFocus();
        return;
    }
    
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
    : wxFrame(NULL, wxID_ANY, "Dialog Examples", wxDefaultPosition, wxSize(500, 450)) {
    
    wxPanel* panel = new wxPanel(this);
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    
    wxStaticText* title = new wxStaticText(panel, wxID_ANY,
                                          "Click buttons to open different dialogs:");
    mainSizer->Add(title, 0, wxALL, 10);
    
    // Buttons
    wxButton* btnMessage = new wxButton(panel, ID_MESSAGE_BOX, "Message Box");
    wxButton* btnOpen = new wxButton(panel, ID_FILE_OPEN, "Open File");
    wxButton* btnSave = new wxButton(panel, ID_FILE_SAVE, "Save File");
    wxButton* btnColor = new wxButton(panel, ID_COLOR, "Color Picker");
    wxButton* btnCustom = new wxButton(panel, ID_CUSTOM, "Custom Dialog");
    
    mainSizer->Add(btnMessage, 0, wxEXPAND | wxALL, 5);
    mainSizer->Add(btnOpen, 0, wxEXPAND | wxALL, 5);
    mainSizer->Add(btnSave, 0, wxEXPAND | wxALL, 5);
    mainSizer->Add(btnColor, 0, wxEXPAND | wxALL, 5);
    mainSizer->Add(btnCustom, 0, wxEXPAND | wxALL, 5);
    
    mainSizer->AddSpacer(10);
    
    // Color display
    wxBoxSizer* colorSizer = new wxBoxSizer(wxHORIZONTAL);
    colorSizer->Add(new wxStaticText(panel, wxID_ANY, "Selected color:"),
                   0, wxALIGN_CENTER_VERTICAL | wxRIGHT, 10);
    m_colorPanel = new wxPanel(panel, wxID_ANY, wxDefaultPosition, wxSize(80, 30));
    m_colorPanel->SetBackgroundColour(*wxWHITE);
    colorSizer->Add(m_colorPanel, 0);
    mainSizer->Add(colorSizer, 0, wxALL, 10);
    
    // Text area
    m_textCtrl = new wxTextCtrl(panel, wxID_ANY, "",
                               wxDefaultPosition, wxDefaultSize,
                               wxTE_MULTILINE | wxTE_READONLY);
    m_textCtrl->SetValue("Dialog results will be displayed here...\n");
    mainSizer->Add(m_textCtrl, 1, wxEXPAND | wxALL, 10);
    
    panel->SetSizer(mainSizer);
    
    Bind(wxEVT_BUTTON, &MyFrame::OnMessageBox, this, ID_MESSAGE_BOX);
    Bind(wxEVT_BUTTON, &MyFrame::OnFileOpen, this, ID_FILE_OPEN);
    Bind(wxEVT_BUTTON, &MyFrame::OnFileSave, this, ID_FILE_SAVE);
    Bind(wxEVT_BUTTON, &MyFrame::OnColorDialog, this, ID_COLOR);
    Bind(wxEVT_BUTTON, &MyFrame::OnCustomDialog, this, ID_CUSTOM);
    
    Centre();
}

void MyFrame::OnMessageBox(wxCommandEvent& event) {
    int choice = wxMessageBox(
        "This is a message box example.\n\nClick Yes for more info.",
        "Message Box",
        wxYES_NO | wxICON_QUESTION,
        this
    );
    
    if (choice == wxYES) {
        wxMessageBox("You clicked Yes!", "Info", wxOK | wxICON_INFORMATION, this);
    }
    
    m_textCtrl->AppendText("Message box displayed\n");
}

void MyFrame::OnFileOpen(wxCommandEvent& event) {
    wxFileDialog openFileDialog(
        this,
        "Select file",
        "",
        "",
        "Text files (*.txt)|*.txt|All files (*.*)|*.*",
        wxFD_OPEN | wxFD_FILE_MUST_EXIST
    );
    
    if (openFileDialog.ShowModal() == wxID_CANCEL) {
        m_textCtrl->AppendText("Cancelled\n");
        return;
    }
    
    wxString path = openFileDialog.GetPath();
    m_textCtrl->AppendText("Opened: " + path + "\n");
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
        m_textCtrl->AppendText("Cancelled\n");
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
            "Color: RGB(%d, %d, %d)\n",
            color.Red(), color.Green(), color.Blue()
        ));
    }
}

void MyFrame::OnCustomDialog(wxCommandEvent& event) {
    CustomDialog dialog(this);
    
    if (dialog.ShowModal() == wxID_OK) {
        m_textCtrl->AppendText(wxString::Format(
            "Name: %s\nEmail: %s\n",
            dialog.GetName(), dialog.GetEmail()
        ));
    } else {
        m_textCtrl->AppendText("Cancelled\n");
    }
}

wxIMPLEMENT_APP(MyApp);
