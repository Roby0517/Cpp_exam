#include <iostream>

using namespace std;

class Classe
{
private:
    int anno;
    char sezione;
public:
    Classe() {}
    Classe(int anno, char sezione) : anno(anno), sezione(sezione) {}

    int getAnno() const { return anno; }
    char getSezione() const { return sezione; }
    
    void setAnno(int anno) { this->anno = anno; }
    void setSezione(char sezione) { this->sezione = sezione; }

    virtual double getMedia() const = 0;
    virtual void stampa() const {}

    ~Classe() {}
};

class Studente : public Classe
{
private:
    string nome;
    string cognome;
    double media;
public:
    Studente() {}
    Studente(int anno, char sezione, string nome, string cognome, double media) :
    Classe(anno, sezione), nome(nome), cognome(cognome), media(media) {}
    
    double getMedia() const override { return media; }

    void stampa() const override {
        cout << "Classe: " << getAnno() << "° " << getSezione() << ", "
        << nome << ", " << cognome << ", " << "Media: " << getMedia() << endl;
    }
    
    ~Studente() {}
};

void merge(Classe* a[], int sinistra, int centro, int destra)
{
    int i = sinistra;
    int j = centro + 1;
    int k = 0;
    Classe* temp[destra - sinistra + 1];

    while (i <= centro && j <= destra)
    {
        if (a[i]->getMedia() < a[j]->getMedia())
        {
            temp[k++] = a[i++];
        } else temp[k++] = a[j++];
    }
    
    while (i <= centro)
    {
        temp[k++] = a[i++];
    }

    while (j <= destra)
    {
        temp[k++] = a[j++];
    }
    
    for (int t = 0; t < k; t++)
    {
        a[sinistra + t] = temp[t];
    }
}

void mergeSort(Classe* a[], int sinistra, int destra)
{
    if (sinistra < destra)
    {
        int centro = (sinistra + destra) / 2;

        mergeSort(a, sinistra, centro);
        mergeSort(a, centro + 1, destra);
        merge(a, sinistra, centro, destra);
    }
}

int main(int argc, char const* argv[])
{
    const int n = 3;
    // double* a = new double[n];
    
    // cout << "Inserisci " << n << " elementi:\n" << endl;
    
    // for (int i = 0; i < n; i++)
    // {
    //     cin >> a[i];
    // }
    
    // cout << endl;
    
    // mergeSort(a, 0, n - 1);

    // cout << "Dopo l'ordinamento:\n" << endl;

    // for (int i = 0; i < n; i++)
    // {
    //     cout << a[i] << endl;
    // }

    // delete[] a;

    Classe** miaClasse = new Classe*[n];
    miaClasse[0] = new Studente(4, 'B', "Richard", "V", 8.5);
    miaClasse[1] = new Studente(4, 'B', "Ferdinand", "Brown", 10);
    miaClasse[2] = new Studente(4, 'B', "Gadolt", "Rizzler", 2.7);

    for (int i = 0; i < n; i++)
    {
        miaClasse[i]->stampa();
    }

    cout << "\nDopo l'ordinamento per media in ordine crescente:" << endl;
    
    mergeSort(miaClasse, 0, n - 1);

    for (int i = 0; i < n; i++)
    {
        miaClasse[i]->stampa();
    }

    return 0;
}