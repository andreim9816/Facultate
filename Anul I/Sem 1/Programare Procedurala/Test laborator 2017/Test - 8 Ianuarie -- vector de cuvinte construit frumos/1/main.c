#include <stdio.h>
#include <stdlib.h>

int *citire(int*n)
{
    FILE*f=fopen("date.in","r");
    fscanf(f,"%d",n);

    int i,*v;
    v=(int*)malloc(sizeof(int)*(*n));
    for(i=0;i<*n;i++)
        fscanf(f,"%d",&v[i]);
    return v;
}

int cmpcresc(const void*a,const void*b)
{
    int vala=*(int*)a;
    int valb=*(int*)b;
    return (vala-valb);
}

int *distincte(int *v,int n,int *m)
{
    int i,*w,*aux;

    *m=0;
    qsort(v,n,sizeof(int),cmpcresc);

    w=NULL;

    for(i=0;i<n-1;i++)
        if(v[i]!=v[i+1])
    {
        (*m)++;
        aux=realloc(w,sizeof(int)*(*m));
        if(!aux)
        {
            printf("EROARE");
            free(w);
            return;
        }
        w=aux;
        w[*m-1]=v[i];
    }
        (*m)++;
        aux=realloc(w,sizeof(int)*(*m));

        if(!aux)
        {
            printf("EROARE");
            free(w);
            return;
        }
        w=aux;
        w[*m-1]=v[n-1];
        return w;
}
void afis(int*v,int n)
{
    int i;
    for(i=0;i<n;i++)
        printf("%d ",v[i]);
    printf("\n");
}

int main()
{
   int*v,*w,m,n;
   v=citire(&n);afis(v,n);
   w=distincte(v,n,&m);
   afis(w,m);
    return 0;
}
