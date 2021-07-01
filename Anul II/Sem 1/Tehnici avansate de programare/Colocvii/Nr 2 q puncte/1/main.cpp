#include <iostream>
#include<vector>
#include<fstream>
using namespace std;

vector<int>v;
int n;

void citire()
{
    ifstream fin("date.in");
    int i;
    fin>>n;
    v.resize(n);

    for(i = 0 ; i < n ; i++)
        fin >> v[i];

    fin.close();
}

void cautaBinar()
{
    int m , st , dr;
    st = 0 ;
    dr = n - 1 ;

    while(st <= dr)
    {
        m = (st + dr) /2;

        if(v[m] < v[m + 1] && v[m] < v[m - 1])
        {
            cout << m << "\n" << v[m];
            break ;
        }
        else if(v[ m ] < v[ m + 1 ])
            dr = m - 1;
        else st = m + 1;
    }
}

int main()
{
    citire();
    cautaBinar();
    return 0;
}
