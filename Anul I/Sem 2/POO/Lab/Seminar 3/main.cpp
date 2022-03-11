#include <iostream>

using namespace std;

class lista
{
protected:
    int *v;
    int dim,nr;
public:
    lista();
    lista(int dim_max);
   lista(const lista &ob);
    lista&operator=(const lista &ob);
    bool inserare(int poz,int val);
};

lista :: lista()
{
    v=NULL;
    nr=0;
    dim=1;
    v=new int[1];
}

lista :: lista (int dim_max)
{
    nr=0;
    dim=dim_max;
    v=new int[dim];
}

lista :: lista(const lista & ob) /// constructor de copiere
{
    dim=ob.dim;
    nr=ob.nr;

    v=new int[dim];

    for(int i=0;i<nr;i++)
        v[i]=ob.v[i];
}

bool lista:: inserare(int poz,int val)
{
    if(poz>nr || poz<0 || nr==dim)
        return false;
    for(int i=nr;i>poz;i--)
        v[i]=v[i-1];
    nr++;
    v[poz]=val;
    return true;
}

lista &lista:: operator = (const lista &ob) // operator de atribuire
{
    if(this == &ob)
        return *this;

    delete []v;

    dim=ob.dim;
    nr=ob.nr;
    v=new int[dim];

    for(int i=0;i<nr;i++)
        v[i]=ob.v[i];
    return *this;
}

class stiva : protected lista
{
public:
    stiva(){};
    stiva(int dim_max): lista(dim_max) {};
    bool push (int val)
    {
        return inserare(nr,val);
    }

};

class coada : protected lista
{
public:
    coada() {}
    coada (int d) : lista(d){}
    bool inserare(int val)
    {
        return lista::inserare(nr,val);
    }
};

class

int main()
{
    cout << "Hello world!" << endl;
    return 0;
}