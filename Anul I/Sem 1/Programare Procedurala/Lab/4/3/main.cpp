#include <stdio.h>
#include <stdlib.h>
///merge cred

typedef struct
{
    long long cnp;
    char nume[30];
    short varsta,norma; /// norma 1- full 2-part-time
}ANGAJATI;

void citire(ANGAJATI v[],int n)
{
    int i;
    for(i=0;i<n;++i)
    {
        scanf("%lld",&v[i].cnp);
        scanf("%s",v[i].nume);
        scanf("%hd %hd",&v[i].varsta,&v[i].norma);

    }
}

void afis(ANGAJATI v[],int n)
{
    int i;
    for(i=0;i<n;i++)
        if((v[i].varsta>>5)<=0)
        printf("%s \n",v[i].nume);
}

int main()
{
    ANGAJATI v[101];
    short n;
    scanf("%hi",&n);
    citire(v,n);

  ///  printf("%d",sizeof(ANGAJATI));

    afis(v,n);

    return 0;
}
