#include "ThreadedBST.h"

using namespace std;


void ThreadedBST::insert(int key) {
    root = insert(root, key);
}

void ThreadedBST::remove(int key) {
    root = remove(root, key);
}

Node* ThreadedBST::insert(Node* node, int key) {
    if (node == nullptr) {
        return new Node(key);
    }

    Node* parent = nullptr;
    Node* curr = node;

    while (curr != nullptr) {
        if (key == curr->key) return node;
        
        parent = curr;
        
        if (key < curr->key) {
            if (!curr->lthread)
                curr = curr->left;
            else
                break;
        } 
        else {
            if (!curr->rthread)
                curr = curr->right;
            else
                break;
        }
    }

    Node* newNode = new Node(key);

    if (key < parent->key) {
        
        newNode->left = parent->left; 
        newNode->right = parent;      
        parent->left = newNode;
        parent->lthread = false;
    } else {
        newNode->left = parent;        
        newNode->right = parent->right;
        parent->right = newNode;
        parent->rthread = false;
    }

    return node;
}

void ThreadedBST::inorder() const {
    if (root == nullptr) return;

    Node* curr = root;

    while (!curr->lthread)
        curr = curr->left;

    while (curr != nullptr) {
        cout << curr->key << " ";

        if (curr->rthread) {
            curr = curr->right;
        } else {
            curr = curr->right;
            if (curr == nullptr) break;
            while (!curr->lthread)
                curr = curr->left;
        }
    }
    cout << endl;
}

Node* ThreadedBST::findMin(Node* node) const {
    if (node == nullptr) return nullptr;
    while (!node->lthread) {
        node = node->left;
    }
    return node;
}

Node* ThreadedBST::remove(Node* node, int key) {
    Node* parent = nullptr;
    Node* curr = node;
    bool found = false;

    while (curr != nullptr) {
        if (key == curr->key) {
            found = true;
            break;
        }
        parent = curr;
        if (key < curr->key) {
            if (!curr->lthread) curr = curr->left;
            else break;
        } else {
            if (!curr->rthread) curr = curr->right;
            else break;
        }
    }

    if (!found) return node;

    if (!curr->lthread && !curr->rthread) {
        Node* succ = curr->right;
        while (!succ->lthread) succ = succ->left;
        
        int val = succ->key;
        remove(node, succ->key); 
        curr->key = val;
        return node;
    }

    Node* child = nullptr;
    if (!curr->lthread) child = curr->left;
    else if (!curr->rthread) child = curr->right;
    else child = nullptr;

    if (child == nullptr) {
        if (parent == nullptr) {
            delete curr;
            return nullptr;
        }
        
        if (curr == parent->left) {
            parent->lthread = true;
            parent->left = curr->left;
        } else {
            parent->rthread = true;
            parent->right = curr->right;
        }
        delete curr;
    }
    else {
        if (!curr->lthread) {
             Node* temp = curr->left;
             while (!temp->rthread) temp = temp->right;
             temp->right = curr->right;
             
             if (parent == nullptr) {
                 delete curr;
                 return child;
             }
             
             if (curr == parent->left) parent->left = child;
             else parent->right = child;
        } 
        else {
             Node* temp = curr->right;
             while (!temp->lthread) temp = temp->left;
             temp->left = curr->left;

             if (parent == nullptr) {
                 delete curr;
                 return child;
             }

             if (curr == parent->left) parent->left = child;
             else parent->right = child;
        }
        delete curr;
    }

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
