#include <iostream>
#include<vector>
#include<algorithm>
#include<fstream>
using namespace std;

ifstream fin("plimbare1.in");
ofstream fout("plimbare1.out");

vector<pair<int,pair<int,int> > >E; // vector de muchii
vector<int>tata,grad;
vector<pair<int,int > >APCM;

int n,m,nr_much,cost_total;


void init()
{
    int i;
    for(i=1;i<=n;i++)
        tata[i]=i;
}

int find_(int x)
{
    if(tata[x] == x)
        return x;
    return find_(tata[x]);
}

void union_(int x,int y)
{
    int r1,r2;
    r1=find_(x);
    r2=find_(y);

    if(grad[r1] > grad[r2])
        tata[r2]=r1;
    else if(grad[r1] < grad[r2])
        tata[r1]=r2;
    else
    {
        tata[r2]=r1;
        grad[r1]++;
    }
}

void citire()
{
    fin>>n>>m;

    tata.resize(n+1);
    grad.resize(n+1,0);
    E.resize(m+1);
    int tip;

    init();

    for(int i=1;i<=m;i++)
    {
        int x,y,c;
        fin>>tip;
        if(tip == 1)
        {
            fin>>x>>y;
            union_(x,y);
            nr_much++;
        }
        else
        fin>>E[i].second.first>>E[i].second.second>>E[i].first;
    }

    sort(E.begin(),E.end());

 //   for(auto p : E)
 //       cout<<p.first<<" "<<p.second.first<<" "<<p.second.second<<endl;
}

void kruskal()
{
    int x,y,c,i=1;
    while(nr_much<n-1 && i<=m)
    {
        c=E[i].first;
        x=E[i].second.first;
        y=E[i].second.second;

        if(find_(x) != find_(y))
        {

            nr_much++;
            APCM.push_back({x,y});
            union_(x,y);
            cost_total+=c;
        }
        i++;
    }
    fout<<cost_total;
}

int main()
{
    citire();
    kruskal();
    return 0;
}
