#include <iostream>
#include<fstream>
using namespace std;

class Plata;

class Data
{
    private:
        int zi,luna,an;
    public:

    Data(int zi = 0,int luna = 0,int an = 0) : zi(zi), luna(luna), an(an) {}
    Data (const Data & x) : zi(x.zi), luna(x.luna), an(x.an){}
    Data & operator =(const Data & x)
    {
        zi = x.zi;
        an = x.an;
        luna = x.luna;
        return *this;
    }

    ~Data()
    {
        zi = luna = an =0;
    }

    void afis(ostream &out)
    {
        out<<zi<<"."<<luna<<"."<<an;
    }

    friend istream & operator >> (istream &in, Data &x)
    {
        in>>x.zi>>x.luna>>x.an;
        return in;
    }

    friend ostream & operator <<(ostream& out, Data&x)
    {
        x.afis(out);
        return out;
    }
};

class Plata
{
protected:
    Data data;
    double suma;
public:
    virtual void afis(ostream &out)=0;
    virtual void citire(istream &in)=0;

    friend istream & operator >>(istream &in, Plata& x)
    {
        in>>x.suma>>x.data;
        x.citire(in);
        return in;
    }

    friend ostream & operator <<(ostream &out, Plata& x)
    {
        out<<x.suma<<" "<<x.data<<" ";
        x.afis(out);
        return out;
    }

    Plata(Data data={0,0,0}, double suma=0):data(data),suma(suma){}

    virtual ~Plata()
    {
        suma=0;
    }

};

/*******************/

class Numerar : public Plata
{

public:
   Numerar(Data data={0,0,0}, double suma=0) : Plata(data,suma){}
   Numerar (const Numerar& x) : Plata(x.data,x.suma){}
   Numerar & operator = (const Numerar &x)
   {
       Plata :: operator=(x);
       return *this;
   }

   ~Numerar()
   {
    // #Nimic
   }

   void afis(ostream &out)
   {
    // #Nimic
   }

   void citire(istream &in)
   {
       // #Nimic
   }
};

/*******************/

class Cec : public Plata
{

    string nume,prenume; // am adaugat eu campul asta sa fie
public:
    Cec(string nume="",string prenume="",Data data={0,0,0},double suma=0) : Plata(data,suma), nume(nume),prenume(prenume) {}
    Cec(const Cec & c) : nume(c.nume), Plata(c){}
    Cec & operator =(const Cec & c)
    {
        nume = c.nume;
        prenume = c.prenume;
        Plata::operator=(c);
        return *this;
    }

    ~Cec()
    {
       nume="";
       prenume="";
    }

    void citire(istream &in)
    {
       in>>nume;
       in>>prenume;
    }

    void afis(ostream &out)
    {
        out<<nume<<" "<<prenume;
    }

};

/*******************/

class Card_debit : public Plata
{

    string nr_card;
public:
    Card_debit(string nr_card="",Data data={0,0,0}, double suma=0) : nr_card(nr_card), Plata(data,suma){}
    Card_debit(const Card_debit & c) : nr_card(c.nr_card), Plata(c) {}
    Card_debit & operator = (const Card_debit &c)
    {
        nr_card = c.nr_card;
        Plata :: operator=(c);
        return *this;
    }

    ~Card_debit()
    {
        nr_card="";
    }

    void citire(istream &in)
    {
        in>>nr_card;
    }

    void afis(ostream &out)
    {
        out<<nr_card;
    }
};
int main()
{

    int n=0,opt,i;
    Plata **v;
    cout<<"Introduceti numarul de obiecte: ";cin>>n;
    cout<<"\nNumerar : suma, data\nCec : suma, data, numele persoanei\nCard de debit : suma, data, numar card credit\n\n\n";
    v=new Plata*[n];
    for(i=0;i<n;i++)
    {
        cout<<"Pentru plata numerar, apasati 1\nPentru plata cec, apasati 2\nPentru plata prin card de debit, apasati 3\n";
        cout<<"Optiunea este ";cin>>opt;
        if(opt == 1)
            v[i] = new Numerar;
        else if(opt == 2)
            v[i] = new Cec;
        else v[i] = new Card_debit;

        cin>>*(v[i]);
        cout<<'\n';
    }
    for(i=0;i<n;i++)
        cout<<*(v[i])<<"\n";

    for(i=0;i<n;i++)
        delete v[i];
    delete v;
    return 0;
}