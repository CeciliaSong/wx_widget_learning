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
    wxTextCtrl* m_textName;
    wxTextCtrl* m_textMultiline;
    wxCheckBox* m_checkSubscribe;
    wxRadioButton* m_radioMale;
    wxRadioButton* m_radioFemale;
    wxChoice* m_choiceCity;
    wxSlider* m_sliderAge;
    wxStaticText* m_labelAgeValue;
    
    void OnButtonClick(wxCommandEvent& event);
    void OnTextChanged(wxCommandEvent& event);
    void OnCheckBox(wxCommandEvent& event);
    void OnRadioButton(wxCommandEvent& event);
    void OnChoiceSelected(wxCommandEvent& event);
    void OnSlider(wxCommandEvent& event);
    void OnSubmit(wxCommandEvent& event);
};

bool MyApp::OnInit() 
{
    MyFrame* frame = new MyFrame();
    frame->Show(true);
    return true;
}

MyFrame::MyFrame()
    : wxFrame(NULL, wxID_ANY, "Basic Controls Example", wxDefaultPosition, wxSize(500, 600)) 
    {
    wxPanel* panel = new wxPanel(this);

    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText* labelName = new wxStaticText(panel, wxID_ANY, "Name:");
    m_textName = new wxTextCtrl(panel, wxID_ANY, "");
    
    mainSizer->Add(labelName, 0, wxALL, 5);
    mainSizer->Add(m_textName, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 5);

    wxStaticText* labelBio = new wxStaticText(panel, wxID_ANY, "Self-introduction:");
    m_textMultiline = new wxTextCtrl(panel, wxID_ANY, "",
                                     wxDefaultPosition, wxSize(-1, 80),
                                     wxTE_MULTILINE);
    
    mainSizer->Add(labelBio, 0, wxALL, 5);
    mainSizer->Add(m_textMultiline, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 5);
    
    m_checkSubscribe = new wxCheckBox(panel, wxID_ANY, "Participate in Exchange Program");
    mainSizer->Add(m_checkSubscribe, 0, wxALL, 5);

    wxStaticText* labelGender = new wxStaticText(panel, wxID_ANY, "Gender:");
    mainSizer->Add(labelGender, 0, wxALL, 5);
    
    wxBoxSizer* genderSizer = new wxBoxSizer(wxHORIZONTAL);
    m_radioMale = new wxRadioButton(panel, wxID_ANY, "Male",
                                    wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
    m_radioFemale = new wxRadioButton(panel, wxID_ANY, "Female");
    
    genderSizer->Add(m_radioMale, 0, wxALL, 5);
    genderSizer->Add(m_radioFemale, 0, wxALL, 5);
    mainSizer->Add(genderSizer, 0, wxLEFT, 5);

    wxStaticText* labelCity = new wxStaticText(panel, wxID_ANY, "Major:");
    mainSizer->Add(labelCity, 0, wxALL, 5);
    
    wxArrayString cities;
    cities.Add("Aerospace Engineering");
    cities.Add("Architectural Environment Engineering");
    cities.Add("Architecture");
    cities.Add("Chemical Engineering");
    cities.Add("Chemistry");
    cities.Add("Civil Engineering");
    cities.Add("Computer Science");
    cities.Add("Electrical and Electronic Engineering");
    cities.Add("Environmental Engineering");
    cities.Add("Mechanical Engineering");
    
    m_choiceCity = new wxChoice(panel, wxID_ANY, wxDefaultPosition,
                               wxDefaultSize, cities);
    m_choiceCity->SetSelection(7);  
    
    mainSizer->Add(m_choiceCity, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);
    
    wxStaticText* labelAge = new wxStaticText(panel, wxID_ANY, "Age:");
    mainSizer->Add(labelAge, 0, wxALL, 5);
    
    wxBoxSizer* ageSizer = new wxBoxSizer(wxHORIZONTAL);
    m_sliderAge = new wxSlider(panel, wxID_ANY, 25, 1, 100,
                               wxDefaultPosition, wxSize(200, -1));
    m_labelAgeValue = new wxStaticText(panel, wxID_ANY, "25");
    
    ageSizer->Add(m_sliderAge, 1, wxALL | wxEXPAND, 5);
    ageSizer->Add(m_labelAgeValue, 0, wxALL | wxALIGN_CENTER_VERTICAL, 5);
    mainSizer->Add(ageSizer, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 10);
    
    mainSizer->AddSpacer(20);  
    
    wxBoxSizer* buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    wxButton* btnSubmit = new wxButton(panel, wxID_ANY, "Submit");
    wxButton* btnClear = new wxButton(panel, wxID_ANY, "Clear");
    
    buttonSizer->Add(btnSubmit, 0, wxALL, 5);
    buttonSizer->Add(btnClear, 0, wxALL, 5);
    mainSizer->Add(buttonSizer, 0, wxALIGN_CENTER);

    m_textName->Bind(wxEVT_TEXT, &MyFrame::OnTextChanged, this);
    m_checkSubscribe->Bind(wxEVT_CHECKBOX, &MyFrame::OnCheckBox, this);
    m_radioMale->Bind(wxEVT_RADIOBUTTON, &MyFrame::OnRadioButton, this);
    m_radioFemale->Bind(wxEVT_RADIOBUTTON, &MyFrame::OnRadioButton, this);
    m_choiceCity->Bind(wxEVT_CHOICE, &MyFrame::OnChoiceSelected, this);
    m_sliderAge->Bind(wxEVT_SLIDER, &MyFrame::OnSlider, this);
    btnSubmit->Bind(wxEVT_BUTTON, &MyFrame::OnSubmit, this);
    btnClear->Bind(wxEVT_BUTTON, &MyFrame::OnButtonClick, this);
    
    panel->SetSizer(mainSizer);
    
    CreateStatusBar();
    SetStatusText("Please fill reletive information");
    
    Centre();
}

void MyFrame::OnButtonClick(wxCommandEvent& event) 
{
    m_textName->Clear();
    m_textMultiline->Clear();
    m_checkSubscribe->SetValue(false);
    m_radioMale->SetValue(true);
    m_choiceCity->SetSelection(0);
    m_sliderAge->SetValue(25);
    m_labelAgeValue->SetLabel("25");
    
    SetStatusText("Form cleared");
}

void MyFrame::OnTextChanged(wxCommandEvent& event) 
{
    wxString name = m_textName->GetValue();
    if (!name.IsEmpty()) 
    {
        SetStatusText("Name: " + name);
    } 
    else 
    {
        SetStatusText("Please enter name");
    }
}

void MyFrame::OnCheckBox(wxCommandEvent& event) 
{
    if (m_checkSubscribe->GetValue()) 
    {
        SetStatusText("Participate in Exchange Program");
    } 
    else 
    {
        SetStatusText("4+0 Program");
    }
}

void MyFrame::OnRadioButton(wxCommandEvent& event) 
{
    wxString gender = m_radioMale->GetValue() ? "Male" : "Female";
    SetStatusText("Gender: " + gender);
}

void MyFrame::OnChoiceSelected(wxCommandEvent& event) 
{
    wxString city = m_choiceCity->GetStringSelection();
    SetStatusText("Major: " + city);
}

void MyFrame::OnSlider(wxCommandEvent& event) 
{
    int age = m_sliderAge->GetValue();
    m_labelAgeValue->SetLabel(wxString::Format("%d", age));
    SetStatusText(wxString::Format("Age: %d", age));
}

void MyFrame::OnSubmit(wxCommandEvent& event) 
{

    wxString name = m_textName->GetValue();
    wxString bio = m_textMultiline->GetValue();
    bool subscribe = m_checkSubscribe->GetValue();
    wxString gender = m_radioMale->GetValue() ? "Male" : "Female";
    wxString city = m_choiceCity->GetStringSelection();
    int age = m_sliderAge->GetValue();

    if (name.IsEmpty()) 
    {
        wxMessageBox("Please enter name!", "Error", wxOK | wxICON_ERROR);
        return;
    }
    
    wxString message;
    message << "Name: " << name << "\n";
    message << "Age: " << age << "\n";
    message << "Gender: " << gender << "\n";
    message << "Major: " << city << "\n";
    message << "Exchange Student?: " << (subscribe ? "Yes" : "No") << "\n";
    
    if (!bio.IsEmpty()) 
    {
        message << "Selfintroduction:\n" << bio;
    }
    
    wxMessageBox(message, "Form Data", wxOK | wxICON_INFORMATION);
    SetStatusText("Form submitted");
}

wxIMPLEMENT_APP(MyApp);