#include <stdio.h>
#include <stdlib.h>
int par(int x)
{
    return(x%2==0);
}
int impar(int x)
{
    return(x%2==1);
}
int negativ(int x)
{
    return(x<0);
}

int cautare(int *v,int n,int (*fct)(int))
{
    int i;
    for(i=0;i<n;i++)
        if(fct(v[i])==1)
        return i;
    return -1;
}

int main()
{
   int v[]={2,5,4,-1,-7,6,7,8};
   int n;
   printf("%d %d %d ",cautare(v,8,par),cautare(v,8,impar),cautare(v,8,negativ));
    return 0;
}
