//
// Created by chen on 2021/4/23.
//
#include "env.h"
#include "node.h"
#include "parser.h"
#include "stringify.h"
#include "walk.h"

string readJson() {
    string filename = __FILE__;
    filename.replace(filename.length() - 8, 8, "test.json");
    return JSON::readFile(filename);
}

int main() {
    string input = readJson();
    JSON::Parser parser(input);
    JSON::Node node = parser.parse();
    JSON::Stringifier stringifier;

    JSON::walk(node, [](JSON::Node &n, JSON::WalkContext ctx)->void {
       cout << n.toString() << endl;
    });

    cout << stringifier.stringify(node, 2) << endl;
    return 0;
}
