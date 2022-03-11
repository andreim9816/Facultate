#include <iostream>
#include<fstream>
#include<vector>
#include<set>
using namespace std;

ifstream fin("catun.in");
ofstream fout("catun.out");

const int inf=100000;

vector<int>tata;
vector<int>d; // vector de distante
vector<int>viz; // vector de vizitati
vector<pair<int,int> >L[36001]; // lista de adiacenta
set<pair<int,int> >Q; /// coada in care pe prima pozitie va fi costul muchiei astfel incat sa fie ordonarea dupa el
vector<int>fortarete;

int n,m,k;

void citire()
{
    int x,y,z,i;
    fin>>n>>m>>k;

    tata.resize(n+1,0);
    d.resize(n+1,inf);
    viz.resize(n+1,0);

    for(i=0;i<k;i++)
    {
        fin>>x;
        fortarete.push_back(x);
        d[x]=0;
    }

    for(i=1;i<=m;i++)
    {
        fin>>x>>y>>z;
        L[x].push_back({z,y});
        L[y].push_back({z,x});
    }
}

void Dijkstra()
{
    int x,y,c;

    for (auto p: fortarete) // punem fortaretele in coada
        {
            Q.insert({0,p}); // distanta 0 si nodul respectiv
            tata[p]=p;
        }

    while(!Q.empty())
    {

            x=Q.begin()->second;
            Q.erase(Q.begin());


       // cout<<'\n'<<x<<": ";

        viz[x] = 1; // am vizitat

        for(auto p:L[x])
        { //  cout<<p.second<<" ";
            y=p.second; // nodul
            c=p.first; // costu

            if(d[y] > c + d[x])
            {
                d[y] = c+ d[x];
                tata[y]=tata[x];
                Q.insert({d[y],y});
            }
            else if(d[y]==d[x]+c)
                tata[y]=min(tata[y],tata[x]);
        }
    }
}

int main()
{
    citire();
    Dijkstra();

    for(auto p: fortarete)
        tata[p]=0;

    for(int p=1;p<=n;p++)
        fout<<tata[p]<<" ";

    return 0;
}