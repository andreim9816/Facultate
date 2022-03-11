#include <stdio.h>
#include <stdlib.h>

int cmpIntregi(const void*a,const void*b)
{
    int x,y;
    x=*(int*)a;
    y=*(int*)b;

    if(x<y)
        return -1;
    else if(x>y)
        return 1;
    else return 0;
}

void *cautare(const void*x,const void*tablou,int n,int dim,int (*cmp)(const void*,const void*))
{
    int i;
    char *pcrt;
    if(n==0)
        return NULL;
    for(i=0;i<n;i++)
    {
        pcrt=(char*)tablou+i*dim;
        if(cmp(x,pcrt)<0)
            return pcrt;
    }
    return NULL;
}

int verif_descresc(int *v,int n)
{
    int i;
    for(i=0;i<n-1;i++)
        if(cautare(&v[i],v+i+1,n-i-1,sizeof(int),cmpIntregi))
        return 0;
    return 1;
}
int main()
{
    int v[]={3,2,1};
    printf("%d ",verif_descresc(v,3));
    return 0;
}