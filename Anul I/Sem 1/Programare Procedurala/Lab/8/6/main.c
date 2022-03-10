#include <stdio.h>
#include <stdlib.h>

void citire(int **v,int *n)
{
    int i;
    FILE *f=fopen("numere.txt","r");
    fscanf(f,"%d",n);

    *v=(int*)malloc(sizeof(int)*(*n));

    for(i=0;i<*n;i++)
    {
        fscanf(f,"%d",*v+i);
    }
}

int maxim(int *v,int n)
{
    int i,maxi=v[0];

    for(i=1;i<n;i++)
        if(maxi<v[i])
    {
        maxi=v[i];
    }
    return maxi;
}

void construct(int *v,int n,int **poz,int *m)
{
    int i,maxi,*aux;
    *m=0;
    *poz=NULL;

    maxi=maxim(v,n);

    for(i=0;i<n;i++)
        if(v[i]==maxi)
    {
        (*m)++;
        aux=(int*)realloc(*poz,sizeof(int)*(*m));

        if(aux==NULL)
        {
            printf("EROARE");
            free(poz);
            return;
        }
        else
        {
            *poz=aux;
            (*poz)[*m-1]=i;
        }
    }
}

void afis(int *v,int n)
{
    int i;
    for(i=0;i<n;i++)
        printf("%d ",v[i]);
}

int main()
{
   int *v,n,*pozitii,m;
   citire(&v,&n);
   construct(v,n,&pozitii,&m);
   afis(pozitii,m);
    return 0;
}
