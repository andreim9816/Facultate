#include <iostream>
#include<fstream>
#include<cstring>
using namespace std;

ifstream fin("date");

struct nod
{
    nod*st,*dr;
    char s[50];
};

void creare(nod*&r,char s[])
{
    if(r==NULL)
    {
        r=new nod;
        strcpy(r->s,s);
        r->st=NULL;
        r->dr=NULL;
    }
    else if (strcmp(s,r->s)<0)
        creare(r->st,s);
    else creare(r->dr,s);
}

void afis(nod*r)
{
    if(r!=NULL)
    {
        afis(r->st);
        cout<<r->s<<' ';
        afis(r->dr);
    }
}

void citire(nod*&r,int &n)
{
    fin>>n; fin.get();
    char s[50];
    int i;
    r=NULL;
    for(i=1;i<=n;i++)
    {
        fin>>s;
        creare(r,s);
    }
}

int main()
{
    nod*r;int n;
    citire(r,n);
    afis(r);
    return 0;
}
