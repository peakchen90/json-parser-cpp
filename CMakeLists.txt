cmake_minimum_required(VERSION 3.2)
project(json_parser_cpp)

set(CMAKE_CXX_STANDARD 14)

# test
add_executable(
    json_parser_test
    src/test.cpp
    src/parser.cpp
    src/node.cpp
    src/token.cpp
    src/util.cpp
    src/stringify.cpp
    src/walk.cpp
)

# build
add_executable(
    json_parser
    src/cli.cpp
    src/parser.cpp
    src/node.cpp
    src/token.cpp
    src/util.cpp
    src/stringify.cpp
    src/walk.cpp
)

