#include <iostream>
#include<fstream>
#include<vector>
#include<queue>
#include<set>
#include<algorithm>
using namespace std;

const int inf = 10000000;
int n,m;
vector<pair<int,int> >L[101];
vector<int>d;
vector<int>t;
queue<int>Q;
vector<int>gr,viz;
vector<int>sortat_top;

ifstream fin("date.in");
ofstream fout("date.out");

void citire()
{
    fin>>n>>m;
    int x,y,c;

    gr.resize(n+1,0);
    t.resize(n+1,0);
    d.resize(n+1,inf);
    viz.resize(n+1,0);

    for(int i=1;i<=m;i++)
    {
        fin>>x>>y>>c;
        L[x].push_back({c,y});
        gr[y]++;
    }
}

void top_sort(int x)
{
    viz[x]=1;

    for(auto e:L[x])
        if(!viz[e.second])
        top_sort(e.second);
    sortat_top.push_back(x);
}

void drum_minim(int st)
{
    d[st]=0;
    t[st]=0;

    while(!sortat_top.empty())
    {
        int x=sortat_top.front();
        sortat_top.erase(sortat_top.begin());

        for(auto v:L[x])
        {
            int y=v.second;
            int c=v.first;

            if(d[y] > d[x] + c)
            {
                d[y]=d[x]+c;
                t[y]=x;
            }
        }
    }
}

int main()
{
    citire();
    int i;
    for(i=1;i<=n;i++)
        if(!viz[i])
            top_sort(i);

    reverse(sortat_top.begin(),sortat_top.end());

    for(auto p:sortat_top)
        cout<<p<<" ";
    return 0;
}

