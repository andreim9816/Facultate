#include <stdio.h>
#include <stdlib.h>
#include<string.h>
void inlocuire(char *w, char *s, char *t)
{
    char *p, *aux;
    aux = (char*)malloc(strlen(w) + 1);
    p = strstr(w, s);
    while(p != NULL)
    {
        strcpy(aux, p + strlen(s));
        strcpy(p, t);printf("%s\n ",w);
        strcat(w, aux);
        p = strstr(p + strlen(t), s);
    }
    free(aux);
}
int main()
{
    char w[30];
    scanf("%s",w);
    char*s="ere";
    char*t="as";
    inlocuire(w,s,t);
    printf("%s ",w);
    return 0;
}
