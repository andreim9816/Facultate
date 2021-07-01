#include <iostream>
#include<fstream>

using namespace std;

void citire(int a[][101],int &m, int &n, int &k)
{
    int i,j;
    ifstream fin("date.in");

    fin>>m>>n;
    for(i = 1 ; i <= m ; i++)
        for(j = 1 ; j <= n ; j++)
        {
            fin>>a[i][j];
        //    a[i][j] = 1 - a[i][j];
        }
    fin>>k;

    fin.close();
}

void afis(int a[][101],int m,int n)
{
    for(int i =1;i<=m;i++)
        {
            for(int j=1;j<=n;j++)

        cout<<a[i][j]<<" ";
        cout<<endl;
    }
}

void pd(int a[][101], int m, int n, int s[][101],int k)
{
    int i,j,nr = 0, maxim = -1, coordi, coordj;

    for(i = 1 ; i <= m ; i++)
        s[i][1] = 1- a[i][0];

    for(j = 1; j <= n ; j++)
        s[1][j] = 1-  a[0][j];

    for(i = 1 ; i <= m ; i++)
        for(j = 1 ; j <= n ; j++)
    {
        if(a[i][j] == 0)
        {
            int minim = s[i-1][j-1];

            if(minim > s[i-1][j])
                minim = s[i-1][j];

            if(minim > s[i][j-1])
                minim = s[i][j-1];

            s[i][j] = minim + 1;
        }
        else s[i][j] = 0;

        if(maxim < s[i][j])
            {
                maxim = s[i][j];
                coordi = i;
                coordj = j;
            }

        if(s[i][j] >= k)
         nr += (s[i][j]-k+1);

    }
    cout<<maxim<<"\n";
    cout<<coordi - maxim + 1 <<" "<<coordj - maxim + 1 <<"\n";
    cout<<nr;
}

int main()
{
    int a[101][101],m,n,k,mat[101][101];

    citire(a,m,n,k);
    pd(a,m,n,mat,k);
    return 0;
}
