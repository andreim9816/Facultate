#include <iostream>
#include<fstream>
using namespace std;
ifstream fin("nr.in");

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

void afisSRD(nod*arb)
{
    if(arb)
    {
         afisSRD(arb->st);
        cout<<arb->vf<<' ';
        afisSRD(arb->dr);
    }
}

void afisSDR(nod*arb)
{

if(arb)
    {
        afisSDR(arb->st);
        afisSDR(arb->dr);
        cout<<arb->vf<<' ';
    }
}

int cautare(nod*arb,int x)
{
    if(!arb)
    return 0;
    else
    {
        if(arb->vf==x)
            return 1;
        else if(arb->vf<x)
            return cautare(arb->dr,x);
        else return cautare(arb->st,x);
    }
}

int maxim(nod*arb)
{
    if(!arb)
        return -1;
    else {if(arb->dr)
            return maxim(arb->dr);
          else return (arb->vf);
        }
}

void stergere(nod*&arb,int x)
{
    if(arb->vf<x)
        stergere(arb->dr,x);
    else if(arb->vf>x)
        stergere(arb->st,x);
    else
    {
        if(!arb->st && !arb->dr) // frunza
            arb=NULL;
        else if(!arb->st &&arb->dr)
        {
            arb=arb->dr;

        }
        else if(arb->st && !arb->dr)
        {
            arb=arb->st;
        }
        else // cazul cu 2 fii
        {
            nod*st,*dr,*tst,*tdr;
            st=new nod;
            dr=new nod;
            tst=new nod;
            tdr=new nod;

            dr=arb->dr;
            st=arb->st;

   /// cauta minimul din subarborele drept si maximul din cel stang

            if(st->dr!=NULL)
            {
                tst=st; /// tatal nodului din stanga radacinii
                while(tst->dr->dr!=NULL)
                    tst=tst->dr;
                st=tst->dr;

                arb->vf=st->vf;
                tst->dr=NULL;

            }

            else if(dr->st!=NULL)
            {
                tdr=dr;
                while(tdr->st->st!=NULL)
                    tdr=tdr->st;
                dr=tdr->st;

                arb->vf=dr->vf;
                tdr->st=NULL;
            }
            else
            {
                nod*q;
                q=new nod;
                q=arb->dr; /// tine minte subarborele drept pt a-l uni
                arb=arb->st;
                arb->dr=q;
            }
        }

    }
}

int main()
{
    nod*arb;
    arb=new nod;
    creare(arb);
   stergere(arb,7);
   afisRSD(arb);
    return 0;
}
