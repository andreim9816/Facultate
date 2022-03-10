#include <iostream>
#include<vector>
#include<stdlib.h>
#include<fstream>

#include<string>
using namespace std;
ifstream fin("date.in");
class Data
{
    int zi,luna,an;
public:
    Data(int x=0,int y=0,int an=0) : zi(x),luna(y),an(an){}
    Data (const Data&x) : zi(x.zi),luna(x.luna),an(x.an){}
    Data & operator =(const Data &x)
    {
        if(this !=&x)
        {
            zi=x.zi;
            luna=x.luna;
            an=x.an;
        }
        return *this;
    }

    void Set_data(int zile)
    {
        zi+=zile;
        int t=zi/30;
        zi=zi%30;
        luna=luna+t;
        t=luna/12;
        luna=luna%12;
        an=an+t;
    }

    friend istream & operator >>(istream & in, Data&x)
    {
        in>>x.zi>>x.luna>>x.an;
        return in;
    }

    friend ostream &operator <<(ostream &out, Data&x)
    {
        out<<x.zi<<"."<<x.luna<<"."<<x.an<<" ";
        return out;
    }
};

class Zbor
{
protected:
    string plecare,dest,ID;
    Data d;
    int durata;
public:

    virtual ~Zbor()
    {
        plecare=dest=ID="";
        d={0,0,0};
        durata=0;
    }
    Zbor(string pl="",string de="",string I="",Data x={Data()},int dur=0) : plecare(pl),dest(de),ID(I),d(x),durata(dur){}
    Zbor(const Zbor &x)
    {
        d=x.d;
        durata=x.durata;
        plecare=x.plecare;
        dest=x.dest;
        ID=x.ID;
    }
    Zbor & operator =(const Zbor&x)
    {
        if(this != &x)
        {
        d=x.d;
        durata=x.durata;
        plecare=x.plecare;
        dest=x.dest;
        ID=x.ID;
        }
        return *this;
    }

    virtual void citire(istream &in)
    {
        in>>ID>>plecare>>dest;
        in >> d;
        in >>durata;
    }

    virtual void afisare(ostream &out)
    {
        out<<ID<<" "<<plecare<<" -> "<<dest<<" "<<d<<" "<<durata<<" ore";
    }

    friend istream & operator >>(istream &in, Zbor&x)
    {
        x.citire(in);
        return in;
    }

    friend ostream & operator << (ostream&out, Zbor &x)
    {
        x.afisare(out);
        return out;
    }
};

class Zbor_temp : virtual public Zbor
{
protected:
    int perioada;
    Data df;
public:
    Zbor_temp(int perioada=0, string Id="",string plec="",string dest="",Data d={Data()},int dur=0) : Zbor(plec,dest,Id,d,dur),perioada(perioada)
    {
        df=d;
        df.Set_data(perioada); // adauga perioada zile de la data la care s-a inceput
    }

    Zbor_temp(const Zbor_temp &x) : Zbor(x)
    {
        perioada = x.perioada;
        df=x.df;
    }

    Zbor_temp & operator=(const Zbor_temp &x)
    {
        if(this != &x)
        {
            this->Zbor :: operator=(x);
            perioada = x.perioada;
            df=x.df;
        }
        return *this;
    }

    void citire(istream& in)
    {
        this-> Zbor::citire(in);
        in>>perioada; // citeste pentru cate zile are loc zbrul temporar
    }

    void afisare(ostream& out)
    {
        this->Zbor::afisare(out);
        out<<" zbor care dureaza "<< perioada <<" zile pana pe data de "<<df;
    }
};

class Zbor_discount : virtual public Zbor
{
protected:
    int discount;
public:
    Zbor_discount(int d=0,string Id="",string plec="",string dest="",Data da={Data()},int dur=0) : Zbor(plec,dest,Id,da,dur), discount(d) {}
    Zbor_discount(const Zbor_discount &x) : Zbor(x),discount(x.discount){}
    Zbor_discount & operator=(const Zbor_discount &x)
    {
        if(this != &x)
        {
            this->Zbor::operator=(x);
            discount=x.discount;
        }
        return *this;
    }

    void citire(istream & in)
    {
        this->Zbor::citire(in);
        in>>discount;
    }

    void afisare(ostream &out)
    {
        this->Zbor::afisare(out);
        out<<" "<<discount<<"% ";
    }
};

class Zbor_temp_discount : public Zbor_temp, public Zbor_discount
{
public:
    Zbor_temp_discount(string Id="",string plec="",string dest="",Data da={Data()},int dur=0,int disc=0,int per=0) : Zbor(plec,dest,Id,da,dur),Zbor_temp(per), Zbor_discount(disc){}

    void citire(istream &in)
    {
        this->Zbor::citire(in);
        in>>discount>>perioada;
    }

    void afisare(ostream &out)
    {
        this->Zbor::afisare(out);
        out<<discount<<" % "<<perioada<<" zile ";
    }
};

class Ruta
{
    string plecare,dest;
    int nrcurse;
    float pret;
    Data d;
    vector<Zbor*>v;
public:
    Ruta(string plec="",string dest="",int nr=0,float pret=0.0,Data dd={0,0,0}) : plecare(plec),dest(dest),nrcurse(nr),pret(pret),d(dd){}

    ~Ruta()
    {
        plecare=dest="";
        nrcurse=0;
        pret=0;
        d={0,0,0};
        int i;
        for(i=0;i<v.size();i++)
            delete v[i];
    }

    void add_zbor(Zbor*x)
    {
        v.push_back(x);
        nrcurse++;
    }

    friend istream & operator >>(istream &in, Ruta&x)
    {
        in>>x.plecare>>x.dest>>x.pret>>x.d;
        return in;
    }

    friend ostream & operator <<(ostream &out, Ruta&x)
    {
        out<<x.plecare<<" -> "<<x.dest<<" "<<x.d<<" "<<x.pret<<" lei ";
        return out;
    }

};

int main()
{
    try
    {
        Ruta*v;
        int i,n,j,tip,x;
        cout<<"Introduceti numarul de rute ";
        cin>>n;
        v=new Ruta[n];
        if(!v)
            throw 1;

        for(i=0;i<n;i++)
        {
            cin>>v[i];
            cout<<"\nIntroduceti numarul de zboruri si zborurile\n";
            cin>>x;
            for(j=0;j<x;j++)
            {
                Zbor*z;
            cout<<"\n1.Zbor simplu\n2.Zbor discount\n3.Zbor temporar\n4.Zbor cu discount si temporar\n\n";
            cin>>tip;

            if(tip==1)
                z=new Zbor;
            else if(tip == 2)
                z=new Zbor_discount;
            else if(tip == 3)
                z=new Zbor_temp;
            else if(tip == 4)
                z=new Zbor_temp_discount;

                cin>>*z;
                v[i].add_zbor(z);
            }
        }

        for(i=0;i<n;i++)
            cout<<v[i]<<" ";



    }
    catch(int e)
    {
        cout<<"Nu s-a putut aloca memorie";
    }
    return 0;
}
