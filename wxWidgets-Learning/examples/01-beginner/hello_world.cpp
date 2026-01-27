#include <wx/wx.h>

class MyApp : public wxApp 
{
public:
    virtual bool OnInit();
};

// ============================================
// 主窗口类
// ============================================
class MyFrame : public wxFrame {
public:
    MyFrame();

private:
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
};

// ============================================
// 实现应用程序类
// ============================================
bool MyApp::OnInit() {
    // 创建主窗口
    MyFrame* frame = new MyFrame();
    
    // 显示窗口
    frame->Show(true);
    
    // 返回 true 表示继续运行
    return true;
}

// ============================================
// 实现主窗口类
// ============================================

// 为菜单项定义 ID
enum {
    ID_HELLO = 1
};

MyFrame::MyFrame()
    : wxFrame(NULL, wxID_ANY, "Hello World - wxWidgets First Program") {
    
    // 设置窗口大小
    SetSize(wxSize(450, 350));
    
    // 居中显示
    Centre();
    
    // ----- 创建菜单栏 -----
    wxMenu* menuFile = new wxMenu;
    menuFile->Append(ID_HELLO, "&Hello...\tCtrl-H",
                    "Show greeting message");
    menuFile->AppendSeparator();  // 分隔线
    menuFile->Append(wxID_EXIT, "E&xit\tAlt-F4",
                    "Quit this application");
    
    wxMenu* menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT, "&About\tF1",
                    "About this program");
    
    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
    
    SetMenuBar(menuBar);
    
    // ----- 创建状态栏 -----
    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");
    
    // ----- 绑定事件 -----
    Bind(wxEVT_MENU, &MyFrame::OnHello, this, ID_HELLO);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
}

void MyFrame::OnHello(wxCommandEvent& event) {
    wxMessageBox("This is a wxWidgets Hello World example!\n\n"
                "Congratulations on running your first wxWidgets program.",
                "Hello",
                wxOK | wxICON_INFORMATION);
}

void MyFrame::OnExit(wxCommandEvent& event) {
    // 关闭窗口
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& event) {
    wxString message = wxString::Format(
        "This is a program written with wxWidgets cross-platform GUI framework.\n\n"
        "wxWidgets version: %s\n"
        "Platform: %s",
        wxVERSION_STRING,
        wxPlatformInfo::Get().GetOperatingSystemIdName()
    );
    
    wxMessageBox(message, "About Hello World", wxOK | wxICON_INFORMATION);
}

// ============================================
// 程序入口
// ============================================
wxIMPLEMENT_APP(MyApp);

/*
 * 代码说明：
 * 
 * 1. MyApp::OnInit()
 *    - 应用程序启动时调用
 *    - 在这里创建主窗口并显示
 *    - 返回 true 继续运行，false 退出
 * 
 * 2. MyFrame 构造函数
 *    - 设置窗口标题、大小
 *    - 创建菜单栏和状态栏
 *    - 绑定事件处理器
 * 
 * 3. 事件处理器
 *    - OnHello: 显示欢迎消息
 *    - OnExit: 关闭应用
 *    - OnAbout: 显示关于信息
 * 
 * 4. wxIMPLEMENT_APP(MyApp)
 *    - 创建应用程序实例
 *    - 生成 main() 函数
 *    - 启动事件循环
 * 
 * 练习建议：
 * 1. 修改窗口标题和大小
 * 2. 添加更多菜单项
 * 3. 修改消息框的内容和图标
 * 4. 尝试修改窗口样式（wxDEFAULT_FRAME_STYLE）
 */
