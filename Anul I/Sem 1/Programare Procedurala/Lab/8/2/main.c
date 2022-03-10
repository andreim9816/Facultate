#include <stdio.h>
#include <stdlib.h>

int main()
{
    long long x;
    scanf("%lld",&x);
   unsigned char *p;
    int i;
     p=&x;
    for(i=0;i<sizeof(long long);i++)
    {

        printf("%u ",*p);
        p++;
    }
    return 0;
}
