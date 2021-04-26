//
// Created by chen on 2021/4/24.
//

#include "env.h"
#include "util.h"

namespace JSON {

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

    string readFile(const string &path) {
        string data;
        string chunk;
        int i = 0;
        ifstream file(path);

        if (!file) {
            cerr << "Error: File not found: " << path << endl;
            exit(1);
        }

        while (getline(file, chunk)) {
            if (i++ > 0) {
                data += "\n";
            }
            data += chunk;
        }
        file.close();

        return data;
    }

    void writeFile(string &path, string &data) {
        ofstream file;
        file.open(path);
        file << data;
        file.close();
    }

    string getCWD() {
        char buffer[1024];
        getcwd(buffer, 1024);
        string res = buffer;
        return res;
    }

    string resolvePath(string &path) {
        string cwd = getCWD();
        return cwd + '/' + path;
    }

    Position getPosition(string &source, int pos) {
        Position position{1, 0};
        int len = source.length();
        int i = 0;
        while (i < len && i < pos) {
            if (source[i] == '\n') {
                position.line++;
                position.column = 0;
            } else {
                position.column++;
            }
            i++;
        }
        return position;
    }
}