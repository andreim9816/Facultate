#include <iostream>
#include<fstream>
#include<vector>
#include<algorithm>
using namespace std;


struct interval
{
    int start, finish;
};

int cmpCresc(interval x, interval y)
{
    return (x.start < y.start || (x.start == y.start && x.finish < y.finish));
}

vector<interval>v;
vector<interval>solutie;
int n;
int a,b;

void citire()
{
    int i;
    ifstream fin("date.in");

    fin >> a >> b;
    fin >> n;

    for(i= 0 ; i < n ; i++)
    {
        interval x;
        fin >> x.start >> x.finish;
        v.push_back(x);
    }

    fin.close();
}

void sortare(vector<interval>&v, int n)
{
    sort(v.begin(), v.end(), cmpCresc);
}

void greedy()
{
    int i = 0;
    int poz;

    while( a < b && i < n)
    {
      int maxim = v[i].finish;
      poz = i;

      while(v[i].start <= a && i < n)
      {
          if(v[i].finish > maxim)
          {
              maxim = v[i].finish;
              poz = i;
          }
          i++;
      }

      if(i != poz)
       solutie.push_back({v[poz].start , v[poz].finish});

      else
      {
          cout<< -1 ;
          solutie.clear();
          return ;
      }
      a = maxim;
    }

    if(a < b)
      {
          cout<< -1 ;
          solutie.clear();
          return ;
      }
}

int main()
{
    citire();
    sortare(v, n);

    if(v[0].start > a)
     cout<< -1;
    else
    {
        int maxim = v[0].finish;
        for(auto elem : v)
         if(maxim < elem.finish)
          maxim = elem.finish;

        if(maxim < b)
            cout << -1;
        else greedy();
    }

    if(!solutie.empty())
     for(auto T : solutie)
        cout<<T.start << " " << T.finish<<"\n";
    return 0;
}
