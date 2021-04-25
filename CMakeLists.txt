cmake_minimum_required(VERSION 3.2)
project(json_parser_cpp)

set(CMAKE_CXX_STANDARD 14)

add_executable(
    json_parser_cpp
    src/test.cpp
    src/parser.cpp
    src/node.cpp
    src/token.cpp
    src/util.cpp
#    src/stringify.cpp
)

