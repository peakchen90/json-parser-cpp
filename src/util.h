//
// Created by chen on 2021/4/23.
//

#ifndef JSON_PARSER_CPP_UTIL_H
#define JSON_PARSER_CPP_UTIL_H


#include "env.h"

//struct Position {
//    int line;
//    int column;
//};
//
//struct Location {
//    Position start;
//    Position end;
//};

//Location getLocation(int startLine, int startColumn, int endLine, int endColumn);

bool isNumberChar(int code);

bool isWordChar(int code);

bool stringEquals(string a, string b);


#endif //JSON_PARSER_CPP_UTIL_H