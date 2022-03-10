#include <iostream>
#include<cstdlib>
using namespace std;

/*
    Program care realizeaza operatii pe "numere mari" i.e. pot avea oricat de multe cifre.
    Programul retine numerele sunt forma unei liste, in care cifrele sunt memorate invers
    ex: 2589 este memorat 9->8->5->2->NULL
*/

class Numar_intreg
{
private:

struct nod
{
    int cifra;
    nod*urm;
};
    nod*prim,*ultim;
    int lungime;
    int semn;

public:

    Numar_intreg();
    ~Numar_intreg();
    Numar_intreg(const Numar_intreg &);
    const Numar_intreg& operator = (const Numar_intreg&);

    void ad_fin(nod*&,nod*&,int);
    void ad_in(nod*&,nod*&,int);
    void afis_recursiv (nod*) const;
    void parcurge_invers_scadere(nod*,int&);
    int parcurge_max(nod*,nod*);

    Numar_intreg max_abs(Numar_intreg);
    Numar_intreg min_abs(Numar_intreg);
    Numar_intreg adunare(Numar_intreg);
    Numar_intreg scadere(Numar_intreg);
    Numar_intreg elimin_zero();

    friend istream& operator >> (istream&,Numar_intreg&);
    friend ostream& operator << (ostream&,const Numar_intreg&);
    //       ostream& operator<<(ostream& out,const Numar_intreg &x)
    friend bool operator ==(Numar_intreg,Numar_intreg);
    friend Numar_intreg operator + (Numar_intreg,Numar_intreg);
    friend Numar_intreg operator - (Numar_intreg,Numar_intreg);
    friend Numar_intreg operator * (Numar_intreg,Numar_intreg);
    friend class Vector;
};

void Numar_intreg :: ad_fin(nod*&prim,nod*&ultim,int x)
{
    // functie care insereaza un nod la finalul unei liste simplu inlantuite, memorata prin
    // nodurile "prim" si "ultim"

    if(!prim)
    {
     nod*q;
     q=new nod;
     q->cifra=x;
     q->urm=NULL;
     prim=ultim=q;
    }
    else
    {
        nod *q;
        q=new nod;
        q->cifra=x;
        q->urm=NULL;
        ultim->urm=q;
        ultim=q;
    }
}

void Numar_intreg :: ad_in(nod*&prim,nod*&ultim,int x)
{
    // functie care insereaza un nod la inceputul unei liste simplu inlantuite, memorata prin
    // nodurile "prim" si "ultim"

    if(!prim)
    {
        nod*q;
        q= new nod;
        q->cifra=x;
        q->urm=NULL;
        prim=ultim=q;
    }
    else
    {

        nod*q;
        q=new nod;
        q->cifra=x;
        q->urm=prim;
        prim=q;
    }
}

Numar_intreg::Numar_intreg()
{
    // constructor simplu
    prim=ultim=NULL;
    lungime=0;
    semn=0;
}

Numar_intreg::~Numar_intreg()
{
    //destructor
    nod*q,*r;

    for(q=prim;q;)
    {
        r=q;
        q=q->urm;
        delete r;
    }
}

const Numar_intreg& Numar_intreg:: operator = (const Numar_intreg& x)
{
    //supraincarcarea operatorului = de atribuire

    nod*q;

    if(this != &x)
    {
        delete []prim;
        prim=ultim=NULL;

        lungime=x.lungime;
        semn=x.semn;

        for(q=x.prim;q;q=q->urm)
            ad_fin(prim,ultim,q->cifra);
    }
    return (*this);
}

Numar_intreg::Numar_intreg (const Numar_intreg& x)
{
    // constructor de copiere

    prim=ultim=NULL;

    lungime=x.lungime;
    semn=x.semn;
    nod*q;
    for(q=x.prim;q!=NULL;q=q->urm)
        ad_fin(prim,ultim,q->cifra);

}

istream& operator>>(istream& in,Numar_intreg &x)
{
    //    functie care supraincarca >>, citind un obiect de tip Numar_intreg

        char nr[1000];
        x.lungime=0;
        cin>>nr;
        int i;

        if(nr[0]=='-')
            x.semn=-1;
        else
        {
           x.semn=1;
           x.lungime++;
           x.ad_in(x.prim,x.ultim,nr[0]-'0');
        }

        for(i=1;nr[i];i++)
        {
            x.ad_in(x.prim,x.ultim,nr[i]-'0');
            x.lungime++;
        }

        return in;
}

void Numar_intreg::afis_recursiv(nod*q) const
{
     //functie care afiseaza recursiv o lista

    if(q)
    {
        afis_recursiv(q->urm);
        cout<<q->cifra;
    }
}

ostream& operator<<(ostream& out,const Numar_intreg &x)
{
    // functie care afiseaza un Numar_intreg

       if(x.semn==-1)
         out<<'-';
       x.afis_recursiv(x.prim);

        return out;
}

bool operator==(Numar_intreg x,Numar_intreg y)
{
    // functie care supraincarca operatorul == ce verifica daca cele 2 obiecte
    // memoreaza acelasi numar, in valoare absoluta

    if(x.lungime!=y.lungime)
        return false;

    if(x.semn!=y.semn)
        return false;

    Numar_intreg::nod*q,*p;

    for(p=x.prim,q=y.prim; p && q; p=p->urm, q=q->urm)
        if(p->cifra != q->cifra)
            return false;

    return true;
}

Numar_intreg Numar_intreg::elimin_zero()
{

    nod*p,*q,*r;
    int ok;

    for(p=(*this).prim;p!=NULL;p=p->urm)
    {
        ok=1;
        for(q=p->urm;q!=NULL;q=q->urm)
            if(q->cifra!=0)  // am gasit cifra diferita de 0
            {
                ok=0;
                break;
            }

        if(ok) // daca cifrele de dupa p sunt toate 0, trebuie eliminate
        {
            for(q=p->urm;q!=NULL;)
            {
                (*this).lungime--;
                r=q;
                q=q->urm;
                delete r;
            }
            (*this).ultim=p;
            (*this).ultim->urm=NULL;
        }
    }
    return (*this);
}


Numar_intreg operator*(Numar_intreg x,Numar_intreg y)
{
    // functie care incarca operatorul * si inmulteste cele 2 liste alea obiectelor

    Numar_intreg z;
    z.semn = x.semn * y.semn;

    int pl=0,rl=1,i,t,l;
    l=x.lungime+y.lungime-1;

    Numar_intreg::nod *p,*q,*r;

    for(i=1;i<=l;i++)       // initializare cu 0
        {
            z.ad_in(z.prim,z.ultim,0);
            z.lungime++;
        }

    for(p=x.prim;p;p=p->urm)
        {
            pl++;   // pozitionarea lui r
            rl=1;
            for( r=z.prim; pl!=rl; r=r->urm)
                rl++;

            for(q=y.prim;q;q=q->urm)
                {
                    r->cifra+=p->cifra * q->cifra;
                    r=r->urm;
                }
        }

    t=0;

    for(p=z.prim;p;p=p->urm)
    {
        p->cifra=p->cifra+t;
        t=p->cifra/10;
        p->cifra=p->cifra%10;
    }
    if(t)
    {
         z.lungime++;
         z.ad_fin(z.prim,z.ultim,t);
    }


    if(z.lungime == 1 && z.prim->cifra == 0 ) // daca a ramas o singura cifra si este 0, setam semnul +
        z.semn=1;

    return z;
}

int Numar_intreg::parcurge_max(nod*x,nod*y)
{
    //functie care gaseste cel mai mare numar: returneaza -1 daca e param stang sau 1 daca e param drept

    int ok=0;

    for(;x;x=x->urm,y=y->urm)
    {
        if(x->cifra > y->cifra)
            ok=-1;
        else if(x->cifra<y->cifra)
            ok=1;
    }
    return ok;
}

Numar_intreg Numar_intreg::max_abs(Numar_intreg x)
{
    // functie care returneaza cel mai mare numar dintre 2 numere intregi

    if(x.lungime>this->lungime)
        return x;

    if(x.lungime<this->lungime)
        return *this;

    int rez=parcurge_max(this->prim,x.prim);

    if(rez==1)
        return x;
    return *this;
}

Numar_intreg Numar_intreg::min_abs(Numar_intreg x)
{
    //functie care returneaza cel mai mic numar dintre 2 numere intregi

    if(x.lungime<this->lungime)
        return x;

    if(x.lungime>this->lungime)
        return *this;

    int rez=parcurge_max(this->prim,x.prim);

    if(rez==1)
        return *this;
    return x;
}

Numar_intreg Numar_intreg::adunare(Numar_intreg y)
{
    // functie care aduna 2 numere intregi, (*this) fiind mai mare(in val absoluta)

   Numar_intreg z;
   nod*p,*q;
   int t=0;

   p=this->prim;
   q=y.prim;

   for(;p!=NULL && q!=NULL; p=p->urm, q=q->urm)
   {
       int x=p->cifra+ q->cifra+ t;
       t=x/10;
       ad_fin(z.prim, z.ultim, x%10);
       z.lungime++;
   }

   //continua parcurgerea primului numar, DACA au mai ramas cifre neaccesate

   for(;p!=NULL;p=p->urm)
   {
       int x=p->cifra+ t;
       t=x/10;
       ad_fin(z.prim, z.ultim, x%10);
       z.lungime++;
   }

    if(t)
    {
        z.ad_fin(z.prim, z.ultim, t);
        z.lungime++;
    }
    return z;
}


Numar_intreg Numar_intreg::scadere(Numar_intreg y)
{
     // functie care scade 2 numere intregi, (*this) fiind mai mare (in val absoluta)

    Numar_intreg z;
    int t=0,x;
    nod*p,*q;

    p=this->prim;
    q=y.prim;

    for(;q!=NULL;p=p->urm,q=q->urm)
    {
       x= p->cifra - q->cifra - t;
       if(x<0)
       {
           t=1;
           x=x+10;
       }
       else t=0;

       z.ad_fin(z.prim, z.ultim, x);
       z.lungime++;
    }

    // se continua parcurgerea primului numar, daca exista cifre neaccesate

    for(;p!=NULL;p=p->urm)
    {
        x=p->cifra - t;
        if(x<0)
        {
            t=1;
            x=x+10;
        }
        else t=0;

        z.ad_fin(z.prim, z.ultim, x);
        z.lungime++;
    }

    return z;
}

Numar_intreg operator+(Numar_intreg x,Numar_intreg y)
{
    /*
       functie de supraincarcare a operatorului +, ce aduna 2 numere intregi
       Se copiaza in a valoarea mai mare, in b valoarea mai mica, si se iau
       4 cazuri diferite, IN CARE PRIMUL PARAMETRU ESTE MAI MARE CA AL DOILEA
    */

    Numar_intreg a,b,z;

    a=x.max_abs(y);

    if(a==x)
        b=y;
    else
        b=x;


    if(a.semn==1 && b.semn==1)          // primul numar este pozitiv, al doilea pozitiv
    {
        z=a.adunare(b);
        z.semn=1;
    }

   else if(a.semn==1 && b.semn==-1)     // primul numar este pozitiv, al doilea negativ
    {
         z=a.scadere(b);
         z.semn=1;                               // rezultatul ia semnul numarului mai mare in modul, adica a
    }

    else if(a.semn==-1 && b.semn==1)    // primul numar este negativ, al doilea pozitiv
    {
        z=a.scadere(b);
        z.semn=-1;                                // rezultatul ia semnul numarului mai mare in modul, adica b
    }

    else                                // primul numar negativ, al doilea negativ
    {
        z=a.adunare(b);
        z.semn=-1;
    }

     z.elimin_zero();

     if(z.lungime==1 && z.prim->cifra==0) // rezultatul este 0
        z.semn=1;

    return z;
}

Numar_intreg operator-(Numar_intreg x,Numar_intreg y)
{
    /*
       functie de supraincarcare a operatorului -, ce scade 2 numere intregi
       Se copiaza in a valoarea mai mare, in b valoarea mai mica, si se iau
       4 cazuri diferite, IN CARE PRIMUL PARAMETRU ESTE MAI MARE CA AL DOILEA
    */

    Numar_intreg a,b,z;
    a=x.max_abs(y);
    int schimb=1;

    if(a==x)
    {
        b=y;
    }
    else
    {
        b=x;
        schimb=-1;
    }

    if(a.semn==1 && b.semn==1)           // primul numar este pozitiv, al doilea pozitiv
    {

        z=a.scadere(b);
        z.semn=schimb;
    }
    else if(a.semn==1 && b.semn==-1)    // primul numar este pozitiv, al doilea negativ
    {
        z=a.adunare(b);

        if(schimb==-1)
            z.semn=-1;
        else z.semn=1;
    }
    else if(a.semn==-1 && b.semn==1)    // primul numar este negativ, al doilea pozitiv
    {
        z=a.adunare(b);

        if(schimb==-1)
            z.semn=1;
        else z.semn=-1;
    }
    else                                // primul numar este negtiv, al doilea negativ
    {
        z=a.scadere(b);
        z.semn=0-schimb;
    }

     z.elimin_zero();
     if(z.lungime==1 && z.prim->cifra==0) // rezultatul este 0
            z.semn=1;

    return z;
}

class Vector
{
    // clasa Vector, avand campurile :
    // nr_elem - numarul elementelor
    // *v - pointer de tip Numar_intreg in care vor fi retinute elemente de tip Numar_intreg

    private:
    int nr_elem;
    Numar_intreg *v;

    public:

    Vector();
    ~Vector();
    Vector(int);
    Vector(const Vector&);
    const Vector& operator=(const Vector&);

    friend istream& operator >> (istream&,Vector&);
    friend ostream& operator << (ostream&,Vector&);
    friend Numar_intreg operator*(Vector,Vector);

    Numar_intreg max_abs_vector();

};

Vector::Vector()
{
    v=NULL;
    nr_elem=0;
}

Vector::~Vector()
{
    nr_elem=0;///
    delete []v;
}
Vector :: Vector(int x)
{
    nr_elem=x;
    v=new Numar_intreg[x];
}

const Vector& Vector:: operator=(const Vector& x)
{
    delete []v;
    v=new Numar_intreg[x.nr_elem];
    nr_elem=x.nr_elem;

    for(int i=0;i<x.nr_elem;i++)
        v[i]=x.v[i];

    return (*this);
}

Vector :: Vector(const Vector &x)
{
    v=new Numar_intreg[x.nr_elem];
    nr_elem=x.nr_elem;

    for(int i=0;i<x.nr_elem;i++)
        v[i]=x.v[i];
}

istream& operator >>(istream& in,Vector &x)
{
    int i;

    in>>x.nr_elem;
    x.v=new Numar_intreg[x.nr_elem];

    for(i=0;i<x.nr_elem;i++)
        in>>x.v[i];
    return in;
}

ostream& operator << (ostream& out,Vector &x)
{
    int i;
    for(i=0;i<x.nr_elem;i++)
        out<<x.v[i]<<" ";
    return out;
}

Numar_intreg operator * (Vector x, Vector y)
{
    int i,m;
    m=x.nr_elem;
    Numar_intreg prod,rez;

    if(x.nr_elem!=0)
    {

        prod=x.v[0]*y.v[0];

        for(i=1;i<m;i++)
        {
            rez=x.v[i]*y.v[i];
            prod=prod+rez;
        }

    }
    else cout<<"Vectorii nu au elemente\n";

    return prod;

}

Numar_intreg Vector::max_abs_vector()
{
    Numar_intreg maxi;

    if(nr_elem!=0)
    {
        maxi=v[0];
        for(int i=1;i<nr_elem;i++)
            maxi=maxi.max_abs(v[i]);

        return maxi;
    }
    else
    {
        cout<<"Vectorul nu are elemente";
        return maxi;
    }
}

int main()
{

int optiune;

    cout<<"\nIntroduceti o optiune :\n";
    cout<<"1. Adunarea a 2 numere intregi\n";
    cout<<"2. Scaderea a 2 numere intregi\n";
    cout<<"3. Inmultirea a 2 numere intregi\n";
    cout<<"4. Afisarea celui mai mare numar intreg( in valoarea absoluta )\n";
    cout<<"5. Produs scalar a 2 vectori de numere intregi\n";
    cout<<"6. Afisarea celui mai mare numar (in valoare absoluta ) dintr-un vector de numere intregi\n";
    cout<<"7. Iesire \n\n";

    cin>>optiune;

    while(optiune!=7)
    {
          Numar_intreg x,y,sum,dif,prod,maxi;
          Vector v,w,produs;

        switch(optiune)
        {

            case 1:

                 cout<<"\nIntroduceti 2 numere: ";
                 cin>>x>>y;
                 sum=x+y;
                 cout<<"\nSuma este "<<sum;
                 break;

            case 2 :

                cout<<"\nIntroduceti 2 numere: ";
                cin>>x>>y;
                dif=x-y;
                cout<<"\nDiferenta este "<<dif;
                break;

            case 3 :

                cout<<"\nIntroduceti 2 numere: ";
                cin>>x>>y;
                prod=x*y;
                cout<<"\nProdusul este "<<prod;
                break;

            case 4 :

                cout<<"\nIntroduceti 2 numere: ";
                cin>>x>>y;
                maxi=x.max_abs(y);
                cout<<"\nCel mai mare numar este "<<maxi;
                break;

            case 5 :

                cout<<"\nIntroduceti 2 vectori de numere intregi: ";
                cout<<"\nIntroduceti numarul de elemente al vectorului si elementele: ";
                cin>>v;
                cout<<"\nIntroduceti numarul de elemente al vectorului si elementele: ";
                cin>>w;
                prod=v*w;
                cout<<"Produsul scalar este "<<prod;
                break;

            case 6 :
                cout<<"\nIntroduceti numarul de elemente al vectorului si elementele: ";
                cin>>v;
                maxi=v.max_abs_vector();
                cout<<"\nCea mai mare valoare este "<<maxi;
                break;

            case 7 : break;
        }


        if(optiune!=7)
        {
            cout<<"\n\n*************************************************\n\n";
            cout<<"Introduceti o optiune :\n";
            cout<<"1. Adunarea a 2 numere intregi\n";
            cout<<"2. Scaderea a 2 numere intregi\n";
            cout<<"3. Inmultirea a 2 numere intregi\n";
            cout<<"4. Afisarea celui mai mare numar intreg( in valoarea absoluta )\n";
            cout<<"5. Produs scalar a 2 vectori de numere intregi\n";
            cout<<"6. Afisarea celui mai mare numar ( in valoare absoluta ) dintr-un vector de numere intregi\n";
            cout<<"7. Iesire \n\n";

            cin>>optiune;
        }

    }

    return 0;
}
