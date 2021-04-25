#! /bin/bash

# 生成配置
cmake -S . -B build

# 编译构建
cmake --build build -- -j 6
