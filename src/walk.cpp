//
// Created by chen on 2021/4/26.
//

#include "walk.h"

namespace JSON {

    void walk(Node &node, void (*cb)(Node &, WalkContext), WalkContext context) {
        if (context.isStop) return;
        cb(node, context);

        if (node.type == NodeType::Root) {
            walk(node.children[0], cb, context);
        } else if (node.type == NodeType::ObjectExpression) {
            int size = node.children.size();
            int i = 0;
            while (i < size) {
                walk(node.children[i], cb, context);
                i++;
            }
        } else if (node.type == NodeType::ObjectProperty) {
            walk(node.children[0], cb, context);
            walk(node.children[1], cb, context);
        } else if (node.type == NodeType::ArrayExpression) {
            int size = node.children.size();
            int i = 0;
            while (i < size) {
                walk(node.children[i], cb, context);
                i++;
            }
        }
    }

}
