//
// Created by chen on 2021/4/24.
//

#include "node.h"

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

string Node::toString() {
    return "Node:" + type + "(" + to_string(start) + "," + to_string(end) + ")";
}