#include <iostream>
#include<fstream>
#include<time.h>
#include<cstdlib>
using namespace std;
/// quickselect

ifstream fin("nr");

void citire(int v[],int &n)
{
    int i;
    fin>>n;
    for(i=1;i<=n;i++)
        fin>>v[i];
}

void afis(int v[],int n)
{
    int i;
    for(i=1;i<=n;i++)
        cout<<v[i]<<' ';
}

int pivot(int v[],int p,int u)
{

    int piv;
    piv=v[u];
    while(p<u)
        {
            while(p<u && piv>=v[p])
                p++;
            v[u]=v[p];
            while(p<u && piv<=v[u])
                u--;
            v[p]=v[u];
        }
        v[u]=piv;
        return p;
}

int quickselect(int v[],int p,int u,int k)
{
    if(p==u)
        return v[p];
    int q=pivot(v,p,u);
    int nr=q-p+1;

    if(k==nr)
        return v[k];
    else if(k>nr)
        return quickselect(v,q+1,u,k-nr);
    else return quickselect(v,p,q-1,k);
}
int main()
{
  int v[100],n,k;
   citire(v,n);
   fin>>k;
   int x=quickselect(v,1,n,k);
    cout<<x;
    return 0;
}
