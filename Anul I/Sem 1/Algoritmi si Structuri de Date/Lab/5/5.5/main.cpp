#include <iostream>
#include<fstream>
using namespace std;

ifstream fin("nr");
/* adunare pe numere mari */
struct nod
{
    nod*urm;
    int val;
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

void nr_lista(nod*&prim,nod*&ultim)
{ /// functie care transforma cifrele unui nr intr o lista
  /// ex: 542 ---> 2->4->5
    prim=ultim=NULL;
    char s[1001];
    fin.getline(s,1000);
    for(int i=0;s[i];i++)
        adi(prim,ultim,s[i]-'0');
}

void adunare(nod*prim1,nod*ultim1,nod*prim2,nod*ultim2,nod*&prim3,nod*&ultim3)
{
    nod*q,*r,*s;
    q=new nod;
    r=new nod;
    s=new nod;
    int t=0;
    for(q=prim1, r=prim2;q && r; q=q->urm,r=r->urm)
    {
        t=q->val+r->val+t;
        adf(prim3,ultim3,t%10);
        t=t/10;
    }
    if(q==NULL)
    for(s=r;s;s=s->urm)
    {
        t=t+s->val;
        adf(prim3,ultim3,t%10);
        t=t/10;
    }

    else
    {
        for(s=q;s;s=s->urm)
        {
            t=t+s->val;
            adf(prim3,ultim3,t%10);
            t=t/10;
        }
    }
    if(t)
        adf(prim3,ultim3,t);
}

void afis(nod*prim)
{ ///afisare recursiva a listei
    if(prim)
    {
        afis(prim->urm);
        cout<<prim->val;
    }

}


int main()
{
    nod*prim1,*prim2,*ultim1,*ultim2,*prim3,*ultim3;
    prim1=prim2=prim3=ultim1=ultim2=ultim3=NULL;

    nr_lista(prim1,ultim1);
    nr_lista(prim2,ultim2);

   adunare(prim1,ultim1,prim2,ultim2,prim3,ultim3);

    afis(prim3);

    return 0;
}
