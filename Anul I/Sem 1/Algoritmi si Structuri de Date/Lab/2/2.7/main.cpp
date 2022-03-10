#include <iostream>
#include<fstream>
using namespace std;
ifstream fin("nr");

void invers(int v[],int n)
{
    int st=0,dr=n;
    for(;st<dr;st++,dr--)
    {
        int aux;
        aux=v[st];
        v[st]=v[dr];
        v[dr]=aux;
    }
}

void afis(int v[],int n)
{
    int i;
    if(v[n]==1)
    cout<<"x^"<<n;
    else cout<<v[n]<<"x^"<<n;
       for(i=n-1;i>=1;i--)
        if(v[i]!=0)
        {
            if(v[i]!=1)
                cout<<" +"<<v[i]<<"x^"<<i;
            else cout<<" +"<<"x^"<<i;
        }
        if(v[0]!=0)
            cout<<" +"<<v[0];
}

void afis_simplu(int v[],int n)
{
    int i;
    for(i=0;i<=n;i++)
        cout<<v[i]<<' ';
    cout<<'\n';
}

void citire(int v[],int &n)
{
    fin>>n;
    for(int i=0;i<=n;i++)
        fin>>v[i];

}

void prod(int v[],int n,int w[],int m,int fin[],int &p)
{
    int i,j;
    p=n+m;

    for(i=0;i<=p;i++)
        fin[i]=0;

    for(i=0;i<=n;i++)
        for(j=0;j<=m;j++)
        fin[i+j]+=v[i]*w[j];

}
int main()
{
   int v[1001],w[1001],fin[1001],n,m,p;

    citire(v,n);    invers(v,n);
    citire(w,m);    invers(w,m);

    prod(v,n,w,m,fin,p);

    afis(fin,p);
    return 0;
}
