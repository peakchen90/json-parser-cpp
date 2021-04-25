//
// Created by chen on 2021/4/23.
//
#include <fstream>
#include "env.h"
#include "index.h"

string readJson() {
   string data;
   string chunk;
   int i = 0;
   ifstream file;
   file.open("../test.json");

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
    cout << "----------- DEBUG -----------" << endl;
    cout << "----------- DEBUG 222-----------" << endl;

    string input = readJson();
    Node obj = json_parser::parse(input);
    cout << json_parser::stringify(obj) << endl;

    return 0;
}
