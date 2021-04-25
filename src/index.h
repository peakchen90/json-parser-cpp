//
// Created by chen on 2021/4/25.
//

#ifndef JSON_PARSER_CPP_INDEX_H
#define JSON_PARSER_CPP_INDEX_H


#include "env.h"
#include "node.h"

namespace json_parser {
    Node parse(string input);

    string stringify(Node &obj);
}


#endif //JSON_PARSER_CPP_INDEX_H
