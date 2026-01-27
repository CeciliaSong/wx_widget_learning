/*
 * wxWidgets 自定义绘制示例
 * 
 * 展示：
 * - 使用 wxDC 绘制图形
 * - 自定义控件绘制
 * - 处理绘制事件
 * - 绘制线条、矩形、圆形、文本等
 * 
 * 编译：g++ -o custom_draw custom_draw.cpp `wx-config --cxxflags --libs`
 */

#include <wx/wx.h>
#include <wx/dcbuffer.h>
#include <cmath>
#include <vector>

// 自定义绘制面板
class DrawPanel : public wxPanel {
public:
    DrawPanel(wxWindow* parent);

private:
    std::vector<wxPoint> m_points;  // 存储鼠标轨迹点
    wxPoint m_currentPos;
    bool m_drawing;
    int m_drawMode;  // 0=自由绘制, 1=矩形, 2=圆形, 3=直线
    
    void OnPaint(wxPaintEvent& event);
    void OnMouseDown(wxMouseEvent& event);
    void OnMouseMove(wxMouseEvent& event);
    void OnMouseUp(wxMouseEvent& event);
    void OnEraseBackground(wxEraseEvent& event);
    
    void DrawBackground(wxDC& dc);
    void DrawGrid(wxDC& dc);
    
public:
    void SetDrawMode(int mode) { m_drawMode = mode; }
    void Clear() { m_points.clear(); Refresh(); }
};

class MyApp : public wxApp {
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame {
public:
    MyFrame();

private:
    DrawPanel* m_drawPanel;
    wxSlider* m_sizeSlider;
    wxColourPickerCtrl* m_colorPicker;
    int m_penSize;
    wxColour m_penColor;
    
    void OnDrawMode(wxCommandEvent& event);
    void OnClear(wxCommandEvent& event);
    void OnSizeChanged(wxCommandEvent& event);
    void OnColorChanged(wxColourPickerEvent& event);
    
    enum {
        ID_MODE_FREE = 1,
        ID_MODE_RECT,
        ID_MODE_CIRCLE,
        ID_MODE_LINE,
        ID_CLEAR,
        ID_SIZE_SLIDER
    };
};

// ==================== DrawPanel 实现 ====================

DrawPanel::DrawPanel(wxWindow* parent)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE),
      m_drawing(false), m_drawMode(0) {
    
    SetBackgroundStyle(wxBG_STYLE_PAINT);  // 避免闪烁
    
    Bind(wxEVT_PAINT, &DrawPanel::OnPaint, this);
    Bind(wxEVT_LEFT_DOWN, &DrawPanel::OnMouseDown, this);
    Bind(wxEVT_MOTION, &DrawPanel::OnMouseMove, this);
    Bind(wxEVT_LEFT_UP, &DrawPanel::OnMouseUp, this);
    Bind(wxEVT_ERASE_BACKGROUND, &DrawPanel::OnEraseBackground, this);
}

void DrawPanel::OnEraseBackground(wxEraseEvent& event) {
    // 不做任何事，避免闪烁
}

void DrawPanel::OnPaint(wxPaintEvent& event) {
    wxAutoBufferedPaintDC dc(this);  // 使用双缓冲避免闪烁
    dc.Clear();
    
    DrawBackground(dc);
    DrawGrid(dc);
    
    // 绘制已保存的点
    if (m_points.size() > 1) {
        dc.SetPen(wxPen(wxColour(0, 0, 255), 2));
        
        for (size_t i = 1; i < m_points.size(); i++) {
            dc.DrawLine(m_points[i-1], m_points[i]);
        }
    }
}

void DrawPanel::DrawBackground(wxDC& dc) {
    wxSize size = GetClientSize();
    
    // 渐变背景
    dc.GradientFillLinear(wxRect(0, 0, size.x, size.y),
                         wxColour(250, 250, 255),
                         wxColour(220, 220, 240),
                         wxSOUTH);
}

void DrawPanel::DrawGrid(wxDC& dc) {
    wxSize size = GetClientSize();
    dc.SetPen(wxPen(wxColour(200, 200, 200), 1, wxPENSTYLE_DOT));
    
    // 绘制网格
    for (int x = 0; x < size.x; x += 50) {
        dc.DrawLine(x, 0, x, size.y);
    }
    for (int y = 0; y < size.y; y += 50) {
        dc.DrawLine(0, y, size.x, y);
    }
}

void DrawPanel::OnMouseDown(wxMouseEvent& event) {
    m_drawing = true;
    m_currentPos = event.GetPosition();
    m_points.push_back(m_currentPos);
    CaptureMouse();
}

void DrawPanel::OnMouseMove(wxMouseEvent& event) {
    if (m_drawing && event.Dragging()) {
        wxPoint pos = event.GetPosition();
        m_points.push_back(pos);
        m_currentPos = pos;
        Refresh();
    }
}

void DrawPanel::OnMouseUp(wxMouseEvent& event) {
    if (m_drawing) {
        m_drawing = false;
        ReleaseMouse();
    }
}

// ==================== MyApp 实现 ====================

bool MyApp::OnInit() {
    MyFrame* frame = new MyFrame();
    frame->Show(true);
    return true;
}

// ==================== MyFrame 实现 ====================

MyFrame::MyFrame()
    : wxFrame(NULL, wxID_ANY, "自定义绘制示例", wxDefaultPosition, wxSize(900, 700)),
      m_penSize(2), m_penColor(*wxBLACK) {
    
    wxPanel* panel = new wxPanel(this);
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    
    // ==================== 工具栏 ====================
    wxStaticBoxSizer* toolBox = new wxStaticBoxSizer(wxHORIZONTAL, panel, "工具");
    
    // 绘制模式
    wxRadioButton* radioFree = new wxRadioButton(panel, ID_MODE_FREE, "自由绘制",
                                                wxDefaultPosition, wxDefaultSize, wxRB_GROUP);
    wxRadioButton* radioRect = new wxRadioButton(panel, ID_MODE_RECT, "矩形");
    wxRadioButton* radioCircle = new wxRadioButton(panel, ID_MODE_CIRCLE, "圆形");
    wxRadioButton* radioLine = new wxRadioButton(panel, ID_MODE_LINE, "直线");
    radioFree->SetValue(true);
    
    toolBox->Add(radioFree, 0, wxALL, 5);
    toolBox->Add(radioRect, 0, wxALL, 5);
    toolBox->Add(radioCircle, 0, wxALL, 5);
    toolBox->Add(radioLine, 0, wxALL, 5);
    toolBox->AddSpacer(20);
    
    // 画笔大小
    toolBox->Add(new wxStaticText(panel, wxID_ANY, "大小:"),
                0, wxALIGN_CENTER_VERTICAL | wxLEFT, 10);
    m_sizeSlider = new wxSlider(panel, ID_SIZE_SLIDER, 2, 1, 20,
                               wxDefaultPosition, wxSize(100, -1));
    toolBox->Add(m_sizeSlider, 0, wxALIGN_CENTER_VERTICAL | wxLEFT | wxRIGHT, 5);
    
    // 颜色选择
    toolBox->Add(new wxStaticText(panel, wxID_ANY, "颜色:"),
                0, wxALIGN_CENTER_VERTICAL | wxLEFT, 10);
    m_colorPicker = new wxColourPickerCtrl(panel, wxID_ANY, *wxBLACK);
    toolBox->Add(m_colorPicker, 0, wxALL, 5);
    
    toolBox->AddStretchSpacer(1);
    
    // 清空按钮
    wxButton* btnClear = new wxButton(panel, ID_CLEAR, "清空画布");
    toolBox->Add(btnClear, 0, wxALL, 5);
    
    mainSizer->Add(toolBox, 0, wxEXPAND | wxALL, 5);
    
    // ==================== 绘制区域 ====================
    m_drawPanel = new DrawPanel(panel);
    mainSizer->Add(m_drawPanel, 1, wxEXPAND | wxALL, 5);
    
    // ==================== 示例绘制区 ====================
    wxStaticBoxSizer* exampleBox = new wxStaticBoxSizer(wxHORIZONTAL, panel, "绘制示例");
    
    // 创建示例面板
    wxPanel* example1 = new wxPanel(panel, wxID_ANY, wxDefaultPosition, wxSize(150, 100));
    example1->Bind(wxEVT_PAINT, [](wxPaintEvent& evt) {
        wxPaintDC dc((wxPanel*)evt.GetEventObject());
        
        // 绘制渐变矩形
        dc.GradientFillLinear(wxRect(10, 10, 130, 80),
                             wxColour(255, 100, 100),
                             wxColour(100, 100, 255),
                             wxEAST);
        
        dc.SetTextForeground(*wxWHITE);
        dc.DrawText("渐变", 60, 40);
    });
    
    wxPanel* example2 = new wxPanel(panel, wxID_ANY, wxDefaultPosition, wxSize(150, 100));
    example2->Bind(wxEVT_PAINT, [](wxPaintEvent& evt) {
        wxPaintDC dc((wxPanel*)evt.GetEventObject());
        
        // 绘制圆形和线条
        dc.SetPen(wxPen(*wxBLUE, 3));
        dc.SetBrush(*wxCYAN_BRUSH);
        dc.DrawCircle(wxPoint(75, 50), 30);
        
        dc.SetPen(wxPen(*wxRED, 2));
        dc.DrawLine(10, 10, 140, 90);
        dc.DrawLine(140, 10, 10, 90);
    });
    
    wxPanel* example3 = new wxPanel(panel, wxID_ANY, wxDefaultPosition, wxSize(150, 100));
    example3->Bind(wxEVT_PAINT, [](wxPaintEvent& evt) {
        wxPaintDC dc((wxPanel*)evt.GetEventObject());
        
        // 绘制多边形
        wxPoint points[] = {
            wxPoint(75, 10),
            wxPoint(140, 50),
            wxPoint(110, 90),
            wxPoint(40, 90),
            wxPoint(10, 50)
        };
        
        dc.SetPen(wxPen(*wxBLACK, 2));
        dc.SetBrush(wxBrush(wxColour(255, 200, 100)));
        dc.DrawPolygon(5, points);
        
        dc.SetTextForeground(*wxBLACK);
        dc.DrawText("五角星", 55, 45);
    });
    
    wxPanel* example4 = new wxPanel(panel, wxID_ANY, wxDefaultPosition, wxSize(150, 100));
    example4->Bind(wxEVT_PAINT, [](wxPaintEvent& evt) {
        wxPaintDC dc((wxPanel*)evt.GetEventObject());
        
        // 绘制贝塞尔曲线
        dc.SetPen(wxPen(wxColour(0, 150, 0), 3));
        
        wxPoint start(10, 90);
        wxPoint control1(10, 10);
        wxPoint control2(140, 10);
        wxPoint end(140, 90);
        
        // 手动绘制贝塞尔曲线
        for (double t = 0; t <= 1.0; t += 0.01) {
            double mt = 1.0 - t;
            double mt2 = mt * mt;
            double mt3 = mt2 * mt;
            double t2 = t * t;
            double t3 = t2 * t;
            
            int x = mt3 * start.x + 3 * mt2 * t * control1.x +
                   3 * mt * t2 * control2.x + t3 * end.x;
            int y = mt3 * start.y + 3 * mt2 * t * control1.y +
                   3 * mt * t2 * control2.y + t3 * end.y;
            
            dc.DrawPoint(x, y);
        }
        
        dc.SetTextForeground(*wxBLACK);
        dc.DrawText("曲线", 60, 45);
    });
    
    exampleBox->Add(example1, 0, wxALL, 5);
    exampleBox->Add(example2, 0, wxALL, 5);
    exampleBox->Add(example3, 0, wxALL, 5);
    exampleBox->Add(example4, 0, wxALL, 5);
    
    mainSizer->Add(exampleBox, 0, wxEXPAND | wxALL, 5);
    
    panel->SetSizer(mainSizer);
    
    // ==================== 绑定事件 ====================
    Bind(wxEVT_RADIOBUTTON, &MyFrame::OnDrawMode, this, ID_MODE_FREE);
    Bind(wxEVT_RADIOBUTTON, &MyFrame::OnDrawMode, this, ID_MODE_RECT);
    Bind(wxEVT_RADIOBUTTON, &MyFrame::OnDrawMode, this, ID_MODE_CIRCLE);
    Bind(wxEVT_RADIOBUTTON, &MyFrame::OnDrawMode, this, ID_MODE_LINE);
    Bind(wxEVT_BUTTON, &MyFrame::OnClear, this, ID_CLEAR);
    Bind(wxEVT_SLIDER, &MyFrame::OnSizeChanged, this, ID_SIZE_SLIDER);
    m_colorPicker->Bind(wxEVT_COLOURPICKER_CHANGED, &MyFrame::OnColorChanged, this);
    
    Centre();
}

void MyFrame::OnDrawMode(wxCommandEvent& event) {
    int mode = 0;
    switch (event.GetId()) {
        case ID_MODE_FREE: mode = 0; break;
        case ID_MODE_RECT: mode = 1; break;
        case ID_MODE_CIRCLE: mode = 2; break;
        case ID_MODE_LINE: mode = 3; break;
    }
    m_drawPanel->SetDrawMode(mode);
}

void MyFrame::OnClear(wxCommandEvent& event) {
    m_drawPanel->Clear();
}

void MyFrame::OnSizeChanged(wxCommandEvent& event) {
    m_penSize = m_sizeSlider->GetValue();
}

void MyFrame::OnColorChanged(wxColourPickerEvent& event) {
    m_penColor = event.GetColour();
}

wxIMPLEMENT_APP(MyApp);

/*
 * 绘制说明：
 * 
 * 1. wxDC (Device Context) - 设备上下文
 *    所有绘制操作都通过 DC 进行：
 *    - wxPaintDC: 用于 OnPaint 事件
 *    - wxClientDC: 用于即时绘制
 *    - wxBufferedDC: 双缓冲绘制（避免闪烁）
 *    - wxMemoryDC: 内存绘制
 * 
 * 2. 绘制函数
 *    - DrawLine(x1, y1, x2, y2): 直线
 *    - DrawRectangle(x, y, w, h): 矩形
 *    - DrawCircle(center, radius): 圆形
 *    - DrawEllipse(x, y, w, h): 椭圆
 *    - DrawPolygon(n, points): 多边形
 *    - DrawText(text, x, y): 文本
 *    - DrawBitmap(bitmap, x, y): 位图
 * 
 * 3. 画笔和画刷
 *    - SetPen(pen): 设置画笔（线条）
 *    - SetBrush(brush): 设置画刷（填充）
 *    - SetFont(font): 设置字体
 *    - SetTextForeground(color): 文本颜色
 * 
 * 4. 避免闪烁
 *    - 使用 wxAutoBufferedPaintDC
 *    - SetBackgroundStyle(wxBG_STYLE_PAINT)
 *    - 不在 OnEraseBackground 中绘制
 * 
 * 5. 坐标系统
 *    - 默认：左上角 (0,0)，向右向下递增
 *    - SetDeviceOrigin(): 改变原点
 *    - SetUserScale(): 缩放
 * 
 * 6. 渐变填充
 *    - GradientFillLinear(): 线性渐变
 *    - GradientFillConcentric(): 径向渐变
 * 
 * 练习：
 * 1. 实现矩形、圆形、直线绘制模式
 * 2. 添加橡皮擦功能
 * 3. 实现撤销/重做
 * 4. 保存绘制结果为图片
 * 5. 添加更多绘制工具（文本、箭头等）
 */
