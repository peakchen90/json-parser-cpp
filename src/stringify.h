//
// Created by chen on 2021/4/25.
//

#ifndef JSON_PARSER_CPP_STRINGIFY_H
#define JSON_PARSER_CPP_STRINGIFY_H


#include "env.h"
#include "node.h"

class Stringifier {
private:
    int currentIndent;

    int pushIndent();

    int popIndent();

    string getIndentStr();

public:
    int indent;

    Stringifier(int indent = 0);

    string stringify(Node &node);
};


#endif //JSON_PARSER_CPP_STRINGIFY_H
