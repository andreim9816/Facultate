#include <iostream>
#include<fstream>
#include<vector>
#include<list>
using namespace std;

int m,n,viz[101];
vector <int>v[101];

ifstream fin("graf.in");

void citire()
{
    fin>>n>>m;
    int i,x,y;

    for(i=0;i<m;i++)
    {
        fin>>x>>y;
        v[x].push_back(y);
        v[y].push_back(x);
    }
}

void df(int x)
{
    cout<<x<<" ";

    int i;
    viz[x]=1;
    for(i=0;i<v[x].size();i++)
        if(viz[v[x][i]]==0)
        df(v[x][i]);
}

int main()
{
    citire();
    int i;
    for(i=1;i<=n;i++)
        if(viz[i]==0)
            df(i);
    return 0;
}
