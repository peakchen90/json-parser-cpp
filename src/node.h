//
// Created by chen on 2021/4/23.
//

#ifndef JSON_PARSER_CPP_NODE_H
#define JSON_PARSER_CPP_NODE_H


#include "env.h"
#include "util.h"

namespace NodeType {
    const string ObjectProperty = "ObjectProperty";
    const string ObjectExpression = "ObjectExpression";
    const string ArrayExpression = "ArrayExpression";
    const string StringLiteral = "StringLiteral";
    const string NumericLiteral = "NumericLiteral";
    const string BooleanLiteral = "BooleanLiteral";
    const string NullLiteral = "NullLiteral";
    const string Root = "Root";
}

class Node {
public:
    string type;
    int start;
    int end;
    void *key;
    void *value;
    void *properties;
    void *elements;
    void *body;

    string toString();
};

class ObjectProperty : public Node {
public:
    string key;
    Node value;

    ObjectProperty(string key, Node value);

    // string toString() override;
};

class ObjectExpression : public Node {
public:
    ObjectProperty *properties;

    ObjectExpression(ObjectProperty *properties);

    // string toString() override;
};

class ArrayExpression : public Node {
public:
    Node *elements;

    ArrayExpression(Node *elements);

    // string toString() override;
};

class StringLiteral : public Node {
public:
    string value;

    StringLiteral(string value);

    // string toString() override;
};

class NumericLiteral : public Node {
public:
    double value;

    NumericLiteral(double value);

    // string toString() override;
};

class BooleanLiteral : public Node {
public:
    bool value;

    BooleanLiteral(bool value);

    // string toString() override;
};

class NullLiteral : public Node {
public:
    NullLiteral();

    // string toString() override;
};

class Root : public Node {
public:
    Node body;

    Root(Node body);

    // string toString() override;
};


#endif //JSON_PARSER_CPP_NODE_H
