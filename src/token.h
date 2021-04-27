//
// Created by chen on 2021/4/24.
//

#ifndef JSON_PARSER_CPP_TOKEN_H
#define JSON_PARSER_CPP_TOKEN_H


#include "env.h"
#include "util.h"

namespace JSON {

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

        Token() {}

        Token(TokenType type, string value) : type(type), value(value) {
        }

        Token(TokenType type, string value, int start, int end) : type(type), value(value), start(start), end(end) {
        }

        void setRange(int start, int end) {
            this->start = start;
            this->end = end;
        }

        string toString() {
            return "Token:" + value + "(" + to_string(start) + "," + to_string(end) + ")";
        }
    };

}


#endif //JSON_PARSER_CPP_TOKEN_H
