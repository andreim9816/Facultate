#include <iostream>
#include<fstream>
#include <cstdlib>
#include<time.h>
using namespace std;

ifstream fin("nr");

void citire(int v[],int &n)
{
    int i;
    fin>>n;
    for(i=1;i<=n;i++)
        fin>>v[i];
}

void afis(int v[],int n)
{
    int i;
    for(i=1;i<=n;i++)
        cout<<v[i]<<' ';
}

int pivot(int v[],int p,int u )
{

    int piv;
    piv=v[p];
    while(p<u)
        {
            while(p<u && piv<=v[u]) //comparăm pivotul cu capătul din dreapta și parcurgem cât timp se păstreaza relația
                u--;
            v[p]=v[u];
            while(p<u && piv>=v[p]) //comparăm pivotul cu capătul din stânga și parcurgem cât timp se păstreaza relația
                p++;
            v[u]=v[p];
        }
        v[p]=piv; // copiem pivotul pe poziția finală a acestuia
        return p;
}

int partitionare(int v[],int p,int u)
{
    srand(time(NULL));
    int random=p+rand()%(u-p);
    swap(v[p],v[random]);
    return pivot(v,p,u);
}

void quick(int v[],int p,int u)
{
    int m;
    if(p<u)
    {
        m=partitionare(v,p,u); // apelăm funcția pentru a găsi poziția pivotului
        quick(v,p,m-1); // trimitem în recursie pentru zona de tablou situată în stânga componentei pivot
        quick(v,m+1,u); // trimitem în recursie pentru zona de tablou situată în dreapta componentei pivot
    }
}


int main()
{
   int v[101],n;

  srand (time(NULL));

    citire(v,n);
    quick(v,1,n);
    afis(v,n);
    return 0;
}
