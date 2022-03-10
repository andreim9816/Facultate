#include <iostream>
#include<typeinfo>
using namespace std;
/*
class A
{
    static int * const x;
public:
    A() {}
    int get_x()
    {
        return (*x)++;
    }
};

int * const A :: x(new int (1000));

int main()
{
    A *a=new A,b;
    cout<<b.get_x();
    cout<<a->get_x();
    return 0;
}

*/

/*
class A
{
    int x;
public:
    A(int i) : x(i){}
    int get_x(){return x;}
    A operator+(int &);
};

ostream& operator<<(ostream&o, A a)
{
    o<<a.get_x();
    return o;
}

A A:: operator +(int &i)
{
    A t(i);
    return t;
}

int main()
{
    A a(5);
    int b=55;
    int c=7;
    cout<<a+b<<" "<<a+c;
    return 0;
}
*/

/*
class cls1 {
  int x;
public:
  cls1 () {
    x = 13;
  }
  int g() {
    static int i; i++;
    return (i+x);
  }
};

class cls2 {
  int x;
public:
  cls2() {
    x = 27;
  }
  cls1& f() {
     cls1 ob; return ob;
  }
};

int main() {
  cls2 ob;
  cout << ob.f().g();
  return 0;
}

*/

/*

class Cls {
int x;
public:
Cls(int i = 0) {
cout << 1;
x = i;
}
Cls(const Cls &ob) {
cout << 2;
x = ob.x;
}
int getX() const {
return x;
}
};
const Cls &f(const Cls &c) {
return c;
}
int main() {
Cls r;
Cls s = f(f(f(r)));
cout << s.getX();
return 0;
}

*/

template <class T, class Y>
void f(T*x, T y)
{
    cout<<"DA";
}

template<class A, class T=int>
void f(A*x, T y )
{
    cout<<"UN";
}

void f(int a,int b)
{
    cout <<a +b;
}

class A
{
public:
    virtual void f(){}
};

class B : public A
{    int x;
public:
    void f(){}
};
int main ()
{
   cout<<sizeof(A);
  return 0;
}
