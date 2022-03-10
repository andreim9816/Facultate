#include <iostream>
#include<fstream>
using namespace std;

ifstream fin("nr");
/* inmultirea cu o cifra */
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

void nrToLista(nod*&prim,nod*&ultim)
{ /// functie care transforma cifrele unui nr intr o lista
  /// ex: 542 ---> 2->4->5
    prim=ultim=NULL;
    char s[1001];
    fin.getline(s,1000);
    for(int i=0;s[i];i++)
        adi(prim,ultim,s[i]-'0');
}

void prodScalar(nod*prim,nod*ultim,nod*&prim2,nod*&ultim2,int x)
{
    int t=0;
    nod*q;
    q=new nod;
    for(q=prim;q;q=q->urm)
    {
        t=t+(q->val)*x;
        adf(prim2,ultim2,t%10);
        t=t/10;
    }
    if(t)
        adf(prim2,ultim2,t);
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
    nod*prim,*ultim,*prim2,*ultim2;
    prim=prim2=ultim2=ultim=NULL;
    int x;
    nrToLista(prim,ultim);
    fin>>x;
    prodScalar(prim,ultim,prim2,ultim2,x);
    afis(prim2);
    return 0;
}
