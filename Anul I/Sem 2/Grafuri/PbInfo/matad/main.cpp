#include <iostream>

#include<set>
using namespace std;


set<int>E[101];
int n;

int cautare(int nodx,int nody)
{
    // functie care cauta nody in lista de adiacenta pt nodx

    for(auto i=E[nodx].begin(); i!=E[nodx].end();i++)
        if( *i == nody)
            return 1;
    return 0;
}

int citire()
{
    int i,j,x;
    cin>>n;

    for(i=1;i<=n;i++)
    for(j=1;j<=n;j++)
    {
        cin>>x;
        if(x!=1 && x!=0) return 0;
        if(x==1)
        {
            if(i==j)    /// daca exista muchie de la i la i
                return 0;
            E[i].insert(j);
        }
    }

    for(i=1;i<=n;i++)
        for(auto j=E[i].begin(); j!= E[i].end();j++)
            if(!cautare(*j,i))
            return 0;

return 1;

}

int main()
{
    cout<<citire();
    return 0;
}
