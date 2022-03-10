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


void citire(int v[],int &n)
{
    fin>>n;
    for(int i=0;i<=n;i++)
        fin>>v[i];

}

int main()
{
    int v[1001],w[1001],fin[1001],m,n,i;

    citire(v,n);    invers(v,n);
    citire(w,m);    invers(w,m);

    if(n>m)
        {for(i=m+1;i<=n;i++)
            w[i]=0;
            m++;
        }
    else {for(i=n+1;i<=m;i++)
            v[i]=0;
            n++;
            }

    for(i=0;i<=n;i++)
        fin[i]=v[i]+w[i];

    afis(fin,n);

    return 0;
}
