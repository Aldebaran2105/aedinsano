#include "ThreadedBST.h"
#include <iostream>
using namespace std;
int main() {
    ThreadedBST tree;
    // Insertar algunos nodos
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);  
    // Recorrido inorden
    cout << "Recorrido inorden del Threaded BST:\n";
    tree.inorder(); 
    tree.graficarGraphviz("threaded_bst1.dot");
    tree.remove(50);
    tree.graficarGraphviz("threaded_bst2.dot");
    return 0;
}
