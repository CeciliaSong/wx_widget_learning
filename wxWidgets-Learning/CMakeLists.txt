cmake_minimum_required(VERSION 3.10)
project(wxWidgets-Learning)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找 wxWidgets
find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

# 创建可执行文件的函数
function(add_wx_executable target_name source_file)
    add_executable(${target_name} ${source_file})
    target_link_libraries(${target_name} ${wxWidgets_LIBRARIES})
endfunction()

# 入门示例
add_wx_executable(hello_world examples/01-beginner/hello_world.cpp)
add_wx_executable(basic_controls examples/01-beginner/basic_controls.cpp)
add_wx_executable(menus examples/01-beginner/menus.cpp)

# 中级示例
add_wx_executable(dialogs examples/02-intermediate/dialogs.cpp)
add_wx_executable(list_tree examples/02-intermediate/list_tree.cpp)

# 高级示例
add_wx_executable(custom_draw examples/03-advanced/custom_draw.cpp)
add_wx_executable(text_editor examples/03-advanced/text_editor.cpp)

# 打印配置信息
message(STATUS "wxWidgets found: ${wxWidgets_FOUND}")
message(STATUS "wxWidgets version: ${wxWidgets_VERSION}")
message(STATUS "wxWidgets libraries: ${wxWidgets_LIBRARIES}")
