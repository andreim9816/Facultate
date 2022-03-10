#include <stdio.h>
#include <stdlib.h>

void citire(FILE *f,int v[],int *n)
{
    int i;
    fscanf(f,"%d",n);
    for(i=0;i<*n;i++)
        fscanf(f,"%d",&v[i]);
}

int cautare_binara(int v[],int n,int x)
{
    int st=0,dr=n-1;
    while(st<=dr)
    {
        int m;
        m=(st+dr)/2;
        if(v[m]==x)
            return m;
        else if(v[m]<x)
           st=m+1;
        else  dr=m-1;
    }
    return -1;
}

int main()
{
    int v[101],n,x,y;

    FILE *f=fopen("nr","r");
    citire(f,v,&n);
    fscanf(f,"%d %d",&x,&y);
    int poz1=cautare_binara(v,n,x);
    int poz2=cautare_binara(v,n,y);
    int i;

    for(i=poz1;i<=poz2;i++)
        printf("%d ", v[i] );

    return 0;
}
