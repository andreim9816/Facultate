#include <stdio.h>
#include <stdlib.h>
#include<string.h>
typedef struct
{
 int nrMatricol;
 char *nume;
 int grupa;
 double medie;
} student;

void citire(student**v,int *n,char *fisier)
{
    *n=0;
    *v=NULL;

    int i;
    char linie[500],*p;
    FILE*f=fopen(fisier,"r");
    student *aux;

    if(!f)
    {
        printf("Nu s-a gasit fisierul");
        return;
    }

    while(fgets(linie,500,f)!=NULL)
    {
       //  printf("%s ",linie);
        (*n)++;
        aux=realloc(*v,sizeof(student)*(*n));
        if(!aux)
        {
            printf("EROARE");
            free(*v);
            return;
        }
        *v=aux;

        p=strtok(linie,",");

            (*v)[*n-1].nrMatricol=atoi(p);
            p=strtok(NULL,",");

            (*v)[*n-1].nume=malloc(sizeof(char)*(strlen(p)) +1 );
            strcpy((*v)[*n-1].nume,p);
            (*v)[*n-1].nume[strlen((*v)[*n-1].nume)]='\0';

            p=strtok(NULL,",");

            (*v)[*n-1].grupa=atoi(p);

            p=strtok(NULL,",\n");

            (*v)[*n-1].medie=atof(p);

    }
    fclose(f);
}

void afis(student *v,int n)
{
    int i;
    for(i=0;i<n;i++)
        printf("%d %s %d %f\n",v[i].nrMatricol,v[i].nume,v[i].grupa,v[i].medie);
}

void scrieBin(student *v,int n, char*binar)
{
    FILE*f=fopen(binar,"wb+");
    int i;

    for(i=0;i<n;i++)
    {
        int matricol=v[i].nrMatricol;
        int lungime=strlen(v[i].nume)+1;
        int grupa=v[i].grupa;
        double medie=v[i].medie;

        fwrite(&matricol,sizeof(int),1,f);
        fwrite(&lungime,sizeof(int),1,f);
        fwrite(v[i].nume,sizeof(char),lungime,f);
        fwrite(&grupa,sizeof(int),1,f);
        fwrite(&medie,sizeof(double),1,f);
    }

    fflush(f);

    fseek(f,0,SEEK_SET);
    fclose(f);
}

void afisBinar(char*binar)
{
    FILE*f=fopen(binar,"rb");

        int matricol,grupa,lungime;
        double medie;
        char nume[50];
    while(fread(&matricol,sizeof(int),1,f)==1)
    {
        printf("matricol = %d\n",matricol);

        fread(&lungime,4,1,f);
        printf("lungime cuvant = %d \n",lungime);

        fread(nume,sizeof(char),lungime,f);
        printf("cuvantu = %s\n",nume);

        fread(&grupa,4,1,f);
        printf("grupa = %d\n",grupa);

        fread(&medie,sizeof(double),1,f);
        printf("medie = %f\n",medie);
    }
  fclose(f);
}


void citireFromBinar(student**v,int *n,char *bin)
{
    FILE*f=fopen(bin,"rb");

    *v='\0';
    *n=0;

    int matricol,grupa,lungime;
    float medie;
    char *nume;

    while(fread(&matricol,sizeof(int),1,f)==1)
    {
        student *aux;
        aux=realloc(*v,sizeof(student) *(*n+1));

        if(!aux)
        {
            printf("EROARE");
            free(*v);
            return;
        }
        *v=aux;

        (*v)[*n].nrMatricol=matricol;

        fread(&lungime,sizeof(int),1,f);
        (*v)[*n].nume=malloc(sizeof(char)*lungime);
        fread( (*v)[*n].nume , sizeof(char) , lungime , f);

        fread(&(*v)[*n].grupa,sizeof(int),1,f);

        fread(&(*v)[*n].medie,sizeof(double),1,f);
          (*n)++;
    }
    fclose(f);
}

void sterge_student(char*binar,int mat)
{
    FILE*f=fopen(binar,"rb+");
    FILE*fp=fopen("fisierNEW.txt","wb");
    int matricol,grupa,i,lungime;
    char nume[50];
    double medie;
    student v;

    while(fread(&matricol,4,1,f)==1)
    {
        fread(&lungime,4,1,f);
        fread(nume,1,lungime,f);
        fread(&grupa,4,1,f);
        fread(&medie,sizeof(double),1,f);

        if(matricol!=mat)
        {
            fwrite(&matricol,4,1,fp);
            fwrite(&lungime,4,1,fp);
            fwrite(nume,1,lungime,fp);
            fwrite(&grupa,4,1,fp);
            fwrite(&medie,sizeof(double),1,fp);
        }
    }

    fclose(f);
    fclose(fp);

    remove(binar);
    rename("fisierNEW.txt",binar);
}

int main()
{
    char *text="date.in";
    char *textBin="date.bin";
    student *v,*w;
    int n,m;
    citire(&v,&n,text);
    scrieBin(v,n,textBin);

    sterge_student(textBin,112);
    afisBinar(textBin);
    citireFromBinar(&w,&m,textBin);
    afis(v,n);
    return 0;
}
