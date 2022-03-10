#include<iostream>
using namespace std;


class cls
{public:
    int vi;

    cls(int v=37) : vi(v){}
    int& f() const;
};
int& cls :: f() const
{
    return vi;
}

int main()
{
  const  cls d(15);
    d.f()=9;
    cout<<d.f();
return 0; }
