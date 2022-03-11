#include <iostream>
#include<vector>
#include<algorithm>
#include<fstream>
using namespace std;

const int inf = 10000000;

ifstream fin("kruskal.in");
ofstream fout("kruskal.out");

int n,m;
vector<pair< int ,int > >T; /// arborele partial
vector<pair<int,pair<int,int > > >E; /// vector de muchii
vector<int>d; ///
vector<int>tata;
void citire()
{
    int x,y,c,i;
    fin>>n>>m;
    E.resize(m);
    d.resize(n+1,0);
    tata.resize(n+1);

    for(i=0;i<m;i++)
    {
        fin>>E[i].second.first>>E[i].second.second>>E[i].first;
    }
}

void init()
{
    int i;
    for(i=1;i<=n;i++)
        tata[i]=i;
}

int find_(int x)
{
    if(x==tata[x])
        return x;
    return find_(tata[x]);
}

void union_(int x,int y)
{
    int r1,r2;
    r1=find_(x);
    r2=find_(y);

    if(d[r1] > d[r2])
        tata[r2]=r1;
    else if(d[r1] < d[r2])
        tata[r1]=r2;
    else
    {
        d[r1]++;
        tata[r2]=r1;
    }
}

void kruskal()
{
    int nr_much=n-1,cost_total=0;
    while(nr_much != 0)
    {
        int cost,x,y;

        cost=E.begin()->first;
        x=E.begin()->second.first;
        y=E.begin()->second.second;
        E.erase(E.begin());

        if(find_(x) != find_(y))
        {
            T.push_back({x,y});
            union_(x,y);
            cost_total+=cost;
            nr_much--;
        }
    }
    fout<<cost_total<<'\n';
}

int main()
{
    citire();
    init();
    sort(E.begin(),E.end());
    kruskal();

    for(auto p : T)
        fout<<p.first<<" "<<p.second<<endl;
    return 0;
}