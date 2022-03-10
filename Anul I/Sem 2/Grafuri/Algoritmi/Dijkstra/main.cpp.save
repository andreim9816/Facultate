#include <iostream>
#include<vector>
#include<set>
#include<fstream>
using namespace std;

ifstream fin("dijkstra2.in");
ofstream fout("dijkstra2.out");

int n,m,p;
const int inf= 1000000;
vector<pair<int,int> >L[100001]; // lista de adiacenta
set<pair<int,int > >Q; /// coada de prioritati ( set -> sortare implicit dupa prima chestie)
vector<int>d; /// vector de distante
vector<int>tata; /// vector de tati

void citire()
{
    int x,y,z,i;
    fin>>n>>m>>p;

    for(i=1;i<=m;i++)
    {
        fin>>x>>y>>z;
        L[x].push_back({z,y});
        L[y].push_back({z,x});
    }
}

void init()
{
    d.resize(n+1,inf);
    tata.resize(n+1,0);
}

void dijkstra(int start)
{
    int x,c,y;
    d[start]=0;

    Q.insert( {d[start],start} );
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

void afis_drum(int x)
{
    if(tata[x] !=0)
    {
        afis_drum(tata[x]);
        fout<<x<<" ";
    }
    else fout<<x<<" ";
}

int main()
{
    int start,i;
    citire();
    init();

    dijkstra(p);
    for(i=1;i<=n;i++)
        if(d[i] == inf)
            fout<<-1<<" ";
        else fout<<d[i]<<" ";

    /*
    for(i=1;i<=n;i++)
        if(i != start)
    {
        fout<<"Drumul minim de la " << start << " la "<< i<<" este de cost "<<d[i]<<" si este: ";
        afis_drum(i);
        fout<<endl;
    }
    */
    return 0;
}
