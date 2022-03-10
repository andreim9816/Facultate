#include <iostream>
#include<fstream>
#include<set>
#include<vector>

using namespace std;

set<int>E[101];
vector<int>V;
vector<int>ok;
int n;

ifstream fin("gradmax.in");
ofstream fout("gradmax.out");

void citire()
{
    int i,x,y;
    fin>>n;

    ok.resize(n+1,0);     /// punem 0

    while(fin>>x>>y)
    {
        E[x].insert(y);
        E[y].insert(x);
    }

    int maxi=0;
    for(i=1;i<=n;i++)
        {
        ok.at(i)=E[i].size();   /// punem pe ok[i] gradul
        }

    for(auto i=ok.begin(); i!= ok.end(); i++)
        if(maxi < *i)
        maxi = *i;

    for(auto i=ok.begin(); i!= ok.end(); i++)
        if(*i==maxi)
        V.push_back(i-ok.begin());  /// atentie!! i este o adresa

    fout<<V.size()<<" ";
    for(auto i=V.begin(); i!= V.end(); i++)
        fout<<*i<<" ";

}

int main()
{
    citire();
    return 0;
}
