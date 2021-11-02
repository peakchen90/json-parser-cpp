//
// Created by chen on 2021/11/1.
//
#include "env.h"
#include "node.h"
#include "parser.h"
#include "stringify.h"
#include "walk.h"

extern "C" void formatJSON(const char *filename, int indent) {
    string absoluteFilename = JSON::resolvePath(filename);
    JSON::Parser parser(JSON::readFile(filename));
    JSON::Stringifier stringifier;
    parser.parse();
    string str = stringifier.stringify(parser.ast, indent);
    JSON::writeFile(absoluteFilename, str);
}

