cmake_minimum_required(VERSION 3.10)
project(json_parser_cpp)

set(CMAKE_CXX_STANDARD 14)

# test
add_executable(
    json_test
    src/test.cpp
    src/parser.cpp
    src/util.cpp
    src/stringify.cpp
    src/walk.cpp
)

# cli
add_executable(
    json
    src/cli.cpp
    src/parser.cpp
    src/util.cpp
    src/stringify.cpp
    src/walk.cpp
)

