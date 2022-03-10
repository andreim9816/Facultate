#include <stdio.h>
#include <stdlib.h>
#include<string.h>
typedef struct
{
    char*nume,*prenume;
    int nota[12];
    float punctaj;
}stud;

void citire(stud **v,int *n)
{
    int i,j,sum=0;
    FILE*f=fopen("matrice.txt","r");

    char s[40],t[40];

    fscanf(f,"%d",n); fgetc(f);

    *v=(stud*)malloc(sizeof(stud)*(*n));

    for(i=0;i<*n;i++)
    {
        fscanf(f,"%s %s",t,s);

        int lung1,lung2;

        lung1=strlen(t);
        lung2=strlen(s);

        t[lung1]=NULL;
        s[lung2]=NULL;

        (*v)[i].nume=malloc(sizeof(char)*(lung1+1));
        (*v)[i].prenume=malloc(sizeof(char)*(1+lung2));

        strcpy( (*v)[i].nume ,s);
        strcpy( (*v)[i].prenume ,t);

        sum=0;

        for(j=0;j<12;j++)
            {
                fscanf(f,"%d",&(*v)[i].nota[j]);
                sum=sum+(*v)[i].nota[j];
            }
        (*v)[i].punctaj=sum*5;
    }

    fclose(f);
}

void afis(stud*v,int n)
{
    int i,j;
    for(i=0;i<n;i++)
        {
            printf("%s %s ",v[i].nume,v[i].prenume);

            for(j=0;j<12;j++)
                printf("%d ",v[i].nota[j]);
            printf("\n");
        }
    printf("\n");
}

void afis_punctaje(stud*v,int n)
{
    int i;
    FILE*f=fopen("punctaje.txt","w");
    for(i=0;i<n;i++)
    {
        fprintf(f,"%f \n",v[i].punctaj);
    }
}

int cmpdescresc(const void*a,const void*b)
{
    stud x=*(stud*)a;
    stud y=*(stud*)b;

    if(x.punctaj<y.punctaj)
        return 1;
    else if(x.punctaj>y.punctaj)
        return -1;
    else
    {
        int nota1=x.nota[3];
        int nota2=y.nota[3];

        if(nota1<nota2)
            return 1;
        else return -1;
    }

}

void sortare(stud*v,int n)
{
    qsort(v,n,sizeof(v[0]),cmpdescresc);
}

int max(int a,int b)
{
    if(a>b)
        return a;
    return b;
}

void repartizare(stud*v,int n)
{
    FILE*g=fopen("Grozavesti.txt","w");
    FILE*k=fopen("Kogalniceanu.txt","w");
    FILE*c=fopen("Constructii.txt","w");

    int loc_groz=15;
    int loc_koga=3;
    int loc_cons=max(n-18,0);
    int i,j;

    for(i=0;i<n && loc_groz;i++)
    {
        fprintf(g,"%s %s \n",v[i].nume,v[i].prenume);
        loc_groz--;
    }

    for(j=i;j<n && loc_koga;j++)
    {
        fprintf(k,"%s %s \n",v[j].nume,v[j].prenume);
        loc_koga--;
    }
    for(i=j;i<n && loc_cons;i++)
    {
        fprintf(c,"%s %s\n",v[i].nume,v[i].prenume);
        loc_cons--;
    }

}

int main()
{
    stud*v;
    int n;
    citire(&v,&n);
    afis(v,n);
    sortare(v,n);
    afis_punctaje(v,n);
    repartizare(v,n);
    return 0;
}
