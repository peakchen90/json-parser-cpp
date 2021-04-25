//
// Created by chen on 2021/4/23.
//

#ifndef JSON_PARSER_CPP_NODE_H
#define JSON_PARSER_CPP_NODE_H


#include "env.h"
#include "util.h"

namespace NodeType {
    const string Root = "Root";
    const string ObjectExpression = "ObjectExpression";
    const string ObjectProperty = "ObjectProperty";
    const string ArrayExpression = "ArrayExpression";
    const string StringLiteral = "StringLiteral";
    const string NumericLiteral = "NumericLiteral";
    const string BooleanLiteral = "BooleanLiteral";
    const string NullLiteral = "NullLiteral";
}

class Node {
public:
    string type;
    int start;
    int end;

    bool bValue;
    string sValue;
    double dValue;

    // 子节点信息
    // properties、elements 作为数组使用
    // key、value 分别取第 0 1 个元素
    // 其他类型取第 0 个元素
    vector<Node> children;

    Node();

    Node(string type);

    Node(string type, string value);

    Node(string type, double value);

    Node(string type, bool value);

    Node(string type, vector<Node> children);

    string toString();
};


#endif //JSON_PARSER_CPP_NODE_H
