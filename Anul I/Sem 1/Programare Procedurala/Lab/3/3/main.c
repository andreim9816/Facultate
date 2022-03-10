#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<math.h>
#define medie_admitere(nota_mate,nota_info,nota_bac) 0.8*((nota_mate+nota_info)/2.0)+0.2*nota_bac
#define trecere 5
/// CRED CA MERGE
typedef struct
{
    unsigned nr_legitimatie;
    char nume[40];
    float nota_mate,nota_info,nota_bac,medie;
    char admis,buget;
}stud;

void creare_lista(stud v[],int nr_candidati, FILE *in)
{
    float nota1,nota2,nota3;
    int i;
    char nume[40];

    for(i=0;i<nr_candidati;i++)
    {
        fgets(nume,40,in);

        nume[strlen(nume)-1]='\0';
        fscanf(in,"%f %f %f",&nota1,&nota2,&nota3);   fgetc(in);

        strcpy(v[i].nume,nume);
        v[i].nota_mate=nota1;
        v[i].nota_info=nota2;
        v[i].nota_bac =nota3;
        v[i].medie=medie_admitere(nota1,nota2,nota3);
        v[i].admis=v[i].medie>=trecere?'y':'n';
    }
}

void ordonare_nume(stud v[],int nr_candidati)
{
      ///ordonare dupa nume
      int i;
    for(i=1;i<nr_candidati;i++)
    {
        stud x=v[i];
        int j=i-1;
        while(j>=0 && strcmp(v[j].nume,x.nume)>0)
        {
            v[j+1]=v[j];
            j--;
        }
        v[j+1]=x;
    }
}


void buget_taxa(stud v[],int n)
{

    ///functie care daca esti admis spune daca esti la buget sau la taxa
    int i,j,x;
    ordonare_nota(v,n);
    x=n*3/4;

    for(i=n-1;x!=0 && i>=0;i--)
        if(v[i].admis=='y')
    {
        v[i].buget='y';
        x--;
    }
    for(j=i;j>=0;j--)
        if(v[i].admis=='y')
        v[j].buget='n';
}

void afis_buget(stud v[],int nr_candidati)
{
    int i;
    for(i=0;i<nr_candidati;i++)
        if(v[i].buget=='y')
            printf("%s %f \n",v[i].nume,v[i].medie);
}
void afis_taxa(stud v[],int nr_candidati)
{
    int i;
    for(i=0;i<nr_candidati;i++)
        if(v[i].buget=='n')
            printf("%s \n",v[i].nume);
}
void afis_respinsi(stud v[],int nr_candidati)
{
    int i;
    for(i=nr_candidati-1;i>=0;i--)
        if(v[i].admis=='n')
        printf("%s \n",v[i].nume);
}

void ordonare_nota(stud v[],int n)
{
    int i,j;
    for(i=1;i<n;i++)
    {
        stud x=v[i];
        j=i-1;
        while(j>=0 && v[j].medie>x.medie)

        {
            v[j+1]=v[j];
            j--;
        }
        v[j+1]=x;
    }
}

void meniu(int op, stud v[],int nr_candidati)
{
printf("Introduceti 1 pentru a afisa toti candidatii \n Introduceti 2 pentru a afisa candidatii admisi la buget\n");
printf("Introduceti 3 pentru a afisa candidatii admisi la taxa \n Introduceti 4 pentru a afisa candidatii respinsi\n");
scanf("%d",&op);
    switch(op)
    {
        case 1: ordonare_nume(v,nr_candidati); afis_toti(v,nr_candidati); break;
        case 2: ordonare_nume(v,nr_candidati); afis_buget(v,nr_candidati); break;
        case 3: ordonare_nume(v,nr_candidati); afis_taxa(v,nr_candidati); break;
        case 4: ordonare_nota(v,nr_candidati); afis_respinsi(v,nr_candidati); break;

    }
}

int main()
{
    FILE *in=fopen("txt","r");

    stud v[1000];
    int nr_candidati,op;

    fscanf(in,"%d",&nr_candidati);
    fgetc(in);

    creare_lista(v,nr_candidati,in);

    ordonare_nota(v,nr_candidati);
    buget_taxa(v,nr_candidati);

    meniu(op,v,nr_candidati);

    return 0;
}


