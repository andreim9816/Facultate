#include <stdio.h>
#include <stdlib.h>

struct complex
{
    int real,imaginar;
};


void citire(int *n,struct complex **v)
{
    int i;

    scanf("%d",n);

    *v=(struct complex *)malloc((*n)*sizeof(struct complex));

    for(i=0;i<*n;++i)
    scanf("%d %d",&(*v)[i].real,&(*v)[i].imaginar);

}

void afis(int n,struct complex *v)
{
    int i;
    for(i=0;i<n;++i)
    {

        printf("%d ",v[i].real);
        printf("%d \n",v[i].imaginar);
    }
}
int main()
{
    struct complex *v;
    int n;
    citire(&n,&v);
    afis(n,v);
    return 0;
}
