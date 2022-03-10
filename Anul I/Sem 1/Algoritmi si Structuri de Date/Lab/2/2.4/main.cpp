#include <iostream>
#include<fstream>
using namespace std;
ifstream fin("nr");

int main()
{   int n,x=0,y,i;
    fin>>n;
    for(i=1;i<=n;i++)
    {
        fin>>y;
        x=x^y;
    }
    cout<<x;

    return 0;
}
