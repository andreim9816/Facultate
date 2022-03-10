#include <stdio.h>
#include <stdlib.h>
typedef struct
{
    float a,b;
}complex;

void citire(complex **v,int *n)
{
    int i;
    FILE *f=fopen("numere.in","r");
    fscanf(f,"%d",n);

    *v=malloc(sizeof(complex*)*(*n));

    for(i=0;i<*n;i++)
    {
        fscanf(f,"%f %f",&((*v+i)->a),&((*v+i)->b));
    }
}
void afis(complex *v,int n)
{
    int i;
    for(i=0;i<n;i++)
        printf("%f %f\n",v[i].a,v[i].b);
}

float modul(complex v)
{
    return (v.a)*(v.a)+(v.b)*(v.b);
}

complex modul_maxim(complex*v,int n)
{ // returneaza un pointer la nr respectiv
    int i;
    float mod,max=0;
    complex t;
    for(i=0;i<n;i++)
    {
        mod=modul(v[i]);
        if(max<mod)
            {max=mod;;
             t=v[i];
            }
    }
    return t;
}

int main()
{
   complex *v;
   int n;
   citire(&v,&n);
   complex t=modul_maxim(v,n);
   printf("%f %f ",t.a,t.b);
    return 0;
}
