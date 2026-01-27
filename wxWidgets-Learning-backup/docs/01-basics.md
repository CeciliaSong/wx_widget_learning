# wxWidgets 基础知识

## 核心概念

### 1. 应用程序架构

wxWidgets 应用程序遵循以下基本结构：

```cpp
#include <wx/wx.h>

// 应用程序类 - 继承自 wxApp
class MyApp : public wxApp {
public:
    virtual bool OnInit();  // 应用程序初始化
};

// 主窗口类 - 继承自 wxFrame
class MyFrame : public wxFrame {
public:
    MyFrame();
};

// 实现宏 - 创建应用程序实例
wxIMPLEMENT_APP(MyApp);
```

### 2. 关键类说明

#### wxApp - 应用程序类

- 每个 wxWidgets 应用必须有一个 wxApp 派生类
- `OnInit()` 方法是应用程序入口点
- `wxIMPLEMENT_APP` 宏创建应用实例和 main() 函数

#### wxFrame - 主窗口类

- 表示顶层窗口（带标题栏、边框、菜单栏）
- 是其他控件的容器
- 可以设置菜单、工具栏、状态栏

#### wxPanel - 面板类

- 用作其他控件的容器
- 提供 TAB 键导航
- 通常作为 wxFrame 的子窗口

---

## 窗口层次结构

```
wxApp (应用程序)
  └── wxFrame (主窗口)
        ├── wxMenuBar (菜单栏)
        ├── wxToolBar (工具栏)
        ├── wxPanel (面板)
        │     ├── wxButton (按钮)
        │     ├── wxTextCtrl (文本框)
        │     └── wxStaticText (标签)
        └── wxStatusBar (状态栏)
```

---

## 坐标系统

### 窗口坐标

- 原点 (0, 0) 在窗口左上角
- X 轴向右递增
- Y 轴向下递增
- 单位是像素

### 窗口尺寸

```cpp
// 创建窗口时指定位置和大小
wxFrame* frame = new wxFrame(NULL, wxID_ANY, "标题",
                            wxPoint(100, 100),    // 位置 (x, y)
                            wxSize(800, 600));    // 大小 (宽, 高)

// 使用默认值
wxFrame* frame = new wxFrame(NULL, wxID_ANY, "标题",
                            wxDefaultPosition,
                            wxDefaultSize);
```

---

## 窗口样式

窗口样式通过构造函数的 style 参数指定：

```cpp
// wxFrame 常用样式
wxDEFAULT_FRAME_STYLE    // 默认样式（标题栏、边框、最小化、最大化、关闭按钮）
wxCAPTION                // 标题栏
wxMINIMIZE_BOX           // 最小化按钮
wxMAXIMIZE_BOX           // 最大化按钮
wxCLOSE_BOX              // 关闭按钮
wxRESIZE_BORDER          // 可调整大小
wxSTAY_ON_TOP            // 总在最前

// 组合样式
wxFrame* frame = new wxFrame(NULL, wxID_ANY, "标题",
                            wxDefaultPosition, wxDefaultSize,
                            wxDEFAULT_FRAME_STYLE & ~wxRESIZE_BORDER);  // 不可调整大小
```

---

## ID 系统

wxWidgets 使用 ID 来标识窗口和菜单项：

```cpp
// 预定义 ID
wxID_ANY        // 自动分配 ID
wxID_OK         // 确定按钮
wxID_CANCEL     // 取消按钮
wxID_EXIT       // 退出
wxID_ABOUT      // 关于

// 自定义 ID
enum {
    ID_HELLO = 1,
    ID_SAVE = 2
};
```

---

## 字符串类型

wxWidgets 使用 `wxString` 类处理字符串：

```cpp
wxString str1 = "Hello";
wxString str2 = wxT("World");  // wxT 宏确保跨平台兼容

// 转换
std::string stdStr = str1.ToStdString();
const char* cStr = str1.c_str();

// 格式化
wxString formatted = wxString::Format("数字：%d", 42);
```

---

## 内存管理

### 重要规则

1. **窗口自动管理**：
   - 子窗口由父窗口自动删除
   - 不要手动 delete 窗口，除非你用 `new` 创建且没有父窗口

2. **正确的创建方式**：
   ```cpp
   // ✓ 正确 - 有父窗口
   wxButton* btn = new wxButton(parent, wxID_OK, "确定");
   // parent 销毁时会自动删除 btn

   // ✗ 错误 - 会造成内存泄漏
   wxButton* btn = new wxButton(NULL, wxID_OK, "确定");
   ```

3. **智能指针**：
   - 一般不需要使用智能指针管理窗口
   - 窗口系统有自己的管理机制

---

## 显示窗口

```cpp
bool MyApp::OnInit() {
    MyFrame* frame = new MyFrame();
    frame->Show(true);  // 显示窗口
    return true;        // 返回 true 继续运行
}
```

---

## 应用程序生命周期

```
启动
  ↓
wxApp::OnInit()  ← 创建主窗口
  ↓
进入事件循环
  ↓
处理用户交互
  ↓
关闭主窗口
  ↓
wxApp::OnExit()  ← 清理资源
  ↓
结束
```

---

## 常见控件 ID 命名约定

```cpp
enum {
    // 菜单 ID
    ID_MENU_NEW = wxID_HIGHEST + 1,
    ID_MENU_OPEN,
    ID_MENU_SAVE,
    
    // 按钮 ID
    ID_BUTTON_ADD,
    ID_BUTTON_DELETE,
    
    // 文本框 ID
    ID_TEXT_NAME,
    ID_TEXT_EMAIL
};
```

---

## 调试技巧

```cpp
// 输出调试信息
wxLogMessage("调试信息：%s", someString);
wxLogError("错误信息");
wxLogWarning("警告信息");

// 断言
wxASSERT(condition);
wxASSERT_MSG(condition, "错误消息");
```

---

## 下一步

学习 [事件处理机制](02-events.md)，了解如何响应用户操作。
