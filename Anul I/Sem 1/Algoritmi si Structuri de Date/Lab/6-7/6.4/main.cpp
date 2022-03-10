#include <iostream>
#include<fstream>
using namespace std;
///

ifstream fin("nr");

void citire(int v[],int &n)
{
    int i,x;
    fin>>n;
    for(i=1;i<=n;i++)
       {
        fin>>x;
        v[x]++;
       }
}

int v[10];

void count_sort(int v[],int n)
{
    int i;
    for(i=0;i<=10;i++)
        for(int j=1;j<=v[i];j++)
            cout<<i<<' ';

}

int main()
{
   int n,i;
   citire(v,n);
   count_sort(v,n);
    return 0;
}
