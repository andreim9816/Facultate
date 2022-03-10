#include <iostream>
#include<fstream>
using namespace std;

ifstream fin("nr");
void citire(int v[], int &n)
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

void insertMinHeap(int v[],int &n,int x)
{
    int i;
    v[++n]=x;
    i=n;
    while(i>1 && v[i]<=v[i/2])
    {
        swap(v[i],v[i/2]);
        i=i/2;
    }
}

void extractMin(int v[],int &n)
{
    v[1]=v[n--];

    int i,j,ok,a,b;

    i=1;

    while(i<=n)
        {
            ok=0;
            if(2*i<=n) /// exista nod in stanga
            {
                a=v[2*i];
                ok=1;
            }

            if(2*i+1<=n) /// exista nod in dreapta
            {
                b=v[2*i+1];
                ok=1;
            }

            if(a<b)
                j=2*i; /// coordonata cu care se va face schimbarea
            else
                j=2*i+1; /// coordonata cu care se va face schimbarea

            if(ok && v[i]>v[j]) /// daca radacina mai mare decat ce e in jos si am cu cine compara
                swap(v[i],v[j]);

        i=j;
        }

}

int return_min(int v[],int n)
{
    return v[1];
}

void HeapSort(int v[],int &n)
{
    int i,x,k=0,w[1001];

    fin>>n;
    ///citeste si insereaza intr-un minHeap
    for(i=1;i<=n;i++)
    {
        fin>>x;
        insertMinHeap(w,k,x);
    }
    /// construieste vectorul final: il scoate pe cel mai mic numar din heap si il pune in vector samd
    for(i=1;i<=n;i++)
    {
        x=return_min(w,k);
        extractMin(w,k);
        v[i]=x;
    }
}

int main()
{
    int v[1001],n;
    HeapSort(v,n);
    afis(v,n);
    return 0;
}
