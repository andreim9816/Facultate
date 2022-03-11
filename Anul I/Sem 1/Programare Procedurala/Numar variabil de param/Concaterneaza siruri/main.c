#include <stdio.h>
#include <stdlib.h>
#include<stdarg.h>
#include<string.h>

char *concaternare(const char*primSir,...)
{
    char *p,*q;
    int lungimeTotal,i;

    if(!primSir)
        return NULL;

    va_list lista;
    va_start(lista,primSir);

    lungimeTotal=strlen(primSir);

    while( (p=va_arg(lista,char*))!=NULL)
        lungimeTotal=lungimeTotal+strlen(p);

    va_end(lista); ///!!!!!!!!!!
    q=(char*)malloc(sizeof(char)*(lungimeTotal+1));
    if(!q)
        return NULL;

    strcpy(q,primSir);

    va_start(lista,primSir);
    while((p=va_arg(lista,char*))!=NULL)
        strcat(q,p);

    va_end(lista); ///!!!!!!!!!!
    return q;
}
int main()
{
    char *q=concaternare("Am mancat ","multe mere ", "si pereeee ",(char*)NULL);
    printf("%s",q);
    return 0;
}