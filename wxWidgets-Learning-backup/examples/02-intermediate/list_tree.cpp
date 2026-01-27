/*
 * wxWidgets 列表和树控件示例
 * 
 * 展示：
 * - wxListCtrl (列表控件 - 报表视图)
 * - wxTreeCtrl (树形控件)
 * - wxListBox (简单列表框)
 * 
 * 编译：g++ -o list_tree list_tree.cpp `wx-config --cxxflags --libs`
 */

#include <wx/wx.h>
#include <wx/listctrl.h>
#include <wx/treectrl.h>
#include <wx/imaglist.h>
#include <wx/artprov.h>

class MyApp : public wxApp {
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame {
public:
    MyFrame();

private:
    wxListCtrl* m_listCtrl;
    wxTreeCtrl* m_treeCtrl;
    wxTextCtrl* m_log;
    
    // 事件处理器
    void OnListItemSelected(wxListEvent& event);
    void OnListItemActivated(wxListEvent& event);
    void OnListColumnClick(wxListEvent& event);
    void OnListRightClick(wxListEvent& event);
    
    void OnTreeSelChanged(wxTreeEvent& event);
    void OnTreeItemActivated(wxTreeEvent& event);
    void OnTreeRightClick(wxTreeEvent& event);
    
    void OnAddItem(wxCommandEvent& event);
    void OnDeleteItem(wxCommandEvent& event);
    void OnClearAll(wxCommandEvent& event);
    
    void PopulateList();
    void PopulateTree();
    
    enum {
        ID_ADD_ITEM = 1,
        ID_DELETE_ITEM,
        ID_CLEAR_ALL
    };
};

bool MyApp::OnInit() {
    MyFrame* frame = new MyFrame();
    frame->Show(true);
    return true;
}

MyFrame::MyFrame()
    : wxFrame(NULL, wxID_ANY, "列表和树控件示例", wxDefaultPosition, wxSize(900, 600)) {
    
    // 创建主面板
    wxPanel* panel = new wxPanel(this);
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    
    // ==================== 工具栏 ====================
    wxBoxSizer* toolbarSizer = new wxBoxSizer(wxHORIZONTAL);
    wxButton* btnAdd = new wxButton(panel, ID_ADD_ITEM, "添加项目");
    wxButton* btnDelete = new wxButton(panel, ID_DELETE_ITEM, "删除项目");
    wxButton* btnClear = new wxButton(panel, ID_CLEAR_ALL, "清空");
    
    toolbarSizer->Add(btnAdd, 0, wxALL, 5);
    toolbarSizer->Add(btnDelete, 0, wxALL, 5);
    toolbarSizer->Add(btnClear, 0, wxALL, 5);
    mainSizer->Add(toolbarSizer, 0);
    
    // ==================== 分割窗口 ====================
    wxBoxSizer* contentSizer = new wxBoxSizer(wxHORIZONTAL);
    
    // === 左侧：wxListCtrl ===
    wxStaticBoxSizer* listBox = new wxStaticBoxSizer(wxVERTICAL, panel, "列表控件 (wxListCtrl)");
    
    m_listCtrl = new wxListCtrl(panel, wxID_ANY,
                               wxDefaultPosition, wxDefaultSize,
                               wxLC_REPORT | wxLC_SINGLE_SEL);
    
    // 创建列
    m_listCtrl->InsertColumn(0, "ID", wxLIST_FORMAT_LEFT, 50);
    m_listCtrl->InsertColumn(1, "姓名", wxLIST_FORMAT_LEFT, 100);
    m_listCtrl->InsertColumn(2, "年龄", wxLIST_FORMAT_LEFT, 60);
    m_listCtrl->InsertColumn(3, "城市", wxLIST_FORMAT_LEFT, 100);
    m_listCtrl->InsertColumn(4, "职业", wxLIST_FORMAT_LEFT, 120);
    
    listBox->Add(m_listCtrl, 1, wxEXPAND | wxALL, 5);
    contentSizer->Add(listBox, 2, wxEXPAND | wxALL, 5);
    
    // === 右侧：wxTreeCtrl ===
    wxStaticBoxSizer* treeBox = new wxStaticBoxSizer(wxVERTICAL, panel, "树形控件 (wxTreeCtrl)");
    
    m_treeCtrl = new wxTreeCtrl(panel, wxID_ANY,
                               wxDefaultPosition, wxDefaultSize,
                               wxTR_DEFAULT_STYLE);
    
    treeBox->Add(m_treeCtrl, 1, wxEXPAND | wxALL, 5);
    contentSizer->Add(treeBox, 1, wxEXPAND | wxALL, 5);
    
    mainSizer->Add(contentSizer, 3, wxEXPAND);
    
    // ==================== 日志区域 ====================
    wxStaticBoxSizer* logBox = new wxStaticBoxSizer(wxVERTICAL, panel, "事件日志");
    m_log = new wxTextCtrl(panel, wxID_ANY, "",
                          wxDefaultPosition, wxSize(-1, 100),
                          wxTE_MULTILINE | wxTE_READONLY);
    logBox->Add(m_log, 1, wxEXPAND | wxALL, 5);
    mainSizer->Add(logBox, 1, wxEXPAND | wxALL, 5);
    
    panel->SetSizer(mainSizer);
    
    // ==================== 填充数据 ====================
    PopulateList();
    PopulateTree();
    
    // ==================== 绑定事件 ====================
    // 列表事件
    m_listCtrl->Bind(wxEVT_LIST_ITEM_SELECTED, &MyFrame::OnListItemSelected, this);
    m_listCtrl->Bind(wxEVT_LIST_ITEM_ACTIVATED, &MyFrame::OnListItemActivated, this);
    m_listCtrl->Bind(wxEVT_LIST_COL_CLICK, &MyFrame::OnListColumnClick, this);
    m_listCtrl->Bind(wxEVT_LIST_ITEM_RIGHT_CLICK, &MyFrame::OnListRightClick, this);
    
    // 树事件
    m_treeCtrl->Bind(wxEVT_TREE_SEL_CHANGED, &MyFrame::OnTreeSelChanged, this);
    m_treeCtrl->Bind(wxEVT_TREE_ITEM_ACTIVATED, &MyFrame::OnTreeItemActivated, this);
    m_treeCtrl->Bind(wxEVT_TREE_ITEM_RIGHT_CLICK, &MyFrame::OnTreeRightClick, this);
    
    // 按钮事件
    Bind(wxEVT_BUTTON, &MyFrame::OnAddItem, this, ID_ADD_ITEM);
    Bind(wxEVT_BUTTON, &MyFrame::OnDeleteItem, this, ID_DELETE_ITEM);
    Bind(wxEVT_BUTTON, &MyFrame::OnClearAll, this, ID_CLEAR_ALL);
    
    Centre();
}

void MyFrame::PopulateList() {
    // 示例数据
    struct Person {
        int id;
        const char* name;
        int age;
        const char* city;
        const char* job;
    };
    
    Person people[] = {
        {1, "张三", 28, "北京", "软件工程师"},
        {2, "李四", 32, "上海", "产品经理"},
        {3, "王五", 25, "广州", "UI设计师"},
        {4, "赵六", 30, "深圳", "数据分析师"},
        {5, "钱七", 27, "杭州", "前端开发"},
        {6, "孙八", 35, "成都", "项目经理"},
        {7, "周九", 29, "武汉", "测试工程师"},
        {8, "吴十", 26, "西安", "运维工程师"}
    };
    
    for (int i = 0; i < 8; i++) {
        long index = m_listCtrl->InsertItem(i, wxString::Format("%d", people[i].id));
        m_listCtrl->SetItem(index, 1, people[i].name);
        m_listCtrl->SetItem(index, 2, wxString::Format("%d", people[i].age));
        m_listCtrl->SetItem(index, 3, people[i].city);
        m_listCtrl->SetItem(index, 4, people[i].job);
        
        // 交替行颜色
        if (i % 2 == 1) {
            m_listCtrl->SetItemBackgroundColour(index, wxColour(240, 240, 240));
        }
    }
}

void MyFrame::PopulateTree() {
    // 创建根节点
    wxTreeItemId root = m_treeCtrl->AddRoot("公司组织架构");
    
    // 部门
    wxTreeItemId tech = m_treeCtrl->AppendItem(root, "技术部");
    wxTreeItemId sales = m_treeCtrl->AppendItem(root, "销售部");
    wxTreeItemId hr = m_treeCtrl->AppendItem(root, "人力资源部");
    
    // 技术部子节点
    wxTreeItemId dev = m_treeCtrl->AppendItem(tech, "研发组");
    m_treeCtrl->AppendItem(dev, "张三 - 前端");
    m_treeCtrl->AppendItem(dev, "李四 - 后端");
    m_treeCtrl->AppendItem(dev, "王五 - 全栈");
    
    wxTreeItemId qa = m_treeCtrl->AppendItem(tech, "测试组");
    m_treeCtrl->AppendItem(qa, "赵六 - 测试");
    m_treeCtrl->AppendItem(qa, "钱七 - 自动化");
    
    wxTreeItemId ops = m_treeCtrl->AppendItem(tech, "运维组");
    m_treeCtrl->AppendItem(ops, "孙八 - 运维");
    
    // 销售部子节点
    m_treeCtrl->AppendItem(sales, "周九 - 销售经理");
    m_treeCtrl->AppendItem(sales, "吴十 - 客户经理");
    
    // 人力资源部子节点
    m_treeCtrl->AppendItem(hr, "郑一 - HR总监");
    m_treeCtrl->AppendItem(hr, "王二 - 招聘专员");
    
    // 展开根节点和技术部
    m_treeCtrl->Expand(root);
    m_treeCtrl->Expand(tech);
}

void MyFrame::OnListItemSelected(wxListEvent& event) {
    long index = event.GetIndex();
    wxString name = m_listCtrl->GetItemText(index, 1);
    wxString age = m_listCtrl->GetItemText(index, 2);
    
    m_log->AppendText(wxString::Format("[列表] 选中: %s (年龄: %s)\n", name, age));
}

void MyFrame::OnListItemActivated(wxListEvent& event) {
    long index = event.GetIndex();
    wxString name = m_listCtrl->GetItemText(index, 1);
    wxString job = m_listCtrl->GetItemText(index, 4);
    
    m_log->AppendText(wxString::Format("[列表] 双击: %s - %s\n", name, job));
    
    wxMessageBox(wxString::Format("姓名: %s\n职业: %s", name, job),
                "详细信息", wxOK | wxICON_INFORMATION);
}

void MyFrame::OnListColumnClick(wxListEvent& event) {
    int col = event.GetColumn();
    wxString colName = m_listCtrl->GetColumn(col).GetText();
    m_log->AppendText(wxString::Format("[列表] 点击列: %s (可以实现排序)\n", colName));
}

void MyFrame::OnListRightClick(wxListEvent& event) {
    long index = event.GetIndex();
    m_log->AppendText(wxString::Format("[列表] 右键点击项: %ld\n", index));
    
    // 可以显示右键菜单
    wxMenu menu;
    menu.Append(wxID_ANY, "编辑");
    menu.Append(wxID_ANY, "删除");
    menu.AppendSeparator();
    menu.Append(wxID_ANY, "查看详情");
    
    m_listCtrl->PopupMenu(&menu);
}

void MyFrame::OnTreeSelChanged(wxTreeEvent& event) {
    wxTreeItemId item = event.GetItem();
    wxString text = m_treeCtrl->GetItemText(item);
    
    m_log->AppendText(wxString::Format("[树] 选中: %s\n", text));
}

void MyFrame::OnTreeItemActivated(wxTreeEvent& event) {
    wxTreeItemId item = event.GetItem();
    wxString text = m_treeCtrl->GetItemText(item);
    
    m_log->AppendText(wxString::Format("[树] 双击: %s\n", text));
    
    // 如果有子节点，展开/折叠
    if (m_treeCtrl->ItemHasChildren(item)) {
        m_treeCtrl->Toggle(item);
    }
}

void MyFrame::OnTreeRightClick(wxTreeEvent& event) {
    wxTreeItemId item = event.GetItem();
    wxString text = m_treeCtrl->GetItemText(item);
    
    m_log->AppendText(wxString::Format("[树] 右键点击: %s\n", text));
}

void MyFrame::OnAddItem(wxCommandEvent& event) {
    static int nextId = 9;
    
    long index = m_listCtrl->InsertItem(m_listCtrl->GetItemCount(),
                                       wxString::Format("%d", nextId++));
    m_listCtrl->SetItem(index, 1, "新用户");
    m_listCtrl->SetItem(index, 2, "30");
    m_listCtrl->SetItem(index, 3, "未知");
    m_listCtrl->SetItem(index, 4, "新职位");
    
    m_log->AppendText("[操作] 添加了新项目\n");
}

void MyFrame::OnDeleteItem(wxCommandEvent& event) {
    long selected = m_listCtrl->GetFirstSelected();
    
    if (selected == -1) {
        wxMessageBox("请先选择一个项目！", "提示", wxOK | wxICON_INFORMATION);
        return;
    }
    
    wxString name = m_listCtrl->GetItemText(selected, 1);
    m_listCtrl->DeleteItem(selected);
    
    m_log->AppendText(wxString::Format("[操作] 删除了: %s\n", name));
}

void MyFrame::OnClearAll(wxCommandEvent& event) {
    if (wxMessageBox("确定要清空所有数据吗？", "确认",
                    wxYES_NO | wxICON_QUESTION) == wxYES) {
        m_listCtrl->DeleteAllItems();
        m_log->AppendText("[操作] 清空了所有项目\n");
    }
}

wxIMPLEMENT_APP(MyApp);

/*
 * 控件说明：
 * 
 * 1. wxListCtrl - 列表控件
 *    样式：
 *    - wxLC_REPORT: 报表视图（多列）
 *    - wxLC_LIST: 列表视图（单列）
 *    - wxLC_ICON: 图标视图
 *    - wxLC_SMALL_ICON: 小图标视图
 *    - wxLC_SINGLE_SEL: 单选
 *    - wxLC_EDIT_LABELS: 可编辑标签
 * 
 *    方法：
 *    - InsertColumn(): 插入列
 *    - InsertItem(): 插入行
 *    - SetItem(): 设置单元格内容
 *    - GetItemText(): 获取单元格内容
 *    - DeleteItem(): 删除行
 * 
 *    事件：
 *    - wxEVT_LIST_ITEM_SELECTED: 选中
 *    - wxEVT_LIST_ITEM_ACTIVATED: 激活（双击）
 *    - wxEVT_LIST_COL_CLICK: 列标题点击
 * 
 * 2. wxTreeCtrl - 树形控件
 *    方法：
 *    - AddRoot(): 添加根节点
 *    - AppendItem(): 添加子节点
 *    - InsertItem(): 插入节点
 *    - DeleteItem(): 删除节点
 *    - Expand() / Collapse(): 展开/折叠
 *    - GetItemText(): 获取节点文本
 *    - ItemHasChildren(): 是否有子节点
 * 
 *    事件：
 *    - wxEVT_TREE_SEL_CHANGED: 选择改变
 *    - wxEVT_TREE_ITEM_ACTIVATED: 激活（双击）
 *    - wxEVT_TREE_ITEM_EXPANDING: 展开前
 * 
 * 练习：
 * 1. 实现列表的排序功能
 * 2. 添加树节点的编辑功能
 * 3. 实现虚拟列表（大量数据）
 * 4. 添加拖放功能
 * 5. 使用图标（wxImageList）
 */
