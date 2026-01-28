#include "AVL.h"
#include "node.h"
#include <iostream>
#include <queue>
#include <stack>
#include <fstream>
#include <cmath>

using namespace std;

AVL::AVL() : root(nullptr) {}

// ---------------- INSERCIÓN ----------------
Node* AVL::insert(Node* node, int key) {
    if (node == nullptr)
        return new Node(key);
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    updateHeight(node);

    int balance = h(node->left) - h(node->right);

    if (balance > 1 and key < node->left->key )
        return rotacionderecha(node);

    if (balance > 1 and key > node->left->key ) {
        node -> left = rotacionizquierda(node->left);
        return rotacionderecha(node);
    }

    if (balance < -1 and key > node->right->key)
        return rotacionizquierda(node);

    if (balance < -1 and key < node->right->key) {
        node -> right = rotacionderecha(node->right);
        return rotacionizquierda(node);
    }
    return node;
}

void AVL::insert(int key) {
    root = insert(root, key);
}

// ---------------- ROTACIONES ----------------
Node* AVL::rotacionderecha(Node* y) {
    Node* x = y->left;
    Node* T = x->right;

    x->right = y;
    y->left = T;

    updateHeight(y);
    updateHeight(x);

    return x;
}

Node* AVL::rotacionizquierda(Node* x) {
    Node* y = x->right;
    Node* T = y->left;

    y->left = x;
    x->right = T;

    updateHeight(x);
    updateHeight(y);

    return y;
}

// --------------- BUSQUEDA -------------------

bool AVL::search(Node* node, int key) const {
    if (!node) return false;
    if (node->key == key) return true;
    return (key < node->key) ? search(node->left, key)
                             : search(node->right, key);
}

bool AVL::search(int key) const {
    return search(root, key);
}

// --------------- ELIMINAR -------------------
void AVL::remove(int key) {
    root = remove(root,key);
}

Node* AVL::remove(Node* node, int key) {
    if (node == nullptr)
        return nullptr;

    if (key < node->key)
        node->left = remove(node->left, key);

    else if (key > node->key)
        node->right = remove(node->right, key);

    else {
        // Nodo con 0 o 1 hijo
        if (node->left == nullptr || node->right == nullptr) {
            Node* temp = node->left ? node->left : node->right;

            if (temp == nullptr) {
                // Sin hijos
                delete node;
                return nullptr;
            } else {
                // Un hijo
                Node* old = node;
                node = temp;
                delete old;
            }
        }
        else {
            // Dos hijos: sucesor inorder
            Node* temp = findMin(node->right);
            node->key = temp->key;
            node->right = remove(node->right, temp->key);
        }
    }

    // Si el árbol quedó vacío
    if (node == nullptr)
        return nullptr;

    // Actualizar altura
    updateHeight(node);

    int balance = h(node->left) - h(node->right);
    cout << "balance" << balance << endl;
    // LL
    if (balance > 1 && h(node->left->left) >= h(node->left->right))
        return rotacionderecha(node);

    // LR
    if (balance > 1 && h(node->left->left) < h(node->left->right)) {
        node->left = rotacionizquierda(node->left);
        return rotacionderecha(node);
    }

    // RR
    if (balance < -1 && h(node->right->right) >= h(node->right->left))
        return rotacionizquierda(node);

    // RL
    if (balance < -1 && h(node->right->right) < h(node->right->left)) {
        node->right = rotacionderecha(node->right);
        return rotacionizquierda(node);
    }

    return node;
}

Node* AVL::findMin(Node* node){
    while (node->left != nullptr)
        node = node->left;
    return node;
}

// ---------------- RECORRIDOS ----------------
void AVL::inorder(Node* node) const {
    if (!node) return;
    inorder(node->left);
    cout << node->key << " ";
    inorder(node->right);
}

void AVL::inorder() const {
    inorder(root);
    cout << endl;
}

void AVL::BFS() {
    if (!root) return;
    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* n = q.front(); q.pop();
        cout << n->key << " ";
        if (n->left) q.push(n->left);
        if (n->right) q.push(n->right);
    }
}

void AVL::DFS() {
    if (!root) return;
    stack<Node*> s;
    s.push(root);

    while (!s.empty()) {
        Node* n = s.top(); s.pop();
        cout << n->key << " ";
        if (n->right) s.push(n->right);
        if (n->left) s.push(n->left);
    }
}

// ---------------- GRAPHVIZ ----------------
void AVL::exportDOT(Node* node, ofstream& file) const {
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

void AVL::graficarGraphviz(const string& filename) const {
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
