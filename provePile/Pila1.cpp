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

template<typename T> class Stack
{
private:
    Node<T>* head;
public:
    Stack() : head(nullptr) {}
    Stack(const T& key)
    {
        head = new Node<T>(key);
    }

    Node<T>* getHead() const { return head; }
    void setHead(Node<T>* head) { this->head = head; }

    Stack* push(const T& key)
    {
        Node<T>* tmp = this->head;
        this->head = new Node<T>(key);
        this->head->setNext(tmp);
        return this;
    }

    Stack* pop()
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

    void del()
    {
        while (this->head != nullptr)
        {
            pop();
        }
        
    }

    void stampa() const
    {
        if (this->getHead() == nullptr)
        {
            cout << "Pila vuota" << endl;
            return;
        }
        
        Node<T>* tmp = this->getHead();
        
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
    
    ~Stack()
    {
        del();
    }
};

int main(int argc, char const* argv[])
{
    // Prova con una pila di double
    Stack<double>* pila = new Stack<double>(2.6);

    pila->push(4.2)->push(7.4)->push(8.9)->push(5.7);
    pila->stampa();
    pila->pop()->pop();
    pila->stampa();
    pila->del();
    pila->stampa();
    delete pila;

    return 0;
}