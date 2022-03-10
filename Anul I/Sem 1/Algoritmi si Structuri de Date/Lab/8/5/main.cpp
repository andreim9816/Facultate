#include <iostream>
#include<fstream>
using namespace std;

ifstream fin("nr.in");

struct nod
{
    nod*urm;
    int info;
};

struct coada
{
    nod*primx,*ultimx;
    nod*primy,*ultimy;
};

void afis(int a[][500],int n)
{
int i,j;
for(i=1;i<=n;++i)
{
    for(j=1;j<=n;j++)
        cout<<a[i][j]<<" ";
    cout<<endl;
}
 cout<<endl;
}

void push(nod*&prim,nod*&ultim,int x)
{
    if(!prim) // lista e vida
    {
        nod*q;
        q=new nod;
        q->info=x;
        prim=ultim=q;
        ultim->urm=NULL;
    }
    else
    {
        nod*q;
        q=new nod;
        q->info=x;

        q->urm=NULL;
        ultim->urm=q;
        ultim=q;
    }
}

int my_empty(nod*prim,nod*ultim)
{
    if(!prim)
        return 1;
    return 0;
}

int pop(nod*&prim,nod*ultim)
{
    if(!prim)
        return -1;

    nod*q;
    q= new nod;

    q=prim;
    prim=prim->urm;

    int val=q->info;

    delete q;
    return val;
}

int dx[]={-1,0,1,0};
int dy[]={0,-1,0,1};

int interior(int a[][500],int n,int x,int y)
{
    return (x>0 && y>0 && x<=n && y<=n);
}

void lee(int a[][500],int n,int x,int y,int val)
{
    int xn,yn,i;
  /*  nod*px,*ux,*py,*uy;

    px=new nod;
    ux=new nod;
    py=new nod;
    uy=new nod;

    px=ux=py=uy=NULL;

    push(px,ux,x);
    push(py,uy,y);

    while()
    */

    coada c;
    c.primx=c.primy=c.ultimx=c.ultimy=new nod;
    c.primx=c.ultimx=NULL;
    c.primy=c.ultimy=NULL;

    push(c.primx,c.ultimx,x);
    push(c.primy,c.ultimy,y);
    a[x][y]=val;

    while(!my_empty(c.primx,c.ultimx))
    {  // cout<<x<<' '<<y<<endl;
        x=pop(c.primx,c.ultimx);
        y=pop(c.primy,c.ultimy);
        for(i=0;i<=3;++i)
        {
            xn=x+dx[i];
            yn=y+dy[i];
            if(interior(a,n,xn,yn) && a[xn][yn]==1)
            {
                push(c.primx,c.ultimx,xn);
                push(c.primy,c.ultimy,yn);
                a[xn][yn]=val;
            }
        }
    }
}

void rezolvare(int a[][500],int n)
{
    int i,j,val=2;
    for(i=1;i<=n;i++)
    for(j=1;j<=n;j++)
    if(a[i][j]==1)
        lee(a,n,i,j,val++);

}

void citire(int a[][500],int &m)
{
    int i,j;
    fin>>m;
    for(i=1;i<=m;++i)
        for(j=1;j<=m;++j)
        fin>>a[i][j];
}

int main()
{
    int a[500][500],m;
    citire(a,m);
    rezolvare(a,m);
     afis(a,m);
    return 0;
}
