//
// Created by chen on 2021/4/24.
//

#include "token.h"

namespace JSON {

    Token::Token() {}

    Token::Token(TokenType type, string value) : type(type), value(value) {
    }

    Token::Token(TokenType type, string value, int start, int end) : type(type), value(value), start(start), end(end) {
    }

    void Token::setRange(int start, int end) {
        this->start = start;
        this->end = end;
    }

    string Token::toString() {
        return "Token:" + value + "(" + to_string(start) + "," + to_string(end) + ")";
    }

}