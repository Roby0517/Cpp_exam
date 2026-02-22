#include <iostream>
#include <limits.h>

using namespace std;

template<typename T> class Nodo
{
private:
    T dato;
    Nodo* next;
public:
    Nodo() : next(nullptr) {}
    Nodo(const T& dato) : dato(dato), next(nullptr) {}

    const T& getDato() const { return dato; }
    Nodo* getNext() const {  return next; }

    void setDato(const T& dato) { this->dato = dato; }
    void setNext(Nodo* next) { this->next = next; }

    ~Nodo() {}
};

template<typename T> class Lista
{
private:
    Nodo<T>* head;
public:
    Lista() : head(nullptr) {}
    Lista(const T& dato)
    {
        head = new Nodo<T>(dato);
    }
    
    Nodo<T>* getHead() const { return head; }
    void setHead(Nodo<T>* head) { this->head = head; }

    Lista* inserisci_testa(const T& dato)
    {
        Nodo<T>* tmp = this->head;
        this->head = new Nodo<T>(dato);
        this->head->setNext(tmp);
        return this;
    }
    
    Lista* inserisci_coda(const T& dato)
    {
        Nodo<T>* tmp = this->getHead();
        if (tmp == nullptr) 
        {
            return inserisci_testa(dato);
        }

        while (tmp->getNext() != nullptr)
        {
            tmp = tmp->getNext(); // scorre la lista fino all'ultimo nodo
        }

        tmp->setNext(new Nodo<T>(dato)); // mette come next il nodo che vogliamo inserire (in coda)
        return this;
    }

    Lista* cancella_testa()
    {
        if (this->getHead() == nullptr)
        {
            return this;
        }

        Nodo<T>* tmp = this->getHead();
        this->setHead(tmp->getNext());
        delete tmp;
        return this;
    }

    Lista* cancella_coda()
    {
        Nodo<T>* prev = nullptr;
        Nodo<T>* tmp = this->getHead();

        if (tmp == nullptr)
        {
            return this;
        }
        
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

    Nodo<T>* ricerca(const T& chiave)
    {
        Nodo<T>* tmp = this->getHead();
        while (tmp != nullptr && tmp->getDato() != chiave)
        {
            tmp = tmp->getNext();
        }
        return tmp;
    }
    
    Lista<T>* inserisci_dopo(const T& chiave, const T& precedente)
    {
        Nodo<T>* prev = ricerca(precedente);
        if (prev == nullptr)
        {
            return this;
        }
        Nodo<T>* nodoChiave = new Nodo<T>(chiave);
        nodoChiave->setNext(prev->getNext());
        prev->setNext(nodoChiave);
        return this;
    }

    Lista<T>* cancella(const T& chiave)
    {
        // dato che ricerca non mi fornisce il puntatore al nodo precedente
        // riscrivo la funzione ricerca adattandola
        
        Nodo<T>* prev = nullptr;
        Nodo<T>* tmp = this->getHead();
        
        while (tmp != nullptr && tmp->getDato() != chiave)
        {
            prev = tmp;
            tmp = tmp->getNext();
        }

        if (tmp == nullptr)
        {
            return this;
        }
        
        if (prev == nullptr)
        {
            return cancella_testa();
        }
        
        prev->setNext(tmp->getNext());
        delete tmp;
        return this;
    }

    ~Lista()
    {
        // cancella la testa finche' la lista non e' vuota
        while (this->getHead() != nullptr)
        {
            this->cancella_testa();
        }
    }
};

template<typename T> class Grafo
{
private:
    T** data;
    bool** adj;
    int size;
    int capacity;
    int source;
    
    int* findVertices(const T& first, const T& second) const
    {
        int* ret = new int[2]{-1, -1};
        for (int i = 0; i < size; i++)
        {
            if (*data[i] == first && ret[0] == -1)
            {
                ret[0] = i;
            } else if (*data[i] == second && ret[1] == -1)
            {
                ret[1] = i;
            }
            if (ret[0] != -1 && ret[1] != -1)
            {
                return ret;
            }
        }
        return ret;
    }

    bool checkAdjacency(const int& pos1, const int& pos2)
    {
        if (pos1 < size && pos2 < size)
        {
            return adj[pos1][pos2];
        }
        return false;
    }
    
    void BreadthFirstSearch(const int& source)
    {
        int* color = new int[this->getSize()];
        int* distances = new int[this->getSize()];
        int* predecessors = new int[this->getSize()];

        for (int i = 0; i < this->getSize(); i++)
        {
            if (i != source)
            {
                color[i] = 0;
                distances[i] = INT_MIN;
            } else {
                color[i] = 1;
                distances[i] = 0;
            }
            predecessors[i] = -1;
        }

        Lista<int>* queue = new Lista<int>();
        queue->inserisci_coda(source); // enqueue
        cout << "Visiting: ";
        while (queue->getHead() != nullptr)
        {
            // Nodo<int>* tmp = queue->cancella_testa(); // dequeue
            // Nodo<int>* tmp = queue->getHead();
            int u = queue->getHead()->getDato();
            queue->cancella_testa();

            for (int i = 0; i < this->getSize(); i++)
            {
                if (this->checkAdjacency(u, i))
                {
                    if (color[i] == 0) // If white
                    {
                        color[i]++; // Gray
                        // distances[i]++;
                        distances[i] = distances[u] + 1;
                        predecessors[i] = u;
                        queue->inserisci_coda(i);
                    }
                }
            }
            color[u]++; // Black
            cout << *(data[u]) << " ";
        }
        
        cout << endl;
        for (int i = 0; i < size; i++)
        {
            cout << "Precedessors of " << *data[i] << " is ";
            if (predecessors[i] >= 0)
            {
                cout << *(data[predecessors[i]]) << endl;
            } else cout << "Null" << endl;
        }

        // cleaning up
        delete[] color;
        delete[] distances;
        delete[] predecessors;
        delete queue;
    }

    void DepthFirstSearchVisit(int& vertex, int& time,  int color[], int discovered[], int finished[], int predecessors[])
	{
		time++;
		discovered[vertex] = time;
		color[vertex]++; // Gray
		cout << data[vertex] << " ";
		for (int i = 0; i < this->getSize(); i++)
        {
            if (this->checkAdjacency(vertex, i))
            {
                if (color[i] == 0) // If white
                {
                    predecessors[i] = vertex;
                    DepthFirstSearchVisit(i, time, color, discovered, finished, predecessors);
                }
            }
        }
		color[vertex]++; // Black
		time++;
		finished[vertex] = time;
	}

    void DepthFirstSearch()
	{		
		int* color = new int[this->getSize()];		
		int* predecessors = new int[this->getSize()];
		int* discovered = new int[this->getSize()];
		int* finished = new int[this->getSize()];
		int time = 0;
		/*
		   init algorithm
		*/
		for (int i = 0; i < size; i++)
		{
			color[i] = 0;
			predecessors[i] = -1;
			discovered[i] = 0;
			finished[i] = 0;
		}
		cout << "Visiting: ";
		for (int i = 0; i < size; i++)
        {
			if (color[i] == 0)
            {
                DepthFirstSearchVisit(i, time, color, discovered, finished, predecessors);
            }
        }	
		cout << endl;
		for (int i = 0; i < size; i++)
		{
			// string s = (predecessors[i] >= 0) ? data[predecessors[i]] : "Null";
			cout << "Precedessors of " << *data[i] << " is ";
            if (predecessors[i] >= 0)
            {
                cout << *(data[predecessors[i]]) << endl;
            } else cout << "Null" << endl;
		}
        
		//cleaning up
		delete[] color;
		delete[] discovered;
		delete[] finished;
		delete[] predecessors;
	}


public:
    Grafo() : data{ new T * [0] }, adj{ new bool[0] }, size{ 0 }, capacity{ 0 }, source{-1} {}
	Grafo(int capacity) : size{ 0 }, capacity { capacity }, source{-1}
	{
		data = new T * [capacity];
		adj = new bool* [capacity];
		for (int i = 0; i < capacity; i++)
        {
            adj[i] = new bool[capacity] {0};
        }
	}

    int getSize() const { return size; }
	int getCapacity() const { return capacity; }
	int getSourcePosition() { return source; }	
	bool setSourcePosition(const int& source)
	{		
		if (source < size)
		{
			this->source = source;
			return true;
		}
		return false;
	}
	
	
	int findVertex(const T& vertex) const
	{
		int ret = -1;
		for (int i = 0; i < size; i++)
		{
			if (*data[i] == vertex)
			{
				ret = i;
				break;
			};
		}
		return ret;
	}

	int addVertex(const T& vertex)	
	{
		T* val = new T(vertex);
		if (size < capacity)
		{			
			data[size] = val;
			size++;
			return size-1;
		}
		return -1;
	}
		

	bool addEdge(const T& first, const T& second)
	{
		int* pos = findVertices(first, second);
		bool ret = false;
		if (pos[0] != -1 && pos[1] != -1)
		{
			adj[pos[0]][pos[1]] = true;
			ret = true;
		}
		delete[] pos;
		return ret;
	
	}

	void printVertices()
	{
		for (int i = 0; i < size; i++)
        {
            cout << *(data[i]) << " ";
        }
		cout << endl;
	}

	void printAdjMatrix()
	{
		for (int i = 0; i < size; i++)
        {
            cout << "    " << i ;
        }
		cout << endl;
		for (int i = 0; i < size; i++)
        {
            cout << i  << " ";
            for (int j = 0; j < size; j++)			
            cout << (adj[i][j] ? "True" : "False") << " ";
            cout << endl;
        }
		cout << endl;
	}

	void BFS()
	{	  
      if(source>=0)
      {
        BreadthFirstSearch(static_cast<int>(source));
      }
	}

	void DFS()
	{				
		DepthFirstSearch();				
	}
    
    ~Grafo()
    {
        for (int i = 0; i < size; i++)
        {
            delete data[i];
        }

        for (int i = 0; i < capacity; i++)
        {
            delete[] adj[i];
        }
        
        delete[] data;
        delete[] adj;
    }
};

int main(int argc, char const* argv[])
{
    Grafo<char> g(10);

    g.addVertex('a');
	g.addVertex('b');
	g.addVertex('c');
	g.addVertex('d');
	g.addVertex('e');
	g.addVertex('f');
	g.addVertex('g');
	g.setSourcePosition(0);	

	g.addEdge('a', 'b');
	g.addEdge('a', 'c');	
	g.addEdge('b', 'd');
	g.addEdge('b', 'e');
	g.addEdge('c', 'f');
	g.addEdge('c', 'g');
	g.addEdge('g', 'a');

	cout << "The vertices are:" << endl;
	g.printVertices();
	cout << "Adjacency Matrix:" << endl;
	g.printAdjMatrix();
	cout << "BFS" << endl;
	g.BFS();
	cout << "DFS" << endl;
	g.DFS();

    return 0;
}