#include <iostream>
#include<fstream>
#include<vector>
using namespace std;

void citire(vector<int>&v, int &n)
{
    int i;
    ifstream fin("date.in");
    fin >> n;
    v.resize(n);
    for(i = 0 ; i < n ; i++)
        fin>>v[i];
}

int cautare(vector<int>v , int st , int dr)
{
    if(st <= dr)
    {
        int m = (st + dr ) /2;
        if(v[m] == m)
            return m;
        else if(v[m] > m )
            return cautare(v, st , m - 1);
        else return cautare(v , m + 1 , dr);
    }
    return -1;

}

int main()
{
    vector<int>v;
    int n;

    citire(v,n);
    cout<<cautare(v , 0 , n - 1);
    return 0;
}
