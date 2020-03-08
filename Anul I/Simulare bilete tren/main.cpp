#include <iostream>
#include<stdexcept>
#include<fstream>
using namespace std;

/// Manolache Andrei 144 C++11
/// GNU CodeBlocks 16.01

ifstream fin("date.in");

class Data
{
    int zi,luna,an;
public:
    Data(int x=0,int y=0,int z=0) : zi(x),luna(y),an(z){}
    Data & operator =(const Data&x)
    {
        if(this != &x)
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

    friend istream & operator >>(istream &in, Data&x)
    {
        in>>x.zi>>x.luna>>x.an;
        return in;
    }

    friend ostream & operator << (ostream & out, Data &x)
    {
        out<<x.zi<<"."<<x.luna<<"."<<x.an<<" ";
        return out;
    }

    ~Data()
    {
        zi=luna=an=0;
    }

};

class Bilet
{
protected:
    string plecare,dest;
    Data d;
    int ora;
    string cod; // IR sau R2100
    int durata;
    int distanta;
    double pret;
    string serie;

    static int nr; // numarul biletului care e emis, 453 in exemplu

public:
    Bilet(string plec="",string de="",Data dd={0,0,0},int ora=0,string co="",int dur=0,int dist=0,double p=0.0,string seri="")
    : plecare(plec), dest(de),d(dd),ora(ora),cod(co),durata(dur),distanta(dist),pret(p),serie(seri) { }

    Bilet( const Bilet &x)
    {
        plecare=x.plecare;
        dest=x.dest;
        ora=x.ora;
        cod=x.cod;
        durata=x.durata;
        distanta=x.distanta;
        pret=x.pret;
        serie=x.serie;
    }

    Bilet & operator=(const Bilet &x)
    {
        if(this != &x)
        {
           plecare=x.plecare;
            dest=x.dest;
            ora=x.ora;
            cod=x.cod;
            durata=x.durata;
            distanta=x.distanta;
            pret=x.pret;
            serie=x.serie;
        }
        return *this;
    }

    virtual void citire(istream &in)
    {
        in>>plecare>>dest>>d>>ora>>cod>>durata>>distanta;
    }

    virtual void afisare(ostream & out)
    {
        out<<serie<<" "<<cod<<" "<<plecare<<" -> " <<dest<<" ora "<<ora<<" "<<d<<" durata de "<< durata << " minute "<< distanta <<" km "<<pret<<" lei ";
    }

    friend istream & operator >> (istream &in, Bilet &x)
    {
        x.citire(in);
        return in;
    }

    friend ostream & operator <<(ostream &out, Bilet&X)
    {
        X.afisare(out);
        return out;
    }

    virtual ~Bilet()
    {
        plecare = dest = "" ;
        d={0,0,0};
        ora = durata = distanta =0;
        pret = 0.0;
        cod="";
    }

    string Get_cod()
    {
        return cod;
    }

    int Get_distanta()
    {
        return distanta;
    }

    string Get_serie()
    {
        return serie;
    }

    void anulare()
    {
        plecare = dest = "" ;
        d={0,0,0};
        ora = durata = distanta =0;
        pret = 0.0;
        cod="";
    }

};

int Bilet :: nr=0; /// am considerat ca e unic numarul unui bilet,indiferent de tren, de tipul biletului (regio ,inter-regio, I sau II )

class R : public Bilet
{
public:

    virtual void citire(istream &in)
    {
        this->Bilet :: citire(in);
    }

    virtual void afisare(ostream &out)
    {
        this->Bilet :: afisare(out);
    }

    void Set_pret_R()
    {
        pret = distanta * 0.39;
    }
};

class IR : public Bilet
{
protected:
    int loc; // nr locului care se citeste Ex locul 82
public:

    IR(int l =0) : loc(l) { }
    void citire(istream & in)
    {
        this->Bilet :: citire(in);
        in>>loc;
    }

    void afisare(ostream & out)
    {
        this->Bilet :: afisare(out);
        out<<" nr loc "<<loc<<" ";
    }

    ~IR()
    {
        loc=0;
    }

    IR(const IR&X)
    {
        loc=X.loc;
    }

    IR & operator =(const IR&x)
    {
        if(this != &x)
        {
            this->Bilet :: operator=(x);
            loc=x.loc;
        }
        return *this;
    }

     void Set_pret_IR()
    {
        pret = double(0.7 * distanta);
    }
};

class I_R : public R
{
public:

    void afisare(ostream &out)
    {
        this->R::afisare(out);
    }
    void Set_serie()
    {
        serie=serie+"RI"; // regio cclasa 1
        /// transformare numar in string
        ///   serie= serie + to_string(nr);
    }


    void citire(istream & in)
    {
        nr++;
        this->R::citire(in);
        this->Set_pret_R();
         pret=1.2*pret;
         this->Set_serie();
    }


};

class II_R : public R
{
public:

    void afisare(ostream &out)
    {
        this->R::afisare(out);
    }

    void Set_serie()
    {
        serie=serie+"RII";
        /// transform numar in string
       /// serie= serie + to_string(nr);
    }

     void citire(istream &in)
    {
        nr++;
        this->R::citire(in);
        this->Set_pret_R();
        this->Set_serie();
    }
};

class I_IR : public IR
{
public:

    void afisare(ostream &out)
    {
        this->IR::afisare(out);
    }

    void Set_serie()
    {
        serie=serie+"IRI";
        /// transform numar in string
        /// serie= serie + to_string(nr);
    }

     void citire(istream &in)
    {
        nr++;
        this->IR::citire(in);
        this->Set_pret_IR();
        pret=1.2*pret;
        this->Set_serie();
    }
};

class II_IR : public IR
{
    public:


    void afisare(ostream &out)
    {
        this->IR::afisare(out);
    }

    void Set_serie()
    {
        serie=serie+"IRI";
        /// transform numar in string
        /// serie= serie + to_string(nr);
    }
    void citire(istream &in)
    {
        nr++;
        this->IR::citire(in);
        this->Set_pret_IR();
        this->Set_serie();
    }
};

int main()
{
    try
    {

        int i,n,tip;
        Bilet **v;
        fin>>n; // se citeste numarul de bilete
        v=new Bilet*[n];

        if(!v)
            throw 1;
        cout<<"Sunt "<<n<<" bilete\n";
        for(i=0;i<n;i++)
        {
            /// 1. Regio clasa 1
            /// 2. Regio clasa 2
            /// 3. Inter Regio clasa 1
            /// 4. Inter Regio clasa 2

            fin>>tip;

            if(tip == 1)
                v[i] = new I_R;
            else if(tip == 2)
                v[i] = new II_R;
            else if(tip == 3)
                v[i] = new I_IR;
            else v[i] = new II_IR;

            // A
            fin>>*v[i]; // citirea unui bilet

        }

        cout<<"Toate biletele sunt:\n";
        for(i=0;i<n;i++)
            cout<<*v[i]<<endl;

        // B

            string cod_tren;    // in date.in codul trenului este R1900
            fin>>cod_tren;
            cout<<"\nTrenurile care au codul "<<cod_tren<<" sunt:\n";
            for(i=0;i<n;i++)
                if(v[i] ->Get_cod() == cod_tren)
                    cout<<*v[i]<< "\n";


        //C
        int dist;
        fin>>dist; // in date.in distanta este 10 km
        cout<<"\nTrenuile care merg pe o distanta mai mare ca "<<dist<<" km sunt:\n";
        for(i=0;i<n;i++)
            if(v[i]->Get_distanta() > dist)
            cout<<*v[i]<<"\n";

        //D

        string serie;
        fin>>serie;

        for(i=0;i<n;i++)
            if(v[i]->Get_serie() == serie)
                {
                    v[i]->anulare();
                    for(int j=i;j<n;j++)
                        v[j]=v[j+1];
                    n--;
                    i--;
                }

        cout<<"\nDupa eliminarea biletelor cu seria "<<serie<<" au ramas:\n";
        for(i=0;i<n;i++)

            cout<<*v[i]<<endl;

    }catch(int e)
    {
        cout<<"Nu s-a putut aloca memorie";
    }

    return 0;
}
