#include <stdio.h>
#include <stdlib.h>
int pali(int x,int ogl)
{
    if(x==ogl || x/10==ogl)
        return 1;
    else if(x<ogl)
        return 0;
    else return pali(x/10,ogl*10+x%10);
}
int main()
{
   int x=21;
  // printf("%d ",pali(x,0));

   int v[]={1,2,3};
   int *p,*q;
   p=&v[0];
   q=&v[2];
   printf("%p ",p);
   printf("%p ",q);
   printf("%d ",q-p);
    return 0;
}