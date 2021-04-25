//
// Created by chen on 2021/4/24.
//

#include "node.h"

string Node::toString() {
    if (type == NodeType::Root) {
        return children[0].toString();
    } else if (type == NodeType::ObjectExpression) {
        string str = "{";
        int size = children.size();
        int i = 0;
        while (i < size) {
            str += children[i].toString() + (i < size - 1 ? "," : "");
            i++;
        }
        str += "}";
        return str;
    } else if (type == NodeType::ObjectProperty) {
        string keyStr = children[0].toString();
        string valueStr = children[1].toString();
        return keyStr + ':' + valueStr;
    } else if (type == NodeType::ArrayExpression) {
        string str = "[";
        int size = children.size();
        int i = 0;
        while (i < size) {
            str += children[i].toString() + (i < size - 1 ? "," : "");
            i++;
        }
        str += "]";
        return str;
    } else if (type == NodeType::StringLiteral) {
        return '"' + sValue + '"';
    } else if (type == NodeType::NumericLiteral) {
        return to_string(dValue);
    } else if (type == NodeType::BooleanLiteral) {
        return bValue ? "true" : "false";
    } else if (type == NodeType::NullLiteral) {
        return "null";
    } else {
        cout << "未知类型" << endl;
        exit(10); // TODO
    }
    return "Node:" + type;
}

Node::Node() {
}

Node::Node(string type) : type(type) {
}

Node::Node(string type, string value) : type(type), sValue(value) {
}

Node::Node(string type, double value) : type(type), dValue(value) {
}

Node::Node(string type, bool value) : type(type), bValue(value) {
}

Node::Node(string type, vector<Node> children) : type(type), children(children) {
}
