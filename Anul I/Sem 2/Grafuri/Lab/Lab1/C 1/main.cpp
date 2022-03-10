#include <iostream>
#include<fstream>
#include<vector>
using namespace std;

ifstream fin("date.in");
int viz[100],n,m;
vector <int>T[100];

void citire()
{
    int i,j;
    fin>>n>>m;
    for(int z=1;z<=m;z++)
    {
        fin>>i>>j;
        T[i].push_back(j);
        T[j].push_back(i);
    }
}

void afis(int v[],int n)
{
    int i;
    for(i=1;i<=n;i++)
        cout<<v[i]<<" ";
    cout<<endl;
}

void df(int x,int start,int st[],int &k,int &ok)
{
    if(!ok)
    {
        viz[x]=1;
        st[++k]=x;
      //  afis(st,k);
        for(auto i:T[x])
            if(viz[i]) // nodul este vizitat, intrebam daca este cel initial sa fie gata ciclul
            {
                if(i == start && k>3)
                    {
                        st[++k]=start;
                        cout<<"solutia este \n";
                        afis(st,k);
                        ok=1;
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
    citire();
    int i,k=0,st[100],ok=0;
    for(i=1;i<=n && !ok;i++)
    {
      //  cout<<"Nodul de start: "<<i<<endl;
        df(i,i,st,k,ok);
        for(int j=1;j<=n;j++)
            viz[j]=0;
      //      cout<<endl<<endl;
    }

    if(!ok)
        cout<<"Nu exista ciclu";

    return 0;
}
