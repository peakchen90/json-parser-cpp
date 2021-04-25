//
// Created by chen on 2021/4/24.
//

#include "parser.h"
#include "util.h"

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
    ast = Root(parseNode());
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
        node = StringLiteral(currentToken.value);
    } else if (type == NUMBER) {
        node = NumericLiteral(stod(currentToken.value));
    } else if (type == WORD) {
        string value = currentToken.value;
        if (stringEquals(value, "null")) {
            node = NullLiteral();
        } else if (stringEquals(value, "true")) {
            node = BooleanLiteral(true);
        } else if (stringEquals(value, "false")) {
            node = BooleanLiteral(false);
        } else {
            unexpected(currentToken); // TODO
        }
    } else {
        unexpected(currentToken); // TODO
    }
    return node;
}

ObjectExpression Parser::parseObjectExpression() {
    expect(BRACES_START);
    ObjectProperty *properties = new ObjectProperty("", Node());
    ObjectProperty *property = properties;
    while (currentToken.type != BRACES_END) {
        expect(STRING);
        string key = currentToken.value;
        expect(SEPARATOR);
        *property = ObjectProperty(key, parseNode());
        next();
        if (currentToken.type == COMMA) {
            next();
        }
        property++;
    }
    ObjectExpression node(properties);
    expect(BRACES_END);
    delete properties;
    return node;
}

ArrayExpression Parser::parseArrayExpression() {
    expect(BRACKETS_START);
    Node *elements = new Node;
    Node *item = elements;
    while (currentToken.type != BRACKETS_END) {
        *item = parseNode();
        next();
        if (currentToken.type == COMMA) {
            next();
        }
        item++;
    }
    ArrayExpression node(elements);
    expect(BRACKETS_END);
    delete elements;
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
    if (currentToken.type == type) {
        next();
    } else {
        unexpected(currentToken);
    }
}

void Parser::unexpected(Token token) {
    cout << endl << " >>>>>>>>>>> unexpected <<<<<<<<<<<" << endl;
    exit(222);
}

