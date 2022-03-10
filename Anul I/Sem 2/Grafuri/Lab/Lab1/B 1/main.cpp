#include <iostream>
#include<vector>
#include<queue>
#include<fstream>
using namespace std;

ifstream fin("date.in");

int n,nr,m,start,viz[100],tata[100];
vector<int> V[100],P;
queue <int>Q;

void citire()
{
    int i,j,x,y;
    fin>>n>>m;
    for(i=1;i<=m;i++)
    {
        fin>>x>>y;
        V[x].push_back(y);
        V[y].push_back(x);
    }
    fin>>nr;
    for(i=1;i<=nr;i++)
    {
        fin>>x;
        P.push_back(x);
    }
    cin>>start;
}


int BF(int start)
{
    int i,x,ok=0;
    viz[start]=1;
    Q.push(start);
    tata[start]=0;

    while(!Q.empty() && !ok)
    {
        x=Q.front();
        Q.pop();
        //cout<<x<<" ";
        for( auto i:V[x])
        if(!viz[i])
        {
            Q.push(i);
            tata[i]=x;
            viz[i]=1;
        }
    }

    for(auto i:P)
        if(viz[i]==1)
    {
        ok=i;
        break;
    }
    return ok;
}

void afis(int ok)
{
    if(ok)
    {
        afis(tata[ok]);
        cout<<ok<<" ";
    }
}

int main()
{
    int x;
    citire();
    if( (x=BF(start))!=0)
       afis(x);
    else cout<<"Nu se poate ajunge\n";
    return 0;
}
