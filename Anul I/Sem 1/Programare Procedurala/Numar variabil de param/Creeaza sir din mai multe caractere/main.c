#include <stdio.h>
#include <stdlib.h>
#include<stdarg.h>

char *create_sir(char c,...)
{
    char x,*sir=NULL,*aux;
    int lung=1;
    if(c=='\0')
        return NULL;
    sir=(char*)malloc(sizeof(char)*lung);
    sir[0]=c;

    va_list lista;
    va_start(lista,c);

    while((x=va_arg(lista,int))!='\0')
          {
              aux=realloc(sir,sizeof(char)*(++lung+1));
              if(!aux)
              {
                  free(sir);
                  return NULL;
              }
              sir=aux;
              sir[lung-1]=x;
          }
    sir[lung]='\0';
    va_end(lista);
    return sir;

}

int main()
{
    char *sir=create_sir('g','a','u','n','a','\0');
    printf("%s",sir);
    return 0;
}
