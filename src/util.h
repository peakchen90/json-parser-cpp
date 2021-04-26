//
// Created by chen on 2021/4/23.
//

#ifndef JSON_PARSER_CPP_UTIL_H
#define JSON_PARSER_CPP_UTIL_H


#include "env.h"

namespace JSON {

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

    string stringEscape(string str, char ch);

    string strIndent(int width, char prefix = 0);

    string readFile(const string &path);

    void writeFile(string &path, string &data);

    string getCWD();

    string resolvePath(string &path);
}

#endif //JSON_PARSER_CPP_UTIL_H
