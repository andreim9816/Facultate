#include <stdio.h>
#include <stdlib.h>

int main()
{
    int x=1;
    char *p;
    p=&x;
    if(*p==0)
        printf("BIG");
    else printf("little ");
    return 0;
}
