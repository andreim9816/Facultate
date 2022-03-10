#include <iostream>
#include<fstream>
#include<queue>
#include<vector>

using namespace std;

ifstream fin("rj.in");
ofstream fout("rj.out");
int dx[]={-1,-1,-1,0,0,1,1,1};
int dy[]={-1,0,1,-1,1,-1,0,1};
int m,n;

struct map
{
    int r=0,j=0,val=0;
};

map a[101][101];

queue <pair<int,int> >Q;

void citire()
{
    fin>>n>>m;
    fin.get();
    int i,j;
    char x;
    for(i=1;i<=n;i++)
        {
            for(j=1;j<=m;j++)
                {
                    a[i][j].r=0;
                    a[i][j].j=0;

                    x=fin.get();
                    if(x==' ')
                        a[i][j].val=0;
                    else if(x=='X')
                        a[i][j].val=-1;
                    else if(x=='R' || x=='J')
                        {
                            a[i][j].val=1;

                            if(x=='R')
                                a[i][j].r=1;  // marcam faptul ca de pe pozitia aia incepe Romeo
                            else a[i][j].j=1; // marcam faptul ca de pe pozitia aia incepe Julieta, si pe urmatoarele tot ea va ajunge

                            Q.push(make_pair(i,j));
                        }
                }
                fin.get(); // citeste \n
    }
}

int interior(int x,int y)
{
    return(x>0 && y>0 && x<=n && y<=m);
}

void BF(int &xx,int &yy,int &timp)
{
    xx=n+1;
    yy=m+1;
    timp=n*m+1;

    int i,j;
    while(!Q.empty())
    {
        pair<int,int>x;
        x=Q.front();
        Q.pop();

        for(i=0;i<8;i++)
        {
            pair<int,int>v;
            v.first=x.first+dx[i];
            v.second=x.second+dy[i];

            if(interior(v.first,v.second))
                {
                   if(a[v.first][v.second].val>1) // a ajuns deja cineva acolo
                    {
                        if(a[x.first][x.second].r + a[v.first][v.second].j == 2 || a[x.first][x.second].j + a[v.first][v.second].r == 2) // adica este deja unul dintre ei ajunsi, si acum pe pozitia noua ajunge si celalalt
                           if(a[v.first][v.second].val<timp)
                           if( (v.first < xx || (v.first == xx && v.second < yy) ) && a[v.first][v.second].val == 1+ a[x.first][x.second].val)
                            {
                               xx=v.first;
                               yy=v.second;
                               timp=a[v.first][v.second].val;
                              }
                    }

                   else if(a[v.first][v.second].val==0)
                   {
                       // este pozitie libera
                       a[v.first][v.second].val=a[x.first][x.second].val+1;
                       a[v.first][v.second].r = a[x.first][x.second].r;
                       a[v.first][v.second].j = a[x.first][x.second].j;
                       Q.push(make_pair(v.first,v.second));
                   }
                }
        }
    }
}


int main()
{
   citire();
   int x,y,timp;
   BF(x,y,timp);
   fout<<timp<<" "<<x<<" "<<y;
    return 0;
}
