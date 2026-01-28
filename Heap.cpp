#include "heap.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <stdexcept>

/* =======================
   CONSTRUCTOR
   ======================= */

// Inicializa un heap vacío.
Heap::Heap() : root(nullptr), size(0) {}

bool Heap::empty() const {
    return size == 0;
}

int Heap::getSize() const {
    return size;
}

// Devuelve la raíz del heap (máximo)
int Heap::top() const {
    return root->key;
}

Node* Heap::getLastNode() {
    if (!root) return nullptr;

    std::queue<Node*> q;
    q.push(root);
    Node* curr = nullptr;

    while (!q.empty()) {
        curr = q.front();
        q.pop();
        if (curr->left)  q.push(curr->left);
        if (curr->right) q.push(curr->right);
    }
    return curr;
}

Node* Heap::getParentOfLast() {
    if (!root || size <= 1) return nullptr;

    Node* last = getLastNode();
    std::queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* curr = q.front();
        q.pop();
        if (curr->left == last || curr->right == last)
            return curr;
        if (curr->left)  q.push(curr->left);
        if (curr->right) q.push(curr->right);
    }
    return nullptr;
}


void Heap::heapifyUp(Node* u) {
    if (!u || u == root) return;
    std::queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        Node* curr = q.front();
        q.pop();
        if (curr->left == u || curr->right == u) {
            if (u->key > curr->key) {
                std::swap(u->key, curr->key);
                heapifyUp(curr);
            }
            return;
        }
        if (curr->left)  q.push(curr->left);
        if (curr->right) q.push(curr->right);
    }
}


void Heap::heapifyDown(Node* u) {
    if (!u) return;
    Node* largest = u;
    // Comparar con hijo izquierdo
    if (u->left && u->left->key > largest->key)
        largest = u->left;
    // Comparar con hijo derecho
    if (u->right && u->right->key > largest->key)
        largest = u->right;
    // Si u no es el mayor, intercambiar y continuar bajando
    if (largest != u) {
        std::swap(u->key, largest->key);
        heapifyDown(largest);
    }
}

void Heap::push(int key) {
}

int Heap::pop() {
}


// Inorden (recursivo)
void Heap::inorder(Node* node) const {
    if (!node) return;
    inorder(node->left);
    cout << node->key << " ";
    inorder(node->right);
}

// Inorden desde la raíz
void Heap::inorder() const {
    inorder(root);
    cout << endl;
}

// Recorrido BFS por niveles
void Heap::BFS() const {
    if (!root) return;

    std::queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* curr = q.front();
        q.pop();
        std::cout << curr->key << " ";

        if (curr->left)  q.push(curr->left);
        if (curr->right) q.push(curr->right);
    }
    std::cout << std::endl;
}

/* =======================
   GRAPHVIZ
   ======================= */

// Exporta el heap en formato DOT recursivamente
void Heap::exportDOT(Node* node, std::ofstream& file) const {
    if (!node) return;

    if (node->left) {
        file << node->key << " -> " << node->left->key << ";\n";
        exportDOT(node->left, file);
    }
    if (node->right) {
        file << node->key << " -> " << node->right->key << ";\n";
        exportDOT(node->right, file);
    }
}

// Genera un archivo DOT para visualizar el heap
void Heap::graficarGraphviz(const std::string& filename) const {
    std::ofstream file(filename);
    file << "digraph Heap {\n";
    exportDOT(root, file);
    file << "}\n";
    file.close();
}
