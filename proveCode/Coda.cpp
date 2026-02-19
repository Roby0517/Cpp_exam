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

// Classe generica per la coda
template<typename T> class Queue
{
private:
    Node<T>* head;
public:
    Queue() : head(nullptr) {}
    // Costruttore per coda creata con un elemento
    Queue(const T& key) {
        head = new Node<T>(key);
    }

    Node<T>* getHead() const { return head; }
    void setHead(Node<T>* head) { this->head = head; }

    // Enqueue serve a inserire da coda
    Queue* enqueue(const T& key)
    {
        Node<T>* tmp = this->getHead();

        if (tmp == nullptr)
        {
            head = new Node<T>(key);
            return this;
        }
        
        while (tmp->getNext() != nullptr)
        {
            tmp = tmp->getNext();
        }
        
        tmp->setNext(new Node<T>(key));
        return this;
    }

    // Dequeue serve a eliminare il nodo in testa
    Queue* dequeue()
    {
        if (this->getHead() == nullptr) return this;
        Node<T>* tmp = this->getHead();
        this->setHead(tmp->getNext());
        delete tmp;
        return this;
    }

    void clear()
    {
        while (this->head != nullptr)
        {
            dequeue();
        }
    }

    // Stampa ottimizzata (può essere fatta più semplice rispetto a come l'ho fatta io)
    void stampa() const
    {
        Node<T>* tmp = this->getHead();
        if (tmp == nullptr)
        {
            cout << "Coda vuota" << endl;
            return;
        }
        
        while (tmp != nullptr)
        {
            cout << tmp->getKey() << " ";

            if (tmp->getNext() != nullptr)
            {
                cout << "- ";
            } else cout << "- nullptr\n" << endl;

            tmp = tmp->getNext();
        }
    }

    ~Queue()
    {
        clear();
    }
};

int main(int argc, char const* argv[])
{
    Queue<int>* coda = new Queue<int>(7);
    
    // Test funzioni
    coda->enqueue(2);
    coda->enqueue(4);
    coda->enqueue(1);
    coda->enqueue(8);

    coda->stampa();

    coda->dequeue();
    coda->dequeue();
    
    coda->stampa();
    
    coda->clear();

    coda->stampa();

    delete coda;

    return 0;
}