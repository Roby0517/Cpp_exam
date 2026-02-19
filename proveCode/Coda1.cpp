#include <iostream>

using namespace std;

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

template<typename T> class Queue
{
private:
    Node<T>* head;
public:
    Queue() : head(nullptr) {}
    Queue(const T& key)
    {
        head = new Node<T>(key);
    }

    Node<T>* getHead() const { return head; }
    void setHead(Node<T>* head) { this->head = head; }

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

    Queue* dequeue()
    {
        if (this->getHead() == nullptr)
        {
            return this;
        }
        Node<T>* tmp = this->getHead();
        this->setHead(tmp->getNext());
        delete tmp;
        return this;
    }

    void clear()
    {
        while (this->getHead() != nullptr)
        {
            dequeue();
        }
    }

    void stampa() const
    {
        if (this->getHead() == nullptr)
        {
            cout << "Coda vuota" << endl;
            return;
        }

        Node<T>* tmp = this->getHead();
        while (tmp != nullptr)
        {
            cout << tmp->getKey();
            if (tmp->getNext() != nullptr)
            {
                cout << " - ";
            } else cout << " - nullptr\n" << endl;
            tmp = tmp->getNext();
        }
    }

    ~Queue() {}
};

int main(int argc, char const* argv[])
{
    // Prova con una coda di char
    Queue<char>* coda = new Queue<char>('c');

    coda->enqueue('i')->enqueue('a')->enqueue('o');

    coda->stampa();

    coda->dequeue()->dequeue();

    coda->stampa();

    coda->clear();

    coda->stampa();

    delete coda;

    return 0;
}