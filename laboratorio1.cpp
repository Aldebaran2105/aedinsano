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
        if (!current) {
            cout << "0" << endl;
            return;
        }
        while (current != nullptr) {
            cout << current->coeficiente << "x^" << current->exponente;
            if (current->next) cout << " -> ";
            current = current->next;
        }
        cout << endl;
    }

    // Insertar ordenado y combinar términos
    void add(int coef, int exp) {
        if (coef == 0) return;
        if (head == nullptr) {
            head = tail = new Node(coef, exp);
            return;
        }

        Node* current = head;
        
        if (exp > head->exponente) {
            Node* nuevo = new Node(coef, exp);
            nuevo->next = head;
            head = nuevo;
            return;
        }

        Node* prev = nullptr;
        while (current != nullptr && current->exponente > exp) {
            prev = current;
            current = current->next;
        }

        if (current != nullptr && current->exponente == exp) {
            current->coeficiente += coef;
        } else {
            Node* nuevo = new Node(coef, exp);
            if (prev == nullptr) {
                nuevo->next = head;
                head = nuevo;
            } else {
                prev->next = nuevo;
                nuevo->next = current;
                if (current == nullptr) tail = nuevo;
            }
        }
    }

    // Insertar al final (usando tail)
    void push_back(int coef, int exp) {
        if (coef == 0) return;
        
        if (tail != nullptr && tail->exponente == exp) {
            tail->coeficiente += coef;
            return;
        }
        
        Node* nuevo = new Node(coef, exp);
        if (head == nullptr) {
            head = tail = nuevo;
        } else {
            tail->next = nuevo;
            tail = nuevo;
        }
    }

    // Sobrecarga del operador +
    Polinomio operator+(const Polinomio& other) const {
        Polinomio result;
        Node* p = head;
        Node* q = other.head;
        
        while (p != nullptr && q != nullptr) {
            if (p->exponente > q->exponente) {
                result.push_back(p->coeficiente, p->exponente);
                p = p->next;
            } else if (q->exponente > p->exponente) {
                result.push_back(q->coeficiente, q->exponente);
                q = q->next;
            } else {
                int suma = p->coeficiente + q->coeficiente;
                if (suma != 0) result.push_back(suma, p->exponente);
                p = p->next;
                q = q->next;
            }
        }

        while (p != nullptr) {
            result.push_back(p->coeficiente, p->exponente);
            p = p->next;
        }
        while (q != nullptr) {
            result.push_back(q->coeficiente, q->exponente);
            q = q->next;
        }

        return result;
    }

    friend Polinomio producto1(const Polinomio& P, const Polinomio& Q);
    friend Polinomio producto2(const Polinomio& P, const Polinomio& Q);
};

// Producto1
Polinomio producto1(const Polinomio& P, const Polinomio& Q) {
    Polinomio R;
    Node* p = P.head;
    while (p != nullptr) {
        Node* q = Q.head;
        while (q != nullptr) {
            int coef = p->coeficiente * q->coeficiente;
            int exp = p->exponente + q->exponente;
            R.add(coef, exp);
            q = q->next;
        }
        p = p->next;
    }
    return R;
}

// Producto2
Polinomio producto2(const Polinomio& P, const Polinomio& Q) {
    vector<pair<int,int>> T;
    
    Node* p = P.head;
    while (p != nullptr) {
        Node* q = Q.head;
        while (q != nullptr) {
            T.push_back({p->exponente + q->exponente, p->coeficiente * q->coeficiente});
            q = q->next;
        }
        p = p->next;
    }

    sort(T.rbegin(), T.rend());

    Polinomio R;
    for (const auto& term : T) {
        R.push_back(term.second, term.first);
    }

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
