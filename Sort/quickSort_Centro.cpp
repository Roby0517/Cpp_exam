#include <iostream>

using namespace std;

int partition(int a[], int sx, int dx)
{
    // versione con pivot scelto al centro
    int mid = (sx + dx) / 2;
    int pivot = a[mid];
    int i = sx - 1;

    int tmp = a[mid];
    a[mid] = a[dx];
    a[dx] = tmp;

    for (int j = sx; j < dx; j++)
    {
        if (a[j] < pivot)
        {
            i++;
            int tmp = a[i];
            a[i] = a[j];
            a[j] = tmp;
        }
    }
    
    tmp = a[i + 1];
    a[i + 1] = a[dx];
    a[dx] = tmp;
    
    return i + 1;
}

void quickSort(int a[], int sx, int dx)
{
    if (sx < dx)
    {
        int p = partition(a, sx, dx);

        quickSort(a, sx, p - 1);
        quickSort(a, p + 1, dx);
    }
}

int main(int argc, char const* argv[])
{
    const int n = 5;
    int a[n] = {4, 1, 9, 7, 2};

    cout << "Prima dell'ordinamento\n" << endl;

    for (int i = 0; i < n; i++)
    {
        cout << a[i] << endl;
    }
    
    cout << "\nDopo l'ordinamento\n" << endl;
    
    quickSort(a, 0, n - 1);
    
    for (int i = 0; i < n; i++)
    {
        cout << a[i] << endl;
    }

    return 0;
}