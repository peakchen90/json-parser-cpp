//
// Created by chen on 2021/4/24.
//

#include "parser.h"
#include "util.h"

namespace JSON {
    Parser::Parser(string input) : input(input) {
        currentToken = Token(START_F, "", 0, 0);
        lastToken = currentToken;
        length = input.length();
        pos = 0;
        start = 0;
        end = 0;
    }

    Parser::~Parser() = default;

    Node Parser::parse() {
        next();
        Node body = parseNode();
        Node node(NodeType::Root, vector<Node>{body});
        ast = node;
        if (currentToken.type != END_F) {
            unexpected(currentToken); // TODO
        }
        return ast;
    }

    Node Parser::parseNode() {
        Node node;
        TokenType type = currentToken.type;
        if (type == BRACES_START) {
            node = parseObjectExpression();
        } else if (type == BRACKETS_START) {
            node = parseArrayExpression();
        } else if (type == STRING) {
            node = Node(NodeType::StringLiteral, currentToken.value);
            next();
        } else if (type == NUMBER) {
            node = Node(NodeType::NumericLiteral, currentToken.value);
            next();
        } else if (type == WORD) {
            string tokenValue = currentToken.value;
            if (stringEquals(tokenValue, "null")) {
                node = Node(NodeType::NullLiteral, tokenValue);
                next();
            } else if (stringEquals(tokenValue, "true") || stringEquals(tokenValue, "false")) {
                node = Node(NodeType::BooleanLiteral, tokenValue);
                next();
            } else {
                unexpected(currentToken); // TODO
            }
        } else {
            unexpected(currentToken); // TODO
        }
        return node;
    }

    Node Parser::parseObjectExpression() {
        bool hasTailComma = false;
        expect(BRACES_START);
        next();
        vector<Node> properties;

        while (isValidPos() && currentToken.type != BRACES_END) {
            hasTailComma = false;
            vector<Node> section;
            // key
            expect(STRING);
            Node key(NodeType::StringLiteral, currentToken.value);
            section.push_back(key);

            next();
            expect(SEPARATOR); // :
            next();

            // value
            section.push_back(parseNode());
            Node property(NodeType::ObjectProperty, section);
            properties.push_back(property);

            // end of comma
            if (currentToken.type == COMMA) {
                hasTailComma = true;
                next();
            }
        }

        if (hasTailComma) {
            unexpected(Token()); // TODO
        }

        Node node(NodeType::ObjectExpression, properties);
        expect(BRACES_END);
        next();
        return node;
    }

    Node Parser::parseArrayExpression() {
        bool hasTailComma = false;
        expect(BRACKETS_START);
        next();
        vector<Node> elements;

        while (isValidPos() && currentToken.type != BRACKETS_END) {
            hasTailComma = false;
            elements.push_back(parseNode());
            if (currentToken.type == COMMA) {
                hasTailComma = true;
                next();
            }
        }

        if (hasTailComma) {
            unexpected(Token()); // TODO
        }

        Node node(NodeType::ArrayExpression, elements);
        expect(BRACKETS_END);
        next();
        return node;
    }

    void Parser::next() {
        Token token;
        lastToken = currentToken;
        skipSpace();
        if (!isValidPos()) {
            token = Token(END_F, "EOF", length, length);
        } else {
            start = pos;
            token = readToken();
        }
        currentToken = token;
    }

    Token Parser::readToken() {
        int code = getCodeAt(pos);

        if (isNumberChar(code) || code == 45) { // 0-9 or '-'
            return readNumberToken();
        } else if (isWordChar(code)) { // A-Z or a-z
            return readWordToken();
        }

        switch (code) {
            case 123: // '{'
                pos++;
                return Token(BRACES_START, "{", pos - 1, pos);
            case 125: // '}'
                pos++;
                return Token(BRACES_END, "}", pos - 1, pos);
            case 91: // '['
                pos++;
                return Token(BRACKETS_START, "[", pos - 1, pos);
            case 93: // ']'
                pos++;
                return Token(BRACKETS_END, "]", pos - 1, pos);
            case 58: // ':'
                pos++;
                return Token(SEPARATOR, ":", pos - 1, pos);
            case 44: // ','
                pos++;
                return Token(COMMA, ",", pos - 1, pos);
            case 34: // '"'
                return readStringToken();
            default:;
                unexpected(Token(END_F, "")); // TODO
        }
    }

    Token Parser::readStringToken() {
        Token token(STRING, "");
        token.start = pos;
        int chunkStart = ++pos;
        int code;
        string value;
        bool isEscapeChar = false;

        while (isValidPos()) {
            if (isEscapeChar) {
                isEscapeChar = false;
                pos++;
                continue;
            }

            code = getCodeAt(pos);
            if (code == 34) { // '"'
                break;
            }
            if (code == 92) { // '\': escape
                isEscapeChar = true;
                value += input.substr(chunkStart, pos - chunkStart);
                chunkStart = ++pos;
            } else {
                pos++;
            }
        }

        if (code != 34) { // '"'
            unexpected(Token(END_F, "")); // TODO
        }

        value += input.substr(chunkStart, pos - chunkStart);
        pos++;
        token.value = value;
        token.end = pos;
        return token;
    }

    Token Parser::readNumberToken() {
        int chunkStart = pos;
        int count = 0;
        bool allowDot = false;
        bool allowE = false;
        bool expectNumber = true;
        int code = getCodeAt(pos);

        if (code == 45) { // '-'
            pos++;
        }

        while (isValidPos()) {
            code = getCodeAt(pos);
            count++;

            if (isNumberChar(code)) {
                if (count == 1) {
                    allowDot = true;
                    allowE = true;
                }
                expectNumber = false;
                pos++;
            } else if (expectNumber) {
                break;
            } else if (allowE && (code == 69 || code == 101)) { // 'E' or 'e'
                allowE = false;
                allowDot = false;
                expectNumber = true;
                pos++;
                if (isValidPos() && getCodeAt(pos) == 43 || getCodeAt(pos) == 45) { // '+' or '-'
                    pos++;
                }
            } else if (allowDot && code == 46) { // '.'
                allowDot = false;
                expectNumber = true;
                pos++;
            } else {
                break;
            }
        }

        // check
        if (expectNumber) {
            unexpected(Token(END_F, "")); // TODO
        }

        string value = input.substr(chunkStart, pos - chunkStart);
        return Token(NUMBER, value, chunkStart, pos);
    }

    Token Parser::readWordToken() {
        int chunkStart = pos;
        while (isValidPos() && isWordChar(getCodeAt(pos))) {
            pos++;
        }

        string value = input.substr(chunkStart, pos - chunkStart);
        return Token(WORD, value, chunkStart, pos);
    }

    Node Parser::startNode(int pos) {
        Node node;
        node.start = start;
        return node;
    }

    Node Parser::finishNode(Node &node) {
        node.end = pos;
        return Node();
    }

    int Parser::getCodeAt(int index) {
        return (unsigned char) input[index];
    }

    void Parser::skipSpace() {
        while (isValidPos()) {
            int code = getCodeAt(pos);
            if (code == 32 || code == 160) { // ` `
                pos++;
            } else if (code == 13 || code == 10 || code == 8232 || code == 8233) { // new line
                if (code == 13 && getCodeAt(pos + 1) == 10) { // CRLF
                    pos++;
                }
                pos++;
            } else if (code > 8 && code < 14) { // 制表符等
                pos++;
            } else {
                break;
            }
        }
    }

    bool Parser::isValidPos() const {
        return pos < length;
    }

    void Parser::expect(TokenType type) {
        if (currentToken.type != type) {
            unexpected(currentToken);
        }
    }

    void Parser::unexpected(Token token) {
        cout << endl << " >>>>>>>>>>> unexpected <<<<<<<<<<<" << endl;
        exit(222);
    }

}