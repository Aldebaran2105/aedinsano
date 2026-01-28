#ifndef BST_H
#define BST_H

#include "node.h"
#include <string>

class BST {
private:
    Node* root;
    Node* insert(Node* node, int key);
    bool search(Node* node, int key) const;
    Node* findMin(Node* node) const;
    Node* remove(Node* node, int key);
    void inorder(Node* node) const;
    // Graphviz
    void exportDOT(Node* node, std::ofstream& file) const;

    int bstToVine(Node* grand);
    void compress(Node* grand, int m);

public:
    BST();
    void insert(int key);
    bool search(int key) const;
    void remove(int key);
    void inorder() const;
    void BFS();
    void DFS();
    void graficarGraphviz(const std::string& filename) const;

    void balance();
};

#endif
