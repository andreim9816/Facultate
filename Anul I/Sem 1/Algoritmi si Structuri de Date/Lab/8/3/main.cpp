#include <iostream>
#include<fstream>
using namespace std;
ifstream fin("paranteze.txt");
struct nod
{
    nod*urm;
    int info;
};

void push(nod*&vf,int val)
{
    nod*q;
    q=new nod;

    q->info=val;
    q->urm=vf;
    vf=q;

}

int pop(nod*&vf)
{
    if(!vf)
        return -1;

    nod*q;
    q=new nod;

    q=vf;
    int x=vf->info;

    vf=vf->urm;

    delete q;
    return x;

}

int my_empty(nod*vf)
{
    return(!vf);
}

void rezolvare(nod*vf)
{
    char c;
    while(fin>>c)
    {
        if(c=='(')
        {
            push(vf,'(');
        }
        else
        {
            if(my_empty(vf)==1)
                {cout<<"INCORECT";
                 return ;
                }
            else pop(vf);
        }
    }
    if(my_empty(vf)==0)
        cout<<"INCORECT";
    else cout<<"CORECT";
}

int main()
{
   nod*stiva;
   stiva = new nod;
   stiva=NULL;
   rezolvare(stiva);
    return 0;
}
