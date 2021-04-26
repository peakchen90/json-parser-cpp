//
// Created by chen on 2021/4/26.
//

#ifndef JSON_PARSER_CPP_WALK_H
#define JSON_PARSER_CPP_WALK_H


#include "node.h"

namespace JSON {

    class WalkContext {
    public:
        bool isStop = false;
        void *state;

        WalkContext(void *state) : state(state) {}

        void stop() {
            isStop = true;
        };
    };

    void walk(Node &node, void (*cb)(Node &current, WalkContext context), WalkContext context = WalkContext(NULL));

}


#endif //JSON_PARSER_CPP_WALK_H
