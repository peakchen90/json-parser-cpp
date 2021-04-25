//
// Created by chen on 2021/4/24.
//

#include "node.h"

Node::Node() {
}

Node::Node(string type) : type(type) {
}

Node::Node(string type, string rawValue) : type(type), rawValue(rawValue) {
}

Node::Node(string type, vector<Node> children) : type(type), children(children) {
}

string Node::toString() {
    return "Node:" + type + "(" + to_string(start) + "," + to_string(end) + ")";
}