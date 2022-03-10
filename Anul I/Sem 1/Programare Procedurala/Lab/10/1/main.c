#include <stdio.h>
#include <stdlib.h>

void citire(int ***a,int *n)
{
    FILE*f=fopen("numere.in","r");
    int i,j;
    fscanf(f,"%d",n);

    *a=(int**)malloc(sizeof(int*)*(*n));

    for(i=0;i<*n;i++)
    {
        (*a)[i]=(int*)malloc(sizeof(int)*(*n));
        for(j=0;j<*n;j++)
        fscanf(f,"%d",&(*a)[i][j]);
    }
}

void afis(int **a,int l,int c)
{
    int i,j;
    for(i=0;i<l;i++)
    {
        for(j=0;j<c;j++)
            printf("%d ",a[i][j]);
        printf("\n");
    }
}

void scoate_diag_principala(int **a,int n,int ***b,int *nrl,int*nrc)
{
    *nrl=n;
    *nrc=n-1;
    int i,j;
    *b=(int**)malloc(sizeof(int*)*(*nrl));
    for(i=0;i<n;i++)
    {
        (*b)[i]=(int*)malloc(sizeof(int)*(*nrc));
        for(j=0;j<n;j++)
            if(i<j)
            (*b)[i][j-1]=a[i][j];
            else
            (*b)[i][j]=a[i][j];

    }
}

int main()
{
    int**a,n,**b,l,c;
    citire(&a,&n);
    scoate_diag_principala(a,n,&b,&l,&c);
    afis(b,l,c);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>

typedef struct
{

    float temp;
    char *nume;

}Oras;



void citire(Oras **v,int *n,char *numeFisier)
{
    FILE *f;
    f=fopen(numeFisier,"r");

    if(f==NULL)
    {
        printf("Eroare la deschidere fisier");
        return ;
    }
    (*n)=-1;

    *v=NULL;
 //   printf("%d\n",*n);
    while(1)
    {
       /*
       VARIANTA 1
        char s[40];
        fscanf(f,"%s %f",s,&(*v)[i].temp);
        int lung=strlen(s);
        (*v)[i].nume=(char *)malloc((lung)*sizeof(char));
        strcpy((*v)[i].nume,s);

        printf("%s  %f   \n",(*v)[i].nume,(*v)[i].temp);*/
        (*n)++;
        int *aux2;
        aux2=realloc((*v),(*n+1)*sizeof(Oras));
        if(aux2==NULL)
            {printf("EROARE");return -1;}
        (*v)=aux2;
        (*v)[(*n)].nume=NULL;
        char c;
        int lung=1;
        while((c=fgetc(f))!=' ')
        {
            lung++;
            char *aux;
            aux=realloc((*v)[(*n)].nume,lung*sizeof(char));

            if(aux!=NULL)
            {
                (*v)[(*n)].nume=aux;
                (*v)[(*n)].nume[lung-2]=c;
                (*v)[(*n)].nume[lung-1]='\0';

            }
        }


        fscanf(f,"%f",&(*v)[(*n)].temp);
        //printf("%.2f ",(*v)[i].temp);
        c=fgetc(f);
        printf("%s  %.2f   \n",(*v)[(*n)].nume,(*v)[(*n)].temp);

        if(feof(f))break;

        printf("\n%d\n",(*n));

    }

    fclose(f);
}


void maxim(Oras *v,int n,char *numeFisier)
{
    FILE *f;
    f=fopen(numeFisier,"w");

    if(f==NULL)
    {
        printf("Eroare la deschidere fisier");
        return ;
    }
    int i;
    int maxi=v[0].temp;
    for(i=1;i<n;i++)
      if(v[i].temp>maxi)
          maxi=v[i].temp;
    fprintf(f,"%d\n",maxi);
    for(i=0;i<=n;i++)
        {
            //printf("%s %.2f",v[i].nume,v[i].temp);
            if(v[i].temp==maxi)
           fprintf(f,"%s ",v[i].nume);
        }
    fclose(f);

}
int main()
{
    Oras *v;
    int n;
    citire(&v,&n,"temperaturi.txt");
    maxim(v,n,"maxime.txt");
    return 0;
}
