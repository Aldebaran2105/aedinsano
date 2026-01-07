#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Node {
    int exponente;
    int coeficiente;
    Node* next;
    Node(int c, int e) : coeficiente(c), exponente(e), next(nullptr) {}
};

class Polinomio {
private:
    Node* head;
    Node* tail;
public:
    Polinomio() : head(nullptr), tail(nullptr) {}

    // Imprimir polinomio
    void print() const {
        Node* current = head;
        while (current != nullptr) {
            cout << current->coeficiente << "x^" << current->exponente << " -> ";
            current = current->next;
        }
        cout << "NULL" << endl;
    }

    // Insertar ordenado y combinar términos
    void add(int coef, int exp) {
        if (coef == 0) return;
        if (head == nullptr) {
            head = tail = new Node(coef, exp);
            return;
        }

        Node* current = head;
        while (current != nullptr) {
            if (current->exponente == exp) {
                current->coeficiente += coef;
                return;
            }
            current = current->next;
        }

        Node* nuevo = new Node(coef, exp);

        if (exp > head->exponente) {
            nuevo->next = head;
            head = nuevo;
            return;
        }

        current = head;
        while (current->next != nullptr && current->next->exponente > exp) {
            current = current->next;
        }

        nuevo->next = current->next;
        current->next = nuevo;

        if (nuevo->next == nullptr) tail = nuevo; // Actualizar tail si es al final
    }

    // Insertar al final (usando tail)
    void push_back(int coef, int exp) {
        if (coef == 0) return;
        if (tail != nullptr && tail->exponente == exp) {
            tail->coeficiente += coef;
            return;
        }
        Node* nuevo = new Node(coef, exp);
        if (head == nullptr) head = tail = nuevo;
        else {
            tail->next = nuevo;
            tail = nuevo;
        }
    }

    // Sobrecarga del operador +
    Polinomio operator+(const Polinomio& other) const {
        Polinomio result;
        Node* p = head;
        Node* q = other.head;
        return result;
    }

    // Funciones amigas para multiplicación
    friend Polinomio producto1(const Polinomio& P, const Polinomio& Q);
    friend Polinomio producto2(const Polinomio& P, const Polinomio& Q);
};

// Producto1 O(m^2 n^2)
Polinomio producto1(const Polinomio& P, const Polinomio& Q) {
    Polinomio R;
    return R;
}

// Producto2 O(m n log(m n))
Polinomio producto2(const Polinomio& P, const Polinomio& Q) {
    vector<pair<int,int>> T;
    Polinomio R;

    return R;
}

// Programa de prueba completo
int main() {
    Polinomio p;
    p.add(1,5);
    p.add(4,1);
    p.add(6,0);
    cout << "Polinomio P: ";
    p.print();

    Polinomio q;
    q.add(2,4);
    q.add(3,1);
    q.add(-5,0);
    cout << "Polinomio Q: ";
    q.print();

    // Suma
    Polinomio s = p + q;
    cout << "Suma P+Q: ";
    s.print();

    // Producto1
    Polinomio r1 = producto1(p, q);
    cout << "Producto1 P*Q: ";
    r1.print();

    // Producto2
    Polinomio r2 = producto2(p, q);
    cout << "Producto2 P*Q: ";
    r2.print();

    return 0;
}