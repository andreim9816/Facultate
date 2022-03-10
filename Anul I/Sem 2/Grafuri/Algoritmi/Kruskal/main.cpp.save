#include <iostream>
#include<vector>
#include<fstream>
#include<algorithm>
using namespace std;

ifstream fin("date.in");


int n,m;
int t[101],h[101];
vector<pair< pair <int,int>, int> >E;
vector<pair<int,int> >T;

int cmp(pair<pair<int,int>,int >x, pair<pair<int,int>,int >y)
{
    return(x.second < y.second);
}

void citire()
{
    int x,y,z,i,j;
    fin>>n>>m;
    E.resize(m);

    for(i=0;i<m;i++)
        fin>>E[i].first.first>>E[i].first.second>>E[i].second;

    sort(E.begin(),E.end(),cmp);
}

void init()
{
    int i;
    for(i=1;i<=n;i++)
    {
        t[i]=i;
        h[i]=0;
    }
}

int my_find(int x)
{
    if(x==t[x])
        return x;
    t[x]=my_find(t[x]);
    return t[x];
}

void my_union(int x,int y)
{
    int r1,r2;
    r1=my_find(x);
    r2=my_find(y);

    if(h[r1]>h[r2])
        t[r2]=r1;
    else if(h[r1]<h[r2])
        t[r1]=r2;
    else
    {
        t[r2]=r1;
        h[r1]++;
    }
}

void Kruskal()
{
    int i,x,y,j,z,nr_much=0;
    for(i=0;i<m;i++)
    {
        if(nr_much == n-1)
            break;

        x=E[i].first.first;
        y=E[i].first.second;

        if(my_find(x) != my_find(y))
        {
            nr_much++;
            my_union(x,y);
            T.push_back(make_pair(x,y));
        }
    }
}

int main()
{
    citire();
    init();
    Kruskal();

    for(auto i:T)
        cout<<i.first<<" "<<i.second<<endl;

    return 0;
}
