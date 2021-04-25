//
// Created by chen on 2021/4/25.
//

#include "stringify.h"
#include "node.h"

Stringifier::Stringifier(int indent) : indent(indent) {
    currentIndent = 0;
}

int Stringifier::pushIndent() {
    currentIndent += indent;
    return currentIndent;
}

int Stringifier::popIndent() {
    currentIndent -= indent;
    return currentIndent;
}

string Stringifier::getIndentStr() {
    if (indent == 0) return "";
    return strIndent(currentIndent, '\n');
}

string Stringifier::stringify(Node &node) {
    if (node.type == NodeType::Root) {
        return stringify(node.children[0]);
    } else if (node.type == NodeType::ObjectExpression) {
        string str = "{";
        pushIndent();
        int size = node.children.size();
        int i = 0;
        while (i < size) {
            str += getIndentStr();
            str += stringify(node.children[i]) + (i < size - 1 ? "," : "");
            i++;
        }
        popIndent();
        str += getIndentStr();
        str += "}";
        return str;
    } else if (node.type == NodeType::ObjectProperty) {
        string keyStr = stringify(node.children[0]);
        string valueStr = stringify(node.children[1]);
        return keyStr + (indent > 0 ? ": " : ":") + valueStr;
    } else if (node.type == NodeType::ArrayExpression) {
        string str = "[";
        pushIndent();
        int size = node.children.size();
        int i = 0;
        while (i < size) {
            str += getIndentStr();
            str += stringify(node.children[i]) + (i < size - 1 ? "," : "");
            i++;
        }
        popIndent();
        str += getIndentStr();
        str += "]";
        return str;
    } else if (node.type == NodeType::StringLiteral) {
        return '"' + stringEscape(node.rawValue, '"') + '"';
    } else if (node.type == NodeType::NumericLiteral) {
        return node.rawValue;
    } else if (node.type == NodeType::BooleanLiteral) {
        return node.rawValue;
    } else if (node.type == NodeType::NullLiteral) {
        return node.rawValue;
    } else {
        cout << "未知类型" << endl;
        exit(10); // TODO
    }
}
