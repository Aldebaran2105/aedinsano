#ifndef NODE_H
#define NODE_H

struct Node {
    int key;
    int height;
    Node* left;
    Node* right;
    Node(int k);
};

int h(Node* n);
void updateHeight(Node* n);

#endif
