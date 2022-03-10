#include <stdio.h>
#include <stdlib.h>
#include<string.h>
int anagrame(char*s,char *t)
{
    if(strlen(s)!=strlen(t))
        return 0;
    if(!s[0] && !t[0])
        return 1;
    char *p=strchr(s,t[0]);
    if(!p)
        return 0;
    strcpy(t,t+1);
    strcpy(p,p+1);
    return anagrame(s,t);
}
int main()
{
    char s[20],t[20];
    scanf("%s %s",s,t);
    printf("%d",anagrame(s,t));
    return 0;
}
