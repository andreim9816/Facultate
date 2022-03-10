#include <stdio.h>
#include <stdlib.h>
#include"cod.h"

int main()
{

FILE *in=fopen("txt","r");
        int a,b;
        char op;


        fscanf(in,"%d",&a);
        fscanf(in,"%d",&b);

        fgetc(in);

        fscanf(in,"%c",&op);

        afis2(a,op,b);


        return 0;
}
