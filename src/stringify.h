//
// Created by chen on 2021/4/25.
//

#ifndef JSON_PARSER_CPP_STRINGIFY_H
#define JSON_PARSER_CPP_STRINGIFY_H


#include "env.h"
#include "node.h"

namespace JSON {
    class Stringifier {
    private:
        int configIndent;
        int current = 0;

        int pushIndent();

        int popIndent();

        string getIndentStr() const;

    public:
        string stringify(Node &node, int indent = 0);
    };
}

#endif //JSON_PARSER_CPP_STRINGIFY_H
