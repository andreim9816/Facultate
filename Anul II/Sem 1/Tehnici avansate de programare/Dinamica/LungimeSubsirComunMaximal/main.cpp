#include <iostream>
#include <fstream>
#include<cstring>

using namespace std;

ifstream fin("lungimesubsircomunmaximal.in");
ofstream fout("lungimesubsircomunmaximal.out");
void citire(char *s)
{
    fin >> s;
}

int PD(char *s, char *t)
{
    int m = strlen(s);
    int n = strlen(t);

    int i, j;
    int matrix[m + 1][n + 1];

    // caz separat pt prima litera

    for(i = 0 ; i < n ; i++)
     if(s[0] == t[i])
      matrix[0][i] = 1;
     else matrix[0][i] = 0;

    for(i = 0 ; i < m ; i++)
      if(s[i] == t[0])
       matrix[i][0] = 1;
      else matrix[i][0] = 0;

    // PD
    for(i = 1 ; i < m ; i++)
     for(j = 1 ; j < n ; j++)
      if(s[i] == t[j])
       matrix[i][j] = matrix[i - 1][j - 1 ] + 1;
      else matrix[i][j] = max(matrix[i - 1][j] , matrix[i][j - 1]);

    return matrix[m-1][n-1];

}

int main()
{
    char s[1001];
    char t[1001];

    citire(s);
    citire(t);

    fout<<PD(s,t);

    fin.close();
    fout.close();

    return 0;
}
