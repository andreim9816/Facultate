#include <stdio.h>
#include <stdlib.h>
#define medie_admitere(nota_mate,nota_info,nota_bac) 0.8*((nota_mate+nota_info)/2)+0.2*nota_bac
#define trecere 5
typedef struct
{
    unsigned nr_legitimatie;
    char nume[40];
    float nota_mate,nota_info,nota_bac,medie;
    char admis,buget;
}stud;

void deplasare(stud v[],int &n,int poz)
{
    int i;
    for(i=n;i>=poz;i--)
        v[i+1]=v[i];
    n++;
}

int cautare(stud v[],int n,char nume[])
{
    int i;
    if(n==0)
        return 0;
    if(strcmp(v[n].nume,nume)>0)
        return n+1;
    else if(strcmp(nume,v[0].nume)<0)
        return 0;
    else for(i=1;i<=n;i++)
        if(strcmp(v[i].nume,nume)>0)
        return i+1;
}

void ad(stud v[],int n, char nume[],float nota_mate,float nota_info,,float nota_bac,int poz)
{
    strcpy(v[poz].nume,nume);
    v[poz].nota_mate=nota_mate;
    v[poz].nota_info=nota_info;
    v[poz].nota_bac=nota_bac;
}

void creare_lista(int nr_candidati)
{
    int i;
    char nume[40];

    for(i=1;i<=nr_candidati;i++)
    {
        fgets(nume)
    }
}
int main()
{
    FILE *in=fopen("txt","r");

    stud v[1000];
    int nr_candidati;

    scanf("%d",&nr_candidati);


    return 0;
}


