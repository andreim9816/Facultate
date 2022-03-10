#include <stdio.h>
#include <stdlib.h>

typedef struct
{
   int suprafata;
    int nrCamere;
    char adresa[101];
    char tipLocuinta[31];

    union
    {
    int balcon;
    char decomandat;
    char tipCasa[20];
    };

}locuinta;

void citire(FILE *f, int n, locuinta v[])
{
    int i;
    for(i=0;i<n;i++)
    {
        fscanf(f,"%s %s",v[i].adresa,v[i].tipLocuinta);

        fscanf(f,"%d %d",&v[i].suprafata,&v[i].nrCamere);

        if(strcmp(v[i].tipLocuinta,"garsoniera")==0)
            fscanf(f,"%d",&v[i].balcon);
        else if(strcmp(v[i].tipLocuinta,"apartament")==0)
            fscanf(f,"%c",&v[i].decomandat);
        else fscanf(f,"%s",v[i].tipCasa);
    }
}

void afis(locuinta v[],int n)
{
    int i;
    for(i=0;i<n;i++)
        printf("%s %d \n",v[i].adresa,v[i].suprafata);
}

int main()
{
    FILE *f=fopen("txt","r");
    int i,n;
    locuinta v[1001];
    fscanf(f,"%d",&n);
    fflush(f);

    afis(v,n);
    return 0;
}
