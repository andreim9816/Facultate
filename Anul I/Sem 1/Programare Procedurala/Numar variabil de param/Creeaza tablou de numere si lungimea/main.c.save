#include <stdio.h>
#include <stdlib.h>
#include<stdarg.h>
/// SE OPRESTE LA NULL ??????
void create_tablou(int *nrElem,int **v,int x,...)
{
    int y,*aux;
    (*nrElem)=1;
    *v=NULL;

    if(x=='\0')
        {
            (*nrElem)=0;
            return;
        }

    *v=(int*)malloc(sizeof(int)*(*nrElem));
    if(!*v)
        {
            (*nrElem)=0;
            return;
        }
    (*v)[0]=x;

    va_list lista;
    va_start(lista,x);

    while((y=va_arg(lista,int))!='\0')
    {
        aux=realloc(*v,sizeof(int)*((*nrElem)+1));
        if(!aux)
        {
            free(*v);
            (*nrElem)=0;
            return;
        }
        *v=aux;

        (*nrElem)++;
        (*v)[*nrElem-1]=y;
    }

    free(aux);
    va_end(lista);

}
int main()
{
   int *v,n;
   create_tablou(&n,&v,8,2,3,0,5,6,7,'\0');
   int i;
   for(i=0;i<n;i++)
    printf("%d ",v[i]);
    return 0;
}
