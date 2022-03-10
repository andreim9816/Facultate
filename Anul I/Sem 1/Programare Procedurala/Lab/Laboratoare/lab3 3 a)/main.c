#include <stdio.h>
#include <stdlib.h>

void citire(FILE *f,char v[],int *n)
{
    int i;
    fscanf(f,"%d",n);
    for(i=0;i<*n;i++)
        fscanf(f,"%d",&v[i]);
}

void afis(char v[],int n)
{
    int i;
    for(i=0;i<n;i++)
        printf("%d",v[i]);
}

void rasturnare(char v[],int n)
{
    int st=0,dr=n-1;
    while(st<dr)
    {
        char aux=v[st];
        v[st]=v[dr];
        v[dr]=aux;
        st++;
        dr--;
    }
}

void adunare(char v[],int n,char w[],int m, char sum[],int *p)
{
    int i,t;
    if(n>m)
        {
        for(i=m;i<n;i++)
            w[i]=0;
            *p=n;
        }
    else {
            for(i=n;i<m;i++)
            v[i]=0;
            *p=m;
         }
    for(i=0;i<*p;i++)
    {

        t=v[i]+w[i];
        sum[i]=t%10;
        t=t/10;
    }
    if(t!=0)
    sum[++(*p)]=1;
}

int main()
{
    FILE *f=fopen("nr","r");
    char v[1001],w[1001],sum[1001];

    int n,m,p;

    citire(f,v,&n);
    citire(f,w,&m);

    rasturnare(v,n);
    rasturnare(w,m);

    adunare(v,n,w,m,sum,&p);
    rasturnare(sum,p);
    afis(sum,p);

    return 0;
}
