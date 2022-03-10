#include <iostream>
#include<fstream>
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

void interclasare(int v[],int st,int dr)
{
    int m,i,j;
    int k=0,aux[st+dr]; //vector aux[] în care vom interclasa elementele, tablou cu k elemente
    m=(st+dr)/2;
    //pozițiile de început ale celor 2 subsecvențe
    i=st;
    j=m+1;

    //interclasăm cele 2 subsecvențe ale tabloului
    while(i<=m && j<=dr)
        if(v[i] < v[j])
            aux[++k]=v[i++];
        else aux[++k]=v[j++];
    while(i<=m)
        aux[++k]=v[i++];
    while(j<=dr)
        aux[++k]=v[j++];

    for(i=dr;i>=st;i--)
        v[i]=aux[k--]; // in final, copiem conținutul vectorului aux in tabloul inițial
}

void mergesort(int v[],int st,int dr)
{
    int m;
    if(st<dr)
    {
        m=(st+dr)/2;
        mergesort(v,st,m); //trimitem în recursie funcția, pentru prima jumătate a tabloului
        mergesort(v,m+1,dr); //trimitem în recursie funcția, pentru a doua jumătate a tabloului
        interclasare(v,st,dr); //interclasăm cele 2 jumătăți ale tabloului ordonate
    }
}


int main()
{
    int v[101],n;
    citire(v,n);
    mergesort(v,1,n);
    afis(v,n);
    return 0;
}
