#include <stdio.h>
#include <stdlib.h>
#include<string.h>

int cmpIntregi(const void *a,const void *b)
{
    int va=*(int *)a;
    int vb=*(int *)b;
    if(va<vb)return -1;
    if(va>vb)return 1;
    return 0;
}

int cmpSiruri(const void *a,const void *b)
{
    return strcmp(*(char **)a,(char *)b);
}

void replaceInteger(void *a,void *b)
{
    int *va=(int *)a;
    int *vb=(int *)b;
    memcpy(va,vb,sizeof(int));
}

void replaceSiruri(void *a,void *b)
{
    char *x=(char *)a;
    char *y=(char *)b;
    printf("%d %d \n",*x,*y);
    memcpy(x,y,sizeof(char*));
}

void inlocuire(void *x,void *y,void *v,int n,int dim,int (*cmp)(const void *,const void *),void replace(void *,void *))
{
    char *p=v;
    int i;
    for(i=0;i<n;i++)
        if(cmp(p+dim*i,x)==0)
            replace(p+i*dim,y);
}

void afisare(int *v,int n)
{
    int i;
    for(i=0;i<n;i++)
        printf("%d ",v[i]);
    printf("\n");
}


int main()
{
    int v[]={3,7,1,7,4,2,7,4,7};
    int x=7;
    int y=10;
    inlocuire(&x,&y,v,9,sizeof(int),cmpIntregi,replaceInteger);
    afisare(v,9);

    ////////////////////////////////////////////////////

    char *w[100]={"laura","laura","laura","nu","laura","simte","laura","badulescu","morris","laura","matematica","laura","laura"};
    char *x1="laura";
    char *y1="JOSqwe";
    inlocuire(x1,&y1,w,12,sizeof(char*),cmpSiruri,replaceSiruri);
    int i;
  w[0]="mama";
    for(i=0;i<9;i++)
        printf("%s ",w[i]);
    printf("\n");

    return 0;
}
