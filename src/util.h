//
// Created by chen on 2021/4/23.
//

#ifndef JSON_PARSER_CPP_UTIL_H
#define JSON_PARSER_CPP_UTIL_H


#include "env.h"

namespace JSON {

    bool isNumberChar(int code);

    bool isWordChar(int code);

    bool stringEquals(string a, string b);

    string stringEscape(string str, char ch);

    string strIndent(int width, char prefix = 0);

    int getStringBytesAt(string &str, int pos);

    string getStringAt(string &str, int pos);

    int getStringIndexAt(string &str, int pos);

    unsigned int getCodePointAt(string &str, int index = 0);

    string readFile(const string &path);

    void writeFile(string &path, string &data);

    string getCWD();

    string resolvePath(string &path);

    struct Position {
        int line;
        int column;
    };

    Position getPosition(string &source, int pos);
}

#endif //JSON_PARSER_CPP_UTIL_H
