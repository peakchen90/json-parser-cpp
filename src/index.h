//
// Created by chen on 2021/4/26.
//

#ifndef JSON_PARSER_CPP_INDEX_H
#define JSON_PARSER_CPP_INDEX_H

#include "env.h"

namespace JSON {
    template<typename T>
    T parse(string text);

    template<typename T>
    string stringify(T obj);
}


#endif //JSON_PARSER_CPP_INDEX_H
