#include <stdio.h>
#include <stdlib.h>

void citire(int **v,int *n)
{
    int i;
    scanf("%d",n);

    *v=(int*)malloc(sizeof(int)*(*n));

    for(i=0;i<*n;i++)
        scanf("%d",*v+i);
}

void min_max(int *v,int n,int *mini,int*maxi)
{
    int i;
    *mini=*maxi=v[0];
    for(i=1;i<n;i++)
    {
        if(v[i]<*mini)
            *mini=v[i];
        if(v[i]>*maxi)
            *maxi=v[i];
    }
}

int elem_egale(int *v,int n)
{
    int mini,maxi;
    min_max(v,n,&mini,&maxi);
    if(mini==maxi)
        return 1;
    return 0;
}

int main()
{
    int *v,n;
    citire(&v,&n);
    if(elem_egale(v,n))
        printf("TOATE ELEMENTELE SUNT EGALE");
    else printf("NU ARE TOATE ELEMENTELE EGALE");
    return 0;
}
