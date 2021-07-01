#include <iostream>
#include<fstream>
#include<cstring>
#include<stdlib.h>
using namespace std;

void citire(int matrix[][101], int &n, int &k)
{
    ifstream fin("date.in");
    char s[200];
    int i;

    fin>>n>>k;
    fin.get();

    for( i = 0; i < n ; i++)
    {
        matrix[i][0] = 0;
        fin.getline(s,200);
        char *p =strtok(s," ");

        while(p)
        {
            int nr = atoi(p);
            matrix[i][++matrix[i][0]] = nr;
            p=strtok(NULL," ");
        }
    }
    fin.close();
}

int matrix_sum[101][101];
int prec[101][101];

void pd(int matrix[][101], int n, int matrix_sum[][101], int k)
{
    int i,j,nr,p;

    // prima linie o completam manual
    nr = matrix[0][0] ; // cate elemente sunt in primul vector

    for(j = 1 ; j <= nr; j++)
        matrix_sum[0][matrix[0][j]] = 1;

    // pentru fiecare linie
    for(i = 1 ; i < n ; i++)
    {
       for(p = 1 ; p <= k ; p++)
        for( j = 1 ; j <= matrix[i][0] ; j++)
         if(matrix_sum[i-1][p] == 1) // suma p a fost deja obtinuta
          {
              if(p+matrix[i][j]<=k)
              {
                  matrix_sum[i][p+matrix[i][j]] = 1; // marcam ca suma p + elementul curent de pe linia i se poate obtine
                  prec[i][p+matrix[i][j]] = matrix[i][j] ; // retinem elementul curent care a fost adunat la suma p
              }
          }
    }

    if(matrix_sum[n-1][k] == 1) // daca s-a putut obtine suma k, afisam
    {
        for(i = n-1 ; i >= 1; i--)
        {
            cout<< prec[i][k]<<" ";
            k = k - prec[i][k];
        }
        cout<<k;
    }
    else cout<<0;
}

int main()
{
   int matrix[101][101],n,k;

   citire(matrix,n,k);
   pd(matrix,n,matrix_sum,k);
   return 0;
}
