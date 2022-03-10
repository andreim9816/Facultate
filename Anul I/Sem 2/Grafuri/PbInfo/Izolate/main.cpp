#include <iostream>
#include<fstream>
#include<set>
#include<vector>
using namespace std;

ifstream fin("izolate.in");
ofstream fout("izolate.out");

set<int>E[101];
vector<int>V;
int n;

void citire()
{
    fin>>n;
    int x,y,i;
    while(fin>>x>>y)
    {
        E[x].insert(y);
        E[y].insert(x);
    }

    for(i=1;i<=n;i++)
        if(E[i].size()==0)
        V.push_back(i);
    fout<<V.size()<<" ";
    for(auto i=V.begin(); i!= V.end(); i++)
        fout<<*i<<" ";

}
int main()
{
    citire();
    return 0;
}
