//
// Created by chen on 2021/4/23.
//
#include <fstream>
#include "env.h"
#include "node.h"
#include "parser.h"

string readJson() {
    string data;
    string chunk;
    int i = 0;
    ifstream file;
    string filename = __FILE__;
    filename.replace(filename.length() - 8, 8, "test.json");
    file.open(filename);

    while (getline(file, chunk)) {
        if (i++ > 0) {
            data += "\n";
        }
        data += chunk;
    }
    file.close();
    return data;
}

int main() {
    string input = readJson();
    Parser parser(input);
    Node ast = parser.parse();
    cout << ast.toString() << endl;

    return 0;
}
