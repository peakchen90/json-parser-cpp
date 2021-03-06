//
// Created by chen on 2021/4/23.
//

#ifndef JSON_PARSER_CPP_PARSER_H
#define JSON_PARSER_CPP_PARSER_H


#include "env.h"
#include "token.h"
#include "node.h"

namespace JSON {

    enum TokenTypeName {
        TYPE_STRING,
        TYPE_NUMBER
    };

    class Parser {
    protected:
        int length;
        int pos = 0;
        Token currentToken;
        Token lastToken;

        Node parseNode();

        Node parseObjectExpression();

        Node parseArrayExpression();

        void next();

        Token readToken();

        Token readStringToken();

        Token readNumberToken();

        Token readWordToken();

        int getCodeAt(int index);

        void skipSpace();

        void skipLineComment();

        void skipBlockComment();

        bool isValidPos() const;

        void expect(TokenType type);

        void checkEndOfUnexpected(int pos) const;

        void unexpected(Token &token);

        void unexpected(int pos);

        void unexpected(TokenTypeName name, int pos);

    public:
        const string input;
        Node ast;

        explicit Parser(const string &input);

        ~Parser();

        Node &parse();
    };

}

#endif //JSON_PARSER_CPP_PARSER_H
