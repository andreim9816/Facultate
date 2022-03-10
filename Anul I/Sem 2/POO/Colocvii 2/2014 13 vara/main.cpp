#include <iostream>
#include<cstring>
#include<vector>

#include<fstream>
using namespace std;

ifstream fin("date.in");

class Data
{
    int zi,luna,an;
public:
    Data(int z=0,int l=0,int a=0) : zi(z),luna(l),an(a){}

    ~Data()
    {
        zi=luna=an=0;
    }

    friend  istream & operator >>(istream &in, Data&x)
    {
        in>>x.zi>>x.luna>>x.an;
        return in;
    }

    friend ostream & operator << (ostream &out,Data &x)
    {
        out<<x.zi<<"."<<x.luna<<"."<<x.an<<" ";
        return out;
    }

    Data(const Data&x)
    {
        zi=x.zi;
        an=x.an;
        luna=x.luna;
    }

    Data & operator = (const Data &x)
    {
        if(this !=&x)
        {

        zi=x.zi;
        luna=x.luna;
        an=x.an;
        }
        return *this;
    }
};

class Factori
{
    int TA,CT;
    Data dTA,dCT;
public:

    int Get_TA()
    {
        return TA;
    }

    int Get_CT()
    {
        return CT;
    }

    Factori(int x=0,Data d1={0,0,0},int y=0,Data d2={0,0,0}) : TA(x),CT(y), dTA(d1),dCT(d2){}

    Factori(const Factori &x)
    {
        TA=x.TA;
        dTA=x.dTA;
        CT=x.CT;
        dCT=x.dCT;
    }

    Factori & operator =(const Factori &x)
    {
        if(this != &x)
        {
            TA=x.TA;
            dTA=x.dTA;
            CT=x.CT;
            dCT=x.dCT;
        }
        return *this;
    }

    ~Factori()
    {
        TA=CT=0;
        dTA={0,0,0};
        dCT={0,0,0};
    }

    friend istream & operator >> (istream &in, Factori &x)
    {
        in>>x.TA>>x.dTA>>x.CT>>x.dCT;
        return in;
    }

    friend ostream & operator <<(ostream & out, Factori &x)
    {
        out<<x.TA<<" "<<x.dTA<<" "<<x.CT<<" "<<x.dCT<<" ";
        return out;
    }
};

class Pacient
{
protected:
    string nume,prenume;
    int varsta;
    string adresa;
    string risc_cardiovascular;
    Factori f;
public:
    Pacient(string nume,string prenume,int varsta,string adresa1,string risc,Factori f) :nume(nume),prenume(prenume),varsta(varsta),risc_cardiovascular(risc),f(f),adresa(adresa1){}
    Pacient()
    {
        nume=prenume=adresa=risc_cardiovascular="";
        varsta=0;
        f={0,0};
    }

    string Get_nume()
    {
        return nume;
    }

    Pacient(const Pacient &x) : nume(x.nume),prenume(x.prenume),varsta(x.varsta),risc_cardiovascular(x.risc_cardiovascular),f(x.f)
    {
        adresa=x.adresa;
    }

    Pacient & operator =(const Pacient &x)
    {
        if(this !=&x)
        {
            nume=x.nume;
            prenume=x.prenume;
            varsta=x.varsta;
            adresa=x.adresa;
            risc_cardiovascular=x.risc_cardiovascular;
            f=x.f;
        }

        return *this;
    }

    friend istream & operator >>(istream &in, Pacient &x);
    friend ostream & operator <<(ostream &out, Pacient &x);

    virtual void citire(istream &in)
    {
        cout<<"Introduceti nume,prenume, varsta si adresa(orasul) ";
        in>>nume>>prenume>>varsta;
        in>>adresa>>f;
    }

    virtual void afisare(ostream &out)
    {
        out<<nume<<" "<<prenume<<" "<<varsta<<"  adresa este: "<<adresa<<" Risc cardiovascular : "<<risc_cardiovascular<<"| "<<f;
    }

    virtual void set_risc()=0;
    virtual int verif_risc_ridicat()=0;

    virtual ~Pacient()=0;
};

Pacient :: ~Pacient()
{
        nume=prenume=risc_cardiovascular="";
        varsta=0;
        adresa[0]='\0';
}

istream & operator >>(istream &in, Pacient &x)
{
    x.citire(in);
    return in;
}

ostream & operator <<(ostream & out, Pacient &x)
{
    x.afisare(out);
    return out;
}

class Copil : public Pacient
{
    string nume1,prenume1;
    string nume2,prenume2;
    double proteina;
    Data d;
    string antecedent;

public:

    Copil ( string n1="",string p1="",string n2="",string p2="",double prot=0.0,Data d={0,0,0}, string x="nu")
    {
        nume1=n1;
        prenume1=p1;
    }

    bool risc()
    {
        if(risc_cardiovascular != "nu")
            return true;
        return false;
    }

    Copil & operator =(const Copil & x)
    {
        if(this != &x)
        {
            this->Pacient :: operator=(x);

            nume1=x.nume1;
            nume2=x.nume2;
            prenume1=x.prenume1;
            prenume2=x.prenume2;
            proteina=x.proteina;
            d=x.d;
            antecedent=x.antecedent;
        }
        return *this;
    }

    Copil (const Copil &x) : Pacient(x)
    {
            nume1=x.nume1;
            nume2=x.nume2;
            prenume1=x.prenume1;
            prenume2=x.prenume2;
            d=x.d;
            proteina=x.proteina;
            antecedent=x.antecedent;
    }

    void citire(istream &in)
    {
        this->Pacient :: citire(in);
        cout<<"Introduceti nume ,prenume parinti, proteina, data si daca are antecedent ";
        in>>nume1>>prenume1;
        in>>nume2>>prenume2;
        in>>proteina ;
        in>>d;
        in>>antecedent;
        this->set_risc();
    }

    void afisare(ostream &out)
    {
        this->Pacient :: afisare(out);

        out<<nume1<<" "<<prenume1;
        out<<" "<<nume2<<" "<<prenume2;
        out<<" Proteina "<<proteina <<" "<<d<<" antecedent "<<antecedent;
    }

    void set_risc()
    {
        int k=0;
        if(proteina >0.6)
            k++;
        if(antecedent == "da")
            k++;
        if(f.Get_CT() > 239)
            k++;
        if(f.Get_TA() > 139)
            k++;
        if(k >=2)
            risc_cardiovascular = "ridicat";
        else if(k==1)
            risc_cardiovascular = "da";
        else risc_cardiovascular = "nu";
    }

    int verif_risc_ridicat()
    {
        return 0;
    }


};

class Adult : public Pacient
{
public:
    void citire(istream &in)=0;

    void afisare(ostream &out)
    {
        this->Pacient :: afisare(out);
    }

    void set_risc()=0;

   virtual int verif_risc_ridicat()=0;

};

class Adult_sub_40 : public Adult
{
public:

    void citire(istream &in)
    {
        this->Pacient :: citire(in);
        this->set_risc();
    }

    void afisare(ostream & out)
    {
        this->Adult :: afisare(out);
    }

    void set_risc()
    {
        int k=0;
        if(f.Get_CT() > 239)
            k++;
        if(f.Get_TA() > 139)
            k++;
        if(k>=2)
            risc_cardiovascular="ridicat";
        else if(k==1)
            risc_cardiovascular="da";
        else risc_cardiovascular="nu";
    }

    int verif_risc_ridicat()
    {
        if(risc_cardiovascular == "ridicat")
            return 1;
        return 0;
    }
};

class Adult_peste_40 : public Adult
{
    string sedentarism,fumator;
public:

    Adult_peste_40(string x="scazut", string y="nu") : sedentarism(x),fumator(y){}
    Adult_peste_40 & operator=(const Adult_peste_40 &x)
    {
        if(this != &x)
        {
            sedentarism= x.sedentarism;
            fumator = x.fumator;
        }
        return *this;
    }

    Adult_peste_40(const Adult_peste_40&x)
    {
         sedentarism= x.sedentarism;
         fumator = x.fumator;
    }

    void citire(istream &in)
    {
        this->Pacient::citire(in);
        in>>sedentarism >> fumator;
        this->set_risc();
    }

    void afisare(ostream &out)
    {
        this->Adult :: afisare(out);
        out<<" Sedentarism: "<<sedentarism<<" Fumator : "<<fumator;
    }

    void set_risc()
    {
        int k=0;
        if(f.Get_CT() > 239)
            k++;
        if(f.Get_TA() > 139)
            k++;
        if(sedentarism == "ridicat")
            k++;
        if(fumator == "da")
            k++;

        if(k>=2)
            risc_cardiovascular="ridicat";
        else if(k==1)
            risc_cardiovascular="da";
        else risc_cardiovascular="nu";
    }

    int verif_risc_ridicat()
    {
        if(risc_cardiovascular == "ridicat")
            return 1;
        return 0;
    }
};

int main()
{

    freopen("date.in","r",stdin);
    try
    {
        Pacient **v;
        int n,i,tip;
        cin>>n;
        v=new Pacient*[n+1];
        if(!v)
            throw 1;

        for(i=0;i<n;i++)
        {
            cout<<"\n\n1.Copil\n2.Adult sub 40\n3. Adult peste 40\n";
            cin>>tip;
            if(tip == 1)
                v[i] = new Copil;
            else if(tip == 2)
                v[i] = new Adult_sub_40;
            else if(tip == 3)
                v[i] = new Adult_peste_40;
            cin>>*v[i];
        }

        int opt,stop=1;
        cin>>opt;
        while(opt)
        {

            if(opt == 0)
                break;
            else if(opt == 1)
            {cout<<"\nOptiunea 1\n";
                for(i=0;i<n;i++)
                    cout<<*v[i]<<"\n";
            }
            else if(opt == 2)
                {
                    cout<<"\nOptiunea 2\n";
                    for(i=0;i<n;i++)
                        if(v[i]->verif_risc_ridicat())
                        cout<<*v[i]<<"\n";
                }
            else if(opt == 3)
            {
                cout<<"\nOptiunea 3\n";
                    for(i=0;i<n;i++)
                       {
                           Copil*aux=dynamic_cast<Copil*>(v[i]);
                           if(aux)
                            cout<<*v[i]<<" ";


                       }
            }
            else if(opt == 4)
            {
                cout<<"\nOptiunea4\n";
                for(i=0;i<n;i++)
                    if(v[i]->Get_nume() == "Cozma")
                        cout<<*v[i]<<endl;
            }
            cin>>opt;

        }

    }catch(int e)
    {
        cout<<"Nu s-a putut aloca memorie";
    }
    return 0;
}
