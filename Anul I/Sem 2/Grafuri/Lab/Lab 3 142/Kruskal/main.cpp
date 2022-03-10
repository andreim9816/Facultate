#include <iostream>
#include<fstream>
#include<vector>
#include<list>
#include<algorithm>
/*
    se retine cost x , y
*/
using namespace std;

ifstream fin("graf.in");

vector <pair<int, pair<int,int> > >E; /// graful
list < pair<int,int> >T;    /// lista de muchii

int t[100],h[100];

void init(int n)
{
    int i;
    for(i=1;i<=n;i++)
    {
        t[i]=i;
        h[i]=0;
    }
}

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

void citire(int &n,int &m)
{
    int i,w,S=0;
    fin>>n>>m;

    E.resize(m);
    init(n);

    for(i=0;i<m;i++)
        fin>>E[i].second.first>>E[i].second.second>>E[i].first;

    sort(E.begin(),E.end());
}

void Kruskal(int n,int m)
{
    int i,S=0;

    for(i=0;i<m;i++)
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

        if(T.size() == n-1)
            break;
    }

    cout<<endl<<"Muchiile sunt \n";
    for(auto p:T )
        cout<<p.first<<" "<<p.second<<endl;

    cout<<endl;

    cout<<S;

}

int main()
{
    int n,m;
    citire(n,m);
    Kruskal(n,m);
    return 0;
}
