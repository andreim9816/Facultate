#include <iostream>
#include<vector>
using namespace std;

int cifre_dif(int x)
{
    int v[10];
    for(int i=0;i<=9;i++)
        v[i]=0;

    while(x)
    {
        v[x%10]++;

        if(v[x%10]>1)
            return 0;

        x/=10;
    }

    return 1;
}

int main()
{
   int i,k=0;
   for(i=1000;i<=99999;i++)
    if(i%495==0)
    if(cifre_dif(i))
   {
       k++;
       cout<<i<<" ";
   }
   cout<<"\nSunt "<<k<<" numere";

    return 0;
}
