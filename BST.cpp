#include "BST.h"
#include <iostream>
#include <queue>
#include <stack>
#include <fstream>

using namespace std;

BST::BST() : root(nullptr) {}


// ---------------- INSERCIÓN ----------------

Node* BST::insert(Node* node, int key) {
    if (node == nullptr)
        return new Node(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else
        node->right = insert(node->right, key);

    return node;
}

void BST::insert(int key) {
    root = insert(root, key);
}

// --------------- BUSQUEDA -------------------

bool BST::search(Node* node, int key) const {
    if (node == nullptr)
        return false;

    if (node->key == key)
        return true;

    if (key < node->key)
        return search(node->left, key);
    else
        return search(node->right, key);
}

bool BST::search(int key) const {
    return search(root, key);
}

// --------------- ELIMINAR -------------------

Node* BST::remove(Node* node, int key) {
    if (node == nullptr)
        return nullptr;

    if (key < node->key) {
        node->left = remove(node->left, key);
    }
    else if (key > node->key) {
        node->right = remove(node->right, key);
    }
    else {
        // 0 hijos
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            return nullptr;
        }
        // 1 hijo
        else if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            return temp;
        }
        // 2 hijos
        else {
            Node* temp = findMin(node->right);
            node->key = temp->key;
            node->right = remove(node->right, temp->key);
        }
    }
    return node;
}

void BST::remove(int key) {
    root = remove(root, key);
}

Node* BST::findMin(Node* node) const {
    while (node->left != nullptr)
        node = node->left;
    return node;
}

// ---------------- RECORRIDOS ----------------

void BST::inorder(Node* node) const {
    if (node == nullptr) return;
    inorder(node->left);
    cout << node->key << " ";
    inorder(node->right);
}

void BST::inorder() const {
    inorder(root);
    cout << endl;
}

void BST::BFS() {
    if (!root) return;

    queue<Node*> cola;
    cola.push(root);

    while (!cola.empty()) {
        Node* temp = cola.front();
        cola.pop();
        cout << temp->key << " - ";

        if (temp->left) cola.push(temp->left);
        if (temp->right) cola.push(temp->right);
    }
}

void BST::DFS() {
    if (!root) return;

    stack<Node*> pila;
    pila.push(root);

    while (!pila.empty()) {
        Node* temp = pila.top();
        pila.pop();
        cout << temp->key << " - ";

        if (temp->right) pila.push(temp->right);
        if (temp->left) pila.push(temp->left);
    }
}

// ---------------- GRAPHVIZ ----------------
void BST::exportDOT(Node* node, ofstream& file) const {
    if (!node) return;

    file << "    " << node->key << ";\n";

    if (node->left) {
        file << "    " << node->key << " -> " << node->left->key << ";\n";
        exportDOT(node->left, file);
    } else if (node->right) {
        file << "    invL" << node->key << " [style=invis];\n";
        file << "    " << node->key << " -> invL" << node->key
             << " [style=invis];\n";
    }

    if (node->right) {
        file << "    " << node->key << " -> " << node->right->key << ";\n";
        exportDOT(node->right, file);
    } else if (node->left) {
        file << "    invR" << node->key << " [style=invis];\n";
        file << "    " << node->key << " -> invR" << node->key
             << " [style=invis];\n";
    }
}

void BST::graficarGraphviz(const string& filename) const {
    ofstream file(filename);
    file << "digraph AVL {\n";
    file << "    rankdir=TB;\n";
    file << "    graph [ordering=\"out\"];\n";
    file << "    node [shape=circle];\n";

    if (root)
        exportDOT(root, file);

    file << "}\n";
    file.close();
}
