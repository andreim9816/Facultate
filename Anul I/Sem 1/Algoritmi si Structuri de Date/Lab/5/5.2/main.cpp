#include <iostream>
#include<fstream>
using namespace std;

ifstream fin("nr");
/* construieste lista gata sortata */
 struct nod
{
     int val;
     nod*urm;
};

void adi(nod*&prim,nod*&ultim,int val)
{
    nod*q;
    q=new nod;
    q->val=val;
    if(!prim)
        {
        prim=ultim=q;
        ultim->urm=NULL;
        }
    else
    {
        q->urm=prim;
        prim=q;
    }
}

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
   nod*q,*r;
   q=new nod;
   fin>>n;
   for(i=1;i<=n;i++)
   {
       fin>>x;
       if(!prim)
        adf(prim,ultim,x);
       else if(x<prim->val)
        adi(prim,ultim,x);
       else if(x>ultim->val)
        adf(prim,ultim,x);
       else for(q=prim;q->urm;q=q->urm)
        if(x>=q->val && x<q->urm->val)
       {
           r=new nod;
           r->val=x;
           r->urm=q->urm;
           q->urm=r;
           q=q->urm;
           break;
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
    afis(prim,ultim);

    return 0;
}
