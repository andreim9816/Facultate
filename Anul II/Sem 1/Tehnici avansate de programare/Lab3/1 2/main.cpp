#include <iostream>
#include<vector>
#include<algorithm>
#include<fstream>
using namespace std;

int cmp(pair<int,pair<int,int>>x,pair<int,pair<int,int>>y)
{
    if(x.second.second < y.second.second)
        return 1;
    if(x.second.second == y.second.second && x.second.first > y.second.first)
        return 1;
    return 0;
}

void citire(vector<pair<int,pair<int,int>>>&v,int &n)
{
    ifstream fin("date.in");
    fin >> n;
    int l, t;
    for(int i = 1 ; i <= n ; i++)
    {
        fin >> l >> t;
        v.push_back({i,{l,t}});
    }

    sort(v.begin(),v.end(),cmp);

}

void greedy(vector<pair<int,pair<int,int>>>v,int n)
{

    int fin = 0;
    int late = 0;
    int late_max = 0;


    cout<<"Propunere:\n";

    for(int i = 0 ; i < n ; i++)
    {
        cout << v[i].first << ". "<< fin <<" ";
        fin = fin + v[i].second.first;
        cout << fin <<" ";

        late = fin - v[i].second.second;
        cout << late <<'\n';
        if(late > late_max)
            late_max=late;
    }

    cout<<"Intarziere = "<<late_max;
}

int main()
{
    vector<pair<int,pair<int,int>>>v;
    int n;
    citire(v,n);
    greedy(v,n);
    return 0;
}