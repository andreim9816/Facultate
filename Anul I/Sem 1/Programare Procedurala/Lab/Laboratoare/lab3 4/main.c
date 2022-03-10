#include <stdio.h>
#include <stdlib.h>
void citire(FILE *f,int a[][101],int *n,int *m)
{
    int i,j;

    fscanf(f,"%d %d", n,m);

    for(i=0;i<*n;i++)
        for(j=0;j<*m;j++)
        fscanf(f,"%d",&a[i][j]);
}

void transpusa(int a[][101],int *n,int *m)
{
    int i,j,aux;
    for(i=0;i<*n;i++)
        for(j=i+1;j<*m;j++)
    {
        aux=a[i][j];
        a[i][j]=a[j][i];
        a[j][i]=aux;
    }

    aux=*n;
    *n=*m;
    *m=aux;

}

void afis(int a[][101],int n,int m)
{
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
            printf("%d ",a[i][j]);
        printf("\n");
    }
}
int main()
{   FILE *f=fopen("nr","r");
    int a[101][101],n,m;
    citire(f,a,&n,&m);
    transpusa(a,&n,&m);
    afis(a,n,m);
    return 0;
}
