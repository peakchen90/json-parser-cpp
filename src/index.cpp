//
// Created by chen on 2021/4/25.
//

#include "index.h"
#include "parser.h"
#include "stringify.h"

Node json_parser::parse(string input) {
    Parser parser(input);
    return parser.parse();
}

string json_parser::stringify(Node &obj) {
    return nodeStringify(obj);
}
