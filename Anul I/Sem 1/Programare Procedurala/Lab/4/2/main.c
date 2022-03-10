#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    float suprafata;
    unsigned short camere;
    char adresa[101],tip[31];
    union
    {
        unsigned short balcon ;
        char decomandat;
        char tipCasa[21];

    };
}locuinta;

void citire(locuinta v[],int n)
{
    int i;
    for(i=0;i<n;++i)
    {
        scanf("%f %hu %s %s",&v[i].suprafata,&v[i].camere,v[i].adresa,v[i].tip);
        if(strcmp(v[i].tip,"garsoniera")==0)
            scanf("%hu",&v[i].balcon);
        else if(strcmp(v[i].tip,"apartament")==0)
            scanf("%c",&v[i].decomandat);
        else scanf("%s",v[i].tipCasa);
    }
}

void afis(locuinta v[],int n)
{
    int i;
    for(i=0;i<n;++i)
        printf("%s  %s  %hu \n",v[i].adresa,v[i].tip,v[i].camere);
}

void punctul_b(locuinta v[],int n)
{
    int i;
    float suprafataMax=0;
    char adresa[31];
    for(i=0;i<n;++i)
    {
        if(strcmp(v[i].tip,"garsoniera")==0)
            if(v[i].suprafata>suprafataMax)
                if(v[i].balcon==1)
                    {
                        suprafataMax=v[i].suprafata;
                        strcpy(adresa,v[i].adresa);
                    }
    }
    if(suprafataMax==0)
        printf("Nu exista");
    else printf("%s",adresa);
}

int main()
{
    int n;
    locuinta v[101];
    scanf("%d",&n);
    fflush(stdin);
    citire(v,n);
    punctul_b(v,n);
    return 0;
}
