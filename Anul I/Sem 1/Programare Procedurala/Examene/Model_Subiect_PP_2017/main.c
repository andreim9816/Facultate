#include <stdio.h>
#include <stdlib.h>
#include<string.h>
typedef struct
{
    char*limba_rom;
    char*limba_straina;
}cuvant;

int cmp(const void*a,const void*b)
{
    if(strlen((char*)a) < strlen((char*)b))
        return -1;
    else return 1;
}

void incarca(cuvant **v,int *n,char*fisier)
{
    FILE*f=fopen(fisier,"r");
    if(!f)
    {
        printf("eroare la deschiderea fisierului")
        return;
    }
    fscanf(f,"%d",n);
    *v=(cuvant*)malloc(sizeof(cuvant)*n);
    if(!*v)
    {
        printf("Eroare");
        return;
    }

    int i;
    char s[21],t[21];
    for(i=0;i<n;i++)
    {
        fscanf(f,"%s %s",s,t);
        (*v).limba_rom=(char*)malloc(sizeof(char)*strlen(s)+1);
        (*v).limba_straina=(char*)malloc(sizeof(char)*strlen(t)+1);

        strcpy((*v).limba_rom,s);
        strcpy((*t).limba_rom,s);

    }


}
int main()
{
    printf("Hello world!\n");
    return 0;
}