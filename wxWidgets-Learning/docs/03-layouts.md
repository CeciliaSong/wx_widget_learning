# wxWidgets 布局管理

## 为什么需要 Sizers（布局器）

**不使用 Sizers 的问题**：
- 手动计算每个控件的位置和大小
- 窗口大小改变时控件不会自动调整
- 不同平台上的外观不一致
- 代码难以维护

**使用 Sizers 的优势**：
- 自动计算位置和大小
- 响应窗口大小变化
- 跨平台一致性
- 代码简洁易维护

---

## wxBoxSizer - 盒子布局

最常用的布局器，沿水平或垂直方向排列控件。

### 基本用法

```cpp
// 创建垂直盒子布局
wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

// 添加控件
wxButton* btn1 = new wxButton(panel, wxID_ANY, "按钮1");
wxButton* btn2 = new wxButton(panel, wxID_ANY, "按钮2");

vbox->Add(btn1, 0, wxALL, 5);  // 不拉伸，边距 5
vbox->Add(btn2, 0, wxALL, 5);

// 应用布局
panel->SetSizer(vbox);
```

### 参数说明

```cpp
Add(window, proportion, flags, border)
```

- **proportion**：拉伸比例
  - `0`：不拉伸，使用最小尺寸
  - `1, 2, 3...`：按比例拉伸
  
- **flags**：对齐和边距标志
  - **扩展**：`wxEXPAND`（填充可用空间）
  - **对齐**：`wxALIGN_CENTER`, `wxALIGN_LEFT`, `wxALIGN_RIGHT`, `wxALIGN_TOP`, `wxALIGN_BOTTOM`
  - **边距**：`wxALL`, `wxTOP`, `wxBOTTOM`, `wxLEFT`, `wxRIGHT`
  
- **border**：边距大小（像素）

### 方向

```cpp
wxBoxSizer* hbox = new wxBoxSizer(wxHORIZONTAL);  // 水平
wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);    // 垂直
```

---

## 拉伸比例（Proportion）

```cpp
wxBoxSizer* vbox = new wxBoxSizer(wxVERTICAL);

wxButton* btn1 = new wxButton(panel, wxID_ANY, "固定大小");
wxButton* btn2 = new wxButton(panel, wxID_ANY, "拉伸 1");
wxButton* btn3 = new wxButton(panel, wxID_ANY, "拉伸 2");

vbox->Add(btn1, 0, wxEXPAND);  // 不拉伸
vbox->Add(btn2, 1, wxEXPAND);  // 拉伸比例 1
vbox->Add(btn3, 2, wxEXPAND);  // 拉伸比例 2（是 btn2 的两倍）

panel->SetSizer(vbox);
```

---

## 标志（Flags）组合

```cpp
// 所有边都有 10 像素边距
vbox->Add(btn, 0, wxALL, 10);

// 左右边距 5 像素
vbox->Add(btn, 0, wxLEFT | wxRIGHT, 5);

// 居中对齐，上下边距 5 像素
vbox->Add(btn, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 5);

// 填充可用空间，所有边距 5 像素
vbox->Add(btn, 1, wxEXPAND | wxALL, 5);
```

---

## wxGridSizer - 网格布局

所有单元格大小相同的网格。

```cpp
// 3 行 2 列，行间距 5，列间距 5
wxGridSizer* grid = new wxGridSizer(3, 2, 5, 5);

grid->Add(new wxButton(panel, wxID_ANY, "1"));
grid->Add(new wxButton(panel, wxID_ANY, "2"));
grid->Add(new wxButton(panel, wxID_ANY, "3"));
grid->Add(new wxButton(panel, wxID_ANY, "4"));
grid->Add(new wxButton(panel, wxID_ANY, "5"));
grid->Add(new wxButton(panel, wxID_ANY, "6"));

panel->SetSizer(grid);
```

### 构造函数

```cpp
wxGridSizer(rows, cols, vgap, hgap)
wxGridSizer(cols, vgap, hgap)  // 行数自动计算
```

---

## wxFlexGridSizer - 弹性网格布局

单元格大小可以不同，并且可以设置哪些行/列可拉伸。

```cpp
// 2 列
wxFlexGridSizer* flex = new wxFlexGridSizer(2, 5, 5);

// 添加标签和输入框
flex->Add(new wxStaticText(panel, wxID_ANY, "姓名:"),
         0, wxALIGN_CENTER_VERTICAL);
flex->Add(new wxTextCtrl(panel, wxID_ANY),
         1, wxEXPAND);

flex->Add(new wxStaticText(panel, wxID_ANY, "邮箱:"),
         0, wxALIGN_CENTER_VERTICAL);
flex->Add(new wxTextCtrl(panel, wxID_ANY),
         1, wxEXPAND);

// 设置第二列可拉伸
flex->AddGrowableCol(1, 1);

panel->SetSizer(flex);
```

### 设置可拉伸的行/列

```cpp
flex->AddGrowableRow(0, 1);    // 第 0 行可拉伸
flex->AddGrowableCol(1, 1);    // 第 1 列可拉伸
flex->AddGrowableCol(2, 2);    // 第 2 列可拉伸（比例为 2）
```

---

## wxStaticBoxSizer - 带边框的布局

带有标题边框的布局器。

```cpp
// 创建垂直的静态盒子
wxStaticBoxSizer* box = new wxStaticBoxSizer(wxVERTICAL, panel, "选项");

box->Add(new wxCheckBox(panel, wxID_ANY, "选项 1"), 0, wxALL, 5);
box->Add(new wxCheckBox(panel, wxID_ANY, "选项 2"), 0, wxALL, 5);
box->Add(new wxCheckBox(panel, wxID_ANY, "选项 3"), 0, wxALL, 5);

panel->SetSizer(box);
```

---

## 嵌套布局

复杂界面通常需要嵌套多个布局器。

```cpp
// 主垂直布局
wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

// 顶部水平布局
wxBoxSizer* topSizer = new wxBoxSizer(wxHORIZONTAL);
topSizer->Add(new wxButton(panel, wxID_ANY, "新建"), 0, wxALL, 5);
topSizer->Add(new wxButton(panel, wxID_ANY, "打开"), 0, wxALL, 5);
topSizer->Add(new wxButton(panel, wxID_ANY, "保存"), 0, wxALL, 5);

// 中间内容区域
wxTextCtrl* text = new wxTextCtrl(panel, wxID_ANY, "",
                                  wxDefaultPosition, wxDefaultSize,
                                  wxTE_MULTILINE);

// 底部水平布局
wxBoxSizer* bottomSizer = new wxBoxSizer(wxHORIZONTAL);
bottomSizer->Add(new wxButton(panel, wxID_OK, "确定"), 0, wxALL, 5);
bottomSizer->Add(new wxButton(panel, wxID_CANCEL, "取消"), 0, wxALL, 5);

// 组合
mainSizer->Add(topSizer, 0, wxEXPAND);
mainSizer->Add(text, 1, wxEXPAND | wxALL, 5);
mainSizer->Add(bottomSizer, 0, wxALIGN_RIGHT);

panel->SetSizer(mainSizer);
```

---

## 常见布局模式

### 1. 表单布局

```cpp
wxFlexGridSizer* formSizer = new wxFlexGridSizer(2, 10, 10);
formSizer->AddGrowableCol(1, 1);

// 姓名
formSizer->Add(new wxStaticText(panel, wxID_ANY, "姓名:"),
              0, wxALIGN_CENTER_VERTICAL);
formSizer->Add(new wxTextCtrl(panel, wxID_ANY), 1, wxEXPAND);

// 年龄
formSizer->Add(new wxStaticText(panel, wxID_ANY, "年龄:"),
              0, wxALIGN_CENTER_VERTICAL);
formSizer->Add(new wxSpinCtrl(panel, wxID_ANY), 1, wxEXPAND);

// 性别
formSizer->Add(new wxStaticText(panel, wxID_ANY, "性别:"),
              0, wxALIGN_CENTER_VERTICAL);
wxString choices[] = { "男", "女" };
formSizer->Add(new wxChoice(panel, wxID_ANY, wxDefaultPosition,
                           wxDefaultSize, 2, choices), 1, wxEXPAND);
```

### 2. 工具栏 + 内容 + 状态栏

```cpp
wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);

// 工具栏
wxBoxSizer* toolbarSizer = new wxBoxSizer(wxHORIZONTAL);
toolbarSizer->Add(new wxButton(panel, wxID_ANY, "工具1"), 0, wxALL, 2);
toolbarSizer->Add(new wxButton(panel, wxID_ANY, "工具2"), 0, wxALL, 2);

// 内容区域
wxTextCtrl* content = new wxTextCtrl(panel, wxID_ANY, "",
                                     wxDefaultPosition, wxDefaultSize,
                                     wxTE_MULTILINE);

// 状态栏
wxStaticText* status = new wxStaticText(panel, wxID_ANY, "就绪");

mainSizer->Add(toolbarSizer, 0, wxEXPAND);
mainSizer->Add(content, 1, wxEXPAND | wxALL, 5);
mainSizer->Add(status, 0, wxEXPAND | wxALL, 5);
```

### 3. 左右分栏

```cpp
wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);

// 左侧面板
wxPanel* leftPanel = new wxPanel(panel);
wxBoxSizer* leftSizer = new wxBoxSizer(wxVERTICAL);
leftSizer->Add(new wxStaticText(leftPanel, wxID_ANY, "导航"), 0, wxALL, 5);
leftSizer->Add(new wxListBox(leftPanel, wxID_ANY), 1, wxEXPAND | wxALL, 5);
leftPanel->SetSizer(leftSizer);

// 右侧面板
wxPanel* rightPanel = new wxPanel(panel);
wxBoxSizer* rightSizer = new wxBoxSizer(wxVERTICAL);
rightSizer->Add(new wxStaticText(rightPanel, wxID_ANY, "内容"), 0, wxALL, 5);
rightSizer->Add(new wxTextCtrl(rightPanel, wxID_ANY, "",
                              wxDefaultPosition, wxDefaultSize,
                              wxTE_MULTILINE), 1, wxEXPAND | wxALL, 5);
rightPanel->SetSizer(rightSizer);

// 组合（左侧固定宽度，右侧可拉伸）
mainSizer->Add(leftPanel, 0, wxEXPAND);
mainSizer->Add(rightPanel, 1, wxEXPAND);
```

---

## 间隔器（Spacers）

添加空白空间。

```cpp
wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);

sizer->Add(new wxButton(panel, wxID_ANY, "左"), 0, wxALL, 5);
sizer->AddStretchSpacer(1);  // 弹性空间
sizer->Add(new wxButton(panel, wxID_ANY, "右"), 0, wxALL, 5);
```

### 间隔器类型

```cpp
// 固定大小的空间
sizer->AddSpacer(10);  // 10 像素空间

// 弹性空间
sizer->AddStretchSpacer(1);  // 拉伸比例为 1

// 手动添加空间
sizer->Add(10, 10);  // 10x10 像素的空间
sizer->Add(0, 0, 1);  // 弹性空间（等同于 AddStretchSpacer）
```

---

## 动态布局调整

### 显示/隐藏控件

```cpp
void MyFrame::ToggleControl() {
    // 隐藏/显示控件
    myButton->Show(!myButton->IsShown());
    
    // 更新布局
    Layout();
}
```

### 添加/删除控件

```cpp
void MyFrame::AddControl() {
    wxButton* newBtn = new wxButton(panel, wxID_ANY, "新按钮");
    mySizer->Add(newBtn, 0, wxALL, 5);
    
    // 重新计算布局
    mySizer->Layout();
    panel->Refresh();
}

void MyFrame::RemoveControl(wxWindow* window) {
    // 从布局器中移除
    mySizer->Detach(window);
    
    // 销毁窗口
    window->Destroy();
    
    // 更新布局
    mySizer->Layout();
    panel->Refresh();
}
```

---

## 设置最小/最大尺寸

```cpp
// 设置控件最小尺寸
myButton->SetMinSize(wxSize(100, 30));

// 设置窗口最小尺寸
SetMinSize(wxSize(400, 300));

// 设置窗口最大尺寸
SetMaxSize(wxSize(800, 600));
```

---

## 调试布局

```cpp
// 显示布局器的边界（调试用）
#ifdef __WXDEBUG__
    sizer->ShowItems(true);
#endif

// 获取布局信息
wxSize minSize = sizer->GetMinSize();
wxLogMessage("最小尺寸: %d x %d", minSize.x, minSize.y);
```

---

## 布局最佳实践

1. **总是使用 Sizers**：不要手动设置控件位置
2. **合理使用 proportion**：
   - 固定大小的控件用 `0`
   - 需要拉伸的控件用 `1` 或更大
3. **适当的边距**：
   - 常用 5、10 像素
   - 保持一致性
4. **使用 wxEXPAND**：让控件填充可用空间
5. **嵌套布局**：复杂布局用嵌套的 Sizers
6. **调用 Layout()**：动态修改后需要调用
7. **SetSizerAndFit()**：自动调整窗口到最佳大小

```cpp
panel->SetSizerAndFit(sizer);  // 设置布局并调整窗口大小
```

---

## 常见错误

### ❌ 忘记设置 Sizer

```cpp
wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
sizer->Add(button);
// 忘记: panel->SetSizer(sizer);
```

### ❌ proportion 和 wxEXPAND 混淆

```cpp
// 错误：想要拉伸但没有 wxEXPAND
sizer->Add(button, 1, wxALL, 5);

// 正确
sizer->Add(button, 1, wxEXPAND | wxALL, 5);
```

### ❌ 在栈上创建 Sizer

```cpp
// 错误：Sizer 会被自动删除
wxBoxSizer sizer(wxVERTICAL);
panel->SetSizer(&sizer);  // 危险！

// 正确：在堆上创建
wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
panel->SetSizer(sizer);
```

---

## wxWrapSizer - 自动换行布局

控件会自动换行，类似 HTML 的流式布局。

```cpp
wxWrapSizer* wrapSizer = new wxWrapSizer(wxHORIZONTAL);

for (int i = 0; i < 20; i++) {
    wxButton* btn = new wxButton(panel, wxID_ANY,
                                 wxString::Format("按钮 %d", i));
    wrapSizer->Add(btn, 0, wxALL, 2);
}

panel->SetSizer(wrapSizer);
// 窗口缩小时，按钮会自动换行
```

---

## 下一步

学习 [高级主题](04-advanced.md)，了解自定义绘制、多线程等内容。
