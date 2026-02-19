#include <iostream>

using namespace std;

// ================================================

// classe template nodo per albero binario
template<typename T> class Node
{
private:
    Node* left;
    Node* right;
    Node* parent;
    T key;
public:
    // Costruttore default
    Node() : left(nullptr), right(nullptr), parent(nullptr) {}
    
    
    Node(const T& key) : key(key), left(nullptr), right(nullptr), parent(nullptr) {}

    // Getter
    Node* getLeft() const { return left; }
    Node* getRight() const { return right; }
    Node* getParent() const { return parent; }
    T getKey() const { return key; }

    // Setter
    void setLeft(Node* left) { this->left = left; }
    void setRight(Node* right) { this->right = right; }
    void setParent(Node* parent) { this->parent = parent; }
    void setKey(T key) { this->key = key; }

    // Metodi di 'pulizia'
    Node* removeLeft()
	{
		delete left;
		left = nullptr;
		return this;
	}

	Node* removeRight()
	{
		delete right;		
		right = nullptr;
		return this;
	}

	Node* removeParent()
	{
		delete parent;
		parent = nullptr;
		return this;
	}

	Node* clearLeft()
	{
		left = nullptr;
		return this;
	}
	Node* clearRight()
	{
		right = nullptr;
		return this;
	}
	Node* clearParent()
	{
		parent = nullptr;
		return this;
	}
	Node* clear()
	{
		right = nullptr;
		left = nullptr;
		parent = nullptr;
		return this;
	}
};

// ================================================

// classe template albero binario

template<typename T> class BinaryTree
{
private:
    Node<T>* root;

    // Inserisce un nodo nell'albero
    BinaryTree* insert(Node<T>* key, Node<T>* node)
    {
        // Se il valore del nodo passato è più piccolo di quello presente va a sinistra
        if (key->getKey() <= node->getKey())
        {
            // se a sinistra è libero inserisce il nuovo nodo
            if (node->getLeft() == nullptr)
            {
                // inserisce il nodo
                node->setLeft(key);

                // imposta come padre il nodo che stava scorrendo, sotto il quale si trova
                key->setParent(node);

                // altrimenti richiama se stessa e così scorre chiamando il figlio di sinistra
            } else insert(key, node->getLeft());
            
            // stesso controllo di prima, però se è più grande va a destra
        } else if (key->getKey() >= node->getKey())
        {
            if (node->getRight() == nullptr) // se a destra è libero inserisce il nuovo nodo
            {
                node->setRight(key); // idem
                key->setParent(node); // idem
            } else insert(key, node->getRight()); // altrimenti fa come prima però con il figlio di destra
        }
        return this;
    }

    // Calcola la lunghezza del 'ramo più alto' = altezza albero
    size_t getTreeHeight(Node<T>* node) const
    {
        if (node == nullptr) return 0;
        size_t leftH = getTreeHeight(node->getLeft()); // Cerca a sinistra
        size_t rightH = getTreeHeight(node->getRight()); // Cerca a destra

        // Ritorna il ramo più lungo + se stesso
        if (leftH > rightH)
        {
            return leftH + 1;
        } else return rightH + 1;
    }
    
    // Conta quanti nodi ci sono in totale nell'albero
    size_t getKeyCounter(Node<T>* node) const
    {
        if (node == nullptr) return 0;

        // Ritorna se stesso + tutti i nodi che trova a sinistra e a destra
        return 1 + getKeyCounter(node->getLeft()) + getKeyCounter(node->getRight());
    }

    // Verifica se il nodo passato è un figlio sinistro (metodo di supporto)
    bool isLeftChild(Node<T>* child)
    {
        if (child->getParent() != nullptr && child->getParent()->getLeft() != nullptr
            && child->getParent()->getLeft()->getKey() == child->getKey())
        {
            return true;
        }
        return false;
    }

    // Il successor è il figlio sinistro minore a partire dalla ramificazione destra, serve per deleteNode()
    Node<T>* successor(Node<T>* node)
    {
        if (node == nullptr)
        {
            return nullptr;
        } else if (node->getLeft() != nullptr)
        {
            return successor(node->getLeft());
        } else return node;
    }

    // Sostituisce un nodo con quello che viene passato
    void transplant(Node<T>* node, Node<T>* child)
    {
        if (node->getParent() == nullptr)
        {
            root = child;
        } else if (isLeftChild(node))
        {
            node->getParent()->setLeft(child);
        } else {
            node->getParent()->setRight(child);
        }
        if (child != nullptr)
        {
            child->setParent(node->getParent());
        }
    }

    // Serve a cancellare un nodo, ci sono 3 casi:
    // caso con 2 figli (il più complesso);
    // caso con un figlio (nodo foglia);
    // caso senza figli;
    Node<T>* deleteNode(Node<T>* node)
    {
        if (node == nullptr) return nullptr;

        // 2 figli:
        if (node->getLeft() != nullptr && node->getRight() != nullptr)
        {
            Node<T>* succ = successor(node->getRight());
            if (succ->getParent() != nullptr && succ->getParent()->getKey() != node->getKey())
            {
                transplant(succ, succ->getRight());
                succ->setRight(node->getRight());
                succ->getRight()->setParent(succ);
            }
            transplant(node, succ);
            succ->setLeft(node->getLeft());
            if (succ->getLeft() != nullptr)
            {
                succ->getLeft()->setParent(succ);
            }

            // solo 1 figlio (destro):
        } else if (node->getRight() != nullptr)
        {
            transplant(node, node->getRight());

            // solo 1 figlio (sinistro):
        } else if (node->getLeft() != nullptr)
        {
            transplant(node, node->getLeft());

            // 0 figli:
        } else {
            transplant(node, nullptr);
        }

        node->clear();
        return node;
    }

    // Funzione che si appoggia a deleteNode() per cancellare un nodo che è uguale alla chiave passata
    Node<T>* deleteKey(const T& key, Node<T>* node)
    {
        if (node == nullptr) return nullptr;
        if (key == node->getKey())
        {
            return deleteNode(node);
        } else if (key <= node->getKey())
        {
            return deleteKey(key, node->getLeft());
        } else {
            return deleteKey(key, node->getRight());
        }
    }

    // Visita l'albero in quest'ordine:
    // figlio sinistro - nodo - figlio destro
    void inOrderVisit(Node<T>* node) const
    {
        if (node != nullptr)
        {
            inOrderVisit(node->getLeft());
            printKey(node->getKey());
            inOrderVisit(node->getRight());
        }
    }
    
    // Visita l'albero in quest'ordine:
    // nodo - figlio sinistro - figlio destro
    void preOrderVisit(Node<T>* node) const
    {
        if (node != nullptr)
        {
            printKey(node->getKey());
            inOrderVisit(node->getLeft());
            inOrderVisit(node->getRight());
        }
    }
    
    // Visita l'albero in quest'ordine:
    // figlio sinistro - figlio destro - nodo
    void postOrderVisit(Node<T>* node) const
    {
        if (node != nullptr)
        {
            inOrderVisit(node->getLeft());
            inOrderVisit(node->getRight());
            printKey(node->getKey());
        }
    }

    // Visita l'albero livello per livello basandosi sull'altezza
    void levelOrderVisit(Node<T>* node, const int& level) const
    {
        if (node == nullptr)
        {
            if (level == 0)
            {
                cout << "_ ";
            }
            return;
        }
        if (level == 0)
        {
            printKey(node->getKey());
        } else if (level > 0) {
            levelOrderVisit(node->getLeft(), level - 1);
            levelOrderVisit(node->getRight(), level - 1);
        }
    }

    // trova il min di un sottoalbero
    void getMin(Node<T>* node, T& min) const
    {
        if (node->getLeft() == nullptr)
        {
            min = node->getKey();
            return;
        }
        getMin(node->getLeft(), min);
    }

    // trova il max di un sottoalbero
    void getMax(Node<T>* node, T& max) const
    {
        if (node->getRight() == nullptr)
        {
            max = node->getKey();
            return;
        }
        getMax(node->getRight(), max);
    }

    // Viene usata dalle altre funzioni per la stampa dei nodi/key
    void printKey(const T& key) const
    {
        if constexpr (is_pointer<T>::value)
        {
            cout << *key;
        } else cout << key;
        cout << " ";
    }

    // Confronta 2 valori
    int compare(const T& left, const T& right)
    {
        if constexpr (is_pointer<T>::value)
        {
            if (*left == *right)
            {
                return 0;
            } else if (*left < *right)
            {
                return -1;
            } else return 1;
        }
        if (left == right)
        {
            return 0;
        } else if (left < right)
        {
            return -1;
        } else return 1;
    }

public:
    // Costruttore senza parametri
    BinaryTree() : root(nullptr) {}

    // Costruttore parametrico (albero creato con un nodo)
    BinaryTree(Node<T>* root) : root(root) {}

    // Quando viene instanziato l'albero passandogli un valore (chiave)
    BinaryTree(const T& key) {
        root = new Node<T>(key); // quindi viene creato un nuovo nodo che diventa la radice
    }

    // Getter e Setter
    Node<T>* getRoot() const { return root; }
    Node<T>* setRoot(Node<T>* root) { this->root = root; }
    
    // Queste sono tutte le funzioni che l'utente può vedere, infatti sono più semplici
    // e non fanno altro che delegare il lavoro pesante alle funzioni che sono private
    BinaryTree* insert(const T& key)
    {
        Node<T>* newNode = new Node<T>(key); // crea un nuovo nodo
        if (root == nullptr) // controlla se la radice è "vuota", ovvero se c'è il primo nodo
        {
            root = newNode; // se non c'è allora il nuovo nodo creato diventa la radice
        } else insert(newNode, root); // altrimenti chiama la funzione per l'inserimento di un nodo normale
        return this;
    }

    size_t getTreeHeight() const
    {
        return getTreeHeight(root);
    }

    size_t getKeyCounter() const
    {
        return (getKeyCounter(root));
    }

    Node<T>* deleteKey(const T& key)
    {
        return deleteKey(key, root);
    }

    void inOrderVisit() const
    {
        inOrderVisit(root);
        cout << endl;
    }

    void preOrderVisit() const
    {
        preOrderVisit(root);
        cout << endl;
    }

    void postOrderVisit() const
    {
        postOrderVisit(root);
        cout << endl;
    }

    void levelOrderVisit() const
    {
        int h = getTreeHeight();
        for (int i = 0; i < h; i++)
        {
            levelOrderVisit(root, i);
            cout << endl;
        }
    }

    void getMin(T& min) const
    {
        if (root == nullptr)
        {
            return;
        }
        getMin(root, min);
    }

    void getMax(T& max) const
    {
        if (root == nullptr)
        {
            return;
        }
        getMax(root, max);
    }
    
    // Qui invece avviene la ricerca di un elemento nell'albero, in maniera iterativa
    // e non ricorsiva come lo sono la maggior parte delle funzioni del BST (albero binario di ricerca)
    // (Decisione del professore)
    void search(const T& key, T& find)
    {
        Node<T>* tmp = root;
        while (tmp != nullptr)
        {
            int val = compare(key, tmp->getKey());
            if (val == 0)
            {
                find = tmp->getKey();
                return;
            } else if (val == -1)
            {
                tmp = tmp->getLeft();
            } else tmp = tmp->getRight();            
        }
    }
    
};

int main(int argc, char const *argv[])
{
    // Istanza dell'albero
    BinaryTree<int>* tree = new BinaryTree(6);
    
    // Stampa della radice
    cout << "Root: " << tree->getRoot()->getKey() << endl;

    // Inserimento elementi
    tree->insert(5);
    tree->insert(3);
    tree->insert(4);
    tree->insert(7);
    tree->insert(10);
    tree->insert(15);
    tree->insert(12);
    
    tree->levelOrderVisit();

    // Stampa degli elementi cancellati
    // cout << "Deleted: " << tree->deleteKey(4)->getKey() << endl;
    // cout << "Deleted: " << tree->deleteKey(6)->getKey() << endl;
    // cout << "Deleted: " << tree->deleteKey(12)->getKey() << endl;

    // Stampa dell'altezza dell'albero e del numero delle chiavi
    cout << "Height: " << to_string(tree->getTreeHeight()) << endl;
    cout << "Number of key: " << to_string(tree->getKeyCounter()) << endl;

    // Visite pre-order, in-order, post-order, level-order
    cout << "Pre-Order" << endl;
    tree->preOrderVisit();

    cout << "In-Order" << endl;
    tree->inOrderVisit();

    cout << "Post-Order" << endl;
    tree->postOrderVisit();

    cout << "Level-Order" << endl;
    tree->levelOrderVisit();

    // Utilizzo delle funzioni getMax() e getMin()
    int max = 1000;
	tree->getMax(max);
	cout << "Max: "<< max << endl;
	int min = -1;
	tree->getMin(min);
	cout << "Min: " << min << endl;

    // Ricerca di un elemento all'interno dell'albero
	int search = -1;
	tree->search(10, search);
	cout << search << endl;

    return 0;
}