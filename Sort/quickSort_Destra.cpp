#include <iostream>

using namespace std;

int partition(int a[], int sinistra, int destra)
{
    // versione con pivot scelto alla fine
    int pivot = a[destra];
    int i = sinistra - 1;

    for (int j = sinistra; j < destra; j++)
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
    a[i + 1] = a[destra];
    a[destra] = temp;

    return i + 1;
}

void quickSort(int a[], int sinistra, int destra)
{
    if (sinistra < destra)
    {
        int p = partition(a, sinistra, destra);

        quickSort(a, sinistra, p - 1);
        quickSort(a, p + 1, destra);
    }
}

int main(int argc, char const* argv[])
{
    const int n = 8;
    int a[n] = {3, 6, 4, 1, 9, 22, 12, 4};

    for (int i = 0; i < n; i++)
    {
        cout << a[i] << endl;
    }
    
    cout << endl;

    quickSort(a, 0, n - 1);

    cout << "Dopo l'ordinamento\n" << endl;

    for (int i = 0; i < n; i++)
    {
        cout << a[i] << endl;
    }
    

    return 0;
}