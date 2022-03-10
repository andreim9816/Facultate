#include <iostream>
#include<fstream>
#include<vector>
#include<set>
using namespace std;

ifstream fin("firma.in");
ofstream fout("firma.out");

int n,m;
const int inf= 1000000;
vector<pair<int,int> >L[101]; // lista de adiacenta
set<pair<int,int > >Q; /// coada de prioritati ( set -> sortare implicit dupa prima chestie)
vector<int>d; /// vector de distante
vector<int>tata; /// vector de tati

void citire()
{
    int x,y,z,i;
    fin>>n>>m;

    for(i=1;i<=m;i++)
    {
        fin>>x>>y>>z;
        L[x].push_back({z,y});
        L[y].push_back({z,x});
    }
}

void init()
{

    for(int i=1;i<=n;i++)
    {
        d[i]=inf;
        tata[i]=0;
    }
}

void dijkstra(int start)
{
    int x,c,y;
    init();
    d[start]=0;
    Q.insert( {0,start} );
    while(!Q.empty())
    {
        x=Q.begin()->second; // nodul
        Q.erase(Q.begin());

        for(auto p: L[x])
        {
            y=p.second;
            c=p.first;

            if(d[y] > d[x] + c)
            {
                Q.erase(make_pair(d[y],y));
                d[y] = d[x] + c;
                tata[y] = x;
                Q.insert({d[y],y});
            }
        }
    }
}

void fct()
{
    int i,j,S=0,nod_min=1,mini=inf;
    for(i=1;i<=n;i++)
    {
        S=0;
        dijkstra(i);
        for(j=1;j<=n;j++)
            S+=d[j];

        if(mini > S)
        {
            mini=S;
            nod_min=i;
        }
    }
    fout<<nod_min;
}

int main()
{
   citire();
   d.resize(n+1,inf);
   tata.resize(n+1,0);
   fct();
   return 0;
}
