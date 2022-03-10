#include <iostream>
#include<fstream>
#include<vector>
using namespace std;

ifstream fin("graf.in");

vector<int>T[100];
int n,m;
int viz[100];

void citire()
{
    int x,y,i;
    fin>>n>>m;
    for(i=1;i<=m;i++)
    {
        fin>>x>>y;
        T[x].push_back(y);

    }
}

void df(int x,int start,int st[],int &k,int &ok)
{
    int i;
    if(!ok)
    {
        viz[x]=1;
        st[++k]=x;

        for(auto i:T[x])
            if(viz[i])
            {
                if(start == i && k>3)
                {
                    ok=1;
                    st[++k]=start;

                    for(int j=1;j<=k;j++)
                        cout<<st[j]<<" ";

                }
            }
            else
            {
                df(i,start,st,k,ok);
            }
            viz[x]=0;
            k--;
    }
}

int main()
{
    int i,j,ok=0,k=0,st[100];
    citire();
    for(i=1;i<=n && !ok;i++)
    {
        df(i,i,st,k,ok);
        for(j=1;j<=n;j++)
            viz[j]=0;
    }

    if(!ok)
        cout<<"Realizabil";
    return 0;
}
