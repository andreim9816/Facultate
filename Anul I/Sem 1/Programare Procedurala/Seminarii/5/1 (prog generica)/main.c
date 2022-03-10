#include <stdio.h>
#include <stdlib.h>
int par(const void*a)
{
    int x=*(int*)a;
    if(x%2==0)
        return 1;
    return 0;
}
void *cautare(void *v,int n,int dim,int (*fct)(const void*))
{
    int i;
    char*p=v;
    for(i=0;i<n;i++)
    {
        if(fct(p+i*dim)==1)
            return p+i*dim;
    }
    return NULL;
}
int main()
{
    int v[]={1,3,5,7,-1,6};
    int n=6;
    int *p=cautare(v,n,sizeof(int),par);
    if(!p)
        printf("Nu s-a gasit ");
    else printf("Pozitia este %d",p-v);
    return 0;
}
