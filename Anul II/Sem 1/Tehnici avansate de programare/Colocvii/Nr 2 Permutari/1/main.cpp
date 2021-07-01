#include <iostream>
#include<fstream>
#include<vector>
using namespace std;

void citire(int &n, vector<int>&v)
{
    ifstream fin("date.in");
    int i;
    fin >> n;

    for(i=0;i<n;i++)
    {
        int x;
        fin>>x;
        v.push_back(x);
    }

    fin.close();
}

void cautareBinara(vector<int>v, int n)
{
    int st = 0 ;
    int dr = n - 1;
    int m;

    while(st <= dr)
    {

        m = (st + dr) /2;
        if(v[m] %2 == 1 && v[m+1] %2 == 0) // am gasit
        {
            cout<<"Sunt " << m + 1<<" numere impare si " << n - m - 1<< " numere pare";
            break;
        }
        else if(v[m]%2 == 1 && v[m] %2 == 1)
            st = m + 1;
        else dr = m - 1;
    }

}

int main()
{
    vector<int>v;
    int n;
    citire(n,v);
    cautareBinara(v,n);
    return 0;
}