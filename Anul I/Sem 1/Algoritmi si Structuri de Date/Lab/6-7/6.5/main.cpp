#include <iostream>
#include<fstream>
#include<cmath>
using namespace std;

ifstream fin("nr");

void citire(int v[], int &n)
{
    int i;
    fin>>n;
    for(i=1;i<=n;i++)
        fin>>v[i];
}

void bucketSort(int v[],int n, int p)
{
    int i,x,j,a[10][101];
   // initializare pt galeti
    for(i=0;i<=9;++i)
        a[i][0]=0;

    for(i=1;i<=n;++i)
    {
        x=(v[i]/p)%10;
        a[x][++a[x][0]]=v[i];
    }
    for(int k=0,i=0;i<=9;i++)
        for(j=1;j<=a[i][0];j++)
        v[++k]=a[i][j];
}

int nr_max_pasi(int v[],int n)
{   // cate cifre are cel mai mare numar
    int i,maxi=v[1];
    for(i=2;i<=n;i++)
        if(maxi<v[i])
          maxi=v[i];
    return log10(maxi)+1;

}

void afis(int v[],int n)
{
    int i;
    for(i=1;i<=n;i++)
        cout<<v[i]<<' ';
}

int main()
{
    int v[101],n,i,nr_pasi,p=1;

    citire(v,n);
    nr_pasi=nr_max_pasi(v,n);

    for(i=1; i<=nr_pasi; i++, p=p*10)
        bucketSort(v,n,p);

    afis(v,n);

    return 0;
}
