# wxWidgets 高级主题

## 多线程编程

### wxThread 类

wxWidgets 提供了跨平台的线程支持：

```cpp
class MyThread : public wxThread {
public:
    MyThread(wxFrame* handler) 
        : wxThread(wxTHREAD_DETACHED), m_handler(handler) {}
    
protected:
    virtual ExitCode Entry() {
        // 线程主函数
        for (int i = 0; i < 100; i++) {
            // 执行耗时操作
            wxThread::Sleep(100);
            
            // 通知 GUI 线程
            wxThreadEvent event(wxEVT_THREAD, wxID_ANY);
            event.SetInt(i);
            wxQueueEvent(m_handler, event.Clone());
            
            // 检查是否需要退出
            if (TestDestroy()) {
                break;
            }
        }
        return (ExitCode)0;
    }
    
private:
    wxFrame* m_handler;
};
```

### 线程安全的 GUI 更新

```cpp
class MyFrame : public wxFrame {
public:
    MyFrame() {
        Bind(wxEVT_THREAD, &MyFrame::OnThreadUpdate, this);
        
        // 启动线程
        MyThread* thread = new MyThread(this);
        thread->Run();
    }
    
private:
    void OnThreadUpdate(wxThreadEvent& event) {
        // 在主线程中更新 GUI
        int progress = event.GetInt();
        m_gauge->SetValue(progress);
    }
};
```

### 关键原则

1. **不要在工作线程中直接操作 GUI**
2. **使用事件通信**：工作线程 → 主线程
3. **使用临界区保护共享数据**

---

## 文档/视图架构

### 概念

- **Document**：应用程序的数据
- **View**：数据的可视化表示
- 一个文档可以有多个视图

### 示例

```cpp
class MyDocument : public wxDocument {
public:
    virtual bool OnSaveDocument(const wxString& filename);
    virtual bool OnOpenDocument(const wxString& filename);
    
    void SetData(const wxString& data) { m_data = data; }
    wxString GetData() const { return m_data; }
    
private:
    wxString m_data;
    wxDECLARE_DYNAMIC_CLASS(MyDocument);
};

class MyView : public wxView {
public:
    virtual void OnDraw(wxDC* dc);
    virtual bool OnCreate(wxDocument* doc, long flags);
    
private:
    wxDECLARE_DYNAMIC_CLASS(MyView);
};
```

---

## 拖放（Drag & Drop）

### 文件拖放

```cpp
class FileDropTarget : public wxFileDropTarget {
public:
    FileDropTarget(wxTextCtrl* owner) : m_owner(owner) {}
    
    virtual bool OnDropFiles(wxCoord x, wxCoord y,
                            const wxArrayString& filenames) {
        for (size_t i = 0; i < filenames.GetCount(); i++) {
            m_owner->AppendText(filenames[i] + "\n");
        }
        return true;
    }
    
private:
    wxTextCtrl* m_owner;
};

// 使用
m_textCtrl->SetDropTarget(new FileDropTarget(m_textCtrl));
```

### 文本拖放

```cpp
class TextDropTarget : public wxTextDropTarget {
public:
    virtual bool OnDropText(wxCoord x, wxCoord y, const wxString& data) {
        wxLogMessage("Dropped text: %s", data);
        return true;
    }
};
```

---

## 图像处理

### 加载和显示图像

```cpp
wxImage image;
if (image.LoadFile("photo.jpg", wxBITMAP_TYPE_JPEG)) {
    // 缩放
    image = image.Scale(200, 200);
    
    // 转换为位图
    wxBitmap bitmap(image);
    
    // 显示
    wxStaticBitmap* staticBitmap = new wxStaticBitmap(panel, wxID_ANY, bitmap);
}
```

### 图像处理

```cpp
// 转换为灰度
wxImage gray = image.ConvertToGreyscale();

// 旋转
wxImage rotated = image.Rotate(45 * M_PI / 180, wxPoint(0, 0));

// 镜像
wxImage mirrored = image.Mirror(false);  // 水平镜像

// 调整大小
wxImage resized = image.Rescale(300, 300, wxIMAGE_QUALITY_HIGH);
```

---

## 网络编程

### wxSocket

```cpp
// 客户端
wxSocketClient* socket = new wxSocketClient();
wxIPV4address addr;
addr.Hostname("example.com");
addr.Service(80);

socket->Connect(addr);
if (socket->IsConnected()) {
    wxString request = "GET / HTTP/1.1\r\nHost: example.com\r\n\r\n";
    socket->Write(request.c_str(), request.Length());
    
    char buffer[1024];
    socket->Read(buffer, sizeof(buffer));
    // 处理响应
}
```

### HTTP 请求

可以使用 wxHTTP 或第三方库如 libcurl。

---

## 国际化（i18n）

### 使用 wxLocale

```cpp
class MyApp : public wxApp {
public:
    virtual bool OnInit() {
        // 初始化语言
        m_locale.Init(wxLANGUAGE_CHINESE_SIMPLIFIED);
        m_locale.AddCatalog("myapp");
        
        // ...
        return true;
    }
    
private:
    wxLocale m_locale;
};
```

### 标记可翻译字符串

```cpp
// 使用 _() 宏
wxString msg = _("Hello, World!");

// 使用 wxGetTranslation()
wxString text = wxGetTranslation("File");
```

### 创建翻译文件

1. 提取字符串：`xgettext -C --keyword=_ *.cpp -o messages.pot`
2. 创建语言文件：`msginit -l zh_CN -o zh_CN.po`
3. 翻译 .po 文件
4. 编译：`msgfmt zh_CN.po -o zh_CN.mo`

---

## 数据库访问

wxWidgets 本身不提供数据库功能，可以使用：

### SQLite

```cpp
#include <sqlite3.h>

sqlite3* db;
int rc = sqlite3_open("test.db", &db);

if (rc == SQLITE_OK) {
    const char* sql = "SELECT * FROM users";
    sqlite3_stmt* stmt;
    
    sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const char* name = (const char*)sqlite3_column_text(stmt, 1);
        // 处理数据
    }
    
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
```

---

## XML/JSON 处理

### wxXmlDocument

```cpp
wxXmlDocument doc;
if (doc.Load("data.xml")) {
    wxXmlNode* root = doc.GetRoot();
    
    wxXmlNode* child = root->GetChildren();
    while (child) {
        if (child->GetName() == "item") {
            wxString value = child->GetNodeContent();
            // 处理数据
        }
        child = child->GetNext();
    }
}
```

### JSON（使用第三方库）

推荐使用 nlohmann/json 或 RapidJSON。

---

## 打印支持

### wxPrintout

```cpp
class MyPrintout : public wxPrintout {
public:
    virtual bool OnPrintPage(int page) {
        wxDC* dc = GetDC();
        if (!dc) return false;
        
        // 绘制内容
        dc->DrawText("Hello, Printer!", 100, 100);
        
        return true;
    }
    
    virtual bool HasPage(int page) {
        return page == 1;
    }
};

// 使用
void MyFrame::OnPrint() {
    wxPrinter printer;
    MyPrintout printout("My Document");
    printer.Print(this, &printout, true);
}
```

---

## 配置管理

### wxConfig

```cpp
// 保存配置
wxConfig* config = new wxConfig("MyApp");
config->Write("Window/Width", 800);
config->Write("Window/Height", 600);
config->Write("User/Name", "张三");

// 读取配置
int width = config->Read("Window/Width", 640);  // 默认 640
wxString name = config->Read("User/Name", "");
```

---

## 剪贴板操作

### 复制文本到剪贴板

```cpp
if (wxTheClipboard->Open()) {
    wxTheClipboard->SetData(new wxTextDataObject("Hello, Clipboard!"));
    wxTheClipboard->Close();
}
```

### 从剪贴板获取文本

```cpp
if (wxTheClipboard->Open()) {
    if (wxTheClipboard->IsSupported(wxDF_TEXT)) {
        wxTextDataObject data;
        wxTheClipboard->GetData(data);
        wxString text = data.GetText();
    }
    wxTheClipboard->Close();
}
```

---

## 定时器

### wxTimer

```cpp
class MyFrame : public wxFrame {
public:
    MyFrame() : m_timer(this, ID_TIMER) {
        Bind(wxEVT_TIMER, &MyFrame::OnTimer, this, ID_TIMER);
        m_timer.Start(1000);  // 每秒触发一次
    }
    
private:
    void OnTimer(wxTimerEvent& event) {
        // 定时任务
        wxLogMessage("Timer tick");
    }
    
    wxTimer m_timer;
};
```

---

## 最佳实践总结

1. **内存管理**：让父窗口管理子窗口的内存
2. **事件处理**：优先使用 Bind() 而不是事件表
3. **布局管理**：始终使用 Sizers
4. **线程安全**：不在工作线程中操作 GUI
5. **错误处理**：检查返回值，使用 wxLogError
6. **国际化**：从一开始就使用 _() 宏
7. **配置保存**：使用 wxConfig 保存用户设置
8. **代码组织**：将复杂功能拆分到单独的类

---

## 推荐阅读

- **wxWidgets 官方文档**：https://docs.wxwidgets.org/
- **wxWiki**：https://wiki.wxwidgets.org/
- **《Cross-Platform GUI Programming with wxWidgets》**
- **GitHub 示例项目**：研究开源项目的代码

---

## 进阶项目建议

1. **图像查看器**：支持缩放、旋转、幻灯片
2. **音乐播放器**：使用 wxMediaCtrl
3. **文件管理器**：树形目录、文件操作
4. **聊天应用**：wxSocket + 多线程
5. **绘图工具**：自定义绘制 + 工具栏
6. **数据管理系统**：数据库 + 表格显示
7. **游戏**：2D 游戏引擎

通过实践这些项目，你将深入掌握 wxWidgets 的各个方面！
