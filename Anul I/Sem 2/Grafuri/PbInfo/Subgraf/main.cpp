#include <iostream>
#include<set>
#include<fstream>
using namespace std;

ifstream fin("subgraf.in");
ofstream fout("subgraf.out");

int n;
set<int>E[101];

int prim(int x)
{
    if(x<2)
        return 0;
    if(x==2)
        return 1;
    if(x%2==0)
        return 0;
    for(int i=3;i*i<=x;i++)
        if(x%i==0)
        return 0;
    return 1;
}

void citire()
{
    int x,y,i;
    fin>>n;

    while(fin>>x>>y)
    {
        E[x].insert(y);
        E[y].insert(x);
    }
}

void elimin_nod(int x)
{

    for(auto i=E[x].begin(); i!=E[x].end(); i++)
    {
        E[*i].erase(x); /// il elimin pe x din lista de adiacenta a lui *i
    }
    E[x].clear();
}
void elimin()
{
    int i;
    for(i=1;i<=n;i++)
        if(prim(i) == 1 )
            elimin_nod(i);
}
int numara()
{
    int i,s=0;
    for(i=1;i<=n;i++)
        s+=E[i].size();
    return s/2;
}
int main()
{
    citire();
    elimin();
    fout<<numara();
    return 0;
}
