#include <iostream>
#include<fstream>
using namespace std;
ifstream fin("nr");

void citire(int v[],int &n)
{
    fin>>n;
    for(int i=0;i<=n;i++)
        fin>>v[i];
}

int main()
{
    int v[1001],n,t,i;
    long long S=0,x=1;
    citire(v,n);
    fin>>t;

    for(i=0;i<=n;i++)
        {S=S+v[i]*x;
        x=x*t;
        }
    cout<<S;
    return 0;
}
