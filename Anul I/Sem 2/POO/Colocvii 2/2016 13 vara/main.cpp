#include <iostream>
#include<vector>
#include<string>

using namespace std;

class Produs
{
    string denProd;
    float pretProd;
public:
    Produs(string den="", float p=0.0) : denProd(den), pretProd(p) { }

    Produs(const Produs &x) : denProd(x.denProd),pretProd(x.pretProd){}

    Produs & operator =(const Produs&x)
    {
        if(this != &x)
        {
            denProd=x.denProd;
            pretProd=x.pretProd;
        }
        return *this;
    }

    ~Produs()
    {
        denProd="";
        pretProd=0.0;
    }

    friend istream & operator >>(istream &in, Produs &x)
    {
        in>>x.denProd>>x.pretProd;
        return in;
    }

    friend ostream & operator << (ostream &out, Produs &x)
    {
        out<<x.denProd<<" "<<x.pretProd;
        return out;
    }

    string Get_denProd()
    {
        return denProd;
    }
};


class Data
{
    int zi,luna,an;
public:
    Data(int x=0,int y=0,int z=0) :zi(x),luna(y),an(z){}
    Data & operator=(const Data&x)
    {
        if(this !=&x)
        {
            zi=x.zi;
            luna=x.luna;
            an=x.an;
        }
        return *this;
    }
    Data(const Data&x)
    {
         zi=x.zi;
            luna=x.luna;
            an=x.an;
    }

    friend istream & operator >> (istream &in, Data&x)
    {
        in>>x.zi>>x.luna>>x.an;
        return in;
    }

    friend ostream & operator <<(ostream &out, Data&x)
    {
        out<<x.zi<<"."<<x.luna<<"."<<x.an<<" ";
        return out;
    }
};

class Comanda
{
    static int num; // nr comanda
    Produs prod;
    int nr_portii;
    Data d;
public:
    Comanda(Produs p={Produs()},int nr=0,Data d={Data()}) :prod(p),nr_portii(nr),d(d){ num++;}

    Comanda(string den,float pret=0.0,int nr=0,int zi=0,int luna=0,int an=0)
    {
        prod=Produs(den,pret);
        nr_portii=nr;
        d=Data(zi,luna,an);
    }

    Produs Get_prod()
    {
        return prod;
    }

    Comanda(const Comanda &ob)
    {
        num++;
        prod=ob.prod;
        nr_portii=ob.nr_portii;
        d=ob.d;
    }

    Comanda & operator =(const Comanda &ob)
    {
        if(this != &ob)
        {
            num++;
            prod=ob.prod;
            nr_portii=ob.nr_portii;
            d=ob.d;
        }
        return *this;
    }

    friend istream & operator>>(istream &in, Comanda&x)
    {
        in>>x.prod>>x.nr_portii>>x.d;
        return in;
    }

    friend ostream & operator <<(ostream &out, Comanda &x)
    {
        out<<x.prod<<" "<<
        x.nr_portii<<" portii"
        <<x.d;
        return out;
    }

    friend Comanda operator +(const Comanda &y, int x)
    {
        Comanda aux=y;
        aux.nr_portii+=x;
        return aux;
    }

    friend Comanda operator++(Comanda&x,int )  //postfix
    {
        Comanda aux=x;
        x.nr_portii++;
        return aux;
    }

    void del()
    {
        nr_portii=0;
        d={0,0,0};
        prod={"",0};
    }

};

int Comanda :: num=0;

class Ospatar
{

    string Nume;
    vector<Comanda>comenzi;
    int nr_comenzi;
    char s;
    int varsta;
public:

    Ospatar(const Ospatar &x)
    {
        Nume=x.Nume;
        comenzi=x.comenzi;
        nr_comenzi=x.nr_comenzi;
        s=x.s;
        varsta=x.varsta;
    }

    Ospatar & operator=(const Ospatar&x)
    {
        if(this!=&x)
        {
              Nume=x.Nume;
            comenzi=x.comenzi;
            nr_comenzi=x.nr_comenzi;
            s=x.s;
            varsta=x.varsta;
        }
        return *this;
    }

    Ospatar(string numee="", vector<Comanda>comenzii = {Comanda()}, int nr=0, char se='M', int varstaa=0)
    {

        Nume=numee;
        comenzi = comenzii;
        nr_comenzi=nr;
        s=se;
        varsta=varstaa;

    }
    friend ostream & operator <<(ostream &out, Ospatar x)
    {
        out<<x.Nume<<" "<<x.s<<" "<<x.varsta<<" ani ";

        for(int i=0;i<x.nr_comenzi;i++)
            out<<x.comenzi[i]<<" ";
        return out;
    }

    friend bool operator >(Ospatar x, Ospatar y)
    {
        int k1=0,k2=0,i;

        for(i=0;i<x.nr_comenzi;i++)
           if( ((x.comenzi[i]).Get_prod()).Get_denProd() !="")
            k1++;

         for(i=0;i<y.nr_comenzi;i++)
           if( ((y.comenzi[i]).Get_prod()).Get_denProd() !="")
            k2++;

        if(k1>k2)
            return 1;
        return 0;
    }

    friend bool operator <(Ospatar x, Ospatar y)
    {
        int k1=0,k2=0,i;

        for(i=0;i<x.nr_comenzi;i++)
           if( ((x.comenzi[i]).Get_prod()).Get_denProd() !="")
            k1++;

         for(i=0;i<y.nr_comenzi;i++)
           if( ((y.comenzi[i]).Get_prod()).Get_denProd() !="")
            k2++;

        if(k1<k2)
            return 1;
        return 0;
    }

    friend bool operator == (Ospatar x, Ospatar y)
    {
           int k1=0,k2=0,i;

        for(i=0;i<x.nr_comenzi;i++)
           if( ((x.comenzi[i]).Get_prod()).Get_denProd() !="")
            k1++;

         for(i=0;i<y.nr_comenzi;i++)
           if( ((y.comenzi[i]).Get_prod()).Get_denProd() !="")
            k2++;

        if(k1 == k2)
            return 1;
        return 0;
    }

    string nume()
    {
        return Nume;
    }
};

class Comanda_spec : virtual public Comanda
{
    string ObsC;
    float pretSupl;
public:
    Comanda_spec(string x="",float y=0.0) : ObsC(x),pretSupl(y){}
    Comanda_spec(const Comanda_spec &x) : Comanda(x)
    {

        ObsC=x.ObsC;
        pretSupl=x.pretSupl;
    }

    Comanda_spec & operator=(const Comanda_spec&x)
    {
        if(this !=&x)
        {
            this-> Comanda :: operator=(x);
            ObsC=x.ObsC;
            pretSupl=x.pretSupl;
        }
        return *this;
    }


};

class Comanda_online : virtual public Comanda
{
    string Adresa;
    int comLivr;
public:
    Comanda_online(string x="",int com=0) : Adresa(x),comLivr(com){}

    Comanda_online(const Comanda_online &x): Comanda(x)
    {

        Adresa=x.Adresa;
        comLivr=x.comLivr;
    }

    Comanda_online & operator =(const Comanda_online &x)
    {
        if(this !=&x)
        {
            this->Comanda::operator=(x);
            Adresa=x.Adresa;
            comLivr=x.comLivr;
        }
        return *this;
    }
};

class Comanda_online_spec : public Comanda_online, public Comanda_spec
{

};
int main()
{
    Produs meniu[4]={Produs("frigarui",30),Produs("cola",7.5),Produs("cafea",5)};

    Comanda c1("frigarui",2,2,30,6,2016),c2("cola",3),c3("cafea",1),c4=c2,c5;
    c3=c3+4;
    c2++;
    c1.del();
    cin>>c5;
    cout<<c4<<endl<<c5;
    cout<<"\n----\n";
  //  Comanda *com1=new Comanda[4], *com2=new Comanda[4];

    vector<Comanda>com1,com2;
    com1.resize(4);
    com2.resize(4);

    com1[0]=c1;
    com1[1]=c2;
    com1[2]=c3;

    com2[0]=c4;
    com2[1]=c5;

 //   cout<<com1[0]<<" "<<com1[1]<<" "<<com1[2]<<endl;
  //  cout<<com2[0]<<" "<<com2[1]<<endl;

    Ospatar o1("Ionescu",com1,3,'M',25);

   Ospatar o2("Popescu",com2,2,'F',30);

    cout<<o1<<"\n"<<o2<<"\n";

    if(o1 < o2) cout<<"Ospatarul "<<o2.nume() << " a servit mai multe comenzi decat ospatarul " << o1.nume();
    else if(o1 == o2) cout<<"Ospatarul " <<o2.nume()<<" a servit la fel de multe comenzi ca ospatarul " <<o1.nume();
    else cout<<"Ospatarul "<<o1.nume()<<" a servit mai multe comenzi ca "<<o2.nume()<<endl;

    return 0;

}
//cartofi 20.5 10 28 11 1998
