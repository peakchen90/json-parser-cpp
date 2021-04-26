//
// Created by chen on 2021/4/23.
//
#include "env.h"
#include "node.h"
#include "parser.h"
#include "stringify.h"

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
    cout << stringifier.stringify(node) << endl;
    return 0;
}
