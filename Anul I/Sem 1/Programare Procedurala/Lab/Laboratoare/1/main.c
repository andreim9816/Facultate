#include <stdio.h>
#include <stdlib.h>
#include"cod.h"

int main()
{
    FILE *in=fopen("txt","r");

        int a,b;
        char op;


        scanf("%d",&a);
        scanf("%d",&b);
        getchar();
        scanf("%c",&op);

        afis2(a,op,b);


        return 0;
}
