//
// Created by chen on 2021/4/25.
//

#include "stringify.h"
#include "node.h"

string nodeStringify(Node &obj) {
    string type = obj.type;
    cout << "----------- DEBUG 1-----------" << type << endl;

    if (type == NodeType::Root) {
        cout << "----------- DEBUG 4-----------" << type << endl;
        cout << "----------- DEBUG 3-----------" << ((Node *) obj.body) << endl;
        return nodeStringify(*((Node *) obj.body));
    } else if (type == NodeType::ObjectExpression) {
        string str = "{";
        Node *property = (Node *) obj.properties;
        while (property) {
            cout << "----------- DEBUG 2-----------" << type << endl;
            str += nodeStringify(*((Node *) property)) + ",";
            property++;
        }
        str += "}";
        return str;
    } else if (type == NodeType::ObjectProperty) {
        return "\"" + *((string *) obj.key) + "\": " + nodeStringify(*((Node *) obj.value));
    } else if (type == NodeType::ArrayExpression) {
        string str = "[";
        Node *item = (Node *) obj.elements;
        while (item) {
            str += nodeStringify(*((Node *) item)) + ",";
            item++;
        }
        str += "]";
        return str;
    } else if (type == NodeType::StringLiteral) {
        return *((string *) obj.value);
    } else if (type == NodeType::NumericLiteral) {
        return to_string(*(double *) obj.value);
    } else if (type == NodeType::BooleanLiteral) {
        return *((bool *) obj.value) ? "true" : "false";
    } else if (type == NodeType::NullLiteral) {
        return "null";
    } else {
        cout << "未知类型" << endl;
        exit(10); // TODO
    }
}
