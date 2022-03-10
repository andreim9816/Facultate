#include <stdio.h>
#include <stdlib.h>

void citire(float**v,int *n)
{
    int i;
    FILE*f=fopen("numere.txt","r");
    fscanf(f,"%d",n);
    *v=(float*)malloc(sizeof(float)*(*n));

    for(i=0;i<*n;i++)
    {
        fscanf(f,"%f",*v+i);
    }
}

void construct(float *v,int n,float **w,int *m)
{
    float *aux=NULL,x;
    int i;
    *m=1;
    *w=NULL;

    *w=malloc(sizeof(float));
    (*w)[0]=v[0];

    for(i=0;i<n-1;i++)
    {   (*m)=(*m)+2;
        aux=(float*)realloc(*w,sizeof(float)*(*m));
        if(aux)
        {
            *w=aux;
             x=(v[i]+v[i+1])/2;
            (*w)[*m-2]=x;
            (*w)[*m-1]=v[i+1];
        }
        else
        {
            printf("EROARE");
            free(*w);
            return ;
        }
    }

}

void afis(float *v,int n)
{
    int i;
    for(i=0;i<n;i++)
        printf("%f ",v[i]);
    printf("\n");
}

int main()
{
    float *v,*w;
    int n,m;
    citire(&v,&n);
    construct(v,n,&w,&m);
    afis(w,m);
    return 0;
}
