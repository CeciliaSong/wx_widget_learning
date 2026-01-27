#!/bin/bash

# wxWidgets 项目编译脚本
# 用法: ./build.sh <source_file> [output_name]

set -e  # 遇到错误立即退出

# 颜色输出
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# 检查参数
if [ $# -eq 0 ]; then
    echo -e "${RED}错误: 请提供源文件路径${NC}"
    echo "用法: $0 <source_file> [output_name]"
    echo ""
    echo "示例:"
    echo "  $0 examples/01-beginner/hello_world.cpp"
    echo "  $0 examples/01-beginner/hello_world.cpp my_program"
    exit 1
fi

SOURCE_FILE=$1

# 检查源文件是否存在
if [ ! -f "$SOURCE_FILE" ]; then
    echo -e "${RED}错误: 文件不存在: $SOURCE_FILE${NC}"
    exit 1
fi

# 检查 wx-config 是否可用
if ! command -v wx-config &> /dev/null; then
    echo -e "${RED}错误: wx-config 未找到${NC}"
    echo "请先安装 wxWidgets 开发库："
    echo ""
    echo "Ubuntu/Debian:"
    echo "  sudo apt-get install libwxgtk3.0-gtk3-dev"
    echo ""
    echo "macOS:"
    echo "  brew install wxwidgets"
    exit 1
fi

# 确定输出文件名
if [ $# -eq 2 ]; then
    OUTPUT_NAME=$2
else
    # 从源文件名提取（去掉路径和扩展名）
    OUTPUT_NAME=$(basename "$SOURCE_FILE" .cpp)
fi

echo -e "${YELLOW}=====================================${NC}"
echo -e "${YELLOW}wxWidgets 项目编译${NC}"
echo -e "${YELLOW}=====================================${NC}"
echo ""
echo "源文件: $SOURCE_FILE"
echo "输出: $OUTPUT_NAME"
echo "wxWidgets 版本: $(wx-config --version)"
echo ""

# 编译
echo -e "${GREEN}正在编译...${NC}"

g++ -std=c++11 \
    -o "$OUTPUT_NAME" \
    "$SOURCE_FILE" \
    $(wx-config --cxxflags --libs) \
    -Wall

if [ $? -eq 0 ]; then
    echo ""
    echo -e "${GREEN}✓ 编译成功！${NC}"
    echo ""
    echo "运行程序:"
    echo "  ./$OUTPUT_NAME"
    echo ""
else
    echo ""
    echo -e "${RED}✗ 编译失败${NC}"
    exit 1
fi
