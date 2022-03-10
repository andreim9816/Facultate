#include <stdio.h>
#include <stdlib.h>

void construct(int ***a,int *n)
{
    int i,j;
    FILE*f=fopen("nr","r");

    fscanf(f,"%d",n);

    *a=(int**)malloc(sizeof(int*)*(*n));

    for(i=0;i<*n;i++)
    {
        (*a)[i]=(int*)malloc(sizeof(int)*(i+1));
    }

    for(i=0;i<*n;i++)
        (*a)[*n-1][i]=i+1;

    for(i=0;i<*n;i++)
        (*a)[i][0]=*n-i;


    for(i=*n-2;i>=1;i--)
        for(j=1;j<=i;j++)
        (*a)[i][j]=(*a)[i][j-1]+(*a)[i+1][j];
}

void afis(int **a,int n)
{
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<=i;j++)
            printf("%d ",a[i][j]);
        printf("\n");
    }
}

int main()
{
    int**a,n;
    construct(&a,&n);
    afis(a,n);
    return 0;
}
