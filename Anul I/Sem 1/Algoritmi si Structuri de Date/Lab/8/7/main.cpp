#include <iostream>
#include<fstream>
using namespace std;

ifstream fin("nr");

int main()
{
    int k=0,x,y,i,v[1001],n;

    fin>>n;
    for(i=1;i<=n;i++)
        fin>>v[i];

    x=v[1];
    k=1;

    for(i=2;i<=n;i++)
    {
        y=v[i];
        if(x==y)
            k++;
        else k--;

        if(k==0)
        {
            x=y;
            k=1;
        }
    }

    k=0;
    for(i=1;i<=n;i++)
        if(x==v[i])
        k++;

    if(k>n/2)
        cout<<"Elementul majoritar este "<<x;
    else cout<<"Nu exista element majoritar";

    return 0;
}
