#include<stdlib.h>
#include<stdio.h>
#include<string.h>
int cmp(const void*a,const void*b)
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
void *aparitie(void*tablou,int n,void*val,int dim)
{
    char *pcrt;
    int i;

    for(i=0;i<n;i++)
    {
        pcrt=(char*)tablou+i*dim;
        if(memcmp(val,pcrt,dim)==0)
            return pcrt;
    }
    return NULL;
}

void afis_pozitii(int *v,int n,int x)
{
    int i,poz=0;
    int *p;
    do
    {

        p=aparitie(v+poz,n-poz,&x,sizeof(int));
        if(p)
        printf("Pozitia este %d\n",p-v);
        poz=p-v+1;
    }while(p);
}

int main()
{   int x=7;
    int v[]={4,7,2,1,9,7,8,3,4,5,6};
    int *p=aparitie(v,11,&x,sizeof(int));
    afis_pozitii(v,11,x);
    return 0;
}
