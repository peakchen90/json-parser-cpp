//
// Created by chen on 2021/4/23.
//

#ifndef JSON_PARSER_CPP_PARSER_H
#define JSON_PARSER_CPP_PARSER_H


#include "env.h"
#include "token.h"
#include "node.h"

class Parser {
protected:
    int length;
    int pos;
    Token currentToken;
    Token lastToken;
    int start;
    int end;

    Node parseNode();

    Node parseObjectExpression();

    Node parseArrayExpression();

    void next();

    Token readToken();

    Token readStringToken();

    Token readNumberToken();

    Token readWordToken();

    Node startNode(int pos);

    Node finishNode(Node &node);

    int getCodeAt(int index);

    void skipSpace();

    bool isValidPos() const;

    void expect(TokenType type);

    void unexpected(Token token);

public:
    const string input;
    Node ast;

    Parser(string input);

    ~Parser();

    Node parse();
};


#endif //JSON_PARSER_CPP_PARSER_H
