#include <iostream>
#include<fstream>
using namespace std;
ifstream fin("9");

struct nod
{
    nod*urm;
    int info;
};

void afis(nod*prim,nod*ultim)
{
    if(!prim)
        cout<<"COADA VIDA";
    else
    {
    nod *q;
    q=new nod;
    cout<<"OUT ";
    for(q=prim;q;q=q->urm)
        cout<<q->info<<" ";
    cout<<"IN ";
    }
    cout<<'\n';

}

void push(nod*&prim,nod*&ultim,int x)
{
    if(!prim) // lista e vida
    {
        nod*q;
        q=new nod;
        q->info=x;
        prim=ultim=q;
        ultim->urm=NULL;
    }
    else
    {
        nod*q;
        q=new nod;
        q->info=x;

        q->urm=NULL;
        ultim->urm=q;
        ultim=q;
    }
}


int pop(nod*&prim,nod*ultim)
{
    if(!prim)
        return -1;

    nod*q;
    q= new nod;

    q=prim;
    prim=prim->urm;

    int val=q->info;

    delete q;
    return val;
}

int peek(nod*prim,nod*ultim)
{
    if(!prim)
        return -1;
    return prim->info;
}

int my_empty(nod*prim,nod*ultim)
{
    if(!prim)
        return 1;
    return 0;
}

int my_search(nod*prim,nod*ultim,int x)
{
    nod *q;
    q=new nod;
    int k=1;
    for(q=prim;q;q=q->urm,k++)
    {
        if(q->info==x)
            return k;
    }
    return -1;
}

int main()
{
    nod*prim,*ultim;

    prim=new nod;
    ultim=new nod;
    prim=ultim=NULL;

    push(prim,ultim,1);
    push(prim,ultim,2);

    push(prim,ultim,4);
    push(prim,ultim,5);
     afis(prim,ultim);cout<<'\n';
    cout<<my_search(prim,ultim,2);cout<<'\n';
   cout<<my_search(prim,ultim,4);cout<<'\n';
    cout<<pop(prim,ultim);cout<<'\n';

    return 0;
}
