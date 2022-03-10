#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<stdarg.h>

char *concaternare(char*sir,...)
{
    int lung;
    char *p,*q,*aux;
    q=NULL;

    if(!sir)
        return NULL;
    lung=strlen(sir);

    q=(char*)malloc(sizeof(char)*(lung+1));
    if(!q)
        return NULL;
    strcpy(q,sir);

    va_list lista;
    va_start(lista,sir);

    while( ( p=va_arg(lista,char*) )!=NULL )
    {
        lung+=strlen(p);
        aux=(char*)realloc(q,sizeof(char)*lung);

        if(!aux)
            return NULL;
        q=aux;
        strcat(q,p);
    }
    va_end(lista);
    return q;
}

int main()
{
    char*q=concaternare("Ana ","are ","mere"," siiii " , "ceva pere",(char*)NULL);
    printf("%s",q);
    return 0;
}
