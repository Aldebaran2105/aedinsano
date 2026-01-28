#ifndef HEAP_H
#define HEAP_H

#include "node.h"
#include <queue>
#include <string>

class Heap {
private:
    Node* root;
    int size;

    // Utilidades internas
    Node* getLastNode();
    Node* getParentOfLast();
    void heapifyUp(Node* u);
    void heapifyDown(Node* u);

    // Recorridos
    void inorder(Node* node) const;

    // Graphviz
    void exportDOT(Node* node, std::ofstream& file) const;

public:
    Heap();

    bool empty() const;
    int getSize() const;

    void push(int key);
    int pop();
    int top() const;

    void inorder() const;
    void BFS() const;

    void graficarGraphviz(const std::string& filename) const;
};

#endif
