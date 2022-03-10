#include <stdio.h>
#include <stdlib.h>
#include<string.h>

void fct(char *nume,int v[],int n)
{
    FILE*f=fopen(nume,"w");

    FILE*g=tmpfile();

    int i,x,y;
    fwrite(&v[0],sizeof(int),1,g);

    for(i=1;i<n;i++)
    {
        x=v[i];
        int ok=1;
        fseek(g,0,SEEK_SET);
        while(fread(&y,sizeof(int),1,g)==1)
        {
            if(y==x)
                {
                    ok=0;
                    break;
                }
        }
        if(ok)
            fwrite(&x,sizeof(int),1,g);
        fflush(g);
    }
    fseek(g,0,SEEK_SET);

    while(fread(&x,sizeof(int),1,g)==1)
        fprintf(f,"%d ",x);

    fclose(g);
    fclose(f);
}

void afis(char*nume)
{
    FILE*f=fopen(nume,"r");
    int i;
    while(1)
    {
        fscanf(f,"%d ",&i);
        printf("%d ",i);
        if(feof(f))
       {
            fclose(f);
            return;
       }
    }

}

int main()
{
    int i,n;
   char destinatie[50];
   printf("n= ");
   scanf("%d",&n);
   int v[n];
    printf("\n Introduceti numerele \n");
   for(i=0;i<n;i++)
    scanf("%d",&v[i]);
   fgetc(stdin);
   printf("Numele fisierului: ");
   fgets(destinatie,50,stdin);

   destinatie[strlen(destinatie)-1]=NULL;

   fct(destinatie,v,n);

   afis(destinatie);
    return 0;
}
