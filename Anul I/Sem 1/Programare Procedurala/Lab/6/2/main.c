#include <stdio.h>
#include <stdlib.h>

void citire(FILE *f,FILE *f1,FILE *f2,int *n)
{
    int i,x;
    fscanf(f,"%d",n);
    for(i=1;i<=*n;i++)
    {
        fscanf(f,"%d",&x);
        if(x<0)
            fwrite(&x,sizeof(int),1,f1);
        else fwrite(&x,sizeof(int),1,f2);
    }
}

void afisare(FILE *f)
{
    int x;
    rewind(f);
   while(fread(&x,sizeof(int),1,f))
        printf("%d ",x);

}

int main()
{
    FILE *fin;
    FILE *fout1,*fout2;

    fin=fopen("numere_intregi.txt","r");
    fout1=fopen("pozitive","wb+");
    fout2=fopen("negative","wb+");

    int n;

    citire(fin,fout1,fout2,&n);

    afisare(fout1);
    afisare(fout2);

    return 0;
}
