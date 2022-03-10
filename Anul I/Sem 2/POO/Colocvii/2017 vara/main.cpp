#include <iostream>
#include<vector>
#include<cstdio>
#include<cstring>
using namespace std;

class Data
{
    int luna,an;
public:
    Data(int luna=0,int an=0) : luna(luna),an(an){}
    friend istream & operator >>(istream &in, Data &x)
    {
        in>>x.luna>>x.an;
        return in;
    }

    friend ostream & operator <<(ostream &out, Data &x)
    {
        out<<x.luna<<"."<<x.an;
        return out;
    }

    int Get_luna()
    {
        return luna;
    }

    int Get_an()
    {
        return an;
    }

};

class Proprietate
{
protected:
    char adresa[100];
    int suprafata,pret_mp;
public:

    int Get_suprafara()
    {
        return suprafata;
    }

    int Get_pret_mp()
    {
        return pret_mp;
    }

    Proprietate(char adresa[]=NULL,int suprafata=0,int pret_mp=0) :suprafata(suprafata),pret_mp(pret_mp)
    {
        strcpy(adresa,adresa);
    }

    virtual void citire(istream &in)
    {
        in>>adresa>>suprafata>>pret_mp;
    }

    virtual void afis(ostream &out)
    {
        out<<adresa<<" "<<suprafata<<" mp^2 "<<pret_mp<<" $/mp^2";
    }

    friend ostream & operator <<(ostream& out, Proprietate &x)
    {
        x.afis(out);
        return out;
    }

    friend istream & operator >>(istream &in, Proprietate &x)
    {
        x.citire(in);
        return in;
    }
};

class Casa : public Proprietate
{
    int etaje,curte_mp;
public:

    Casa(char *adresa=NULL,int suprafata=0,int pret_mp=0,int etaje=0,int curte_mp=0) : Proprietate(adresa,suprafata,pret_mp),etaje(etaje),curte_mp(curte_mp){}

    int Get_etaje()
    {
        return etaje;
    }

    int Get_curte_mp()
    {
        return curte_mp;
    }

    void citire(istream &in)
    {
        Proprietate::citire(in);
        in>>etaje>>curte_mp;
    }

    void afis(ostream &out)
    {
        Proprietate::afis(out);
        out<<etaje<<" etaje "<<curte_mp<<" mp^2 de curte ";
    }
};

class Apartament : public Proprietate
{
    int etaj,nr_camere;
public:
    Apartament(char *adresa=NULL,int suprafata=0,int pret_mp=0,int etaj=0,int nr_camere=0) : Proprietate(adresa,suprafata,pret_mp),etaj(etaj),nr_camere(nr_camere){}

    int Get_etaj()
    {
        return etaj;
    }

    int Get_nr_camere()
    {
        return nr_camere;
    }

    void citire(istream &in)
    {
        Proprietate::citire(in);
        in>>etaj>>nr_camere;
    }

    void afis(ostream &out)
    {
        Proprietate::afis(out);
        out<<etaj<<" etaj"<<nr_camere<<" camere ";
    }

};

class Contract
{
protected:
    double discount;
public:

    virtual void citire(istream &in)
    {

    }

    friend istream & operator >>(istream &in, Contract &x)
    {
        x.citire(in);
        return in;
    }

    virtual void afisare(ostream &out)
    {

    }

    friend ostream & operator <<(ostream &out, Contract &x)
    {
        x.afisare(out);
        return out;
    }

    virtual void calcul_discount()=0;
    Contract(int disc=0) : discount(disc){}
};

class Chirie : public Contract
{
protected:
     char nume[50];
     Data di,df;
public:
    virtual void calcul_chirie()=0;

    void calcul_discount()
    {
        int x,y,z,t;
        x=di.Get_luna();
        y=di.Get_an();
        z=df.Get_luna();
        t=df.Get_an();

        if(z+t*12-x-y*12>24)
            discount=10;
        else if(z+t*12-x-y*12>12)
            discount = 5;
        else discount =0;
    }

    Chirie(double disc,char *nume=NULL,Data di={0,0},Data df={0,0}) : Contract(disc),di(di),df(df)
    {
        strcpy(nume,nume);
        this->calcul_discount();
    }

    void citire(istream &in)
    {
        in>>nume>>di>>df;
    }

    void afis(ostream &out)
    {
        out<<nume<<" "<<di<<" -> "<<df<<" ";
    }
};

class Chirie_apart : public Chirie
{
protected:
   double CLA;
   Apartament a;
public:

    void calcul_chirie()
    {
        CLA=a.Get_pret_mp()*a.Get_suprafara()*(100-discount);
        CLA=CLA/100.0;
    }

    Chirie_apart(int disc=0,char nume[]=NULL,Data di={0,0},Data df={0,0},double CLA=0,Apartament a={0,0}) : Chirie(disc,nume,di,df), CLA(CLA),a(a){this->calcul_chirie();}

    void citire(istream &in)
    {
        Chirie::citire(in);
        in>>a;
    }

    void afis(ostream &out)
    {
        Chirie::afisare(out);
        out<<a<<" ";
    }

};

class Chirie_casa : public Chirie
{
    protected:
   double CLC;
   Casa c;
public:

    void calcul_chirie()
    {
        CLC=c.Get_pret_mp()*c.Get_suprafara()*(100-discount);
        CLC=CLC/100.0;
    }

    Chirie_casa(int disc=0,char nume[]=NULL,Data di={0,0},Data df={0,0},double CLC=0,Casa c={0,0}) : Chirie(disc,nume,di,df), CLC(CLC),c(c){this->calcul_chirie();}

    void citire(istream &in)
    {
        Chirie::citire(in);
        in>>c;
    }

    void afis(ostream &out)
    {
        Chirie::afisare(out);
        out<<c<<" ";
    }

};


class Vanzare : public Contract
{
protected:
    char nume[50];
     Data di,df;
public:

    virtual void calcul_vanzare()=0;

    void calcul_discount()
    {
        int x,y,z,t;
        x=di.Get_luna();
        y=di.Get_an();
        z=df.Get_luna();
        t=df.Get_an();

        int rez=t*12+z-y*12-x;
        if(rez==0)
            discount=0;
        else if(rez<=60)
            discount =7;
        else if(rez<=120)
            discount =5;
    }

    Vanzare(double disc=0,char nume[50]=NULL,Data di={0,0},Data df={0,0}) : Contract(disc),di(di),df(df)
    {
        strcpy(nume,nume);
        this->calcul_discount();
    }


};

class Vanzare_apart : public Vanzare
{
protected:
    double CLC;
    Apartament a;
public:
    void calcul_vanzare()
    {
        double CLA;

        CLA=a.Get_pret_mp()*a.Get_suprafara()*(100-discount);
        CLA=CLA/100.0;

        CLC=240 * CLA * (100-discount);
        CLC=CLC/100.0;
    }

    Vanzare_apart(double disc=0,char nume[50]=NULL,Data di={0,0},Data df={0,0},double CLC=0,Apartament a={0,0}) : Vanzare(disc,nume,di,df), CLC(CLC),a(a)
    {
        this->calcul_vanzare();
    }
};

class Vanzare_casa : public Vanzare
{
    protected:
    double CLC;
    Casa c;
public:
    void calcul_vanzare()
    {
        double CLA;

        CLA=c.Get_pret_mp()*c.Get_suprafara()*(100-discount);
        CLA=CLA/100.0;

        CLC=240 * CLA * (100-discount);
        CLC=CLC/100.0;
    }

    Vanzare_casa(double disc=0,char nume[50]=NULL,Data di={0,0},Data df={0,0},double CLC=0,Casa c={0,0}) : Vanzare(disc,nume,di,df), CLC(CLC),c(c)
    {
        this->calcul_vanzare();
    }
};

int main()
{
    /// am gresit clasa de baza Contract. Trebuia sa aiba si numele + cele 2 perioade
    vector<Proprietate*>P;
    vector<Contract*>C;
    int nrP=0,nrC=0,i,tip,j;
    cout<<"Introduceti numarul de proprietati: ";cin>>nrP;
    for(i=0;i<nrP;i++)
    {
        Proprietate *v;
        cout<<"\n\nIntroduceti 1-casa\n2-apartament: ";cin>>tip;

        if(tip==1)
            v=new Casa;
        else v=new Apartament;

        cin>>*v;
        P.push_back(v);
    }

    cout<<"Introduceti numarul de contracte: ";cin>>nrC;

    for(i=0;i<nrC;i++)
    {
        Contract *v;
        cout<<"\n\nIntroduceti 1-chirie casa\n2-chirie apartament\n3-vanzare casa\n4-vanzare apartament\n";
        if(tip==1)
            v= new Chirie_casa;
        else if(tip==2)
            v= new Chirie_apart;
        else if(tip==3)
            v= new Vanzare_casa;
        else if(tip==4)
            v= new Vanzare_apart;
        else cout<<"Introduceti una din valorile 1->4",i--;

        cin>>*v;
        C.push_back(v);
    }

    return 0;
}
