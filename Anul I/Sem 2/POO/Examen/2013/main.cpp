#include <iostream>
#include<typeinfo>
using namespace std;

/*
class B
{
    int i;
public:
    B() {i=1;}
    int get_i(){return i;}
    virtual void f(){}
};


class D : public B
{
    int j;
    public: D(){j=2;}
    int get_j() {return j;}
    void f(){}
};
int main()
{
   B*p=new D;
   cout<<p->get_i();
    cout<<endl<<endl;


   cout<<" pentru pointerul p "<<typeid(p).name()<<endl;
   cout<<" pentru dereferentierea pointerului "<<typeid(*p).name()<<endl;
   cout<<typeid((D*)p).name()<<"\n";

    cout<<endl<<endl;

   if(typeid(p) == typeid(D*))
    cout<<((D*)p)->get_j();

    return 0;
}

*/

/*
class B
{ int i;
public: B() { i=1; }
int get_i() { return i; }
};

class D:  B //! aici trebuie mostenire publica pentru a putea face upcast
{ int j;
public: D() { j=2; }
int get_j() {return j; }
 };

int main()
{ B *p=new D;
    cout<<p->get_i();
    if (typeid((B*)p).name()=="D*")
        cout<<((D*)p)->get_j();
return 0; }

*/

/*
int f(int y)
{ try {if (y>0) throw y;} catch(int i){throw;} return y-2;}
int f(int y, int z)
{ try {if (y<z) throw z-y;} catch(int i){throw;} return y+2;}
float f(float &y)
{ cout<<" y este referinta"; return (float) y/2 ;}
int main()
{ int x;
try
{ cout<<"Da-mi un numar par: ";
cin>>x;
if (x%2) x=f(x, 0);
else x=f(x);
cout<<"Numarul "<<x<<" e bun!"<<endl;
}
catch (int i)
{ cout<<"Numarul "<<i<<" nu e bun!"<<endl;
}
return 0;
}
*/

//! 1

/*
class A
{
    int i;
protected:
    static int x;
public:
    A(int j=7) {i=j;x=j;}
    int get_x(){return x;}
    int set_x(int j)
    {
        int y=x;
        x=j;
        return y;
    }
    A operator=(A a1)
    {
        set_x(a1.get_x());
        return a1;
    }

};
int A :: x=15;
int main()
{
    A a(212),b;
    cout<<(b=a).get_x();

}

*/

//! VII
/*
int f(int y)
{if (y<0)    throw y;
return y/2;
}
int main()
{
    int x;
    try
    {
        cout<<"DA UN NR PAR ";
        cin>>x;
        if(x%3)
            x=f(x);
        else throw x;
        cout<<"nmarul " << x << " e bun ";

    }
    catch(int i)
    {
        cout<<"Numarul nu e bun";
    }
}
*/

//! III
/*
template <class X, class Y>
X f(X x,Y y)
{
    return x+y;
}

int *f(int *x,int y)
{
    return x-y;
}

int main()
{
    int *a=new int(200),*b=a;
    cout<<*f(a,*b);
}
*/

//! X
/*
class cls
{
    int x;
public:
    cls(int i=0)
    {
        cout<<" c1 ";
        x=i;
    }

    ~cls()
    {
        cout<<" d1 " ;
    }
};

class cls1
{
    int x;
    cls xx;
public:
    cls1(int i=0)
    {
        cout<<" c2 ";
        x=i;
    }
    ~cls1()
    {
        cout<<" d2 ";
   }
}c;

class cls2
{
    int x;
    cls1 xx;
    cls xxx;
public:
    cls2(int i=0)
    {
        cout<<" c3 ";x=i;
    }
    ~cls2()
    {
        cout<<" d3 ";
    }
};

int main()
{
    cls2 s;
    return 0;
}
*/

/*
//! XII
class B
{
    int i;
public:
    B() { i=1;}
    int get_i(){return i;}
};

class D : public B
{
    int j;
public:
    D(){j=2;}
    int get_j() {return j;}
};

int main()
{
    B*p=new D;
    cout<<p->get_i();
    if(typeid((B*)p).name()=="D*")
    cout<<((D*)p)->get_j();
}
*/

/*
//! XIII
class cls
{
   public:  int x;
public:
    cls(int i=3){x=i;}

};
    int f( const cls& x)
    {
        return x.x;
    }
int main()
{
    const cls a(-3);
    int b=f(a);
    cout<<b;
    return 0;
}

*/
/*
//! XV
class B
{
protected:
    int x;
public:
    B(int i=0) { x=i;}
    virtual B minus () {return 1-x;}
};

class D : public B
{
public:
    D(int i=0) : B(i) { }
    void afisare(){cout<<x;}
};

int main()
{
    D *p1=new D(18);
    *p1=p1->minus();
    p1->afisare();
}

*/

/*
//! XVI
class A
{
    int *x;
public:
    A() : x(new int (1000)){}
    int get_x(){x++;
    return *x;}
};

int main()
{
    A*a=new A,b;
    cout<<a->get_x()<<" "<<b.get_x();
}

*/
///!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#include<iostream>
using namespace std;

class cls1 {
    int x;
    static const int y;
public:
    cls1(int y=0)
    {
        y=3;
        cout<<" init cls1 ";
    }
    cls1 ( cls1 &x)
    {
        cout<<" cc cls1 ";
    }
    int g()
    {

        return 3;
    }
};

int const cls1 :: y=3;

class cls2 {
    int x;
public:
    cls2(int i=0)
    {
        cout<<" init cls2 ";
    }

    cls2( cls2&x)
    {
        cout<<" cc cls2 ";
    }
     const cls1  f()
    {
        cls1 ob;
        return ob;
    }
};
int main()
{
    cls2 ob;
    cout << ob.f().g();
    return 0;
}
