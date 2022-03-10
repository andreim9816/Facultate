#include <stdio.h>
#include <stdlib.h>
#include<string.h>
int egale(const void*a,int an,const void*b,int bn,int dim)
{   printf("%d ",dim);
    if(an!=bn)
    return 0;

    int i;
    char *pcrt;

    for(i=0;i<an;i++)
            if(memcmp(a+i*dim,b+i*dim,dim))
                return 0;
    return 1;
}

int main()
{
    char *v[]={"cantarrrrrrrrrrrrrrrrrrr","Mama","aresds","me"};
    char *w[]={"cantarrrrrrrrrrrrrrrrrrr","Mama","aresds","me"};
    printf(" %d ",egale(v,4,w,4,sizeof(char*)));
    return 0;
}
