#include "AVL.h"
#include "BST.h"
#include "Heap.h"
#include <iostream>

int main() {
     Heap h;

    std::cout << "Insertando elementos en el Heap:\n";
    int values[] = {20, 15, 30, 5, 10, 25, 40};

    for (int x : values) {
        std::cout << "push(" << x << ")\n";
        h.push(x);
        std::cout << "BFS: ";
        h.BFS();
    }

    std::cout << "\nElemento máximo (top): ";
    std::cout << h.top() << std::endl;

    std::cout << "\nExtrayendo elementos (pop):\n";
    while (!h.empty()) {
        int m = h.pop();
        std::cout << "pop() -> " << m << " | Heap: ";
        h.BFS();
    }

    // Prueba gráfica
    h.push(50);
    h.push(30);
    h.push(40);
    h.push(10);
    h.push(20);

    std::cout << "\nHeap final para Graphviz (BFS): ";
    h.BFS();

    h.graficarGraphviz("heap.dot");
    std::cout << "\nArchivo heap.dot generado.\n";
    std::cout << "Para visualizar:\n";
    std::cout << "dot -Tpng heap.dot -o heap.png\n";


    return 0;
}

// sudo apt update
// sudo apt install graphviz
// dot -Tpng arbol.dot -o arbol.png