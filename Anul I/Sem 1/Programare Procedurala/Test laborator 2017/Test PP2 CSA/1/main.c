#include <stdio.h>
#include <stdlib.h>
#include<string.h>

 /// n am facut ultima functie!!!

struct oras
{
    int populatie;
    char denumire[20];
};

void citire(struct oras **v,int *n)
{
    int i;
    FILE*f=fopen("date","r");
    if(!f)
    {
        printf("eroare la deschidere");
        return;
    }
    fscanf(f,"%d",n);

    *v=(struct oras*)malloc(sizeof(struct oras)*(*n));

    char s[20];

    for(i=0;i<*n;i++)
    {
        fscanf(f,"%s",s);
        s[strlen(s)]=NULL;
        fscanf(f,"%d",&(*v)[i].populatie);
        strcpy((*v)[i].denumire,s);
    }
    fclose(f);
}

void afis(struct oras*v,int n)
{
    int i;
    for(i=0;i<n;i++)
    {
        printf("%s ",v[i].denumire);
        printf("%d \n",v[i].populatie);
    }
}

void scrieBin(struct oras *v,int n,char*nume)
{
    FILE*f=fopen(nume,"wb");

    if(!f)
    {
        printf("eroare fisier");
        return;
    }

    int i,lung;

    for(i=0;i<n;i++)
    {
        lung=strlen(v[i].denumire);
        fwrite(&lung,sizeof(int),1,f);
        fwrite(v[i].denumire,sizeof(char),lung,f);
        fwrite(&v[i].populatie,sizeof(int),1,f);
    }
    fclose(f);
}

void afisare(char*binar,char*text)
{
    int x,y;
    char s[20];

    FILE*fin=fopen(binar,"rb");
    FILE*fout=fopen(text,"w");

    while(fread(&x,sizeof(int),1,fin)==1)
    {
        //x - lungimea , y - populatia
        fread(s,sizeof(char)*x,1,fin);
        fread(&y,sizeof(int),1,fin);

        s[x]=NULL; /// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! TREBUIE PUS NULL

        fprintf(fout,"%s ",s);
        fprintf(fout,"%d\n",y);
    }

    fclose(fin);
    fclose(fout);

}

 /// n am facut ultima functie!!!
int main()
{
    struct oras*v;
    int n;
    citire(&v,&n);afis(v,n);
    scrieBin(v,n,"date.bin");
    afisare("date.bin","date.txt");
    return 0;
}
