#include <iostream>
#include<fstream>
#include<vector>
#include<queue>
#include<fstream>
using namespace std;

ifstream fin("date.in");
int m,n;

int dx[]={-1,0,1,0};
int dy[]={0,-1,0,1};

struct map
{
    int x=0,y=0; /// cordonatele initiale, de unde s-a ajung in punctul respectiv
    int val=0;
};

map a[1001][1001];

vector<pair <int,int> >V;
queue<pair<int ,int> >Q;

void citire()
{
    fin>>n>>m;
    int i,j;
    for(i=1;i<=n;i++)
        for(j=1;j<=m;j++)
        {
            fin>>a[i][j].val;
            if(a[i][j].val==1)
                {
                    Q.push(make_pair(i,j));
                    a[i][j].x=i;
                    a[i][j].y=j;
                }
        }

    while(fin>>i>>j)
        V.push_back(make_pair(i,j));

}

bool gata()
{
    for(auto i:V)
    if(a[i.first][i.second].val==0)
        return false;
    return true;
}

int interior(int x,int y)
{
    return (x>0 && y>0 && x<=n && y<=m);
}

void BF()
{
    int i,j;

    while(!Q.empty() && !gata())
    {
        pair<int,int> x=Q.front();
        Q.pop();
        for(int i=0;i<=3;i++)
        {
            pair<int,int>New;
            New.first=dx[i]+x.first;
            New.second=dy[i]+x.second;
            if(interior(New.first,New.second))
            if(a[New.first][New.second].val > a[x.first][x.second].val+1 || a[New.first][New.second].val == 0)
            {
              //  cout<<New.first<<" "<<New.second<<" "<<endl;
                Q.push(make_pair(New.first,New.second));
                a[New.first][New.second].val= a[x.first][x.second].val+1;
                a[New.first][New.second].x=a[x.first][x.second].x;
                a[New.first][New.second].y=a[x.first][x.second].y;
            }
        }
    }
}

void afis()
{
    for(auto i:V)
        cout<<a[i.first][i.second].val-1<<" ["<<
        a[i.first][i.second].x<<" , "<<
        a[i.first][i.second].y<<"]\n";
}

int main()
{
    citire();
    BF();
    afis();
    return 0;
}
