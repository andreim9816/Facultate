#include <stdio.h>
#include <stdlib.h>
#include<string.h>

typedef struct
{
    char cnp[14];
    char*nume;
    int varsta;
    int salariu;
}angajat;

void citire(angajat **v,int *n)
{
    FILE*f=fopen("date.in","r");

    if(!f)
    {
        printf("Nu s-a gasit fisierul de citire");
        return;
    }

    *n=0;
    *v=NULL;

    angajat *aux;
    int i,lung;
    char nume[50],cnp[14];

    while(fscanf(f,"%s",cnp)==1)
    {
        aux=realloc(*v,sizeof(angajat)*(*n+1));
        if(!aux)
        {
            printf("EROARE");
            for(i=0;i<*n;i++)
                free( (*v)[i].nume);
            free(*v);
            return;
        }

        *v=aux;
       strcpy((*v)[*n].cnp,cnp);


       fscanf(f,"%s",nume);
       lung=strlen(nume)+1;
       (*v)[*n].nume=(char*)malloc(sizeof(char)*lung);
       strcpy((*v)[*n].nume,nume);


       fscanf(f,"%d",&(*v)[*n].varsta);
       fscanf(f,"%d",&(*v)[*n].salariu);
        (*n)++;
    }
    fclose(f);
}

void afis(angajat *v,int n)
{
    int i;
    for(i=0;i<n;i++)
        printf("%s %s %d %d\n",v[i].cnp,v[i].nume,v[i].varsta,v[i].salariu);
}

void scrieBin(angajat*v,int n,char*binar)
{
    FILE*f=fopen(binar,"wb");

    int lung,i;

    for(i=0;i<n;i++)
    {
        fwrite(v[i].cnp,sizeof(char),14,f);     // printf("%s ",v[i].cnp);

        lung=strlen(v[i].nume)+1;
        fwrite(&lung,sizeof(int),1,f);
                                              //  printf("%d ",lung);
        fwrite(v[i].nume,sizeof(char),lung,f); //  printf("%s ",v[i].nume);

        fwrite(&v[i].varsta,sizeof(int),1,f);  //  printf("%d ",v[i].varsta);
        fwrite(&v[i].salariu,sizeof(int),1,f); //  printf("%d\n",v[i].salariu);
        fflush(f);
    }
    fclose(f);
}

void afisBin(char*bin)
{
    FILE*f=fopen(bin,"rb");

    if(!f)
    {
        printf("eroare la deschiderea fisierului");
        return ;
    }

    int lungime,salariu,varsta;
    char cnp[14],nume[50];

    while(fread(cnp,sizeof(char)*14,1,f)==1)
    {
        fread(&lungime,sizeof(int),1,f);
        fread(nume,sizeof(char),lungime,f);
        fread(&varsta,sizeof(int),1,f);     ;
        fread(&salariu,sizeof(int),1,f);


        printf("%s ",cnp);
        printf("%s ",nume);
        printf("%d ",varsta);
        printf("%d \n",salariu);
    }


    fclose(f);

}

void adaugareAng(char*binar,char *cnp,char *nume,int varsta,int salariu)
{
    FILE*f=fopen(binar,"ab+");

    if(!f)
    {
        printf("eroare la deschiderea fisierului");
        return;
    }

    int lungime;
    lungime=strlen(nume)+1;

    fwrite(cnp,sizeof(char),14,f);
    fwrite(&lungime,sizeof(int),1,f);
    fwrite(nume,sizeof(char),lungime,f);
    fwrite(&varsta,sizeof(int),1,f);
    fwrite(&salariu,sizeof(int),1,f);

    fclose(f);
}

void scriereAngajatiSalariuMediu(char*bin)
{
    float mediu=0;
    FILE*f=fopen(bin,"rb");
    FILE*fout=fopen("salarii.txt","w");
    int k=0;
    if(!f)
    {
        printf("EROARE");
        return;
    }

    int varsta,salariu,lungime;
    char cnp[14],nume[50];

    while(fread(cnp,sizeof(char)*14,1,f)==1)
    {
        fread(&lungime,sizeof(int),1,f);
        fread(nume,sizeof(char),lungime,f);
        fread(&varsta,sizeof(int),1,f);
        fread(&salariu,sizeof(int),1,f);
        k++;
        mediu+=salariu;

        fprintf(fout,"%s %d\n",nume,salariu);

    }
    fprintf(fout,"%f",(float)mediu/k);

    fclose(f);
    fclose(fout);
}

void afisSalarMax(char *bin)
{
    char cnp[14],nume[50];
    int varsta,salariu,lungime,salarMax=-1;

    FILE*f=fopen(bin,"rb+");

    while(fread(cnp,sizeof(char)*14,1,f)==1)
    {
        fread(&lungime,sizeof(int),1,f);
        fread(nume,sizeof(char),lungime,f);
        fread(&varsta,sizeof(int),1,f);
        fread(&salariu,sizeof(int),1,f);

        if(salariu>salarMax)
            salarMax=salariu;
    }

    fflush(f);

    fseek(f,0,SEEK_SET);

    while(fread(cnp,sizeof(char)*14,1,f)==1)
    {
        fread(&lungime,sizeof(int),1,f);
        fread(nume,sizeof(char),lungime,f);
        fread(&varsta,sizeof(int),1,f);
        fread(&salariu,sizeof(int),1,f);

        if(salariu==salarMax)
            {printf("%s ",nume);}
    }
    fclose(f);
}

void stergere(char *cnp,char *bin)
{
    FILE*f=fopen(bin,"rb");
    FILE*ft=fopen("TMP_AUX","wb+");

    int salariu,varsta,lungime;
    char nume[50],CNP[14];

    while(fread(CNP,sizeof(char)*14,1,f)==1)
    {
        fread(&lungime,sizeof(int),1,f);
        fread(nume,sizeof(char),lungime,f);
        fread(&varsta,sizeof(int),1,f);
        fread(&salariu,sizeof(int),1,f);

        if(strcmp(cnp,CNP)!=0)
        {
         fwrite(CNP,sizeof(char),14,ft);
         fwrite(&lungime,sizeof(int),1,ft);
         fwrite(nume,sizeof(char),lungime,ft);
         fwrite(&varsta,sizeof(int),1,ft);
         fwrite(&salariu,sizeof(int),1,ft);
        }

    }

    fflush(ft);
    fflush(f);

    fclose(f);
    fclose(ft);

    remove(bin);

    rename("TMP_AUX",bin);
}

int main()
{
    angajat*v;
    int n;
    citire(&v,&n);
    scrieBin(v,n,"date.bin");
    adaugareAng("date.bin","1111111111111","NUME",10,10);
  //  afisBin("date.bin");
  //  scriereAngajatiSalariuMediu("date.bin");
 //   afisSalarMax("date.bin");
    stergere("1111111111111","date.bin");
    afisBin("date.bin");
    return 0;
}

1 1 1 1 1
1 1 1 1
1 1 1
1 1
1
1 1
1 1 1
1 1 1 1
1 1 1 1 1
