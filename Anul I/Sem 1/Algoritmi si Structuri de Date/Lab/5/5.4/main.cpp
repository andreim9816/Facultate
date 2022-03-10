#include <iostream>
#include<fstream>
using namespace std;

ifstream fin("nr");
/* interclaseaza 2 liste */
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

void afis(nod*prim,nod*ultim)
{

    nod *q;
    q=new nod;
    for(q=prim;q!=NULL;q=q->urm)
        cout<<q->val<<' ';

}


void interclasare(nod*prim1,nod*ultim1,nod*prim2,nod*ultim2)
{
    nod*p1,*p2,*q;
    p1=new nod;
    p2=new nod;
     q=new nod; /// nodul curent

    p1=prim1->urm;
    p2=prim2->urm;

    if(prim1->val<=prim2->val)
    {
        prim1=prim1; /// la final, primul element al listei va fi prim1
        q=prim2;
        prim1->urm=q;

    }
    else
    {
        prim1=prim2;
        q=prim1;
        prim2->urm=q;

    }
    while(p1 && p2)
    {
        if(p1->val<=p2->val)
        {
            q->urm=p1;
            q=p1;
            p1=q->urm;
        }
        else
        {
            q->urm=p2;
            q=p2;
            p2=p2->urm;
        }
    }

    if(p1==NULL)
    {
        q->urm=p2;
        ultim1=ultim2;
    }
    else
    {
        q->urm=p1;
        ultim1=ultim1;
    }
}

int main()
{
   nod*prim1,*ultim1,*prim2,*ultim2;

   prim1=ultim1=prim2=ultim2=NULL;

   construct_lista(prim1,ultim1);
   construct_lista(prim2,ultim2);

   interclasare(prim1,ultim1,prim2,ultim2);
    afis(prim1,ultim1);

    return 0;
}
