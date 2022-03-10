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
    fclose(f);
    fclose(g);
}

void afis(char*binar)
{
    int x;
    FILE*f=fopen(binar,"rb");

    while(fread(&x,sizeof(int),1,f)==1)
        printf("%d ",x);
    fclose(f);
}

void schimbaSemn(char*binar)
{
    int x;
    FILE*g=fopen(binar,"rb+");

    while(fread(&x,sizeof(int),1,g)==1)
    {
        x=-x;
        fseek(g,-sizeof(int),SEEK_CUR);
        fwrite(&x,sizeof(int),1,g);
        fflush(g);
    }
    fclose(g);
}
int main()
{
    char *nume="date.in",*binar="date.bin";

    textToBinar("date.in","date.bin");
    schimbaSemn("date.bin");
    afis("date.bin");

    return 0;
}
