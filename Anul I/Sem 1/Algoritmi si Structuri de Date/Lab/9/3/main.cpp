#include <iostream>
#include<fstream>
using namespace std;

ifstream fin("date.in");
struct nod
{
    nod*st,*dr;
    double vf;
};

void inserare(nod*&arb,double x)
{
    if(!arb)
    {
        arb=new nod;
        arb->vf=x;
        arb->st=NULL;
        arb->dr=NULL;
    }
    else
    {
        if(x<arb->vf)
            inserare(arb->st,x);
        else inserare(arb->dr,x);
    }
}

void creare(nod*&arb)
{
    arb=NULL;
    int i,n;
    fin>>n;
    for(i=1;i<=n;i++)
    {
        double x;
        fin>>x;
        inserare(arb,x);
    }
}
void afisRSD(nod*arb)
{
    if(arb)
    {
        cout<<arb->vf<<' ';
        afisRSD(arb->st);
        afisRSD(arb->dr);
    }
}

void cauta(nod*r,int k1,int k2)
{
    if(r)
   {
    if(r->vf<k1)
    cauta(r->dr,k1,k2);
   else if(r->vf>k2)
    cauta(r->st,k1,k2);
   else
   {

       cauta(r->st,k1,k2);
        cout<<r->vf<<' ';
       cauta(r->dr,k1,k2);
   }

   }
}

int main()
{
    nod*r;
    int k1,k2;
    cout<<"k1= ";cin>>k1;
    cout<<"k2= ";cin>>k2;
    creare(r);
    cauta(r,k1,k2);
    return 0;
}
