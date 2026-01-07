#include <iostream>
using namespace std;


struct Node {
    int exponente;
    int coeficiente;
    Node* next;
    // Constructor
    Node(int c, int e) {
    exponente = e;
    coeficiente = c;
    next = nullptr;
    }
};


class Polinomio {
private:
    Node* head;
public:
    // Constructor
    Polinomio() : head(nullptr) {}
    // Asignar cabeza
    void setHead(Node* h) {
    head = h;
    }
// Imprimir la lista
    void print() const {
        Node* current = head;
        while (current != nullptr) {
        cout << current->coeficiente << "x" << "^" << current -> exponente << " -> ";
        current = current->next;
        }
    cout << "NULL" << endl;
    }
    void push_front(int x, int y) {
        //complejidad O(1)
        Node* temporal = new Node(x,y);
        temporal -> next = head;
        head = temporal;
    }

    void add(int coeficiente, int exponente){
        Node* current = head;
        bool find = false;
        while(current -> next != nullptr){
            if(current ->exponente == exponente){
                current -> coeficiente += coeficiente;
                find = true;
            }
            current = current -> next;
        }
        if(find == false){
            Node* temporal = new Node(coeficiente, exponente);
            current = head;
            while(current -> next -> exponente > exponente){
                current = current -> next;
            }
            temporal -> next = current -> next;
            current -> next = temporal;
        }
    }
};


int main() {
    Polinomio p;
    p.push_front(1,0);
    p.push_front(2,1);
    p.push_front(3,2);
    p.print();
    Polinomio q;
    q.push_front(4,0);
    q.push_front(1,1);
    q.print();
    return 0;
}