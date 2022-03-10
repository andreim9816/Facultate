#include <stdio.h>
#include <stdlib.h>

void citire(FILE *f,int a[][101],int *n)
{
    int i,j;

    fscanf(f,"%d", n);

    for(i=0;i<*n;i++)
        for(j=0;j<*n;j++)
        fscanf(f,"%d",&a[i][j]);
}

void afis(int a[][101],int n)
{
    int i,j;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
            printf("%d ",a[i][j]);
        printf("\n");
    }
}

void spiralaTrigo(int a[][101],int n)
{
    int l1,l2,c1,c2,i,j;
    l1=c1=0;
    l2=c2=n-1;

    while(l1<=l2 && c1<=c2)
    {

              for(j=c1;j<=c2;++j)
                printf("%d ",a[l1][j]);


              for(i=l1+1;i<=l2;i++)
                printf("%d ",a[i][c2]);

            if(c1!=c2)
              for(j=c2-1;j>c1;j--)
                printf("%d ",a[l2][j]);

            if(l1!=l2)
            for(i=l2;i>=l1+1;i--)
                printf("%d ",a[i][c1]);

        l1++;
        c1++;
        l2--;
        c2--;
    }
}

int main()
{
   int a[101][101],n;
   FILE *f=fopen("nr","r");
   citire(f,a,&n);
    spiralaTrigo(a,n);
    return 0;
}
