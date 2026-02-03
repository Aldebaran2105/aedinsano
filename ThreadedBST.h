#ifndef THREADED_BST_H
#define THREADED_BST_H

#include "node.h"
#include <iostream>
#include <fstream>
#include <string>

class ThreadedBST {
private:
    Node* root = nullptr;
    Node* insert(Node* node, int key);
    Node* findMin(Node* node) const;
    Node* remove(Node* node, int key); 
    void exportDOT(Node* node, std::ofstream& file) const;

public:
    ThreadedBST() = default;
    void remove(int key);  
    void insert(int key);
    void inorder() const;
    void graficarGraphviz(const std::string& filename) const;
};

#endif
