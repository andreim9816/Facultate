#include <iostream>
#include<vector>
#include<cstdio>
#include<stdexcept>
using namespace std;

class Cursa;
class Cursa_temporar;
class Cursa_discount;
class Cursa_discount_temporar;

class Data
{
private:
    int zi,luna,an;
public:
    friend Cursa_temporar;
    friend Cursa_discount_temporar;

    Data(int zi=0,int luna=0,int an=0) : an(an),luna(luna),zi(zi) {}

    Data Get()
    {
        Data data(zi,luna,an);
        return data;
    }

    void Set(int zi,int luna,int an)
    {
        zi=zi;
        an=an;
        luna=luna;
    }

    ~Data()
    {
        zi=luna=an=0;
    }
    friend istream & operator >>(istream &in,Data &x)
    {
        in>>x.zi>>x.luna>>x.an;
        return in;
    }

    friend ostream &operator <<(ostream &out,Data &x)
    {
        out<<x.zi<<"."<<x.luna<<"."<<x.an;
        return out;
    }

    friend bool operator < (Data d1, Data d2)
    {
        if(d1.an<d2.an)
            return 1;
        if(d1.luna<d2.luna)
            return 1;
        if(d1.zi<d2.zi)
            return 1;
        return 0;
    }

};


class Cursa
{
protected:
    string ID,plecare,dest;
    Data data;
    int durata;

public:
    Cursa(string ID="", string plecare="", string dest="", Data data={0,0,0}, int durata=0) : ID(ID),plecare(plecare),dest(dest),data(data),durata(durata) { }

    virtual void citire(istream &in)
    {
        in>>ID>>plecare>>dest>>data>>durata;
    }


    friend istream & operator >>(istream &in, Cursa &x)
    {
        x.citire(in);
        return in;
    }

    virtual void afis(ostream &out)
    {
         out<<ID<<" "<<plecare<<" -> "<<dest<<" "<<data<<" "<<durata<<" ore";
    }

    friend ostream & operator <<(ostream &out, Cursa &x)
    {
        x.afis(out);
        return out;
    }

};

class Cursa_discount : virtual public Cursa
{
protected:
    int discount;
public:
    Cursa_discount(string ID="",string plecare="", string dest="",Data data={0,0,0},int durata=0, int discount=0) : Cursa(ID,plecare,dest,data,durata) , discount(discount){}

    void citire(istream &in)
    {
        Cursa :: citire(in);
        in>>discount;
    }

    void afis(ostream &out)
    {
        Cursa :: afis(out);
        out<< " "<<discount<<"%";
    }
};

class Cursa_temporar : virtual public Cursa
{
protected:
    int perioada; // cate zile e valabila
    Data f; // data finala pana cand dureaza zborul

public:

    Cursa_temporar(string ID="",string plecare="", string dest="",Data data={0,0,0},int durata=0, int perioada=0) : Cursa(ID,plecare,dest,data,durata), perioada(perioada)
    {
        Data d1,d2;
        int t,zi,an,luna;

        d1=data.Get();

        zi=d1.zi+perioada;
        t=zi/30;
        zi=zi%30;

        luna=d1.luna+t;
        t=luna/12;
        an=d1.an+t;

        f.Set(zi,luna,an);

    }

    void citire(istream &in)
    {
        Cursa :: citire(in);
        in>>perioada;
    }

    void afis(ostream &out)
    {
        Cursa :: afis(out);
        out<<perioada<<" zile";
    }

};

class Cursa_discount_temporar : public Cursa_discount, public Cursa_temporar
{
protected:
    int discount;
    int perioada;
    Data f;
public:
    Cursa_discount_temporar( string ID="",string plecare="", string dest="",Data data={0,0,0},int durata=0, int discount=0,int perioada=0) : Cursa(ID,plecare,dest,data,durata),Cursa_discount(ID,plecare,dest,data,durata,discount),Cursa_temporar(ID,plecare,dest,data,durata,perioada),perioada(perioada),discount(discount)
    {
        Data d1,d2;
        int t,zi,an,luna;

        d1=data.Get();

        zi=d1.zi+perioada;
        t=zi/30;
        zi=zi%30;

        luna=d1.luna+t;
        t=luna/12;
        an=d1.an+t;

        f.Set(zi,luna,an);
    }

    void citire(istream &in)
    {
        Cursa :: citire(in);
        in>>discount>>perioada;
    }

    void afis(ostream &out)
    {
        Cursa :: afis(out);
        out<<discount<<"% "<<perioada<<" zile ";
    }
};

class Ruta
{
protected:

    Data data;
    string plecare,dest;
    float pret;
    int nr_curse;
    vector<Cursa*>v;

public:
    Ruta(Data data={0,0,0},string x="",string y="",float z=0,int nr_curse=0) : data(data),plecare(x),dest(y),pret(z),nr_curse(nr_curse){}

    void afis_toate_cursele()
    {
        for(int i=0;i<v.size();i++)
          cout<<*v[i]<<endl;
    }

    void add(Cursa* z)
    {
        v.push_back(z);
        nr_curse++;
    }

    virtual void citire(istream &in)
    {

        in>>data;
        in>>plecare>>dest;
        in>>pret;
    }

    virtual void afis(ostream &out)
    { //  cout<<"Se afiseaza 2 ";
        out<<plecare<<" -> "<<dest<<" "<<pret<<" dolari "<<data;
    }

    friend istream & operator >>(istream &in, Ruta &x)
    {
        x.citire(in);
        return in;
    }

    friend ostream & operator <<(ostream &out, Ruta &x)
    {  // cout<<"Se afieaza 1 ";
        x.afis(out);
        return out;
    }

    ~Ruta()
    {
        plecare=dest="";
        pret=0;
        nr_curse=0;
        for(auto i=0;i<v.size();i++)
            delete v[i];
    }

};


int main()
{
    freopen("date.in","r",stdin);

    Ruta*v;
    int n,x,tip,i,j;
    cout<<"Cititi numarul de rute : ";cin>>n;
    try
    {
        v=new Ruta[n];
        if(!v)
            throw 1;
        for(i=0;i<n;i++)
            {
                cin>>v[i];
                cout<<"Introduceti numarul zboruri : ";cin>>x;
                for(j=0;j<x;j++)
                {
                    Cursa *z;
                   // cout<<"\nIntroduceti 1 daca vreti sa cititi un zbor cu discount\nIntroduceti 2 daca vreti sa cititi un zbor temporar\nIntrudoceti 3 daca vreti sa cititi un zbor cu discount si temporar\n";
                    cin>>tip;
                    if(tip == 1)
                        z=new Cursa_discount;
                    else if(tip == 2)
                        z=new Cursa_temporar;
                    else if(tip == 3)
                        z=new Cursa_discount_temporar;

                    cin>>*(z);
                    v[i].add(z);
                }
            }
        for(i=0;i<n;i++)
            {
                cout<<v[i]<<endl;
                v[i].afis_toate_cursele();
                cout<<endl;
            }
    }


    catch(int e)
    {
        cout<<"Nu s-a putut aloca memorie suficienta";
    }
    return 0;
}
