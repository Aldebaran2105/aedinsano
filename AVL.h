#ifndef AVL_H
#define AVL_H

#include "node.h"
#include <string>

class AVL {
private:
    Node* root;

    // Metodos internos
    Node* insert(Node* node, int key);
    Node* remove(Node* node, int key);
    Node* rotacionderecha(Node* y);
    Node* rotacionizquierda(Node* x);
    Node* findMin(Node* node);
    bool search(Node* node, int key) const;
    void inorder(Node* node) const;

    // Graphviz
    void exportDOT(Node* node, std::ofstream& file) const;

public:
    // Constructor
    AVL();
    void insert(int key);
    void remove(int key);
    bool search(int key) const;
    void inorder() const;
    void BFS();
    void DFS();
    void graficarGraphviz(const std::string& filename) const;
};

#endif

