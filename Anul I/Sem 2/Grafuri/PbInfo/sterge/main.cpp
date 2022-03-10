#include<iostream>
#include<cstdio>
using namespace std;
class A
{

public:
int a1, a2, a3;
A()
{
    a1=-1;
    a2=-2;
    a3=-3;
}
virtual void Set() = 0;
};
class B:public A
{
public:
int a1, a2, a3;
void Set(){a1=2;a2=3;a3=3;};
B()
{
    a1=2;a2=3;a3=3;
}
};

int main()
{
B b;
cout<<b.A::a1;

}

