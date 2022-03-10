#include <stdio.h>
#include <stdlib.h>

void textToBinar(char*nume,char*binar)
{
    int i,x=0;
    FILE*f=fopen(nume,"r");
    FILE*g=fopen(binar,"wb");

    if(!f)
    {
        printf("Fisierul de deschidere nu este existent");
        return;
    }

    while(fscanf(f,"%d",&x)==1)
        fwrite(&x,sizeof(int),1,g);
}

void binarText(char*nume,char*binar)
{
    int i,x;
    FILE*f=fopen(binar,"rb");
    FILE*g=fopen(nume,"w");

    if(!f)
    {
        printf("Fisierul de deschidere nu exista");
        return;
    }

    while(fread(&x,sizeof(int),1,f)==1)
        fprintf(g+,"%d ",x);
}

int main()
{
    char fisier[]="date.in";
    char binar[]="date.bin";
    binarText(fisier,binar);
    return 0;
}
