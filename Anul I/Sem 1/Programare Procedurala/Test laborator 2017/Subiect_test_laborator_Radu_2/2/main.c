#include <stdio.h>
#include <stdlib.h>

void citire_matrice(int ***a ,int *m,int *n)
{
    int i,j;
    FILE*f=fopen("matrice.txt","r");

    fscanf(f,"%d %d", m,n);

    *a=(int**)malloc(sizeof(int*)*(*m));

    for(i=0;i<*m;i++)
        {
            (*a)[i]=(int*)malloc(sizeof(int)*(*n));

            for(j=0;j<*n;j++)
                fscanf(f,"%d",&(*a)[i][j]);
        }
}

void afis(int **a,int m,int n)
{
    int i,j;
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        printf("%d ",a[i][j]);
        printf("\n");
    } printf("\n");
}

void afis_maxim(int **a,int m,int n)
{
    int i,j,pozi=0,pozj=0;
    int maxi=a[0][0];

    FILE*f=fopen("maxime.txt","w");

    for(i=0;i<m;i++)
        for(j=0;j<n;j++)
        if(maxi<a[i][j])
    {
        maxi=a[i][j];
        pozi=i;
        pozj=j;
    }

    fprintf(f,"%d\n",maxi);
    fprintf(f,"%d\n",pozi);
    fprintf(f,"%d",pozj);


}

int sum_i(int *a,int n)
{
    int i,s=0;
    for(i=0;i<n;i++)
        s+=a[i];
    return s;
}

void afis_sum_linii(int **a,int m,int n)
{
    int i;
    for(i=0;i<m;i++)
    {
        printf("Suma elementelor de pe linia %d este %d\n",i,sum_i(a[i],n));
    }
}

void transpusa(int **a,int m1,int n1,int ***b,int *m2,int *n2)
{
    int i, j;
    *m2=n1;
    *n2=m1;

    *b=(int**)malloc(sizeof(int*)*(*m2));

    for(i=0;i<*m2;i++)
    {
        (*b)[i]=(int*)malloc(sizeof(int)*(*n2));
        for(j=0;j<*n2;j++)
            (*b)[i][j]=a[j][i];
    }
}

int cmpcrescator(const void*a,const void*b)
{
    int vala=*(int*)a;
    int valb=*(int*)b;

    return (vala-valb);
}

void sortare(int **a,int m,int n)
{
    int i;
    for(i=0;i<m;i++)
        qsort(a[i],n,sizeof(int),cmpcrescator);
}

void punctul_c(int **a,int m,int n)
{ /* facem transpusa, astfel sortam pe linii acele coloane,dupa care facem iar transpusa sa obtinem matricea initiala*/
    FILE*f=fopen("matrice_sort.txt","w");
    int **b,m1,n1;

    transpusa(a,m,n,&b,&m1,&n1);

    sortare(b,m1,n1);

    transpusa(b,m1,n1,&a,&m,&n);
    afis(a,m,n);

    fclose(f);
}

int main()
{
    int **a,n,m;
    citire_matrice(&a,&m,&n);
    //a)afis_maxim(a,m,n);
    //b) afis_sum_linii(a,m,n);
    //c) punctul_c(a,m,n);
    return 0;
}
