#include <iostream>
#include<fstream>
#include<vector>
#include<set>
using namespace std;

int n,m,C,p;
const int inf = 1000000;

ifstream fin("parc.in");
ofstream fout("parc.out");

vector<int>d; // vector de distante
vector<int>t; // vector de tati
vector<pair<int,int > >L[101];
set<pair<int,int > >Q; /// coada de prioritati

void citire()
{
    fin>>n>>m>>C;
    d.resize(n+1,inf);
    t.resize(n+1);

    int x,y,z,i,j;
    for(i=1;i<=m;i++)
    {
        fin>>x>>y>>z;
        L[x].push_back({z,y});
        L[y].push_back({z,x});
    }

    fin>>p;
    for(i=1;i<=p;i++)
    {
        fin>>x;
        Q.insert({0,x});
        d[x]=0;
        t[x]=x;
    }
}

void dijkstra()
{
    int x,y,cost;
    while(!Q.empty())
    {
        x=Q.begin()->second;
        Q.erase(Q.begin());

        for(auto e:L[x])
            {
                y=e.second;
                cost=e.first;
                if(d[y] > d[x] + cost)
                {
                    t[y]=t[x];
                    Q.erase(make_pair(d[y],y));
                    d[y] = d[x] + cost;
                    Q.insert(make_pair(d[y],y));
                }
            }
    }
}

int main()
{
    citire();
    dijkstra();
    fout<<t[C];

    return 0;
}
