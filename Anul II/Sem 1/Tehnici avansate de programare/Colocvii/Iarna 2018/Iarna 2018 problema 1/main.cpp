#include <iostream>
#include<fstream>
#include<cmath>
using namespace std;

int matrix[100][100]; // matricea care se citeste
int matrixCost[100][100]; // matricea costurilor (Cel mai mare cost
int matrixMinim[100][100];

int n, m , Sfinal;

void citire(int &n , int &m,int &Sfinal)
{
    ifstream fin("date.in");
    int i,j;
    fin >> n >> m >> Sfinal;

    for(i = 1 ; i <= n; i++)
        for(j = 1 ; j <= m ; j++)
        fin >> matrix[i][j];

    // bordare

    for(i = 0 ; i <= n+1 ; i++)
        matrix[i][0] = matrix[i][m+1] = -100000;

    for(i = 0 ; i <= m+1 ; i++)
        matrix[0][i] = matrix[n+1][i] = -100000;

    fin.close();
}

void PD()
{
    int i , j;

    matrixCost[1][m] = matrix[1][m];
    matrixMinim[1][m] = matrix[1][m];

    for(j = m -1 ; j >= 1 ; j--) // pe prima linie
    {
        matrixCost[1][j] = matrix[1][j] + matrixCost[1][j+1];
        matrixMinim[1][j] = min(matrixCost[1][j] , matrixMinim[1][j+1]);
    }

    for(i = 2 ; i <= n ; i++) // pe prima coloana
    {
        matrixCost[i][m] = matrix[i][m] + matrixCost[i-1][m];
        matrixMinim[i][m] = min(matrixCost[i][m] , matrixMinim[i-1][m]);
    }

    for(i = 2 ; i <= n ; i++)
        for(j = m -1 ; j >= 1 ; j--)
    {
        if(matrixCost[i-1][j] > matrixCost[i][j+1])
        {
            matrixCost[i][j] = matrixCost[i-1][j] + matrix[i][j];
            matrixMinim[i][j] = min(matrixCost[i][j],matrixMinim[i-1][j]);
        }
        else
        {
            matrixCost[i][j] = matrixCost[i][j+1] + matrix[i][j];
            matrixMinim[i][j] = min(matrixCost[i][j],matrixMinim[i][j+1]);
        }
    }
}

int afisMatrix(int n,int m, int matrix[][100])
{
    int i,j;
    for(i = 0 ; i <= n+1 ; i++)
    {
        for(j = 0 ; j <= m+1 ; j++)
            cout<<matrix[i][j]<<" ";
        cout<<endl;
    }
}

void genereazaDrum()
{
    int i,j;

    i = n;
    j = 1;

    while( i!= 1 && j != m)
    {
        cout<<matrix[i][j]<<" ";

        if(matrixMinim[i-1][j] > matrixMinim[i][j+1])
            i--;
        else j++;
    }

    if(i == 1)
     {while(j != m)
      cout<<matrix[i][j++]<<" ";
     }
    else
    {
        while(i != 1)
            cout<<matrix[i--][j]<<" ";
    }

    cout<<matrix[1][m];

}
int main()
{
    citire( n , m , Sfinal);
    PD();
  //  afisMatrix(n,m,matrixMinim);
    cout<<"Smin este " << abs(matrixMinim[n][1])+1 <<"\n\n";

    cout<<"Drumul este:\n\n";
    genereazaDrum();

    return 0;
}
