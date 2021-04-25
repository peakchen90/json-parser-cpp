//
// Created by chen on 2021/4/24.
//

#ifndef JSON_PARSER_CPP_TOKEN_H
#define JSON_PARSER_CPP_TOKEN_H


#include "env.h"
#include "util.h"

enum TokenType {
    BRACES_START = '{',
    BRACES_END = '}',
    BRACKETS_START = '[',
    BRACKETS_END = ']',
    SEPARATOR = ':',
    COMMA = ',',
    STRING,
    NUMBER,
    WORD,
    START_F,
    END_F,
};


class Token {
public:
    TokenType type;
    string value;
    int start;
    int end;

    Token();

    Token(TokenType type, string value);

    Token(TokenType type, string value, int start, int end);

    void setRange(int start, int end);

    void setCharRange(int start);

    string toString();
};


#endif //JSON_PARSER_CPP_TOKEN_H
