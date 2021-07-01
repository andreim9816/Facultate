#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

ifstream fin1("date.in");
ifstream fin2("cod.in");

vector<string>siruri;
string code;

int n, m;

void citire()
{
    fin1 >> n;
    int i ;

    for(i = 0 ; i < n ; i++)
    {
        string C;
        fin1 >> C;
        siruri.push_back(C);
    }

    n++;
    n++;

    siruri.push_back("0");
    siruri.push_back("1");

    fin2 >> code;

    fin1.close();
    fin2.close();
}

void pd()
{
    int i, j, pozString;
    int m = code.length();

    vector<int>minPart; // aici se intampla magia. minPart[i] - incepand cu pozitia i, sirul este partitionat in minPart[i] stringuri
    vector<int>next; // pozitie de unde incepe urmatorul string
    vector<int>stringRespectiv; // stringRespectiv[i] - al cate-lea string din cele citite se gaseste incepand cu pozitia i

    minPart.resize(m + 1);
    next.resize(m + 1);
    stringRespectiv.resize(m + 1);

    minPart[m - 1] = 1;
    minPart[ m ] = 0;

    next[m - 1] = m;
    next[m] = m;

    // cazu de baza
    if(code[m - 1] == '1')
        stringRespectiv[m - 1] = n - 1;
    else stringRespectiv[m -1] = n - 2;

    for(i = m - 2 ; i >= 0 ; i--)
    {
        int minim = 10000;
        for(j = 0 ; j < n; j++)
        {
            int pozitieInString = code.find(siruri[j],i); // cauta fiecare sir din cele date ca input in stringul code, incepand cu pozitia i
            if(pozitieInString == i) // daca incepand cu pozitia i am gasit un sir
             if(minim > minPart[i + siruri[j].length()]) // pot sa impart substring [i , i+1 , ... m-1] intr-un numar mai mic de stringuri
             {
                 next[i] = i + siruri[j].length(); // de unde incepe urmatorul string
                 stringRespectiv[i] = j; // care string se gaseste incepand cu pozitia i
                 minim = minPart[i + siruri[j].length()]; // minimul de impartiri in stringuri al substringului [i, i+1 , ... m-1]
                 minPart[i] = minim + 1; // updatez
             }
        }
    }

    //afisarea
    int pozitie = 0;
    while(pozitie < m)
    {
        cout<< siruri[stringRespectiv[pozitie]]<<" ";
        pozitie = next[pozitie];
    }

}

int main()
{
    citire();
    pd();
    return 0;
}
