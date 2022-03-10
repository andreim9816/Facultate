#include <stdio.h>
#include <stdlib.h>
#include<string.h>
void textToBin(char*text,char*bin)
{
    FILE*fin=fopen(text,"r");
    FILE*fout=fopen(bin,"wb");

    if(!fin)
    {
        printf("eroare");
        return;
    }
    if(!fout)
    {
        printf("Eroare");
        return;
    }

    int x;
    while(fscanf(fin,"%d",&x)==1)
    {
        fwrite(&x,sizeof(int),1,fout);
    }

    fclose(fin);
    fclose(fout);
}

void citire_vect(char*bin, int**v,int *n)
{
    int *aux,x;
    *n=0;
    *v=NULL;
    FILE*fin=fopen(bin,"rb");
    if(!fin)
    {
        printf("EROARE");
        return;
    }
    while(fread(&x,sizeof(int),1,fin)==1)
    {
        (*n)++;
        aux=realloc(*v,sizeof(int)*(*n));
        if(!aux)
        {
            printf("EROARE");
            return;
        }
        *v=aux;
        (*v)[*n-1]=x;
    }
    fclose(fin);

}

int cmpIntregi(const void*a,const void*b)
{   /// descrescator !!
    int x,y;
    x=*(int*)a;
    y=*(int*)b;
    if(x<y)
        return 1;
    else if(x>y)
        return -1;
    else return 0;
}

void sortareDescresc(void *v,int n,int dim,int (*cmp)(const void*,const void*))
{
    char *p=v;
    char*aux=(char*)malloc(dim);
    int i,j;
    for(i=0;i<n-1;i++)
        for(j=i+1;j<n;j++)
        if(cmp(p+i*dim,p+j*dim)>0)
        {
            memcpy(aux,p+i*dim,dim);
            memcpy(p+i*dim,p+j*dim,dim);
            memcpy(p+j*dim,aux,dim);
        }
    free(aux);
}

void sortare_qsort(int *v,int n)
{
    qsort(v,n,sizeof(int),cmpIntregi);
}

void afis(int *v,int n)
{
    int i;
    for(i=0;i<n;i++)
        printf("%d ",v[i]);
}
int main()
{
    int *v,n;
    textToBin("date.in","date.bin");
    citire_vect("date.bin",&v,&n);
    //sortareDescresc(v,n,sizeof(int),cmpIntregi);
    sortare_qsort(v,n);
    afis(v,n);
    return 0;
}
