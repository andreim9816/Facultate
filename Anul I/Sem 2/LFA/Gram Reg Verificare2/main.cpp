#include <iostream>
#include<fstream>
#include<cstring>
#include<cstdlib>

using namespace std;

ifstream fin("date.in");

class Gram
{   public:

    int nr_neterminale; // nr de stari
    char *neterminale;

    int nr_f; // nr stari finale
    char *f; // starile finale

    int nr_lit; // nr litere alfabet
    char *lit;  // alfabet

    char stare; // starea actuala

    struct tranzitie
    {
        char in,out,lit;
    };

    int nr_tranzitii;
    tranzitie *v;


    Gram();
    ~Gram();
    void set_init(char x);
    friend istream& operator >>(istream&,Gram&);

    void verif(char*,int &,int&);
};

Gram::Gram()
{
    nr_f=nr_lit=nr_neterminale=nr_tranzitii=0;

    neterminale=NULL;
    lit=NULL;
    f=NULL;
}

Gram::~Gram()
{
    nr_f=nr_lit=nr_neterminale=nr_tranzitii=0;

    delete[]neterminale;
    delete[]lit;
    delete[]f;
}

void Gram::set_init(char x)
{
    stare=x;
}

istream & operator >> (istream& in, Gram &x)
{
    int i;
    // vom avea cel putin o stare finala
    x.nr_f=1;
    x.f=new char[x.nr_f];
    x.f[0]='|';

    //nr de neterminale
    in>>x.nr_neterminale;
    x.neterminale=new char[x.nr_neterminale];   //aloc memorie

    for(i=0;i<x.nr_neterminale;i++)
        in>>x.neterminale[i];                   // citesc neterminalele

    //nr de litere
    in>>x.nr_lit;
    x.lit=new char[x.nr_lit];                  // aloc memorie

    for(i=0;i<x.nr_lit;i++)
        in>>x.lit[i];                           // citesc literele alfabetului

    // nr de tranzitii
    in>>x.nr_tranzitii;
    x.v=new Gram::tranzitie[x.nr_tranzitii];

    int p=x.nr_tranzitii-1;

    for(i=0;i<x.nr_tranzitii;i++)
        {
            in>>x.v[i].in>>x.v[i].lit>>x.v[i].out;

            // cazurile de tip A -> aS ( A a S) si A -> a ( A a | ) nu trebuie tratate in mod special
            // ca cel de tip A -> lambda

            if(x.v[i].lit== '|') // cazul A-> lambda   A | |
            {
                x.nr_f++;
                char *aux;
                aux=(char*)realloc(x.f,sizeof(char)*(x.nr_f));

                if(!aux)
                {
                    cout<<"IZ OVER";
                    break;
                }

                x.f=aux;
                x.f[x.nr_f-1]=x.v[i].in; // A va fi si stare finala

            }

        }

    return in;

}

void Gram::verif(char*cuv,int &ok,int &poz)
{

    if(strlen(cuv)>=poz)
    {

        int i;
        if(cuv[poz]=='\0') // am parcurs tot cuvantul
        {
            if(stare == '|')
            {
                ok=1;
                return;
            }

            for(i=0;i<nr_f;i++)
                if(stare ==f[i])
            {
                ok=1;
                return;
            }
        }
        else

        for(i=0;i< this->nr_tranzitii; i++)
            if(cuv[poz] == v[i].lit && stare == v[i].in)
                {
                    stare = v[i].out;
                    poz++;
                    verif(cuv,ok,poz);
                }
    }
}

int main()
{
    Gram a;
    char x;
    fin>>a;
    char cuv[20];
    cin>>cuv;
    int poz=0;

 // setam starea initiala
    a.set_init('0'); /// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    int da=0;
    int i;

    a.verif(cuv,da,poz);

    if(da==1)
        cout<<"DA";
    else cout<<"NU";
    return 0;
}