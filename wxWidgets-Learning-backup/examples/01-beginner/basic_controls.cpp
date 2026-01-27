/*
 * wxWidgets 基础控件示例
 * 
 * 展示常用的基础控件：
 * - wxButton (按钮)
 * - wxTextCtrl (文本框)
 * - wxCheckBox (复选框)
 * - wxRadioButton (单选按钮)
 * - wxChoice (下拉框)
 * - wxSlider (滑块)
 * - wxStaticText (静态文本)
 * 
 * 编译：g++ -o basic_controls basic_controls.cpp `wx-config --cxxflags --libs`
 */

#include <wx/wx.h>

class MyApp : public wxApp {
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame {
public:
    MyFrame();

private:
    // 控件指针
    wxTextCtrl* m_textName;
    wxTextCtrl* m_textMultiline;
    wxCheckBox* m_checkSubscribe;
    wxRadioButton* m_radioMale;
    wxRadioButton* m_radioFemale;
    wxChoice* m_choiceCity;
    wxSlider* m_sliderAge;
    wxStaticText* m_labelAgeValue;
    
    // 事件处理器
    void OnButtonClick(wxCommandEvent& event);
    void OnTextChanged(wxCommandEvent& event);
    void OnCheckBox(wxCommandEvent& event);
    void OnRadioButton(wxCommandEvent& event);
    void OnChoiceSelected(wxCommandEvent& event);
    void OnSlider(wxCommandEvent& event);
    void OnSubmit(wxCommandEvent& event);
};

bool MyApp::OnInit() {
    MyFrame* frame = new MyFrame();
    frame->Show(true);
    return true;
}

MyFrame::MyFrame()
    : wxFrame(NULL, wxID_ANY, "基础控件示例", wxDefaultPosition, wxSize(500, 600)) {
    
    // 创建主面板
    wxPanel* panel = new wxPanel(this);
    
    // 创建主垂直布局
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    
    // ==================== 文本框 ====================
    wxStaticText* labelName = new wxStaticText(panel, wxID_ANY, "姓名:");
    m_textName = new wxTextCtrl(panel, wxID_ANY, "");
    
    mainSizer->Add(labelName, 0, wxALL, 5);
    mainSizer->Add(m_textName, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 5);
    
    // ==================== 多行文本框 ====================
    wxStaticText* labelBio = new wxStaticText(panel, wxID_ANY, "个人简介:");
    m_textMultiline = new wxTextCtrl(panel, wxID_ANY, "",
                                     wxDefaultPosition, wxSize(-1, 80),
                                     wxTE_MULTILINE);
    
    mainSizer->Add(labelBio, 0, wxALL, 5);
    mainSizer->Add(m_textMultiline, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 5);
    
    // ==================== 复选框 ====================
    m_checkSubscribe = new wxCheckBox(panel, wxID_ANY, "订阅新闻通讯");
    mainSizer->Add(m_checkSubscribe, 0, wxALL, 5);
    
    // ==================== 单选按钮 ====================
    wxStaticText* labelGender = new wxStaticText(panel, wxID_ANY, "性别:");
    mainSizer->Add(labelGender, 0, wxALL, 5);
    
    wxBoxSizer* genderSizer = new wxBoxSizer(wxHORIZONTAL);
    m_radioMale = new wxRadioButton(panel, wxID_ANY, "男",
                                    wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
    m_radioFemale = new wxRadioButton(panel, wxID_ANY, "女");
    
    genderSizer->Add(m_radioMale, 0, wxALL, 5);
    genderSizer->Add(m_radioFemale, 0, wxALL, 5);
    mainSizer->Add(genderSizer, 0, wxLEFT, 5);
    
    // ==================== 下拉框 ====================
    wxStaticText* labelCity = new wxStaticText(panel, wxID_ANY, "城市:");
    mainSizer->Add(labelCity, 0, wxALL, 5);
    
    wxArrayString cities;
    cities.Add("北京");
    cities.Add("上海");
    cities.Add("广州");
    cities.Add("深圳");
    cities.Add("杭州");
    
    m_choiceCity = new wxChoice(panel, wxID_ANY, wxDefaultPosition,
                               wxDefaultSize, cities);
    m_choiceCity->SetSelection(0);  // 默认选择第一项
    
    mainSizer->Add(m_choiceCity, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 5);
    
    // ==================== 滑块 ====================
    wxStaticText* labelAge = new wxStaticText(panel, wxID_ANY, "年龄:");
    mainSizer->Add(labelAge, 0, wxALL, 5);
    
    wxBoxSizer* ageSizer = new wxBoxSizer(wxHORIZONTAL);
    m_sliderAge = new wxSlider(panel, wxID_ANY, 25, 1, 100,
                               wxDefaultPosition, wxSize(200, -1));
    m_labelAgeValue = new wxStaticText(panel, wxID_ANY, "25");
    
    ageSizer->Add(m_sliderAge, 1, wxALL | wxEXPAND, 5);
    ageSizer->Add(m_labelAgeValue, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    mainSizer->Add(ageSizer, 0, wxEXPAND);
    
    // ==================== 按钮 ====================
    mainSizer->AddSpacer(20);  // 添加间隔
    
    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    wxButton* btnSubmit = new wxButton(panel, wxID_ANY, "提交");
    wxButton* btnClear = new wxButton(panel, wxID_ANY, "清空");
    
    buttonSizer->Add(btnSubmit, 0, wxALL, 5);
    buttonSizer->Add(btnClear, 0, wxALL, 5);
    mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER);
    
    // ==================== 绑定事件 ====================
    m_textName->Bind(wxEVT_TEXT, &MyFrame::OnTextChanged, this);
    m_checkSubscribe->Bind(wxEVT_CHECKBOX, &MyFrame::OnCheckBox, this);
    m_radioMale->Bind(wxEVT_RADIOBUTTON, &MyFrame::OnRadioButton, this);
    m_radioFemale->Bind(wxEVT_RADIOBUTTON, &MyFrame::OnRadioButton, this);
    m_choiceCity->Bind(wxEVT_CHOICE, &MyFrame::OnChoiceSelected, this);
    m_sliderAge->Bind(wxEVT_SLIDER, &MyFrame::OnSlider, this);
    btnSubmit->Bind(wxEVT_BUTTON, &MyFrame::OnSubmit, this);
    btnClear->Bind(wxEVT_BUTTON, &MyFrame::OnButtonClick, this);
    
    // ==================== 应用布局 ====================
    panel->SetSizer(mainSizer);
    
    // 创建状态栏
    CreateStatusBar();
    SetStatusText("请填写表单");
    
    Centre();
}

void MyFrame::OnButtonClick(wxCommandEvent& event) {
    // 清空所有控件
    m_textName->Clear();
    m_textMultiline->Clear();
    m_checkSubscribe->SetValue(false);
    m_radioMale->SetValue(true);
    m_choiceCity->SetSelection(0);
    m_sliderAge->SetValue(25);
    m_labelAgeValue->SetLabel("25");
    
    SetStatusText("表单已清空");
}

void MyFrame::OnTextChanged(wxCommandEvent& event) {
    wxString name = m_textName->GetValue();
    if (!name.IsEmpty()) {
        SetStatusText("姓名: " + name);
    } else {
        SetStatusText("请输入姓名");
    }
}

void MyFrame::OnCheckBox(wxCommandEvent& event) {
    if (m_checkSubscribe->GetValue()) {
        SetStatusText("已订阅新闻通讯");
    } else {
        SetStatusText("已取消订阅");
    }
}

void MyFrame::OnRadioButton(wxCommandEvent& event) {
    wxString gender = m_radioMale->GetValue() ? "男" : "女";
    SetStatusText("性别: " + gender);
}

void MyFrame::OnChoiceSelected(wxCommandEvent& event) {
    wxString city = m_choiceCity->GetStringSelection();
    SetStatusText("城市: " + city);
}

void MyFrame::OnSlider(wxCommandEvent& event) {
    int age = m_sliderAge->GetValue();
    m_labelAgeValue->SetLabel(wxString::Format("%d", age));
    SetStatusText(wxString::Format("年龄: %d", age));
}

void MyFrame::OnSubmit(wxCommandEvent& event) {
    // 收集所有表单数据
    wxString name = m_textName->GetValue();
    wxString bio = m_textMultiline->GetValue();
    bool subscribe = m_checkSubscribe->GetValue();
    wxString gender = m_radioMale->GetValue() ? "男" : "女";
    wxString city = m_choiceCity->GetStringSelection();
    int age = m_sliderAge->GetValue();
    
    // 验证
    if (name.IsEmpty()) {
        wxMessageBox("请输入姓名！", "错误", wxOK | wxICON_ERROR);
        return;
    }
    
    // 显示结果
    wxString message;
    message << "姓名: " << name << "\n";
    message << "年龄: " << age << "\n";
    message << "性别: " << gender << "\n";
    message << "城市: " << city << "\n";
    message << "订阅: " << (subscribe ? "是" : "否") << "\n";
    
    if (!bio.IsEmpty()) {
        message << "\n个人简介:\n" << bio;
    }
    
    wxMessageBox(message, "表单数据", wxOK | wxICON_INFORMATION);
    SetStatusText("表单已提交");
}

wxIMPLEMENT_APP(MyApp);

/*
 * 控件说明：
 * 
 * 1. wxTextCtrl - 文本框
 *    - 单行：默认
 *    - 多行：wxTE_MULTILINE 样式
 *    - 密码：wxTE_PASSWORD 样式
 *    - 只读：wxTE_READONLY 样式
 * 
 * 2. wxCheckBox - 复选框
 *    - GetValue() / SetValue() 获取/设置状态
 * 
 * 3. wxRadioButton - 单选按钮
 *    - wxRB_GROUP 标志表示新组的开始
 *    - 同组内只能选一个
 * 
 * 4. wxChoice - 下拉选择框
 *    - 添加选项：Add() 或构造函数
 *    - 获取选择：GetSelection() / GetStringSelection()
 * 
 * 5. wxSlider - 滑块
 *    - 构造函数：(parent, id, value, min, max)
 *    - GetValue() / SetValue() 获取/设置值
 * 
 * 练习：
 * 1. 添加更多控件（wxSpinCtrl, wxComboBox 等）
 * 2. 实现数据验证（邮箱格式、年龄范围等）
 * 3. 保存表单数据到文件
 * 4. 添加重置按钮的确认对话框
 */
