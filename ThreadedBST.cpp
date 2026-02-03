#include "ThreadedBST.h"


void ThreadedBST::insert(int key) {
    root = insert(root, key);
}

void ThreadedBST::remove(int key) {
    root = remove(root, key);
}

Node* ThreadedBST::insert(Node* node, int key) {
    /// COMPLETAR
    return node;
}

void ThreadedBST::inorder() const {
    /// COMPLETAR
}

Node* ThreadedBST::findMin(Node* node) const {
    /// COMPLETAR
    return node;
}

Node* ThreadedBST::remove(Node* node, int key) {
    /// COMPLETAR
    return node;
}




///////////////////////// GRAFICADOR DEL ARBOL NO TOCAR ///////////////////////
///////////////////////////////////////////////////////////////////////////////

void ThreadedBST::exportDOT(Node* node, std::ofstream& file) const {
    if (!node) return;

    file << "    \"" << node->key << "\";\n";

    if (!node->lthread && node->left)
        file << "    \"" << node->key << "\" -> \"" << node->left->key << "\" [color=black];\n";
    
    if (!node->rthread && node->right)
        file << "    \"" << node->key << "\" -> \"" << node->right->key << "\" [color=black];\n";

    if (node->lthread && node->left)
        file << "    \"" << node->key << "\" -> \"" << node->left->key << "\" [style=dashed, color=blue];\n";

    if (node->rthread && node->right)
        file << "    \"" << node->key << "\" -> \"" << node->right->key << "\" [style=dashed, color=red];\n";

    if (!node->lthread) exportDOT(node->left, file);
    if (!node->rthread) exportDOT(node->right, file);
}

void ThreadedBST::graficarGraphviz(const std::string& filename) const {
    std::ofstream file(filename);
    file << "digraph ThreadedBST {\n";
    file << "    node [shape=circle];\n";
    exportDOT(root, file);
    file << "}\n";
    file.close();
}
