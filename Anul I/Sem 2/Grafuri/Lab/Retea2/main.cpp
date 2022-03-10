#include <iostream>
#include<fstream>
#include<vector>
#include<cmath>
#include<list>
#include<algorithm>
#include<iomanip>
using namespace std;

short N,M,k=-1;
unsigned short t[2001],h[2001];

ifstream fin("retea2.in");
ofstream fout("retea2.out");

struct coord
{
    int x,y;
};

vector <coord> Nod; /// Nod[1] coord primului nod
vector <pair <double, pair <int,int> > >E;

int my_find(int x)
{
    if(x==t[x])
        return x;
    t[x]=my_find(t[x]);
    return t[x];
}

void my_union(int x,int y)
{
    int a,b;

    a=my_find(x);
    b=my_find(y);

    if(h[a]<h[b])
        t[a]=b;
    else if(h[a]>h[b])
        t[b]=a;
    else
    {
        t[b]=a;
        h[a]++;
    }
}

double dist(coord a, coord b)
{
    double x,y;
    x=a.x-b.x;
    y=a.y-b.y;
    return sqrt(x*x+y*y);
}

void citire()
{
    int i,j;
    fin>>N>>M;
    Nod.resize(N+M+1);

    for(i=1;i<=N+M;i++)
        fin>>Nod[i].x>>Nod[i].y;

    int l=(N+M)*(N+M-1)/2;
    E.resize(l+1);

    for(i=1;i<=N+M-1;i++)
        for(j=i+1;j<=N+M;j++)
    {
        E[++k].second.first=i;
        E[k].second.second=j;
        E[k].first=dist( Nod[i],Nod[j] );
    }
     sort(E.begin(),E.end());
}

void init()
{
    int i;
    for(i=1;i<=N;i++)
    {
        h[i]=0; /// conectam toate centralele la aceeasi
        t[i]=1;
    }

    for(i=N+1;i<=M+N;i++)
    {
        h[i]=0;
        t[i]=i;
    }
    h[1]=1;
}

void Kruskal(int n,int m)
{
        int i,nr=0;
        double S=0;

    for(i=0;i<k;i++)
    {
        int x,y;
        double w;
        y=E[i].second.second;
        x=E[i].second.first;
        w=E[i].first;

        if(my_find(x) != my_find(y))
        {
            nr++;
            pair <int,int>a;
            a.first=x;
            a.second=y;
            my_union(x,y);

            S=S+w; /// suma ponderilor APCM
        }
        if(nr==N+M-1)
            break;
    }

    fout<<fixed<<setprecision(6)<<S;

}

int main()
{
    citire();
    init();
    Kruskal(N,M);
    return 0;
}
