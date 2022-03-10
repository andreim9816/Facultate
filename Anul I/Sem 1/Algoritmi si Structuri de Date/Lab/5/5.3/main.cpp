#include <iostream>
#include<fstream>
using namespace std;

ifstream fin("nr");
/* Inverseaza nodurile listei */
 struct nod
{
     int val;
     nod*urm;
};


void adf(nod*&prim,nod*&ultim,int val)
{
    nod *q;
    q=new nod;
    q->val=val;
    if(!prim)
        prim=ultim=q;
    else
    {
        ultim->urm=q;
        ultim=q;

    }
    ultim->urm=NULL;
}

void construct_lista(nod*&prim,nod*&ultim)
{
   int n,i,x;
   fin>>n;
   for(i=1;i<=n;i++)
   {
       fin>>x;
       adf(prim,ultim,x);
   }
}

void inversare(nod*&prim,nod*&ultim)
{

    if(prim!=ultim) ///lista nu are doar un nod
    {
        if(prim->urm==ultim) /// lista are doar 2 noduri
        {
            ultim->urm=prim;
            prim->urm=NULL;
            prim=ultim;
            ultim=prim->urm;
        }
        else
        {
            ///lista are cel putin 3 noduri
            nod*prev,*current,*next;

            prev=new nod;
            current=new nod;
            next=new nod;

            prev=prim;
            current=prev->urm;
            next=current->urm;

            while(next!=NULL)
            {
                current->urm=prev;
                prev=current;
                current=next;
                next=next->urm;
            }
            current->urm=prev;
            ultim=prim;
            ultim->urm=NULL;
            prim=current;
        }

    }

}

void afis(nod*prim,nod*ultim)
{

    nod *q;
    q=new nod;
    for(q=prim;q!=NULL;q=q->urm)
        cout<<q->val<<' ';

}

int main()
{
    nod*prim,*ultim;
    prim=ultim=NULL;
    construct_lista(prim,ultim);
    inversare(prim,ultim);
    afis(prim,ultim);

    return 0;
}
