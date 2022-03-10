#include <stdio.h>
#include <stdlib.h>
#include<string.h>
typedef struct
{
    char *nume;
    float temp;
}oras;

void citire(oras **v,int *n)
{
    int lung;
    *n=0;
    *v=NULL;
    char c,*aux;
    FILE*f=fopen("temperaturi.txt","r");

    if(!f)
    {
        printf("Eroare la deschiderea fisierului");
        return;
    }

    while(1)
    {
        (*n)++;

        oras *aux1;
        aux1=realloc(*v,sizeof(oras)*(*n));

        if(!aux1)
        {
            printf("Eroare de memorie");

            free(v);

            return ;
        }

        *v=aux1;
        lung = 1;
        (*v)[*n-1].nume='\0';

        while(( c = fgetc(f) ) !=' ')
        {

            lung++;
            aux=realloc((*v)[*n-1].nume,sizeof(char)*lung);

            if(!aux)
            {
                printf("EROARE");
                free(v);

                return ;
            }
            (*v)[*n-1].nume=aux;
            (*v)[*n-1].nume[lung-1]='\0';
            (*v)[*n-1].nume[lung-2]=c;
        }

        fscanf(f,"%f",&(*v)[*n-1].temp);
        fgetc(f);

        if(feof(f))
            break;

    }
    fclose(f);
}

void afis(oras *v,int n)
{
    int i;
    for(i=0;i<n;i++)
        {
            printf("%s ",v[i].nume);
            printf("%.2f \n",v[i].temp);
        }
}

void oraseTempMax(oras*v,int n)
{
    int i;
    FILE*f=fopen("maxime.txt","w");

    float maxi=v[0].temp;

    for(i=0;i<n;i++)
        if(v[i].temp>maxi)
            maxi=v[i].temp;

    fprintf(f,"%.2f\n",maxi);

    for(i=0;i<n;i++)
        if(v[i].temp == maxi )
        fprintf(f,"%s\n",v[i].nume);

    fclose(f);
}

void medie_temp(oras*v,int n)
{
    int i;
    float sum=0,medie;

    for(i=0;i<n;i++)
        sum+=v[i].temp;

    medie=(float)sum/n;

    printf("%f\n",medie);
}

int cmpdescresc(const void *a,const void*b)
{
    oras v1,v2;

    v1=*(oras*)a;
    v2=*(oras*)b;

    if(v1.temp>v2.temp)
        return -1;
    else if(v1.temp<v2.temp)
        return 1;
    else
    {
        return strcmp(v1.nume,v2.nume);
    }
}

void sortare_orase(oras*v,int n)
{
    int i;
    qsort(v,n,sizeof(oras),cmpdescresc);

}

int main()
{
    oras*v;
    int n;
    citire(&v,&n);
    oraseTempMax(v,n);
    medie_temp(v,n);
    sortare_orase(v,n);
    afis(v,n);
    return 0;
}
