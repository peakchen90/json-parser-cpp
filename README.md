# json-parser-cpp
使用 C++ 实现一个 JSON AST 解析器

## 环境
- [cmake](https://cmake.org/)

## 安装并执行测试
```bash
./run-test.sh
```

## TODO
- [√] 节点位置信息
- [-] 异常处理（含中文字符的位置不准确）
- [√] JSON 注释支持
- [√] 命令行参数
- JSON 转 C++ 数据结构（反射）