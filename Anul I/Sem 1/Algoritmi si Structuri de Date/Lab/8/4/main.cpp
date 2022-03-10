#include <iostream>
#include<fstream>
using namespace std;

ifstream fin("NR");


struct nod
{
    nod*urm;
    int info;
};

void push(nod*&vf,int val)
{
    nod*q;
    q=new nod;

    q->info=val;
    q->urm=vf;
    vf=q;

}

int pop(nod*&vf)
{
    if(!vf)
        return -1;

    nod*q;
    q=new nod;

    q=vf;
    int x=vf->info;

    vf=vf->urm;

    delete q;
    return x;

}

int peek(nod*vf)
{
    if(!vf)
        return -1;
    return vf->info;
}

int my_empty(nod*vf)
{
    return(!vf);
}

int my_search(nod*vf,int x)
{
    nod*q;
    q=new nod;

    int k=0;

    for(q=vf;q;q=q->urm,k++)
        {
            if(q->info == x)
                return k;
        }
    return -1;
}

void afis(nod*vf)
{

    if(!vf)
        cout<<"STIVA VIDA";
    else
    {
        cout<<"VARF ";

    nod*q;
    q=new nod;
    for(q=vf;q;q=q->urm)
    {
        cout<<q->info<<" ";
    }

        cout<<"BAZA ";
    }
    cout<<'\n';
}

void rezolvare(nod*vf)
{
    int i,n,x;
    fin>>n;
    for(i=1;i<=n;i++)
    {
        fin>>x;
        if(vf)
            if(vf->info==x)
                pop(vf);
            else push(vf,x);
        else push(vf,x);
    }
    if(my_empty(vf))
        cout<<"VALID";
    else cout<<"INVALID";
}
int main()
{
    nod*stiva;
    stiva=new nod;
    stiva=NULL;
    rezolvare(stiva);
    return 0;
}
