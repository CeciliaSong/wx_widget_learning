/*
 * wxWidgets 树控件示例（简化版）
 * 
 * 展示：
 * - wxTreeCtrl (树形控件)
 * 
 * 编译：g++ -o list_tree list_tree.cpp `wx-config --cxxflags --libs`
 */

#include <wx/wx.h>
#include <wx/treectrl.h>

class MyApp : public wxApp {
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame {
public:
    MyFrame();

private:
    wxTreeCtrl* m_treeCtrl;
    wxTextCtrl* m_log;
    
    void OnTreeSelChanged(wxTreeEvent& event);
    void OnTreeItemActivated(wxTreeEvent& event);
    
    void PopulateTree();
};

bool MyApp::OnInit() {
    MyFrame* frame = new MyFrame();
    frame->Show(true);
    return true;
}

MyFrame::MyFrame()
    : wxFrame(NULL, wxID_ANY, "Simple Tree Control", wxDefaultPosition, wxSize(500, 500)) {
    
    wxPanel* panel = new wxPanel(this);
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    
    // Tree control
    wxStaticText* title = new wxStaticText(panel, wxID_ANY, "China - Provinces and Cities:");
    mainSizer->Add(title, 0, wxALL, 10);
    
    m_treeCtrl = new wxTreeCtrl(panel, wxID_ANY,
                               wxDefaultPosition, wxDefaultSize,
                               wxTR_DEFAULT_STYLE | wxTR_HIDE_ROOT);
    mainSizer->Add(m_treeCtrl, 3, wxEXPAND | wxALL, 10);
    
    // Log area
    wxStaticText* logLabel = new wxStaticText(panel, wxID_ANY, "Events:");
    mainSizer->Add(logLabel, 0, wxLEFT | wxRIGHT, 10);
    
    m_log = new wxTextCtrl(panel, wxID_ANY, "",
                          wxDefaultPosition, wxDefaultSize,
                          wxTE_MULTILINE | wxTE_READONLY);
    mainSizer->Add(m_log, 1, wxEXPAND | wxALL, 10);
    
    panel->SetSizer(mainSizer);
    
    // Populate tree
    PopulateTree();
    
    // Bind events
    m_treeCtrl->Bind(wxEVT_TREE_SEL_CHANGED, &MyFrame::OnTreeSelChanged, this);
    m_treeCtrl->Bind(wxEVT_TREE_ITEM_ACTIVATED, &MyFrame::OnTreeItemActivated, this);
    
    Centre();
}

void MyFrame::PopulateTree() {
    // Create root (hidden)
    wxTreeItemId root = m_treeCtrl->AddRoot("Root");
    
    // Beijing Municipality
    wxTreeItemId beijing = m_treeCtrl->AppendItem(root, "Beijing");
    m_treeCtrl->AppendItem(beijing, "Dongcheng District");
    m_treeCtrl->AppendItem(beijing, "Xicheng District");
    m_treeCtrl->AppendItem(beijing, "Chaoyang District");
    m_treeCtrl->AppendItem(beijing, "Haidian District");
    
    // Shanghai Municipality
    wxTreeItemId shanghai = m_treeCtrl->AppendItem(root, "Shanghai");
    m_treeCtrl->AppendItem(shanghai, "Huangpu District");
    m_treeCtrl->AppendItem(shanghai, "Xuhui District");
    m_treeCtrl->AppendItem(shanghai, "Changning District");
    m_treeCtrl->AppendItem(shanghai, "Pudong New Area");
    
    // Guangdong Province
    wxTreeItemId guangdong = m_treeCtrl->AppendItem(root, "Guangdong Province");
    m_treeCtrl->AppendItem(guangdong, "Guangzhou");
    m_treeCtrl->AppendItem(guangdong, "Shenzhen");
    m_treeCtrl->AppendItem(guangdong, "Zhuhai");
    m_treeCtrl->AppendItem(guangdong, "Dongguan");
    m_treeCtrl->AppendItem(guangdong, "Foshan");
    
    // Zhejiang Province
    wxTreeItemId zhejiang = m_treeCtrl->AppendItem(root, "Zhejiang Province");
    m_treeCtrl->AppendItem(zhejiang, "Hangzhou");
    m_treeCtrl->AppendItem(zhejiang, "Ningbo");
    m_treeCtrl->AppendItem(zhejiang, "Wenzhou");
    m_treeCtrl->AppendItem(zhejiang, "Jiaxing");
    
    
    // Expand all
    m_treeCtrl->ExpandAll();
}

void MyFrame::OnTreeSelChanged(wxTreeEvent& event) {
    wxTreeItemId item = event.GetItem();
    wxString text = m_treeCtrl->GetItemText(item);
    
    m_log->AppendText("Selected: " + text + "\n");
}

void MyFrame::OnTreeItemActivated(wxTreeEvent& event) {
    wxTreeItemId item = event.GetItem();
    wxString text = m_treeCtrl->GetItemText(item);
    
    m_log->AppendText("Double-clicked: " + text + "\n");
    
    // Toggle expand/collapse
    if (m_treeCtrl->ItemHasChildren(item)) {
        m_treeCtrl->Toggle(item);
    }
}

wxIMPLEMENT_APP(MyApp);
