//
// Created by chen on 2021/4/26.
//

#include "env.h"
#include "util.h"
#include "parser.h"
#include "stringify.h"

void printHelpInfo() {
    cout << "Usage: json <options> filename" << endl;
    cout << "example: json -f a.json" << endl;
    cout << endl;
    cout << "    -f, --format [indent]   format json file" << endl;
    cout << "    -m, --minify            minify json file" << endl;
    cout << endl;
}

void formatJSON(string filename, int indent) {
    filename = JSON::resolvePath(filename);
    JSON::Parser parser(JSON::readFile(filename));
    JSON::Stringifier stringifier;
    parser.parse();
    string str = stringifier.stringify(parser.ast, indent);
    JSON::writeFile(filename, str);
    cout << endl << str << endl;
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        printHelpInfo();
        return 0;
    }

    string filename = argv[argc - 1];

    for (int i = 0; i < argc - 1; ++i) {
        if (JSON::stringEquals(argv[i], "-f") || JSON::stringEquals(argv[i], "--format")) {
            int indent = 2;
            if (i == argc - 3) { // indent 倒数第2位参数
                string nextArg = argv[i + 1];
                try {
                    indent = stoi(nextArg);
                } catch (exception &e) {
                    cerr << "Error: expect indent is a number" << endl;
                    return 1;
                }
            }
            formatJSON(filename, indent);
            return 0;
        } else if (JSON::stringEquals(argv[i], "-m") || JSON::stringEquals(argv[i], "--minify")) {
            formatJSON(filename, 0);
            return 0;
        }
    }
}