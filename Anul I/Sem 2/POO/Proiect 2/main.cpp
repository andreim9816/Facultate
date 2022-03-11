#include <iostream>
#include<cmath>
using namespace std;

class Matrice
{
protected:
    int **a;
    int n;

public:
    Matrice();
    Matrice(int );
    ~Matrice();

    Matrice (const Matrice &);
    Matrice& operator = ( const Matrice&);

    friend istream& operator >> (istream&, Matrice&);
    friend ostream& operator << (ostream&, Matrice&);

    friend class Graf_Turneu;
};


Matrice :: Matrice()
{
    a=NULL;
    n=0;
}

Matrice :: ~Matrice()
{

    int i;
    if(a)
    {
    for(i=0;i<n;i++)
        delete []a[i];
    delete[] a;
    }
    n=0;

}

Matrice :: Matrice(int n)
{

    int i;
    this->n=n;

    a=NULL;
    a=new int*[n];
    for(i=0;i<n;i++)
        a[i]=new int[n];

}

Matrice :: Matrice (const Matrice &x)  /// constructor de copiere
{

    int i,j;
    this->n=x.n;

    a=NULL;
    a=new int*[x.n];
    for(i=0;i<x.n;i++)
        a[i]=new int[x.n];

    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
        a[i][j]=x.a[i][j];
}

Matrice & Matrice :: operator = (const Matrice &x) /// operator = de atribuire
{

    if(this==&x)
        return *this;

    int j,i;

    // dezaloc
    for(i=0;i<x.n;i++)
        delete []x.a[i];
    delete[] x.a;

    this->n=x.n;

    a=NULL;             // aloc
    a=new int*[x.n];
    for(i=0;i<x.n;i++)
        a[i]=new int[x.n];

    for(i=0;i<x.n;i++)  // atribui
     for(j=0;j<x.n;j++)
      a[i][j]=x.a[i][j];

    return *this;

}

istream & operator >> (istream &in, Matrice &M)
{
    int i,j;
  // deazloc memoria
    for(i=0;i<M.n;i++)
            delete []M.a[i];
        delete[] M.a;

    cout<<"Introduceti numarul de noduri "; in>>M.n;       /// dimensiunea

    M.a=new int*[M.n];
    for(i=0;i<M.n;i++)
        M.a[i]=new int[M.n];

    for(i=0;i<M.n;i++)
        for(j=0;j<M.n;j++)
            in>>M.a[i][j];

    return in;
}

ostream & operator << (ostream &out, Matrice &M)
{
    int i,j;

    for(i=0;i<M.n;i++)
    {
        for(j=0;j<M.n;j++)
            out<<M.a[i][j]<<" ";
        out<<'\n';
    }
    return out;
}

class Graf
{

protected:
    int nr_noduri;

public:

    Graf();
    virtual ~Graf()=0;
    Graf(const Graf&);
    Graf & operator = (const Graf &);

    virtual void display()=0;
};

Graf :: Graf()
{
    // Constructor Graf

    nr_noduri=0;
}

Graf :: ~Graf()
{
    // Destructor Graf

    nr_noduri=0;
}

Graf :: Graf(const Graf & G)                /// constructor de copiere
{
    nr_noduri=G.nr_noduri;
}

Graf& Graf:: operator = (const Graf & G)    ///  operator = de atribuire
{
    nr_noduri=G.nr_noduri;
    return *this;
}


class Graf_complet : public Graf
{

protected:
    int nr_muchii;

public:
    Graf_complet();
    ~Graf_complet();

    Graf_complet(const Graf_complet & );
    Graf_complet & operator = (const Graf_complet & );

    void citire(istream &);
    friend istream & operator >>(istream &, Graf_complet&);

    void display();
};

void Graf_complet :: display()
{
    // nimic
}

Graf_complet :: Graf_complet() : Graf()
{
    nr_muchii=0;
}

Graf_complet :: ~Graf_complet()
{
    nr_muchii=0;

}

Graf_complet :: Graf_complet (const Graf_complet & G) : Graf(G)      /// constructor de copiere
{
    nr_muchii=G.nr_muchii;
}

Graf_complet & Graf_complet :: operator = (const Graf_complet & G)   /// operator = de atribuire
{

    Graf::operator=(G);                    /// apelez operatorul de atribuire = pt clasa de baza
    nr_muchii=G.nr_muchii;

    return *this;
}
void Graf_complet :: citire(istream &in)
{
    in>>nr_muchii;
    nr_noduri=sqrt(nr_muchii*2)+1;
}

istream & operator >> (istream & in, Graf_complet & G)
{
    G.citire(in);
    return in;
}

class Graf_antisimetric : public Graf
{
protected:
    Matrice M;

public:
    Graf_antisimetric();
    ~Graf_antisimetric();

    Graf_antisimetric (const Graf_antisimetric & ) ;
    Graf_antisimetric & operator = (const Graf_antisimetric & );

    friend istream & operator >> (istream &, Graf_antisimetric & );
    friend ostream & operator << (ostream &, Graf_antisimetric & );

    void display();
};

Graf_antisimetric :: Graf_antisimetric()
{
    // Constructor Graf_antisimetric

}

Graf_antisimetric :: ~Graf_antisimetric()
{

}

Graf_antisimetric :: Graf_antisimetric(const Graf_antisimetric & G) : Graf(G), M(G.M)   /// constructor de copiere
{

}


Graf_antisimetric & Graf_antisimetric :: operator = (const Graf_antisimetric & G)   /// operator = de atribuire
{
    Graf::operator = (G); /// am apelat operatorul = pe clasa Graf
    this->M = G.M;        /// am apelat operatorul = pe clasa Matrice

    return *this;
}

istream & operator >> (istream & in, Graf_antisimetric & G)
{
    in>>G.M;
    return in;
}

ostream & operator << (ostream & out, Graf_antisimetric & G)
{
    out<<G.M;
    return out;
}

void Graf_antisimetric :: display()
{
    cout<<M<<'\n';  // se apeleaza operator << din clasa Matrice
}

class Graf_Turneu : public Graf_antisimetric, public Graf_complet
{
public:
    Graf_Turneu();
    ~Graf_Turneu();

    Graf_Turneu (const Graf_Turneu &);
    Graf_Turneu & operator = ( const Graf_Turneu &);

    friend istream & operator >> ( istream &, Graf_Turneu &);
    friend ostream & operator << ( ostream &, Graf_Turneu &);

    void display();
};

Graf_Turneu :: Graf_Turneu() : Graf_antisimetric(), Graf_complet()
{
    // Constructor Graf_Turneu
}

Graf_Turneu :: ~Graf_Turneu()
{
    // Destructor Graf_Turneu

}

Graf_Turneu :: Graf_Turneu(const Graf_Turneu &G) : Graf_antisimetric(G), Graf_complet(G) /// constructor de copiere
{

}

Graf_Turneu & Graf_Turneu :: operator = ( const Graf_Turneu &G) /// operator = de atribuire
{
    Graf_antisimetric :: operator=(G);
    Graf_complet :: operator=(G);

    return *this;
}

istream & operator >> (istream &in, Graf_Turneu &G) /// functie de citire pentru un Graf_Turneu
{
    in>>G.M;
    return in;
}

ostream & operator << (ostream &out, Graf_Turneu &G)    /// functie de afisare pentru un Graf_Turneu
{
    out<<G.M;
    return out;
}

void Graf_Turneu :: display()
{
    /// metoda virtuala ( din cerinta ) care afiseaza arcele unui Graf_Turneu

   int i,j;
    for(i=0;i<M.n;i++)
        for(j=0;j<M.n;j++)
         if(M.a[i][j])
            cout<<"Exista muchie de la nodul "<<i+1<<" la nodul "<<j+1<<'\n';

}

int main()
{

    Graf_Turneu *v;
    int i,n;

    cout<<"Introduceti numarul de Grafuri Turneu :";cin>>n;
    v=new Graf_Turneu[n];
    for(i=0;i<n;i++)
        cin>>v[i];

    for(i=0;i<n;i++)
        {
            cout<<"\nPentru Graful "<<i+1<<endl;
            v[i].display();
        }

// eliberare memorie

    delete []v;



    return 0;
}