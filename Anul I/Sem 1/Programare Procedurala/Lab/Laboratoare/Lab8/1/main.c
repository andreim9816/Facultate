#include <stdio.h>
#include <stdlib.h>

int main()
{
     int x=1;
    unsigned char *p;

    p=&x;
    if((*p) == 0)
        printf("BIG ENDIAN");
    else printf("LIL' ENDIAN");
    return 0;
}
