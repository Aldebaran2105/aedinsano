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
        // Caso especial: si el exponente es mayor que head (insertar al inicio)
        if (exp > head->exponente) {
            Node* nuevo = new Node(coef, exp);
            nuevo->next = head;
            head = nuevo;
            return;
        }

        // Buscar posición
        Node* prev = nullptr;
        while (current != nullptr && current->exponente > exp) {
            prev = current;
            current = current->next;
        }

        // Si existe el exponente, sumar
        if (current != nullptr && current->exponente == exp) {
            current->coeficiente += coef;
        } else {
            // Insertar nuevo nodo
            Node* nuevo = new Node(coef, exp);
            if (prev == nullptr) { // Debería haber caído en el if inicial, pero por seguridad
                nuevo->next = head;
                head = nuevo;
            } else {
                prev->next = nuevo;
                nuevo->next = current;
                if (current == nullptr) tail = nuevo; // Actualizar tail si es al final
            }
        }
    }

    // Insertar al final (usando tail para O(1))
    void push_back(int coef, int exp) {
        if (coef == 0) return;
        
        // Optimización: Si el último término tiene el mismo exponente, sumar coeficientes
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

    // Sobrecarga del operador + (Suma O(m+n))
    Polinomio operator+(const Polinomio& other) const {
        Polinomio result;
        Node* p = head;
        Node* q = other.head;
        
        // Algoritmo de mezcla (Merge)
        while (p != nullptr && q != nullptr) {
            if (p->exponente > q->exponente) {
                result.push_back(p->coeficiente, p->exponente);
                p = p->next;
            } else if (q->exponente > p->exponente) {
                result.push_back(q->coeficiente, q->exponente);
                q = q->next;
            } else {
                // Exponentes iguales
                int suma = p->coeficiente + q->coeficiente;
                if (suma != 0) result.push_back(suma, p->exponente);
                p = p->next;
                q = q->next;
            }
        }

        // Copiar los restantes
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

// Producto1 O(m^2 n^2) - Iterativo con inserción ordenada
Polinomio producto1(const Polinomio& P, const Polinomio& Q) {
    Polinomio R;
    Node* p = P.head;
    while (p != nullptr) {
        Node* q = Q.head;
        while (q != nullptr) {
            int coef = p->coeficiente * q->coeficiente;
            int exp = p->exponente + q->exponente;
            
            // Usamos add() que recorre la lista para ordenar/combinar -> O(k)
            R.add(coef, exp);
            
            q = q->next;
        }
        p = p->next;
    }
    return R;
}

// Producto2 O(mn log(mn)) - Generar, Ordenar, Reducir
Polinomio producto2(const Polinomio& P, const Polinomio& Q) {
    // Usaremos pair<exponente, coeficiente> para facilitar el ordenamiento
    vector<pair<int,int>> T;
    
    // 1. Generar todos los términos O(mn)
    Node* p = P.head;
    while (p != nullptr) {
        Node* q = Q.head;
        while (q != nullptr) {
            T.push_back({p->exponente + q->exponente, p->coeficiente * q->coeficiente});
            q = q->next;
        }
        p = p->next;
    }

    // 2. Ordenar por exponente descendente O(mn log(mn))
    // std::sort ordena pares basándose primero en .first (exponente)
    // Usamos rbegin() y rend() para orden descendente (mayor a menor)
    sort(T.rbegin(), T.rend());

    // 3. Construir polinomio resultado O(mn)
    Polinomio R;
    for (const auto& term : T) {
        // term.first es exponente, term.second es coeficiente
        // push_back usa tail, así que combina términos consecutivos iguales en O(1)
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
