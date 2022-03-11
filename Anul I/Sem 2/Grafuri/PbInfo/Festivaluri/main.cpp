#include <iostream>
#include<fstream>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;

ifstream fin("festivaluri.in");
ofstream fout("festivaluri.out");

const int inf = 10000000;
int n,m,p,z,r;
vector<pair<int,int> >L[101]; /// lista de adiacenta
vector<int>d; // vector distante
set<pair<int,int > >Q; /// coada "de prioritati". Se va retine {d[x],x}
vector<int>R; // intersectiile

void citire()
{
    int i,x,y,c;
    fin>>n>>m>>p>>z>>r;

    d.resize(n+1,inf);

    for(i=1;i<=m;i++)
    {
        fin>>x>>y>>c;
        L[x].push_back({c,y});
    }

    for(i=1;i<=r;i++)
    {
        fin>>x;
        R.push_back(x);
    }
}

void init()
{
    d[z]=0;
}

void dijkstra(int start)
{
    Q.insert({0,start});

    while(!Q.empty())
    {
        int x=Q.begin()->second ; /// nodul
        Q.erase(Q.begin());

        for(auto p:L[x])
        {
            int cost = p.first;
            int y= p.second;

            if(d[y] > d[x] + cost)
            {
                Q.erase(make_pair(d[y],y));
                d[y]=d[x]+cost;
                Q.insert({d[y],y});
            }
        }
    }
}

int main()
{
    citire();
    init();

    dijkstra(z);

    vector<int>aux;
    for(auto p:R)
        aux.push_back(d[p]);

    sort(aux.begin(),aux.end());

    int nr=0;

    for(int i=0;i<aux.size() && p>=0;i++)
        if(p>=aux[i])
        {
            nr++;
            p-=aux[i];
        }
    fout<<nr;

    return 0;
}