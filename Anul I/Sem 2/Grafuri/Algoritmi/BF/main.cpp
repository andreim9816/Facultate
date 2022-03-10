#include <iostream>
#include<vector>
#include<queue>
#include<fstream>
using namespace std;

ifstream fin("graf.in");

vector <int>L[101]; /// lista de adiacenta
queue <int>Q; /// coada
int viz[101];

int n,m;

void citire()
{
    fin>>n>>m;
    int x,y,c,i;
    for(i=0;i<m;i++)
    {
        fin>>x>>y>>c;
        L[x].push_back(y);
        L[y].push_back(x);
    }
}

void bf(int x)
{
    int i,y;
    viz[x]=1;
    Q.push(x);
    while(!Q.empty())
    {
        x=Q.front();
        cout<<x<<" ";

        for(i=0;i<L[x].size();i++)
        {
            y=L[x][i];
            if(!viz[y])
            {
            Q.push(y);
            viz[y]=1;
            }
        }
        Q.pop();
    }
}

int main()
{
    citire();
    int i;
    for(i=1;i<=n;i++)
        if(!viz[i])
            bf(i);

    return 0;
}
