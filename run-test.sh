#! /bin/bash

# 生成配置
cmake -S . -B build

# 编译构建
cmake --build build --target json_parser_test -- -j 6

echo ""
echo "============================== 开始执行 =============================="
echo ""

# 执行
