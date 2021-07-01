#include <iostream>
#include<fstream>
#include<time.h>
#include<stdlib.h>

using namespace std;

ifstream fin("date.in");

struct elem
{
    double w,val;
};

void citire(elem v[],int&n)
{
    fin>>n;

    for(int i=1;i<=n;++i)
        fin>>v[i].val;

     for(int i=1;i<=n;++i)
        fin>>v[i].w;

}

void afis(elem v[],int st,int dr)
{
    cout<<"Vectorul este \n";
    for(int i=st;i<=dr;i++)
        cout<<v[i].val<<" "<<v[i].w<<endl;
    cout<<"\n";
}

int partitionare(elem v[],int st,int dr)
{

    int p=st,u=dr;
    int poz=st+rand()%(dr-st+1);

    swap(v[p],v[poz]);
    elem piv = v[p];

    while(p<u)
    {
        while(p<u && piv.val <= v[u].val)
            u--;
        v[p]=v[u];

        while(p<u && piv.val >= v[p].val)
            p++;
        v[u]=v[p];
    }

    v[p]=piv;
    return p;
}

int weighted_median(elem v[],int n,int st,int dr)
{

    int poz = partitionare(v,st,dr),i;

    double W_st=0,W_dr=0;

    for(i=1;i<poz;i++)
        W_st+=v[i].w;

    for(i=poz+1;i<=n;i++)
        W_dr+=v[i].w;

/*
    cout<<"Pozitia este "<<poz<<" si W_st, W_dr: ";
    cout<<W_st<<" "<<W_dr<<"\n";
        afis(v,st,dr);
    cout<<"\n\n\n";
*/

    if(W_st <0.5)
        if(W_dr <=0.5)
            return v[poz].val;

    if(W_st >=0.5)
        return weighted_median(v,n,st,poz);

    return weighted_median(v,n,poz+1,dr);

}

int main()
{
   int n;
   elem v[100];
   srand(time(NULL));

   citire(v,n);
   cout<<weighted_median(v,n,1,n);
    return 0;
}
