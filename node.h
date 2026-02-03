#ifndef NODE_H
#define NODE_H

  
struct Node {
    int key;
    Node* left = nullptr;
    Node* right = nullptr;
    bool lthread = true;  // true si left apunta al predecesor en inorden
    bool rthread = true; // true si right apunta al sucesor en inorden

    Node(int val) : key(val) {}
};

#endif