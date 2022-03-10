#include <iostream>
#include<cstring>
#include<string>
#include<fstream>

using namespace std;

ifstream fin("date.in");

string prod_cartezian(string x, string y)
{
    // functie care primeste 2 stringuri si realizeaza produsul cartezian intre 2
    // caractere din fiecare

    string z;
    int i,j,lx,ly;
    lx=x.length();
    ly=y.length();

    for(i=0;i<lx;i++)
    for(j=0;j<ly;j++)
    {
        z=z+x[i]+y[j];
    }

    return z;
}

int cauta(string x,string y)
{
    // functie care cauta stringul y (de 2 caractere) in stringul x, mergand din 2 in 2 caractere

    int i,l=x.length();
    for(i=0;i<l;i+=2)
    {
        string aux;
        aux=aux+x[i]+x[i+1];
        if(aux == y)
            return 1;
        aux.erase();
    }
    return 0;
}

string gasire(string x, string date[])
{
    // functie care primeste un string, ce reprezinta un produs cartezian dintre 2 stringuri
    // (pe cate un caracter din fiecare si cauta cate o pereche de 2 caractere in productia
    // corespunzatoare

    int i,l=x.length()-x.length()%2-1;
    string rez;

    for(i=0;i<=l;i+=2)
    {
        string aux;
        aux=aux+x[i]+x[i+1];

        for(int j='A';j<='Z';j++)
            if(cauta(date[j-'A'],aux))
                rez=rez+char(j);
        aux.erase();
    }

    return rez;
}

int main()
{

 // citirea datelor

    string mat[100][100]; // matricea
    string date[40]; // pastrez datele de citire
    string y,z;
    char x;
    int i,l,j,k;

    //citirea si adaugarea productiilor

    while(fin>>x)
    {
        fin>>y;
        char *p;
        p=strtok(&y[0]," |");
        while(p)
        {

            date[x- 'A']=date[x-'A']+p;
            p=strtok(NULL,"| ");
        }

    }

    char cuv[]="baabaa"; ///
    l=strlen(cuv);

    // verificarea acceptare cuvant vid

    if(strlen(cuv)==0)
       {
        int lung='S'-'A';
        int l=date[lung].length();

        for(i=0;i<l;i++)
            if(date[lung][i]=='~')
                {
                    cout<<"Cuvantul vid este acceptat";
                    return 0;
                }
        cout<<"Cuvantul vid nu este acceptat";
        return 0;
       }

    // completarea primei linii

     for(i=0;i<l;i++)
        {

            for(j='A';j<='Z';j++)
            for(k=0;k<=date[j-'A'].length();k++)
                if(cuv[i]==date[j-'A'][k])
                mat[1][1+i]=mat[1][1+i]+char(j);
        }

    // completarea restului tabelului

    for(j=2;j<=l;j++)
        for(i=1;i<=l-j+1;i++)
            for(k=1;k<=j-1;k++)
                {
                    string aux=prod_cartezian(mat[k][i],mat[j-k][i+k]); // produsul cartezian
                    mat[j][i]=mat[j][i]+gasire(aux,date);   // adaug in matrice nodul din care pleaca productia
                    aux.erase();
                }

    for(i=0;i<mat[l][1].length();i++)
        if(mat[l][1][i]=='S')
    {
        cout<<"Cuvant acceptat";
        return 0;
    }
    cout<<"Cuvant neacceptat";
    return 0;
}
