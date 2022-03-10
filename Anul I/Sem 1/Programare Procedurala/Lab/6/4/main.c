#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    unsigned   id;
    float nota;
    char nume[21];
    char prenume[21];

}student;

void citire(student **v,int *n,char *fisier,char *binar)
{
    int i;
    FILE *f=fopen(fisier,"r");
    FILE *g=fopen(binar,"wb");
    fscanf(f,"%d",n);
    fgetc(f);

    *v=malloc((*n)*sizeof(student));

    for(i=0;i<(*n);i++)
    {

        fscanf(f,"%u",&(*v)[i].id); printf("%d ",(*v)[i].id);
        fscanf(f,"%s %s ",(*v)[i].nume,(*v)[i].prenume); printf("%s %s ",(*v)[i].nume,(*v)[i].prenume);
        fscanf(f,"%f",&(*v+i)->nota); printf("%f\n",(*v)[i].nota);
        fwrite(&(*v)[i],sizeof(student),1,g);
    }
    fclose(f);
    fclose(g);
}

void afis(int n,char *nume_binar,char *nume_text)
{
    int i;
    student v;

    FILE *f=fopen(nume_binar,"rb");
    FILE *g=fopen(nume_text,"w");

    for(i=0;i<n;i++)
    {
        fread(&v,sizeof(student),1,f);
        fprintf(g,"%u %s %s %f \n",v.id,v.nume,v.prenume,v.nota);
    }
    fclose(f);
    fclose(g);
}

void modif(char *bin,unsigned id,float nota)
{
    FILE*f=fopen(bin,"rb+");

    int i;
    student v;

    while(fread(&v,sizeof(student),1,f)==1)
    {
        if(id == v.id)
            {
            fseek(f,-sizeof(student),SEEK_CUR);
            fseek(f,sizeof(unsigned int),SEEK_CUR);
            fwrite(&nota,sizeof(float),1,f);
            fflush(f);
            break;
            }
    }
    fclose(f);
}
int main()
{
    char in[]="date.in";
    char out[]="date.bin";
    char finall[]="date.txt";
    student *v;
    int n;
    int id=12;
    float nota=4;
    citire(&v,&n,in,out);
    modif(out,id,nota);
    afis(n,out,finall);
    return 0;
}
