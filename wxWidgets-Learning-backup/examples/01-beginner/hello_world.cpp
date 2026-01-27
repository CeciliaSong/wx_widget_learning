/*
 * wxWidgets 第一个程序 - Hello World
 * 
 * 这个程序展示了 wxWidgets 应用的基本结构：
 * 1. 创建应用程序类（继承 wxApp）
 * 2. 创建主窗口类（继承 wxFrame）
 * 3. 使用 wxIMPLEMENT_APP 宏启动应用
 * 
 * 编译命令：
 * g++ -o hello_world hello_world.cpp `wx-config --cxxflags --libs`
 * 
 * 运行：
 * ./hello_world
 */

#include <wx/wx.h>

// ============================================
// 应用程序类
// ============================================
class MyApp : public wxApp {
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
    : wxFrame(NULL, wxID_ANY, "Hello World - wxWidgets 第一个程序") {
    
    // 设置窗口大小
    SetSize(wxSize(450, 350));
    
    // 居中显示
    Centre();
    
    // ----- 创建菜单栏 -----
    wxMenu* menuFile = new wxMenu;
    menuFile->Append(ID_HELLO, "&Hello...\tCtrl-H",
                    "显示问候消息");
    menuFile->AppendSeparator();  // 分隔线
    menuFile->Append(wxID_EXIT, "退出(&X)\tAlt-F4",
                    "退出应用程序");
    
    wxMenu* menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT, "关于(&A)\tF1",
                    "关于这个程序");
    
    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "文件(&F)");
    menuBar->Append(menuHelp, "帮助(&H)");
    
    SetMenuBar(menuBar);
    
    // ----- 创建状态栏 -----
    CreateStatusBar();
    SetStatusText("欢迎使用 wxWidgets！");
    
    // ----- 绑定事件 -----
    Bind(wxEVT_MENU, &MyFrame::OnHello, this, ID_HELLO);
    Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_MENU, &MyFrame::OnAbout, this, wxID_ABOUT);
}

void MyFrame::OnHello(wxCommandEvent& event) {
    wxMessageBox("这是一个 wxWidgets Hello World 示例！\n\n"
                "恭喜你成功运行了第一个 wxWidgets 程序。",
                "Hello",
                wxOK | wxICON_INFORMATION);
}

void MyFrame::OnExit(wxCommandEvent& event) {
    // 关闭窗口
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& event) {
    wxMessageBox("这是一个使用 wxWidgets 跨平台 GUI 框架编写的程序。\n\n"
                "wxWidgets 版本: " + wxVERSION_STRING + "\n"
                "平台: " + wxPlatformInfo::Get().GetOperatingSystemIdName(),
                "关于 Hello World",
                wxOK | wxICON_INFORMATION);
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
