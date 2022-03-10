#include <iostream>

using namespace std;

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

int main()
{
    nod*stiva;
    stiva = new nod;
    stiva=NULL;

   afis(stiva);cout<<'\n';
   push(stiva,1);cout<<'\n';
   push(stiva,2);cout<<'\n';
   push(stiva,3);cout<<'\n';
   afis(stiva);cout<<'\n';
   cout<<my_search(stiva,2);cout<<'\n';
   cout<<my_search(stiva,4);cout<<'\n';
   cout<<my_empty(stiva);cout<<'\n';
   cout<<pop(stiva);cout<<'\n';
   afis(stiva);cout<<'\n';
   cout<<peek(stiva);cout<<'\n';
   afis(stiva);cout<<'\n';
   pop(stiva);cout<<'\n';
   pop(stiva);cout<<'\n';
   afis(stiva);cout<<'\n';
   cout<<pop(stiva);cout<<'\n';
   cout<<my_empty(stiva);cout<<'\n';
    return 0;
}
