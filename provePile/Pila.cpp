#include <iostream>

using namespace std;

// Classe generica per il nodo
template<typename T> class Node
{
private:
    T key;
    Node* next;
public:
    Node() : next(nullptr) {}
    Node(const T& key) : key(key), next(nullptr) {}

    const T& getKey() const { return key; }
    Node* getNext() const { return next; }

    void setKey(const T& key) { this->key = key; }
    void setNext(Node* next) { this->next = next; }

    ~Node() {}
};

// Classe generica per la pila
template<typename T> class Stack
{
private:
    Node<T>* head;
public:
    Stack() : head(nullptr) {}
    
    // Costruttore per pila creata con un elemento
    Stack(const T& key) {
        head = new Node<T>(key);
    }

    Node<T>* getHead() const { return head; }
    void setHead(Node<T>* head) { this->head = head; }

    // Push serve a inserire da testa
    Stack* push(const T& key)
    {
        Node<T>* tmp = this->head;
        this->head = new Node<T>(key);
        this->head->setNext(tmp);
        return this;
    }

    // Pop serve a eliminare il nodo in testa
    Stack* pop()
    {
        if (this->getHead() == nullptr) return this;

        Node<T>* tmp = this->getHead();
        this->setHead(tmp->getNext());
        delete tmp;
        return this;
    }
    
    void del()
    {
        while (this->head != nullptr)
        {
            pop();
        }
    }

    // Stampa ottimizzata (può essere fatta più semplice rispetto a come l'ho fatta io)
    void stampa() const
    {
        Node<T>* tmp = this->getHead();
        if (tmp == nullptr)
        {
            cout << "Pila vuota" << endl;
            return;
        }
        
        while (tmp != nullptr)
        {
            cout << tmp->getKey() << endl;
            
            if (tmp->getNext() != nullptr)
            {
                cout << "|" << endl;
            } else cout << "|\nnullptr\n" << endl;
            
            tmp = tmp->getNext();
        }
    }

    ~Stack() {}
};

int main(int argc, char const* argv[])
{
    Stack<int>* pila = new Stack<int>(5);

    // Test funzioni
    pila->push(8);
    pila->push(3);
    pila->push(6);
    pila->push(9);
    
    pila->stampa();

    pila->pop();
    pila->pop();

    pila->stampa();

    pila->del();

    pila->stampa();

    return 0;
}