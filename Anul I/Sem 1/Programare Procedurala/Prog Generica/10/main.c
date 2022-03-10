#include <stdio.h>
#include <stdlib.h>
int aparitii_lit(char *s,char c)
{
    if(s[0]==NULL)
        return 0;
    else if(s[0]==c)
        return 1+aparitii_lit(s+1,c);
    else return aparitii_lit(s+1,c);
}
int main()
{
   char *s="abecede";
   char c='e';
   printf("%d ",aparitii_lit(s,c));
    return 0;
}
