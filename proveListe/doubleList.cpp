#include <iostream>

using namespace std;

template<typename T> class Node
{
private:
    T key;
    Node* next;
    Node* prev;
public:
    Node() : next(nullptr), prev(nullptr) {}
    Node(const T& key) : key(key), next(nullptr), prev(nullptr) {}

    const T& getKey() const { return key; }
    Node* getNext() const { return next; }
    Node* getPrev() const { return prev; }

    void setKey(const T& key) { this->key = key; }
    void setNext(Node* next) { this->next = next; }
    void setPrev(Node* prev) { this->prev = prev; }

    ~Node() {}
};

template<typename T> class DoubleList
{
private:
    Node<T>* head;
    Node<T>* tail;
public:
    DoubleList() : head(nullptr), tail(nullptr) {}
    DoubleList(const T& key) {
        head = tail = new Node<T>(key);
    }

    Node<T>* getHead() const { return this->head; }
    Node<T>* getTail() const { return this->tail; }
    void setHead(Node<T>* head) { this->head = head; }
    void setTail(Node<T>* tail) { this->tail = tail; }
    
    DoubleList* inserimentoTesta(const T& key)
    {
        Node<T>* tmp = this->head;
        Node<T>* newNode = new Node<T>(key);
        // this->head = new Node<T>(key);
        if (head == nullptr)
        {
            head = tail = newNode;
            return this;
        }
        
        newNode->setNext(tmp);
        this->head->setPrev(newNode);
        this->setHead(newNode);
        return this;
    }

    DoubleList* inserimentoCoda(const T& key)
    {
        Node<T>* newNode = new Node<T>(key);

        if (tail == nullptr)
        {
            head = tail = newNode;
            return this;
        }
        
        tail->setNext(newNode);
        newNode->setPrev(tail);
        this->setTail(newNode);
        return this;
    }

    DoubleList* cancella_testa()
    {
        if (this->getHead() == nullptr) return this;
        
        Node<T>* tmp = this->getHead();

        this->setHead(tmp->getNext());
        if (this->getHead() != nullptr)
        {
            this->getHead()->setPrev(nullptr);
        } else this->setTail(nullptr);
        
        delete tmp;
        return this;
    }

    DoubleList* cancella_coda()
    {
        Node<T>* prev = nullptr;
        Node<T>* tmp = this->getTail();
        
        if (tmp == nullptr) return this;

        this->setTail(tmp->getPrev());

        if (this->getTail() != nullptr)
        {
            this->getTail()->setNext(nullptr);
        } else this->setHead(nullptr);
        
        delete tmp;
        return this;
    }

    void stampaAvanti() const
    {
        Node<T>* tmp = this->getHead();

        if (tmp == nullptr)
        {
            cout << "Lista vuota" << endl;
            return;
        }
        
        while (tmp != nullptr)
        {
            cout << tmp->getKey();
            if (tmp->getNext() != nullptr)
            {
                cout << " - ";
            } else cout << " - nullptr" << endl;
            tmp = tmp->getNext();
        }
    }

    void stampaIndietro() const
    {
        Node<T>* tmp = this->getTail();

        if (tmp == nullptr)
        {
            cout << "Lista vuota" << endl;
            return;
        }

        while (tmp != nullptr)
        {
            cout << tmp->getKey();
            if (tmp->getPrev() != nullptr)
            {
                cout << " - ";
            } else cout << " - nullptr" << endl;
            tmp = tmp->getPrev();
        }
    }

    void clear()
    {
        while (this->getHead() != nullptr)
        {
            this->cancella_testa();
        }
    }

    ~DoubleList()
    {
        clear();
    }
};

int main(int argc, char const *argv[])
{
    DoubleList<int>* lista = new DoubleList<int>(30);

    lista->inserimentoTesta(4);
    lista->inserimentoTesta(7);
    lista->inserimentoTesta(19);
    lista->inserimentoCoda(22);
    lista->inserimentoCoda(2);
    lista->inserimentoCoda(29);

    lista->stampaAvanti();

    cout << endl;

    lista->stampaIndietro();

    lista->cancella_testa();
    lista->cancella_testa();
    lista->cancella_coda();
    lista->cancella_coda();

    cout << endl;
    
    lista->stampaAvanti();

    cout << endl;
    
    lista->stampaIndietro();

    delete lista;
    
    return 0;
}