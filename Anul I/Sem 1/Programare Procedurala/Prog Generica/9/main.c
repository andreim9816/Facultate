#include <stdio.h>
#include <stdlib.h>
int maxim(int *v,int n)
{
    if(n==1)
        return v[0];
    else
    {
        int x=maxim(v,n-1);
        if(x<v[n-1])
        return v[n-1];
        else return x;
    }
}
int main()
{
    int v[]={2,5,1,0,9,3,4};
    printf("%d ",maxim(v,7));
    return 0;
}
