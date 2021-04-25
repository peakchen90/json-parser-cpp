//
// Created by chen on 2021/4/24.
//

#include "node.h"

string Node::toString() {
    cout << "----------- DEBUG 2-----------" << endl;
    if (type == NodeType::Root) {
        return ((Root *) body)->toString();
    } else if (type == NodeType::ObjectExpression) {
        string str = "{";
        Node *property = (Node *) properties;
        while (property) {
            str += property->toString() + ",";
            property++;
        }
        str += "}";
        return str;
    } else if (type == NodeType::ObjectProperty) {
        return "\"" + *((string *) key) + "\": " + ((Node *) value)->toString();
    } else if (type == NodeType::ArrayExpression) {
        string str = "[";
        Node *item = (Node *) elements;
        while (item) {
            str += item->toString() + ",";
            item++;
        }
        str += "]";
        return str;
    } else if (type == NodeType::StringLiteral) {
        return *((string *) value);
    } else if (type == NodeType::NumericLiteral) {
        return to_string(*(double *) value);
    } else if (type == NodeType::BooleanLiteral) {
        return *((bool *) value) ? "true" : "false";
    } else if (type == NodeType::NullLiteral) {
        return "null";
    } else {
        cout << "未知类型" << endl;
        exit(10); // TODO
    }
    return "Node:" + type;
}

ObjectProperty::ObjectProperty(string key, Node value) : key(key), value(value) {
    type = NodeType::ObjectExpression;
}

//string ObjectProperty::toString() {
//    return "\"" + key + "\": " + value.toString();
//}

ObjectExpression::ObjectExpression(ObjectProperty *properties) : properties(properties) {
    type = NodeType::ObjectExpression;
}

//string ObjectExpression::toString() {
//    string str = "{";
//    Node *property = properties;
//    while (property) {
//        str += property->toString() + ",";
//        property++;
//    }
//    str += "}";
//    return str;
//}

ArrayExpression::ArrayExpression(Node *elements) : elements(elements) {
    type = NodeType::ArrayExpression;
}

//string ArrayExpression::toString() {
//    string str = "[";
//    Node *item = elements;
//    while (item) {
//        str += item->toString() + ",";
//        item++;
//    }
//    str += "]";
//    return str;
//}

StringLiteral::StringLiteral(string value) : value(value) {
    type = NodeType::StringLiteral;
}

//string StringLiteral::toString() {
//    return value;
//}

NumericLiteral::NumericLiteral(double value) : value(value) {
    type = NodeType::NumericLiteral;
}

//string NumericLiteral::toString() {
//    return to_string(value);
//}

BooleanLiteral::BooleanLiteral(bool value) : value(value) {
    type = NodeType::BooleanLiteral;
}

//string BooleanLiteral::toString() {
//    return value ? "true" : "false";
//}

NullLiteral::NullLiteral() {
    type = NodeType::NullLiteral;
}

//string NullLiteral::toString() {
//    return "null";
//}

Root::Root(Node body) : body(body) {
    type = NodeType::Root;
}

//string Root::toString() {
//    cout << "axxx";
//    return body.toString();
//}
