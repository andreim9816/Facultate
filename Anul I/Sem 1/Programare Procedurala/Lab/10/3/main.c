#include <stdio.h>
#include <stdlib.h>

void citire(int ***a,int *nrl)
{
    int i,j,y,x,**aux;
    FILE*f=fopen("siruri.txt","r");
    *nrl=0;
    *a=NULL;

    while(fscanf(f,"%d",&x)==1)
    {
    (*nrl)++;

    aux=(int**)realloc(*a,sizeof(int*)*(*nrl));

    if(aux!=NULL)
    {
        *a=aux;
        (*a)[*nrl-1]=malloc(sizeof(int)*(x+1));
        (*a)[*nrl-1][0]=x;
        for(j=1;j<=x;j++)
        {
            fscanf(f,"%d",&y);
            (*a)[*nrl-1][j]=y;
        }
    }
    else
    {
        printf("EROARE");

        for(i=0;i<*nrl;i++)
        {
            free((*a)[i]);
        }
        free(a);

            return;
    }

    }

}

void afis(int **a,int nrl)
{ ///b) functie care afiseaza o matrice cu nrl linii
    int i,j;
    for(i=0;i<nrl;i++)
    {
        for(j=1;j<=a[i][0];j++)
            printf("%d ",a[i][j]);
        printf("\n");
    }
      printf("\n");
}

int cmpcresc(const void*a,const void*b)
{
    int vala=*(int*)a;
    int valb=*(int*)b;
    return vala-valb;
}


typedef struct
{
    int nr;
    int *adresa;
}vect;


int cmpcrescator_adrese(const void*a,const void*b)
{
    vect aa=*(vect*)a;
    vect bb=*(vect*)b;

    if(aa.nr>bb.nr)
    {
        int *aux;
        aux=aa.adresa;
        aa.adresa=bb.adresa;
        bb.adresa=aux;
        return 1;
    }
    else
        if(aa.nr<bb.nr)
            return -1;
    else return 0;

}

void construct_vector(int **a,int l,vect **v)
{ /// functie care creeaza un vector structura de tip vect in care sunt retinute nr de elemente pt o linie si adresa
/// respectiva, si le sorteaza cu qsort, interschimband manual adresele
    int i;
    *v=(vect*)malloc(sizeof(vect)*l);

    for(i=0;i<l;i++)
    {
        qsort( a[i]+1, a[i][0] , sizeof(int) , cmpcresc); /// sorteaza linia a[i]
        (*v)[i].nr=a[i][0];
        (*v)[i].adresa=a[i];
    }

    qsort(*v,l,sizeof(vect),cmpcrescator_adrese); /// sorteaza si interschimba adresele

    for(i=0;i<l;i++)
        a[i]=(*v)[i].adresa;
}

void interclasare(int **s, int m,int **t,int n)
{   /// interclaseaza 2 vectori s si t cu m, n elemente, si rezultatul il pune inapoi in s.
    /// s si t au ** pt ca se umbla la memoria lor
    int *nou,i=1,j=1;
    int k=1;
    nou=(int*)malloc(sizeof(int)*(m+n+1));

    while(i<=m && j<=n)
    {
        if((*s)[i]<(*t)[j])
        {
            nou[k]=(*s)[i];
            i++;
            (k)++;

        }
        else
        {
            nou[k]=(*t)[j];
            j++;
            (k)++;

        }
    }

    while(i<=m)
    {
        nou[k]=(*s)[i];
        i++;
        (k)++;
    }
    while(j<=n)
        {
            nou[k]=(*t)[j];
            j++;
            (k)++;
        }
    nou[0]=m+n;

    *s=nou;
    free((*t));
}


void interclasare_linii_matrice(int ***a,int *l)
{   /// functie care modifica interclaseaza liniile matricei
    int i;
    for(i=*l-2;i>=0;i--)
        {
        interclasare(&(*a)[i],(*a)[i][0],&(*a)[i+1],(*a)[i+1][0]);
        (*l)--;
        }
}

int main()
{
    int **a,nrl=0;
    vect *v;
    citire(&a,&nrl);
    construct_vector(a,nrl,&v);

  //  afis(a,nrl);
    interclasare_linii_matrice(&a,&nrl);
    afis(a,nrl);
    return 0;
}
