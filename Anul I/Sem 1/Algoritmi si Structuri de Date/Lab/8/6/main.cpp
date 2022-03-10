#include <iostream>
#include<fstream>
using namespace std;

ifstream fin("nr");

struct nod
{
    nod*urm;
    int info;
};

struct coada
{
    nod*prim;
    nod*ultim;
};

void push(coada &c,int x)
{
    nod*q;
    q=new nod;
    q->info=x;
    if(!c.prim)
    {
        q->urm=NULL;
        c.prim=c.ultim=q;

    }
    else
    {
        q->urm=NULL;
        c.ultim->urm=q;
        c.ultim=q;
    }
}

int pop(coada &c)
{
    if(!c.prim)
        return -1;
    int x=c.prim->info;
    c.prim=c.prim->urm;
    return x;
}

void afis(coada c)
{
    nod*q;
    q=new nod;
    for(q=c.prim;q;q=q->urm)
        cout<<q->info<<' ';
    cout<<'\n';
}

void citire(coada &c,int &n,int &k)
{
    int i,x;
    fin>>n;
    for(i=1;i<=n;i++)
    {
        fin>>x;
        push(c,x);
    }
    fin>>k;
}

void initializareNULL(coada &c)
{
    c.prim=c.ultim=NULL;
}

int cautare(coada aux[],int k,int x)
{
    int i;
    for(i=1;i<=k;i++)
    {
        if(aux[i].prim==NULL)
            return i;
        if(x>aux[i].ultim->info)
            return i;
    }
    return -1;
}

int pozitie(coada aux[],int k,int x)
{
    int i;
    for(i=1;i<=k;i++)
        if(x==aux[i].prim->info)
        return i;

}

void rezolvare(coada c,int n,int k)
{
    int i,x,poz;
    coada aux[k];

    for(i=1;i<=k;i++)
        initializareNULL(aux[i]);

    for(i=1;i<=n;i++)
    {
        x=pop(c);
        poz=cautare(aux,k,x);

        if(poz==-1)
        {
            cout<<"Nu se poate rezolva";
            return;
        }
        else
        {
            cout<<"Se scoate elementul "<<x<<" si se introduce in linia "<<poz<<"\n";
            push(aux[poz],x);
        }
    }
        cout<<'\n';

        for(i=1;i<=n;i++)
        {
            poz=pozitie(aux,k,i);
            cout<<"Se scoate elementul "<<i<<" de pe linia auxiliara "<<poz<<'\n';
            pop(aux[poz]);
        }
}

int main()
{
    coada c;
    int n,k;

    initializareNULL(c);
    citire(c,n,k);
    rezolvare(c,n,k);

    return 0;
}
