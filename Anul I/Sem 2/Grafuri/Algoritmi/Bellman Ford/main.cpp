#include <iostream>
#include<fstream>
#include<vector>
using namespace std;

ifstream fin("date.in");

int n,m;
 const int  inf = 100000;

vector<pair<int,int> >L[1001];

vector<int>tata,d;

void citire()
{
    int i,j,x,y,z;
    fin>>n>>m;
    tata.resize(n+1,0);
    d.resize(n+1,inf);

    for(i=1;i<=m;i++)
    {
        fin>>x>>y>>z;
        L[x].push_back({y,z});
    }
}


void BellmanFord()
{
    int i,j;
    d[1]=0;
    tata[1]=0;
    for(i=1;i<=n;i++)
    {
        for(j=0;j<L[i].size();j++)
        {

            int cost=L[i][j].second;
            int y=L[i][j].first;

            if(d[i] + cost < d[y])
            {
                d[y]=d[i]+cost;
                tata[y]=i;
            }
        }
    }

    int ok=0;

    for(i=1;i<=n && !ok;i++)
    {
        for(j=0;!ok && j<L[i].size();j++)
        {
            int cost=L[i][j].second;
            int y=L[i][j].first;

            if(d[i] + cost < d[y])
            {
               cout<<"Ciclu negativ\n";
               ok=1;
            }
        }
    }
}

int main()
{
    citire();
    BellmanFord();

    for(int i=1;i<=n;i++)
        cout<<d[i]<< " ";
    return 0;
}
