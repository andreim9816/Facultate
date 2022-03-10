#include <iostream>
#include<vector>
#include<algorithm>
#include<fstream>
using namespace std;

/// KRUSKAL

ifstream fin("apm.in");
ofstream fout("apm.out");

int n,m;

vector<pair<int,pair<int,int> > >L;
vector<pair<int,int> >T; // arborele APCM
vector<int>tata;
vector<int>grad;

int cmp(pair<int,pair<int,int> > x, pair<int,pair<int,int> >y)
{
    return (x.first<y.first);
}

void citire()
{
    int x,y,z,i;
    fin>>n>>m;

    tata.resize(n+1);
    grad.resize(n+1,0);

    for(i=1;i<=m;i++)
    {
        fin>>x>>y>>z;
        pair<int,pair<int,int> > c=make_pair(z,make_pair(x,y));
        L.push_back(c);
    }
    sort(L.begin(),L.end(),cmp);
}

void init()
{
    int i;
    for(i=1;i<=n;i++)
        tata[i] = i; // initial, fiecare nod e in propria componenta contexa
}

int find_(int x)
{
    if(x == tata[x])
        return x;
    return find_(tata[x]);
}

void union_(int x,int y)
{
    int r1,r2;
    r1=find_(x);
    r2=find_(y);

    if(grad[r1] > grad[r2])
        tata[r2]=r1;
    else if(grad[r1] < grad[r2])
        tata[r1]=r2;
    else
    {
        tata[r2]=r1;
        grad[r1]++;
    }
}

void kruskal()
{
    int cost=0,i,nr_much=0;

    for(i=0;;i++)
    {
        int c=L[i].first;
        int x=L[i].second.first;
        int y=L[i].second.second;

        if(find_(x) != find_(y))
        {
            union_(x,y);
            T.push_back(make_pair(x,y));
            cost+=c;
            nr_much++;
        }

        if(nr_much == n-1)
            break;
    }
    fout<<cost<<'\n';
    fout<<T.size()<<'\n';
    for(auto p:T)
        fout<<p.first<<" "<<p.second<<'\n';
}

int main()
{
    citire();
    init();
    kruskal();
    return 0;
}
