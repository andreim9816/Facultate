#include <stdio.h>
#include <stdlib.h>

int cmpIntregi(const void *a,const void *b)
{
    int va=*(int *)a;
    int vb=*(int *)b;
    if(va<vb)return -1;
    else if(va>vb)return 1;
    return 0;
}



int aparitii(const void *x,void *v,int n,int dim,int (*cmp)(const void *,const void *))
{
    int i,k=0;
    char *p;
    p=(char *)v;
    for(i=0;i<n;i++)
    {
        if(cmp(p+i*dim,x)==0)k++;
    }

    return k;
}



int main()
{   int x=4111;
    int v[]={4111,7111,3111,2111,3111,11110,21111};
    int k=aparitii(&x,v,7,sizeof(int),cmpIntregi);
    printf("%d",k);
    return 0;
}