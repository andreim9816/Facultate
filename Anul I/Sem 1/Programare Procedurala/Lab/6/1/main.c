#include <stdio.h>
#include <stdlib.h>
#include<time.h>

void creare(int n)
{
    FILE*f=fopen("numere.bin","wb");

    int i,x;
    srand(time(NULL));
    for(i=0;i<9;i++)
    {
        x=rand()%(2*n+1);
        x=x-n;
        printf("%d  ",x);

        fwrite(&x,sizeof(int),1,f);
    } printf("\n");
    fclose(f);
}

void sortare(int n)
{
    int ok,i,x,y;
    FILE *f=fopen("numere.bin","rb+");
    ok=1;

    do
    {   rewind(f);
        ok=1;
        for(i=0;i<9;i++)
        {
            fread(&x,sizeof(int),1,f);
            fread(&y,sizeof(int),1,f);

            if(x>y)
            {
                ok=0;
                fseek(f,-2*sizeof(int),SEEK_CUR);
                fwrite(&y,sizeof(int),1,f);
                fwrite(&x,sizeof(int),1,f);


            }
           // fflush(f);
            fseek(f,-sizeof(int),SEEK_CUR);
        }
    }while(ok==0);
    fclose(f);
}

void afis(int n)
{
    int i;
    FILE*f=fopen("numere.bin","r");
    int x;
    for(i=0;i<9;i++)
    {
        fread(&x,4,1,f);
        printf("%d ",x);
    }
    fclose(f);
}

int main()
{
    int n;
  n=5;
    creare(n);
    sortare(n);
    afis(n);
    return 0;
}
