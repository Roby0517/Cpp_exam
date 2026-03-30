#include <iostream>
#include <fstream>

using namespace std;

// oppure si può fare di tipo ofstream ritornando lo stesso tipo
void writeFile(string filename, string message)
{
    ofstream myFile;
    myFile.open(filename, ios::app);

    if (myFile.is_open())
    {
        myFile << message;
        myFile.close();
    }
    // return myFile;
}

void readByChar(string filename)
{
    ifstream myFile;
    myFile.open(filename);
    if (myFile.is_open())
    {
        char ch;
        while (myFile.get(ch))
        {
            cout << ch << endl;
        }
        myFile.close();
    }
}

void readBySpace(string filename)
{
    ifstream myFile(filename);
    if (myFile.is_open())
    {
        string buffer;
        while (myFile >> buffer)
        {
            cout << buffer << endl;
        }
        myFile.close();
    }
}

void readByLine(string filename)
{
    ifstream myFile;
    myFile.open(filename);
    string buffer;
    if (myFile.is_open())
    {
        while (getline(myFile, buffer))
        {
            cout << buffer << endl;
        }
        myFile.close();
    }
}


int main(int argc, char const *argv[])
{
    string filename = "testo.txt";

    // ofstream file = writeFile(filename, "Messaggio 1\n");
    writeFile(filename, "Messaggio 1\n");

    cout << "Reading from " << filename << ":" << endl;

    readByChar(filename);
    cout << "===============" << endl;

    readBySpace(filename);
    cout << "===============" << endl;

    readByLine(filename);
    
    cout << endl;
    return 0;
}