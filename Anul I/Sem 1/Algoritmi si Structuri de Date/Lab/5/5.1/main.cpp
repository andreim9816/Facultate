#include <iostream>
#include<fstream>

using namespace std;

ifstream fin("nr");
/* Insereaza intre oricare 2 noduri media lor aritmetica */
 struct nod
{
     float val;
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
    int n,i;
    fin>>n;
    for(i=1;i<=n;i++)
    {
        int x;
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

void inserareMedie(nod*&prim,nod*&ultim)
{
    nod*q,*r;
    q=new nod;

    for(q=prim;q->urm;q=q->urm)
    {
        r=new nod;
        r->val=(q->val+q->urm->val)/2.0;
        r->urm=q->urm;
        q->urm=r;
        q=q->urm;
    }

}

int main()
{
   nod*prim,*ultim;
    prim=new nod;
   ultim=new nod;
   prim=ultim=NULL;


   construct_lista(prim,ultim);
   inserareMedie(prim,ultim);
    afis(prim,ultim);
    return 0;
}
