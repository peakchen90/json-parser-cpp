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

    int getStringBytesAt(string &str, int pos) {
        int code = (unsigned char) str[pos];
        unsigned int base = 0b10000000;
        if ((code & base) == base) {
            int bytes = 0;
            do {
                bytes++;
                base = base >> 1;
            } while ((code & base) == base);
            return bytes;
        } else {
            return 1;
        }
    }

    string getStringAt(string &str, int pos) {
        int bytes = getStringBytesAt(str, pos);
        return str.substr(pos, bytes);
    }

    int getStringIndexAt(string &str, int pos) {
        if (pos >= str.length()) {
            return -1;
        }
        int index = -1;
        int i = 0;
        while (i <= pos) {
            i += getStringBytesAt(str, i);
            index++;
        }
        return index;
    }

    unsigned int getCodePointAt(string &str, int index) {
        int code = (unsigned char) str[index];
        unsigned int baseBits = 0b10000000;
        unsigned int controlBits;

        // ???????????????????????? n ?????? 1 ?????????
        int bytes = 0;
        if ((code & baseBits) == baseBits) { // 0b1xxxxxxx
            do {
                controlBits = baseBits;
                baseBits = baseBits | (baseBits >> 1);
                bytes++;
            } while ((code & baseBits) == baseBits);
        } else {
            return code;
        }

        // 3???????????????1110xxxx 10xxxxxx 10xxxxxx
        // ??????????????????????????? 8 - ????????? - 1,  ??????????????????????????????: 6
        // ??????????????????????????????6????????????????????????????????? 6 * (???n?????? - 1), ??????????????????
        int i = bytes - 1;
        unsigned int result = (code ^ controlBits) << (i * 6);
        while (i >= 1) {
            int c = (unsigned char) str[index + i];
            result += (c & 0b00111111) << ((bytes - i - 1) * 6);
            i--;
        }

        return result;
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

    string resolvePath(const string &path) {
        string cwd = getCWD();
        return cwd + '/' + path;
    }

    Position getPosition(string &source, int pos) {
        Position position{1, 1};
        int len = source.length();
        int i = 0;
        while (i < len && i < pos) {
            if (source[i] == '\n') {
                position.line++;
                position.column = 1;
            } else {
                position.column++;
            }
            i += getStringBytesAt(source, i);
        }
        return position;
    }
}
