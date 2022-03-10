#include <stdio.h>
#include <stdlib.h>

void citire(int **v,int *n)
{
    int i;

    FILE *f=fopen("nr.in","r");
    fscanf(f,"%d",n);

    *v=malloc(sizeof(int)*(*n));

    for(i=0;i<*n;i++)
    {
       fscanf(f,"%d",*v+i);
    }
}

void negative(int *v,int n,int **neg,int *m)
{
    int i,*aux;
    *m=0;
    *neg=NULL;

    for(i=0;i<n;i++)
    {
        if(v[i]<0)
        {
            (*m)++;
            aux=(int*)realloc(*neg,sizeof(int)*(*m));
            if(aux==NULL)
            {
                free(neg);
                printf("EROARE");
                return ;
            }
            else
            {
                *neg=aux;
                (*neg)[*m-1]=v[i];
            }

        }
    }
}

void pozitive(int *v,int n,int **poz,int *m)
{
    int i;
    int *aux;
    *m=0;
    *poz=NULL;
    for(i=0;i<n;i++)
    {
        if(v[i]>=0)
        {   (*m)++;
            aux=(int*)realloc(*poz,sizeof(int)*(*m));
            if(aux==NULL)
            {
                printf("EROARE");
                free(poz);
                return ;
            }
            else
            {
                *poz=aux;
                (*poz)[*m-1]=v[i];
            }
        }
    }
}

void afis(int *v,int n)
{
    int i;
    for(i=0;i<n;i++)
        printf("%d ",v[i]);
    printf("\n");
}

int main()
{
   int *v,n,*neg,*poz,n1,n2;
    citire(&v,&n);afis(v,n);
    pozitive(v,n,&poz,&n1);afis(poz,n1);
    negative(v,n,&neg,&n2);afis(neg,n2);

    return 0;
}
