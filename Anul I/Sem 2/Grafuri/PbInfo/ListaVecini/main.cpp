#include <iostream>
#include<fstream>
#include<set>
#include<list>

using namespace std;

ifstream fin("listavecini.in");
ofstream fout("listavecini.out");

int n;
set <int>E[101];

void citire()
{
    fin>>n;
    int x,y,i;
    while(fin>>x>>y)
    {
        E[x].insert(y);
        E[y].insert(x);
    }
}

void afis_vecini(int x)
{
    int i;
    fout<<E[x].size()<<" ";

    for(auto it=E[x].begin(); it!=E[x].end(); ++it)
        fout<<*it<<" ";
    fout<<'\n';
}

int main()
{
    citire();
    for(int i=1;i<=n;i++)
        afis_vecini(i);
    return 0;
}
