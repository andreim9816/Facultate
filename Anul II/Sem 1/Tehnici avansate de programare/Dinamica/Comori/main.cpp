#include <iostream>
#include<fstream>
#include<vector>
using namespace std;

vector<vector<int>>matrix;
int n,m;

void citire()
{
    ifstream fin("comori.in");
    fin >> n >> m;
    int i;

    matrix.resize(n + 2);

    matrix[0].resize(m + 2);
    matrix[n + 1].resize(m + 2);

    for(int i = 1 ; i <= n ; i++)
    {
        matrix[i].resize(m + 2);

        for(int j = 1 ; j <= m ; j++)
            fin >> matrix[i][j];
    }

    // bordare
    for(i = 0 ; i <= m + 1 ; i++)
        matrix[0][i] = matrix[n + 1][i] = -100000;

    for(i = 0 ; i <= n + 1 ; i++)
        matrix[i][0] = matrix[i][m + 1] = -100000;
    fin.close();
}

void PD()
{
    int i, j;
    vector<vector<int>>matrixPD;

    matrixPD.resize(n + 2);
    matrixPD[0].resize(m + 2);
    matrixPD[n + 1].resize(m + 2);

    for(i = 1 ; i <= n ; i++)
    {
        matrixPD[i].resize(m + 2);
        for(j = 1 ;j <= m ; j++)
            matrixPD[i][j] = 0;
    }

    for(j = 1 ; j <= m; j++)
        matrixPD[1][j] = matrix[1][j];

    for(i = 2 ; i <= n ; i++)
        for(j = 1 ; j <= m ; j++)
            matrixPD[i][j] = max( max(matrixPD[i - 1][j - 1] , matrixPD[i - 1][j]), matrixPD[i - 1][j + 1]) + matrix[i][j];

    int maxim = -1;

    for(i = 1 ; i <= n ; i++)
        for(j = 1 ; j <= m ; j++)
         if(maxim < matrixPD[i][j])
          maxim = matrixPD[i][j];

    ofstream fout("comori.out");
    fout << maxim ;

    fout.close();

}

int main()
{
    citire();
    PD();
    return 0;
}