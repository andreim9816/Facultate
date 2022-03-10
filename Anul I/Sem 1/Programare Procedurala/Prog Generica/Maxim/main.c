#include <stdio.h>
#include <stdlib.h>

int cmpIntregi(const void *a, const void*b)
{
    int x,y;

    x=*(int*)a;
    y=*(int*)b;
    if(x<y)
        return -1;
    else if(x==y)
        return 0;
    return 1;
}

void* maxim(const void *tablou, int nr_elem, int dim_elem,int (*cmp)(const void*, const void *))
{
 int i;
 char *pcrt, *pmax;
 if(nr_elem == 0)
    return NULL;

 pmax = (char *)tablou;
 for(i = 1; i < nr_elem; i++)
 {
 pcrt = (char *)tablou + i*dim_elem;
 if(cmp(pcrt, pmax) > 0)
 pmax = pcrt;
 }
 return pmax;
}

int main()
{
    int v[]={5127,123,-2323,1};
    int *p;
    p=maxim(v,4,sizeof(int),cmpIntregi);
    printf("%d",*p);
    return 0;
}
