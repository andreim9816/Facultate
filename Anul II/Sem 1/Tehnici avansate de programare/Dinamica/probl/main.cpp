#include <iostream>
#include<queue>
#include<fstream>
#include<vector>
#include<algorithm>
using namespace std;

int cmp(pair<int,int>x, pair<int,int>y) // sortez vectorul descrescator dupa t, si descrescator dupa p
{
    if(x.second.first < y.second.first || (x.second.first == y.second.first && x.second.second < y.second.second))
        return 0;
    return 1;
}

void citire(vector<pair<int,pair<int,int>>> &v,int &n)
{
    ifstream fin("date.in");

    int p,t,i;

    fin>>n;

    for(i=1;i<=n;i++)
    {
        fin >> t >> p;
        v.push_back({t, p});
    }

    fin.close();
}

struct cmp_pq
{
   bool operator()(pair<int,int>x, pair<int,int> y)
    {
     if(x.first < y.first) /// sortez descrescator dupa speed
        return true;
       return false;
    }
};


int greedy(vector<pair<int,int>>v,int n)
{
    int i=0,h_max = v[0].first, T=0;
    priority_queue< pair<int,int>, vector<pair<int,int>>, cmp_pq >pq; // coada de prioritati

    for(i = 0 ; i < n ; i++)
     pq.push({v[i].first , v[i].second})
}

int main()
{
    vector<pair<int,pair<int,int>>>v;
    int n;
    citire(v,n);
    cout<<greedy(v,n);
    return 0;
}