#include <iostream>

using namespace std;

class A
{
    int x;
public:
    void f(){cout<<" A ";}
};

void f(int x,int y=3)
{
    cout<<1;
}

void f(int x)
{
    cout<<2;
}
int main()
{
    f(3);

   return 0;
}