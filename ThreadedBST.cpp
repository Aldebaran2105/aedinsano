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

    Node* actual = node;
    Node* padre = nullptr;

    while (actual != nullptr) {
        if (key == actual->key) {
            return node;
        }
        
        padre = actual;

        if (key < actual->key) {
            if (actual->lthread == false) {
                actual = actual->left;
            } else {
                break;
            }
        } else {
            if (actual->rthread == false) {
                actual = actual->right;
            } else {
                break;
            }
        }
    }

    Node* nuevo = new Node(key);

    if (key < padre->key) {
        nuevo->left = padre->left;
        nuevo->right = padre;
        
        padre->left = nuevo;
        padre->lthread = false;
    } else {
        nuevo->left = padre;
        nuevo->right = padre->right;
        
        padre->right = nuevo;
        padre->rthread = false;
    }

    return node;
}

void ThreadedBST::inorder() const {
    if (root == nullptr) return;

    Node* actual = root;

    while (actual->lthread == false) {
        actual = actual->left;
    }

    while (actual != nullptr) {
        cout << actual->key << " ";

        if (actual->rthread == true) {
            actual = actual->right;
        } 
        else {
            actual = actual->right;
            while (actual != nullptr && actual->lthread == false) {
                actual = actual->left;
            }
        }
    }
    cout << endl;
}

Node* ThreadedBST::findMin(Node* node) const {
    if (node == nullptr) return nullptr;
    while (node->lthread == false) {
        node = node->left;
    }
    return node;
}

Node* ThreadedBST::remove(Node* node, int key) {
    Node* padre = nullptr;
    Node* actual = node;
    bool encontrado = false;

    while (actual != nullptr) {
        if (key == actual->key) {
            encontrado = true;
            break;
        }
        
        padre = actual;
        
        if (key < actual->key) {
            if (actual->lthread == false) actual = actual->left;
            else break;
        } else {
            if (actual->rthread == false) actual = actual->right;
            else break;
        }
    }

    if (!encontrado) return node;

    if (actual->lthread == false && actual->rthread == false) {
        Node* sucesor = actual->right;
        while (sucesor->lthread == false) {
            sucesor = sucesor->left;
        }
        
        int valSucesor = sucesor->key;
        remove(root, sucesor->key);
        actual->key = valSucesor;
        return node;
    }

    Node* hijo = nullptr;
    
    if (actual->lthread == false) {
        hijo = actual->left;
    } else if (actual->rthread == false) {
        hijo = actual->right;
    } else {
        hijo = nullptr;
    }

    if (hijo == nullptr) {
        if (padre == nullptr) {
            delete actual;
            return nullptr;
        }
        
        if (actual == padre->left) {
            padre->lthread = true;
            padre->left = actual->left;
        } else {
            padre->rthread = true;
            padre->right = actual->right;
        }
        delete actual;
    }
    else {
        if (actual->lthread == false) { 
            Node* temp = actual->left;
            while (temp->rthread == false) {
                temp = temp->right;
            }
            temp->right = actual->right;
            
            if (padre == nullptr) {
                delete actual;
                return hijo;
            }
            
            if (actual == padre->left) padre->left = hijo;
            else padre->right = hijo;
            
        } else { 
            Node* temp = actual->right;
            while (temp->lthread == false) {
                temp = temp->left;
            }
            temp->left = actual->left;

            if (padre == nullptr) {
                delete actual;
                return hijo;
            }
            
            if (actual == padre->left) padre->left = hijo;
            else padre->right = hijo;
        }
        delete actual;
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
