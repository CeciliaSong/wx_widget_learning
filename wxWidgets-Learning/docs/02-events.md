# wxWidgets 事件处理系统

## 事件机制概述

wxWidgets 使用**事件驱动**架构。用户操作（点击按钮、输入文字等）会生成事件，应用程序通过**事件处理器**响应这些事件。

---

## 事件表（Event Tables）

### 传统方式：使用宏

```cpp
class MyFrame : public wxFrame {
public:
    MyFrame();
    
private:
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    
    wxDECLARE_EVENT_TABLE();  // 声明事件表
};

// 定义事件表
wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(ID_HELLO, MyFrame::OnHello)
    EVT_MENU(wxID_EXIT, MyFrame::OnExit)
    EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
wxEND_EVENT_TABLE()
```

---

## 动态绑定（推荐）

### 使用 Bind() 方法

```cpp
class MyFrame : public wxFrame {
public:
    MyFrame() : wxFrame(NULL, wxID_ANY, "示例") {
        wxButton* btn = new wxButton(this, wxID_ANY, "点击我");
        
        // 绑定事件
        btn->Bind(wxEVT_BUTTON, &MyFrame::OnButtonClick, this);
        
        // 也可以使用 lambda
        btn->Bind(wxEVT_BUTTON, [](wxCommandEvent& evt) {
            wxMessageBox("按钮被点击了！");
        });
    }
    
private:
    void OnButtonClick(wxCommandEvent& event) {
        wxMessageBox("按钮被点击了！");
    }
};
```

### Bind() vs 事件表

| 特性 | Bind() | 事件表 |
|------|--------|--------|
| 灵活性 | 高 - 可在运行时绑定/解绑 | 低 - 编译时固定 |
| 可读性 | 更清晰 | 需要分离声明和定义 |
| Lambda 支持 | ✓ | ✗ |
| 性能 | 稍慢 | 稍快 |
| 推荐程度 | ✓ 现代 C++ 推荐 | 传统方式 |

---

## 常用事件类型

### 命令事件（wxCommandEvent）

最常用的事件类型，用于按钮、菜单、文本框等。

```cpp
// 按钮点击
wxEVT_BUTTON

// 菜单选择
wxEVT_MENU

// 文本框
wxEVT_TEXT           // 文本改变
wxEVT_TEXT_ENTER     // 按下回车

// 复选框
wxEVT_CHECKBOX

// 单选按钮
wxEVT_RADIOBUTTON

// 列表框
wxEVT_LISTBOX
wxEVT_LISTBOX_DCLICK  // 双击
```

### 示例

```cpp
// 按钮
wxButton* btn = new wxButton(panel, wxID_ANY, "保存");
btn->Bind(wxEVT_BUTTON, &MyFrame::OnSave, this);

// 文本框
wxTextCtrl* text = new wxTextCtrl(panel, wxID_ANY);
text->Bind(wxEVT_TEXT, &MyFrame::OnTextChanged, this);

// 复选框
wxCheckBox* check = new wxCheckBox(panel, wxID_ANY, "启用");
check->Bind(wxEVT_CHECKBOX, &MyFrame::OnCheckBox, this);
```

---

## 窗口事件（wxEvent）

### 关闭事件

```cpp
class MyFrame : public wxFrame {
public:
    MyFrame() {
        Bind(wxEVT_CLOSE_WINDOW, &MyFrame::OnClose, this);
    }
    
private:
    void OnClose(wxCloseEvent& event) {
        // 询问用户是否确定关闭
        if (wxMessageBox("确定要退出吗?", "确认",
                        wxICON_QUESTION | wxYES_NO) == wxYES) {
            event.Skip();  // 继续关闭
        } else {
            event.Veto();  // 取消关闭
        }
    }
};
```

### 大小改变事件

```cpp
Bind(wxEVT_SIZE, &MyFrame::OnSize, this);

void MyFrame::OnSize(wxSizeEvent& event) {
    wxSize size = event.GetSize();
    wxLogMessage("窗口大小: %d x %d", size.x, size.y);
    event.Skip();  // 允许默认处理继续
}
```

---

## 鼠标事件（wxMouseEvent）

```cpp
wxPanel* panel = new wxPanel(this);
panel->Bind(wxEVT_LEFT_DOWN, &MyFrame::OnMouseLeftDown, this);
panel->Bind(wxEVT_LEFT_UP, &MyFrame::OnMouseLeftUp, this);
panel->Bind(wxEVT_MOTION, &MyFrame::OnMouseMove, this);
panel->Bind(wxEVT_RIGHT_DOWN, &MyFrame::OnMouseRightDown, this);

void MyFrame::OnMouseLeftDown(wxMouseEvent& event) {
    wxPoint pos = event.GetPosition();
    wxLogMessage("左键点击：(%d, %d)", pos.x, pos.y);
}

void MyFrame::OnMouseMove(wxMouseEvent& event) {
    if (event.Dragging() && event.LeftIsDown()) {
        // 正在拖动
        wxPoint pos = event.GetPosition();
        // 处理拖动
    }
}
```

### 常用鼠标事件

```cpp
wxEVT_LEFT_DOWN      // 左键按下
wxEVT_LEFT_UP        // 左键释放
wxEVT_LEFT_DCLICK    // 左键双击
wxEVT_RIGHT_DOWN     // 右键按下
wxEVT_MIDDLE_DOWN    // 中键按下
wxEVT_MOTION         // 鼠标移动
wxEVT_MOUSEWHEEL     // 鼠标滚轮
wxEVT_ENTER_WINDOW   // 进入窗口
wxEVT_LEAVE_WINDOW   // 离开窗口
```

---

## 键盘事件（wxKeyEvent）

```cpp
panel->Bind(wxEVT_KEY_DOWN, &MyFrame::OnKeyDown, this);
panel->Bind(wxEVT_CHAR, &MyFrame::OnChar, this);

void MyFrame::OnKeyDown(wxKeyEvent& event) {
    int keyCode = event.GetKeyCode();
    
    if (keyCode == WXK_ESCAPE) {
        Close();
    } else if (event.ControlDown() && keyCode == 'S') {
        // Ctrl+S
        Save();
    }
    
    event.Skip();  // 让其他处理器也能处理此事件
}

void MyFrame::OnChar(wxKeyEvent& event) {
    wxChar ch = event.GetUnicodeKey();
    wxLogMessage("字符: %c", ch);
}
```

### 键盘事件类型

```cpp
wxEVT_KEY_DOWN    // 键按下（原始键码）
wxEVT_KEY_UP      // 键释放
wxEVT_CHAR        // 字符输入（已处理的字符）
```

### 常用按键码

```cpp
WXK_BACK          // 退格
WXK_TAB           // Tab
WXK_RETURN        // 回车
WXK_ESCAPE        // ESC
WXK_SPACE         // 空格
WXK_DELETE        // Delete
WXK_HOME          // Home
WXK_END           // End
WXK_LEFT          // 左箭头
WXK_UP            // 上箭头
WXK_RIGHT         // 右箭头
WXK_DOWN          // 下箭头
WXK_F1 - WXK_F12  // 功能键
```

### 修饰键检测

```cpp
void OnKeyDown(wxKeyEvent& event) {
    if (event.ControlDown()) {
        // Ctrl 被按下
    }
    if (event.ShiftDown()) {
        // Shift 被按下
    }
    if (event.AltDown()) {
        // Alt 被按下
    }
}
```

---

## 事件处理顺序

```
1. 事件产生
   ↓
2. 发送给目标窗口
   ↓
3. 动态绑定的处理器（Bind）
   ↓
4. 事件表处理器
   ↓
5. 如果 event.Skip() 被调用，传递给父窗口
   ↓
6. 重复步骤 3-5 直到到达顶层窗口
   ↓
7. wxApp::OnEvent()
```

---

## event.Skip() 的重要性

```cpp
void OnSize(wxSizeEvent& event) {
    // 你的代码
    
    event.Skip();  // ← 重要！让默认处理继续
                   // 否则窗口可能无法正确调整大小
}
```

### 何时调用 Skip()

✅ **应该调用**：
- 大小调整、绘制等系统事件
- 希望父窗口也处理此事件
- 希望默认行为继续

❌ **不应该调用**：
- 你完全处理了此事件
- 不希望事件继续传播
- Close 事件中 Veto() 后

---

## 自定义事件

### 定义自定义事件类型

```cpp
// 声明事件类型
wxDECLARE_EVENT(wxEVT_MY_CUSTOM_EVENT, wxCommandEvent);

// 在 .cpp 文件中定义
wxDEFINE_EVENT(wxEVT_MY_CUSTOM_EVENT, wxCommandEvent);

// 使用
Bind(wxEVT_MY_CUSTOM_EVENT, &MyFrame::OnCustomEvent, this);

// 发送自定义事件
void MyFrame::TriggerCustomEvent() {
    wxCommandEvent event(wxEVT_MY_CUSTOM_EVENT, GetId());
    event.SetEventObject(this);
    ProcessWindowEvent(event);
}
```

---

## 事件传播示例

```cpp
class MyPanel : public wxPanel {
public:
    MyPanel(wxWindow* parent) : wxPanel(parent) {
        Bind(wxEVT_LEFT_DOWN, &MyPanel::OnClick, this);
    }
    
private:
    void OnClick(wxMouseEvent& event) {
        wxLogMessage("Panel 收到点击");
        event.Skip();  // 传递给父窗口
    }
};

class MyFrame : public wxFrame {
public:
    MyFrame() : wxFrame(NULL, wxID_ANY, "示例") {
        MyPanel* panel = new MyPanel(this);
        panel->Bind(wxEVT_LEFT_DOWN, &MyFrame::OnClick, this);
    }
    
private:
    void OnClick(wxMouseEvent& event) {
        wxLogMessage("Frame 收到点击");
    }
};

// 结果：点击 Panel 时，两个处理器都会被调用
```

---

## 事件过滤器（Event Filters）

```cpp
class MyEventFilter : public wxEventFilter {
public:
    virtual int FilterEvent(wxEvent& event) override {
        if (event.GetEventType() == wxEVT_KEY_DOWN) {
            wxKeyEvent& keyEvent = (wxKeyEvent&)event;
            if (keyEvent.GetKeyCode() == WXK_ESCAPE) {
                // 拦截所有 ESC 键
                return Event_Processed;
            }
        }
        return Event_Skip;
    }
};

// 使用
MyEventFilter* filter = new MyEventFilter();
wxEvtHandler::AddFilter(filter);
```

---

## 最佳实践

1. **优先使用 Bind()**：更现代、更灵活
2. **总是调用 event.Skip()**：除非你确定要阻止事件传播
3. **使用正确的事件类型**：wxCommandEvent、wxMouseEvent 等
4. **注意内存管理**：不要在事件处理器中 delete 发送事件的窗口
5. **避免在事件处理器中显示模态对话框**：可能导致重入问题

---

## 调试事件

```cpp
// 记录所有事件
void OnAnyEvent(wxEvent& event) {
    wxLogMessage("事件类型: %d", event.GetEventType());
    event.Skip();
}

// 绑定到所有事件
Bind(wxEVT_ANY, &MyFrame::OnAnyEvent, this);
```

---

## 下一步

学习 [布局管理](03-layouts.md)，了解如何自动排列控件。
