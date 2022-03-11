#include <iostream>
#include<fstream>
#include<vector>
#include<cmath>
#include<list>
#include<algorithm>
using namespace std;

int N,M,l;
int t[2001],h[2001];

ifstream fin("date.in");

struct coord
{
    int x,y;
};

vector <coord> Nod; /// v[1] coord primului nod
vector <pair <double, pair <int,int> > >E;
list <pair<int,int> >T;    /// lista de muchii

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
    int i;
    fin>>N>>M>>l;
    Nod.resize(N+M+1);

    for(i=1;i<=N+M;i++)
        fin>>Nod[i].x>>Nod[i].y;

    E.resize(l);

    for(i=0;i<l;i++)
    {
        fin>>E[i].second.first>>E[i].second.second;
        E[i].first=dist( Nod[E[i].second.first],Nod[E[i].second.second]);
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
        int i,S=0;

    for(i=0;i<l;i++)
    {
        int x,y,w;
        y=E[i].second.second;
        x=E[i].second.first;
        w=E[i].first;


        if(my_find(x) != my_find(y))
        {
            pair <int,int>a;
            a.first=x;
            a.second=y;

            T.push_back(a);
            my_union(x,y);

            S=S+w; /// suma ponderilor APCM
        }

        if(T.size() == n+m-1)
            break;
    }

    cout<<S;

}

int main()
{

    citire();
    init();
    Kruskal(N,M);

    cout<<'\n';
    for(auto p:T)
        cout<<p.first<<" "<<p.second<<endl;
    return 0;
}