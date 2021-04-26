//
// Created by chen on 2021/4/24.
//

#include "node.h"

namespace JSON {

    Node::Node() {
    }

    Node::Node(string type) : type(type) {
    }

    Node::Node(string type, string rawValue) : type(type), rawValue(rawValue) {
    }

    Node::Node(string type, string rawValue, int start, int end)
            : type(type), rawValue(rawValue), start(start), end(end) {
    }

    Node::Node(string type, vector<Node> children) : type(type), children(children) {
    }

    Node::Node(string type, vector<Node> children, int start, int end)
            : type(type), children(children), start(start), end(end) {
    }

    string Node::toString() {
        return "Node:" + type + "(" + to_string(start) + "," + to_string(end) + ")";
    }

}