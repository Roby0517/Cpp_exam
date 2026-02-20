#include <iostream>

using namespace std;

// Ricerca Sequenziale: Complessità: O(n)

int ricercaLineare(int array[], int dim, int key) {
    int x;
    for (int i = 0; i < dim; i++)
    {
        if (array[i] == key)
        {
            x = i;
            break;
        }
    }
    return -1; // Non trovato
}

// Ricerca Binaria: Complessità: O(log n)

int ricercaBinaria(int array[], int n, int key) {
    int sinistra = 0;
    int destra = n - 1;

    while(sinistra <= destra) {
        int centro = (sinistra + destra) / 2;

        if (array[centro] == key)
        {
            return centro;
        } else if (array[centro] < key)
        {
            sinistra = centro + 1;
        } else {
            destra = centro - 1;
        }
    }
    return -1; // Non trovato
}

// Insertion Sort: Complessità:
// Caso peggiore: O(n²) (array al contrario);
// Caso migliore: O(n) (già ordinato).

void insertionSort(int a[], int n) {
    int chiave = 0;
    for (int i = 1; i < n; i++)
    {
        chiave = a[i];
        int j = i - 1;

        while (j >= 0 && a[j] > chiave)
        {
            a[j + 1] = a[j];
            j--;
        }
        
        a[j + 1] = chiave;
    }
}

// Selection Sort: Complessità: Sempre O(n²)
void selectionSort(int a[], int n) {
    int temp;
    int min;
    for (int i = 0; i < n - 1; i++)
    {
        min = i;

        // cerca il minimo nella parte non ordinata
        for (int j = i + 1; j < n; j++)
        {
            if (a[j] < a[min]) {
                min = j;
            }
        }

        // scambia se necessario
        if (min != i)
        {
            int temp = a[i];
            a[i] = a[min];
            a[min] = temp;
        }
    }
}

// Bubble Sort: Complessità:
// Caso peggiore: O(n²)
// Caso migliore (già ordinato): O(n) grazie all’ottimizzazione.

void bubbleSort(int a[], int n) {
    bool scambiato;
    int temp;

    for (int i = 0; i < n - 1; i++)
    {
        scambiato = false;
        for (int j = 0; j < n - 1; j++)
        {
            if (a[j] > a[j + 1])
            {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
                scambiato = true;
            }
        }
        if (!scambiato)
        {
            break;
        }
        
    }
}

// Merge Sort: Complessità: Sempre O(n log n)

void merge(int a[], int sinistra, int centro, int destra) {
    int i = sinistra; // inizio sotto-array di sinistra
    int j = centro + 1; // inizio sotto-array di destra
    int k = 0; // indice per l'array temporaneo
    int temp[destra - sinistra + 1]; // array temp che serve a rimettere gli elementi ordinati nel posto giusto del vero array
    
    while (i <= centro && j <= destra)
    {
        if (a[i] < a[j])
        {
            temp[k++] = a[i++];
        } else {
            temp[k++] = a[j++];
        }
    }
    while (i <= centro)
        temp[k++] = a[i++];

    while (j <= destra)
        temp[k++] = a[j++];

    for (int t = 0; t < k; t++)
        a[sinistra + t] = temp[t];
}

void mergeSort(int a[], int sinistra, int destra) {
    if (sinistra < destra)
    {
        int centro = (sinistra + destra) / 2;

        mergeSort(a, sinistra, centro);
        mergeSort(a, centro + 1, destra);
        merge(a, sinistra, centro, destra);
    }
}

// Quick Sort: Complessità:
// Caso peggiore: O(n²)
// Caso medio e migliore: O(n log n) 🚀

int partition(int a[], int sx, int dx) {
    int pivot = a[dx];
    int i = sx - 1;
    
    for (int j = sx; j < dx; j++)
    {
        if (a[j] < pivot)
        {
            i++;
            int temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
    }
    
    int temp = a[i + 1];
    a[i + 1] = a[dx];
    a[dx] = temp;

    return i + 1;
}
void quickSort(int a[], int sx, int dx) {
    if (sx < dx)
    {
        int p = partition(a, sx, dx);
        
        quickSort(a, sx, p - 1);
        quickSort(a, p + 1, dx);
    }
}

int main(int argc, char const *argv[]) {
    int arr[7] = {1, 8, 6, 5, 2, 7, 3};

    int n = sizeof(arr) / sizeof(arr[0]);

    mergeSort(arr, 0, n - 1);

    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << endl;
    }

    // ==================================

    int arr2[5] = {8, 6, 2, 7, 3};

    n = sizeof(arr2) / sizeof(arr2[0]);

    quickSort(arr2, 0, n - 1);
    
    cout << "Arr2:" << endl;

    for (int i = 0; i < n; i++)
    {
        cout << arr2[i] << endl;
    }
    
    return 0;
}