#include <iostream>
#include<queue>
#include<fstream>
#include<vector>
#include<algorithm>
using namespace std;

int cmp(pair<int, pair<int,int>>x,pair<int,pair<int,int>>y) // sortez vectorul descrescator dupa t, si descrescator dupa p
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
        fin>>t>>p;
        v.push_back({i,{t,p}});
    }

    sort(v.begin(),v.end(),cmp);

    fin.close();
}

struct cmp_pq
{
   bool operator()(pair<int,pair<int,int>>x,pair<int,pair<int,int>>y)
    {
     if(x.second.second < y.second.second) /// sortez descrescator dupa p
        return true;
       return false;
    }
};


int greedy(vector<pair<int,pair<int,int>>>v,int n)
{
    int i=0,h_max=v[0].second.first,T=0;
    priority_queue< pair<int,pair<int,int>>,vector<pair<int,pair<int,int>>>, cmp_pq >pq; // coada de prioritati in care avem indicele activitatii (din vectorul nesortat), timpul limita si profitul

    while(h_max && i<n)
    {
        while(v[i].second.first==h_max && i<n)
         {
             pq.push({v[i].first,{v[i].second.first,v[i].second.second}}); // adaugam in coada indicele( din vectorul nesortat),timpul limita si profitul
             i++;
         }

      if(pq.size())
           {

            int p=pq.top().second.second; // profitul
            cout<<pq.top().first<<" "; // indicele activitatii (din vectorul nesortat )
            pq.pop();
            T+=p;
           }

        h_max--;
    }
    cout<<"\nRez este ";
    return T;
}

int main()
{
    vector<pair<int,pair<int,int>>>v;
    int n;
    citire(v,n);
    cout<<greedy(v,n);
    return 0;
}
