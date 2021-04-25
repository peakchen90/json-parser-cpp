//
// Created by chen on 2021/4/24.
//

#include "util.h"

//Location getLocation(int startLine, int startColumn, int endLine, int endColumn) {
//    return Location{Position{startLine, startColumn}, Position{endLine, endColumn}};
//}

bool isNumberChar(int code) {
    return code >= 48 && code <= 57; // 0-9
}

bool isWordChar(int code) {
    return (code >= 65 && code <= 90) || (code >= 97 && code <= 122); // A-Z or a-z
}

bool stringEquals(string a, string b) {
    int len = a.length();
    if (len != b.length()) {
        return false;
    }
    for (int i = 0; i < len; ++i) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

string stringEscape(string str, char ch) {
    int length = str.size();
    int i = length - 1;
    while (i >= 0) {
        if (str[i] == ch) {
            str.replace(i, 0, "\\");
        }
        i--;
    }
    return str;
}

string strIndent(int width, char prefix) {
    string res;
    if (prefix) res += prefix;
    int i = 0;
    while (i < width) {
        res += ' ';
        i++;
    }
    return res;
}
