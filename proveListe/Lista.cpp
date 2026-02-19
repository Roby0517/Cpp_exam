#include <iostream>

using namespace std;

// Nodo generico per la lista
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

// Lista generica
template<typename T> class List
{
private:
    Node<T>* head;
public:
    List() : head(nullptr) {}
    // Costruttore per quando la lista viene creata passandogli un valore
    List(const T& key)
    {
        head = new Node<T>(key);
    }

    Node<T>* getHead() const { return head; }
    void setHead(Node<T>* head) { this->head = head; }

    List* insert_testa(const T& key)
    {
        Node<T>* tmp = this->head;
        this->head = new Node<T>(key);
        this->head->setNext(tmp);
        return this;
    }
    
    List* insert_coda(const T& key)
    {
        Node<T>* tmp = this->getHead();

        if (tmp == nullptr)
        {
            return insert_testa(key);
        }

        while (tmp->getNext() != nullptr)
        {
            tmp = tmp->getNext();
        }
        
        tmp->setNext(new Node<T>(key));
        return this;
    }

    List* cancella_testa()
    {
        if (this->getHead() == nullptr) return this;
        
        Node<T>* tmp = this->getHead();
        this->setHead(tmp->getNext());
        delete tmp;
        return this;
    }

    List* cancella_coda()
    {
        Node<T>* prev = nullptr;
        Node<T>* tmp = this->getHead();

        if (tmp == nullptr) return this;

        while (tmp->getNext() != nullptr)
        {
            prev = tmp;
            tmp = tmp->getNext();
        }

        delete tmp;

        if (prev != nullptr)
        {
            prev->setNext(nullptr);
        } else this->head = nullptr;
        return this;
    }

    Node<T>* ricerca(const T& key)
    {
        Node<T>* tmp = this->getHead();
        while (tmp != nullptr && tmp->getKey() != key)
        {
            tmp = tmp->getNext();
        }
        return tmp;
    }

    // Inserimento di un valore come successivo del valore cercato
    List* inserisci_dopo(const T& key, const T& p)
    {
        Node<T>* prev = ricerca(p);
        if (prev == nullptr) return this;
        
        Node<T>* nodoChiave = new Node<T>(key);
        nodoChiave->setNext(prev->getNext());
        prev->setNext(nodoChiave);
        return this;
    }

    // Cancella un valore che è stato cercato;
    List* cancella(const T& key)
    {
        Node<T>* prev = nullptr;
        Node<T>* tmp = this->getHead();
        
        while (tmp != nullptr && tmp->getKey() != key)
        {
            prev = tmp;
            tmp = tmp->getNext();
        }
        
        if (tmp == nullptr) return this;

        if (prev == nullptr) return cancella_testa();
        
        prev->setNext(tmp->getNext());
        delete tmp;
        return this;
    }

    // Stampa ottimizzata (può essere fatta più semplice rispetto a come l'ho fatta io)
    void stampa() const
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

    void clear()
    {
        while (this->getHead() != nullptr)
        {
            this->cancella_testa();
        }
    }

    ~List()
    {
        clear();
    }
};

int main(int argc, char const* argv[])
{
    List<int>* lista = new List<int>(9);

    // Test funzioni
    lista->insert_testa(4);
    lista->insert_testa(7);
    lista->insert_coda(12);
    lista->inserisci_dopo(20, 4);
    lista->inserisci_dopo(15, 7);

    lista->stampa();

    lista->cancella_testa();

    lista->cancella_coda();

    lista->cancella(15);

    lista->stampa();

    lista->clear();

    lista->stampa();

    delete lista;

    return 0;
}