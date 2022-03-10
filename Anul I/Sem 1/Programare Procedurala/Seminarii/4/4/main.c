#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include<math.h>
//a)
void construct (int ***a,int *n)
{
    int i,j;
    srand(time(NULL));
    *n=10+rand()%90;

    printf("Numarul de linii si coloane este %d \n",*n);

    *a=(int**)malloc(sizeof(int*)*(*n));

    for(i=0;i<*n;i++)
    {
        (*a)[i]=(int*)malloc(sizeof(int)*(*n));
        for(j=0;j<*n;j++)
            (*a)[i][j]=abs(i-j);
    }
}

void afis(int **a,int n)
{
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
            printf("%d ",a[i][j]);
        printf("\n");
    }
}

// ii)

void scriereInBinar(int **a,int n,char*nume)
{
    FILE *f=fopen(nume,"wb");
    int i,j,x;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
    {
        fwrite(&a[i][j],sizeof(int),1,f);
    }
    fclose(f);
}

void afis2(char*binar)
{
    int x,n;
    FILE*f=fopen(binar,"rb");
    fseek(f,0,SEEK_END);
    n=ftell(f);
    n=n/sizeof(int);
    n=sqrt(n);

    fseek(f,0,SEEK_SET);
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            fread(&x,4,1,f);
            printf("%d ",x);
        }
        printf("\n");
    }
    fclose(f);
}


void interschimb(int n,char*nume)
{
    int i,j;
    int aux1[n],aux2[n];
    srand(time(NULL));
    i=rand()%n;
    j=rand()%n;

    printf("Liniile care se vor schimb sunt %d si %d \n",i,j);
    FILE*f=fopen(nume,"rb+");

    int k;

    fseek(f,sizeof(int)*i*n,SEEK_SET);//fflush(f);
    fread(aux1,sizeof(int),n,f);fflush(f);

    fseek(f,sizeof(int)*j*n,SEEK_SET);////fflush(f);
    fread(aux2,sizeof(int),n,f);fflush(f);

    fseek(f,sizeof(int)*n*i,SEEK_SET);//fflush(f);
    fwrite(aux2,sizeof(int),n,f);fflush(f);

    fseek(f,sizeof(int)*n*j,SEEK_SET);//fflush(f);
    fwrite(aux1,sizeof(int),n,f);fflush(f);

    fclose(f);

}

int main()
{   int **a,n;
    char*nume="matrice.bin";

    construct(&a,&n);
    scriereInBinar(a,n,nume);

    interschimb(n,nume);
    afis2(nume);

    return 0;
}
