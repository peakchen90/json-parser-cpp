//
// Created by chen on 2021/4/25.
//

#include "stringify.h"
#include "node.h"

//Stringifier::Stringifier(int configIndent) : configIndent(configIndent) {
//    current = 0;
//}

namespace JSON {

    int Stringifier::pushIndent() {
        current += configIndent;
        return current;
    }

    int Stringifier::popIndent() {
        current -= configIndent;
        return current;
    }

    string Stringifier::getIndentStr() const {
        if (configIndent == 0) return "";
        return strIndent(current, '\n');
    }


    string Stringifier::stringify(Node &node, int indent) {
        configIndent = indent;
        if (node.type == NodeType::Root) {
            return stringify(node.children[0], configIndent);
        } else if (node.type == NodeType::ObjectExpression) {
            string str = "{";
            pushIndent();
            int size = node.children.size();
            int i = 0;
            while (i < size) {
                str += getIndentStr();
                str += stringify(node.children[i], configIndent) + (i < size - 1 ? "," : "");
                i++;
            }
            popIndent();
            str += getIndentStr();
            str += "}";
            return str;
        } else if (node.type == NodeType::ObjectProperty) {
            string keyStr = stringify(node.children[0], configIndent);
            string valueStr = stringify(node.children[1], configIndent);
            return keyStr + (configIndent > 0 ? ": " : ":") + valueStr;
        } else if (node.type == NodeType::ArrayExpression) {
            string str = "[";
            pushIndent();
            int size = node.children.size();
            int i = 0;
            while (i < size) {
                str += getIndentStr();
                str += stringify(node.children[i], configIndent) + (i < size - 1 ? "," : "");
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

}