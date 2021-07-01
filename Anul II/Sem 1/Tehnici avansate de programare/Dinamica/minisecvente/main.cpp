#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream fin("minisecvente.in");
ofstream fout("minisecvente.out");

vector<int>v;
int n;

vector<vector<int>>minim;

void citire()
{
    fin >> n;

    for(int i = 0 ; i < n ; i++)
    {
        int x;
        fin >> x;
        v.push_back(x);
    }
}

void PD()
{
    minim.resize(n);
    int i, j , k = 0;

    for(i = 0 ; i < n ; i++)
        {
            minim[i].resize(n , 0);
            minim[i][i] = v[i];
        }



    for(i = 0 ; i < n ; i ++)
        for(j = i + 1 ; j < n ; j ++)
         minim[i][j] = min(v[j] , minim[i][j - 1]);

  /*  for(i = 0 ; i < n; i++)
    {
        for(j = 0 ;j < n ; j++)
        cout<<minim[i][j] <<" ";
        cout<<endl;
    }
    */

   for(i = 0 ; i < n ; i++)
    for(j = i ; j < n ; j ++)
     if(j - i + 1 > minim[i][j])
      k++;

   fout<<k;
}

int main()
{
    citire();
    PD();

    fin.close();
    fout.close();
    return 0;
}
