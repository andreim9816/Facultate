#include <fstream>
#include <iostream>
#include <list>
using namespace std;

int d[100], tata[100], low[100], r, critic[100], time = 0;
list <pair<int, int> >E;
list<int>L[100];

int dfs(int x)
{
    time++;
    low[x] = d[x] = time;
    int nrc = 0; // nr copii
    for (int y:L[x])
    {
        if (d[y] == 0)
        {
            tata[y] = x;
            dfs(y); //low[y] is now oomputed

            low[x]=min(low[x],low[y]);

            if (low[y] >= d[x])
                critic[x] = 1;
            if(low[y] > d[x])
                E.push_back({x,y});
            nrc++;
        }
        else
            if(y != tata[x])
                low[x]=min(low[x],d[y]);
    }
    return nrc;
}

int main()
{
    int n, m, i, x, y;
    ifstream fin("date.in");
    fin>>n>>m;
    for (i = 0; i < m; i++)
    {
        fin>>x>>y;
        L[x].push_back(y);
        L[y].push_back(x);
    }
    cin>>r;
    if (dfs(r) > 1)
        critic[r] = true;
    else critic[r] = false;

    for (pair<int, int>p: E)
        cout<<p.first<<" "<<p.second<<endl;
    fin.close();

}