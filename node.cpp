#include "Node.h"
#include <algorithm>

Node::Node(int k) : key(k), height(0), left(nullptr), right(nullptr) {}

int h(Node* n) {
    return n ? n->height : -1;
}

void updateHeight(Node* n) {
    n->height = 1 + std::max(h(n->left), h(n->right));
}
