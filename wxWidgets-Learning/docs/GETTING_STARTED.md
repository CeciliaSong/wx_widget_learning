# 快速开始指南

## 安装 wxWidgets

### Linux (Ubuntu/Debian)

```bash
sudo apt-get update
sudo apt-get install libwxgtk3.0-gtk3-dev build-essential
```

验证安装：
```bash
wx-config --version
```

### macOS

```bash
brew install wxwidgets
```

### Windows

1. 下载预编译库：https://www.wxwidgets.org/downloads/
2. 或使用 vcpkg：
   ```
   vcpkg install wxwidgets
   ```

---

## 编译和运行示例

### 方法 1：使用提供的脚本

```bash
cd wxWidgets-Learning

# 编译 Hello World
./build.sh examples/01-beginner/hello_world.cpp

# 运行
./hello_world
```

### 方法 2：手动编译

```bash
g++ -o hello_world examples/01-beginner/hello_world.cpp \
    `wx-config --cxxflags --libs`
    
./hello_world
```

### 方法 3：使用 CMake

```bash
mkdir build
cd build
cmake ..
make

# 运行任意示例
./hello_world
./basic_controls
./dialogs
```

---

## 学习路径

### 第 1 周：基础入门

1. **阅读**：[README.md](../README.md) - 了解 wxWidgets 的背景和优势
2. **阅读**：[docs/01-basics.md](01-basics.md) - 学习核心概念
3. **实践**：编译运行 [hello_world.cpp](../examples/01-beginner/hello_world.cpp)
4. **练习**：修改窗口标题、大小，添加更多菜单项

### 第 2 周：控件和事件

1. **阅读**：[docs/02-events.md](02-events.md) - 掌握事件处理
2. **实践**：运行 [basic_controls.cpp](../examples/01-beginner/basic_controls.cpp)
3. **实践**：运行 [menus.cpp](../examples/01-beginner/menus.cpp)
4. **练习**：创建一个简单的计算器应用

### 第 3 周：布局和对话框

1. **阅读**：[docs/03-layouts.md](03-layouts.md) - 学习布局管理
2. **实践**：运行 [dialogs.cpp](../examples/02-intermediate/dialogs.cpp)
3. **实践**：运行 [list_tree.cpp](../examples/02-intermediate/list_tree.cpp)
4. **练习**：创建一个设置对话框

### 第 4 周：高级特性

1. **阅读**：[docs/04-advanced.md](04-advanced.md) - 探索高级主题
2. **实践**：运行 [custom_draw.cpp](../examples/03-advanced/custom_draw.cpp)
3. **实践**：运行 [text_editor.cpp](../examples/03-advanced/text_editor.cpp)
4. **项目**：开始你自己的 wxWidgets 项目

---

## 示例说明

### 入门级（examples/01-beginner/）

| 文件 | 说明 | 关键知识点 |
|------|------|-----------|
| hello_world.cpp | 最基本的窗口应用 | wxApp, wxFrame, 菜单栏 |
| basic_controls.cpp | 常用控件展示 | 按钮、文本框、复选框、下拉框 |
| menus.cpp | 菜单和工具栏 | 菜单、工具栏、状态栏、快捷键 |

### 中级（examples/02-intermediate/）

| 文件 | 说明 | 关键知识点 |
|------|------|-----------|
| dialogs.cpp | 各种对话框 | 文件对话框、颜色选择、自定义对话框 |
| list_tree.cpp | 列表和树控件 | wxListCtrl, wxTreeCtrl |

### 高级（examples/03-advanced/）

| 文件 | 说明 | 关键知识点 |
|------|------|-----------|
| custom_draw.cpp | 自定义绘制 | wxDC, 绘图、渐变 |
| text_editor.cpp | 完整的文本编辑器 | 文件操作、查找替换、综合应用 |

---

## 常见问题

### Q: 编译时找不到 wx-config？

**A:** 确保已安装 wxWidgets 开发包，并且在 PATH 中。

### Q: 运行时报错 "cannot open display"？

**A:** Linux 上需要 X11 环境。如果使用 SSH，需要启用 X11 转发：
```bash
ssh -X user@host
```

### Q: 如何创建自己的项目？

**A:** 复制任意示例文件作为起点，然后修改：
```bash
cp examples/01-beginner/hello_world.cpp my_app.cpp
# 编辑 my_app.cpp
./build.sh my_app.cpp
```

### Q: 如何调试？

**A:** 使用 gdb 或 IDE：
```bash
g++ -g -o hello_world hello_world.cpp `wx-config --cxxflags --libs`
gdb ./hello_world
```

---

## 推荐工具

1. **wxFormBuilder**：可视化 GUI 设计工具
   - https://github.com/wxFormBuilder/wxFormBuilder
   
2. **Code::Blocks**：集成 wxWidgets 支持的 IDE
   - https://www.codeblocks.org/

3. **VS Code**：配合 C++ 插件
   - 安装 C/C++ 扩展
   - 配置 tasks.json 使用 wx-config

---

## 获取帮助

1. **官方文档**：https://docs.wxwidgets.org/
2. **官方论坛**：https://forums.wxwidgets.org/
3. **Stack Overflow**：标签 [wxwidgets]
4. **GitHub Issues**：https://github.com/wxWidgets/wxWidgets/issues

---

## 下一步

- 尝试修改示例代码
- 阅读详细教程文档
- 开始你的第一个项目
- 参考官方文档深入学习

祝学习愉快！🚀
