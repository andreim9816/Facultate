#include <stdio.h>
#include <stdlib.h>
void citire(int ***a,int *n)
{
    int i,j;
    FILE*f=fopen("numere.in","r");
    fscanf(f,"%d",n);

    *a=malloc((*n)*sizeof(int*));

    for(i=0;i<*n;i++)
    {
        *(*a+i)=malloc(sizeof(int)*(*n));
        for(j=0;j<*n;j++)
            fscanf(f,"%d",*(*a+i)+j);
    }
    fclose(f);
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
     printf("\n");
}
//ii)
void intersect_diag(int **a,int n)
{
    int x=n/2;
    printf("%d", *(*(a+x)+x));
}
//iii)

void elemente_diag(int **a,int n,int **v,int **w)
{
    // construieste 2 vectori cu elementele de pe cele 2 diagonale
    int i;
    *v=malloc(sizeof(int*)*n);
    *w=malloc(sizeof(int*)*n);
    for(i=0;i<n;i++)
       (*v)[i]=a[i][i];
    for(i=0;i<n;i++)
        (*w)[i]=a[i][n-i-1];
}

void afis1(int *v,int n)
{
    int i;
    for(i=0;i<n;i++)
        printf("%d ",*(v+i));
    printf("\n");
}

/// iv)
void interschimb(int ***a,int n,int l1,int l2)
{
    int i,aux;
    for(i=0;i<n;i++)
    {
        aux=(*a)[l1][i];
        (*a)[l1][i]=(*a)[l2][i];
        (*a)[l2][i]=aux;
    }
}

int main()
{
    int **a,n,*w,*v,lunu,ldoi;
    citire(&a,&n);
    printf("Matricea este \n");
    afis(a,n);
    printf("Elementele de pe cele 2 diagonale sunt \n");
    elemente_diag(a,n,&v,&w);
    afis1(v,n);
    afis1(w,n);


    printf("Sa se interschimbe liniile:\n ");
    scanf("%d %d",&lunu,&ldoi);
    interschimb(&a,n,lunu,ldoi);
    printf("\nNoua matrice va arata \n");
    afis(a,n);
    return 0;
}
