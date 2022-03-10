#include <stdio.h>
#include <stdlib.h>

 unsigned a[5001],b[5001];

void citire(FILE *f,unsigned frecv[])
{
    int i,x,n;
    fscanf(f,"%d",&n);
    for(i=0;i<n;++i)
        {fscanf(f,"%d",&x);
         frecv[x+2000]++;
        }
}

int main()
{
   int i;
    FILE *f=fopen("nr","r");

    citire(f,a);
    citire(f,b);

    for(i=0;i<=4001;i++)
        if(a[i] && b[i])
        printf("%d ", i-2000);

    return 0;
}
