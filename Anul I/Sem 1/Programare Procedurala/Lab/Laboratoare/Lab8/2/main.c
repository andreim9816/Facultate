#include <stdio.h>
#include <stdlib.h>

int main()
{
   int x,i;
   unsigned  char *p;

   scanf("%d",&x);
   p=&x;

   for(i=0;i<4;i++)
   {
       printf("%d ",*p); ///!*p afiseaza valoarea pointerului de la octetul respeticv. Este afisat un singur octet pt ca pointerul este de tip char
       p++;
   }
    return 0;
}
