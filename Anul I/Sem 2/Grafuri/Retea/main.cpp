#include <iostream>
#include<vector>
#include<set>
#include<cmath>
#include<fstream>
using namespace std;

ifstream fin("retea.in");
ofstream fout("reatea.out");


vector<int>d; // vector de distante
vector<int>t; // vector de tati
vector<pair<int,int> >APCM; // arbore partial de cost minim
vector<pair<int,int> >centrale;
vector<pair<int,int> >blocuri;

const int inf = 10000000;
int n,m;

double distanta(int x,int y,int a,int b)
{
    double t,v;
    t=x-a;
    v=y-b;
    double rez=t*t+v*v;
    return sqrt(rez);
}

void citire()
{
    int x,y,i;
    fin>>n>>m;

    d.resize(n+1,0);
    t.resize(n+1,0);

    for(i=1;i<=n;i++)
    {
        fin>>x>>y;
        centrale.push_back({x,y});
    }

    for(i=1;i<=m;i++)
    {
        fin>>x>>y;
        blocuri.push_back({x,y});
    }

    for(i=0;i<m;i++)
    {
        mini=inf;
        for(j=0;j<n;j++)
            mini=min(mini,distanta(blocuri))
    }

}


int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
