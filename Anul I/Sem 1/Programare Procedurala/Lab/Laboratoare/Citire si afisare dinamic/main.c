#include <stdio.h>
#include <stdlib.h>

void citire(int *n,int **a)
{
    scanf("%d",n);

    int i;

    *a=(int*)malloc((*n)*sizeof(int));

    for(i=0;i<*n;++i)
    {
        scanf("%d",*a+i);
    }
}

void afis(int n,int *a)
{
    int i;
    for(i=0;i<n;i++)
        printf("%d ",*(a+i));
}

int main()
{
    int *v,n;

    citire(&n,&v);
    afis(n,v);
    return 0;
}
