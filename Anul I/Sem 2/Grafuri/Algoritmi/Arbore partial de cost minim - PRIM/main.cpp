#include <iostream>
#include<vector>
#include<set>
#include<fstream>
using namespace std;

ifstream fin("apm.in");
ofstream fout("apm.out");

set<pair<int,int> >Q;
vector<pair<int,int> >L[200001];
vector<pair<int,int> >APCM;
vector<int>tata,d,viz;

int n,m;
int const inf = 10000000;
void citire()
{
    fin>>n>>m;
    d.resize(n+1,inf);
    tata.resize(n+1,0);
    viz.resize(n+1,0);

    for(int i=1;i<=m;i++)
    {
        int x,y,c;
        fin>>x>>y>>c;
        L[x].push_back({c,y});
      // L[y].push_back({c,x});
    }
}

void prim()
{
    Q.insert({0,1}); // incepem de la nodul 1
    int x,nr=0,c,cost=0;

    while(!Q.empty() && nr!=n-1)
    {
        do
        {
            x=Q.begin()->second;
            c=Q.begin()->first;
            Q.erase(Q.begin());
        }while(viz[x] == 1);

        cout<<x<<endl;
        nr++;
        viz[x]=1;
        APCM.push_back({tata[x],x});
        cost+=c;

        for(auto vec : L[x])
            if(d[vec.second] > vec.first)
            {
                Q.erase({d[vec.second],vec.second});
                d[vec.second] = vec.first;
                tata[vec.second] = x;
                Q.insert({d[vec.second], vec.second});
            }
    }
    APCM.erase(APCM.begin());

    fout<<cost<<'\n'<<APCM.size()<<'\n';
    for(auto p:APCM)
        fout<<p.first<< " "<<p.second<<endl;

}

int main()
{
    citire();
    prim();
    return 0;
}
