#include <stdio.h>
#include <stdlib.h>
#include<string.h>
void inlocuire(int n)
{
    char c1='�'; char cc1='t';
    char c2='�'; char cc2='s';
    char c3='�'; char cc3='S';
    char c;
    char *p;
    char s[300];
    int i;
    for(i=0;i<n;i++)
    {
        printf("Nume fisier= ");
        scanf("%s",s);
        printf("\n");
        FILE*f=fopen(s,"r");

        char dest[300];
        strcpy(dest,s);

        strcat(dest,"_final");
        dest[strlen(s)+6]='\0';
        FILE*fout=fopen(dest,"w");
        if(!f)
        {
            printf("Nu s-a gasit fisierul %s. Mai incearca!\n",s);
            i--;
        }
        else
        {
            while( (c=fgetc(f))!=EOF)
                if(c==c1)
                putc(cc1,fout);
                else if(c==c2)
                    putc(cc2,fout);
                else if(c==c3)
                    putc(cc3,fout);
                else putc(c,fout);
        }
        fclose(f);
        fclose(fout);
    }
}

int main()
{   int n;
    printf("Atentie!! Cand introduceti numele fiserelor, trebuie introdusa si extensa acestora (de obice .srt). Daca nu sunteti siguri,intrati in proprietati si veti vedea acolo. Ex: ep1.srt, ep1.txt etc\n\n\n\n");
    printf("Introduceti numarul de fisiere n= ");
    scanf("%d",&n);
    inlocuire(n);
    return 0;
}