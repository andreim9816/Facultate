#include <iostream>
#include<fstream>
#include<vector>
#include<cstring>
#include<set>
using namespace std;

ifstream fin("date.in");

class Persoana
{
    char CNP[13];
    string nume;
public:

    string get_nume()
    {
        return nume;
    }

    char * get_cnp()
    {
        return CNP;
    }

    Persoana(char cnp[],string numee)
    {
        strcpy(CNP,cnp);
        nume=numee;
    }

    Persoana()
    {
        CNP[0]='\0';
        nume="";
    }

    friend istream & operator >> (istream &in, Persoana &x)
    {
        in>>x.CNP>>x.nume;
        return in;
    }

    friend ostream & operator <<(ostream &out, Persoana &x)
    {
        out<<x.CNP<<" "<<x.nume<<" ";
        return out;
    }
};

class Data
{
    int zi,luna,an;

    public:
    Data(int zi=0,int luna=0,int an=0) : zi(zi),luna(luna),an(an){}

    friend class Activitati;
    friend class Concurs_online;

    friend istream & operator >> (istream &in, Data &x)
    {
        in>>x.zi>>x.luna>>x.an;
        return in;
    }

    friend ostream & operator <<(ostream & out, Data &x)
    {
        out<<x.zi<<"."<<x.luna<<"."<<x.an;
        return out;
    }

    friend bool operator ==(Data &x,Data &y)
    {
        return (x.zi == y.zi && x.an == y.an && x.luna == y.luna);
    }
};

class Activitati
{
protected:
    string denumire;
    Data di;
    int indice;
    vector<Persoana>v;
public:
    Activitati(string x="",Data d={0,0,0},int indice=0) :denumire(x),di(d),indice(indice){}

    void sortare_alfabetic()
    {
        int i,j;
        for(i=0;i<v.size()-1;i++)
            for(j=i+1;j<v.size();j++)
            if(v[i].get_nume() > v[j].get_nume())
        {
            Persoana aux;

            aux=v[i];
            v[i]=v[j];
            v[j]=aux;
        }
    }

    void aduna_persoane(vector<Persoana> &w, Data x)
    {
        int i;

        if(x == di)
        {
            for(i=0;i<v.size();i++)
                w.push_back(v[i]);
        }
    }

    void afis_vector()
    {
        this->sortare_alfabetic();
        for(auto i:v)
            cout<<i<<" ";
    }

    void add(Persoana x)
    {
        v.push_back(x);
        indice++;
    }

    void add_n_persoane()
    {
        int n;
        int i;
        Persoana p;
        cout<<"Introduceti nr de persoane : ";fin>>n;
        for(i=1;i<=n;i++)
        {
            fin>>p;
            this->add(p);
        }
    }

    friend istream & operator >> (istream & in, Activitati &x)
    {
        x.citire(in);
        return in;
    }

    friend ostream & operator << (ostream & out, Activitati &x)
    {
        x.afis(out);
        return out;
    }

    virtual void citire(istream &in)
    {
        in>>denumire>>di;
    }

    virtual void afis(ostream &out)
    {
        out<<denumire <<" "<<di<<" ";
    }
};

class Concurs : public Activitati
{
public:
    Concurs(){}
    void citire(istream & in)
    {
        this->Activitati::citire(in);
    }

    void afis(ostream & out)
    {
        this->Activitati::afis(out);
    }
};

class Curs : public Activitati
{
    int credite;
public:
    Curs(int x=0) : credite(x) {}

    void citire(istream &in)
    {
        this-> Activitati :: citire(in);
        in>>credite;
    }

    void afis(ostream & out)
    {
        this->Activitati::afis(out);
        out<<credite<<" ";
    }
};

class Concurs_offline : public Concurs
{
      vector<pair<int,Persoana> >v;
public:
    Concurs_offline(vector<pair<int,Persoana> >w):v(w){ }

    Concurs_offline()
    {

    }
    void citire(istream &in)
    {
        this->Concurs::citire(in);
    }

    void afis(ostream & out)
    {
        this->Concurs::afis(out);
    }
};

class Concurs_online : public Concurs
{
    string site;
    Data df;
    vector<pair<int,Persoana> > v;
public:
    Concurs_online(string x, Data d, vector<pair<int,Persoana > >w =vector<make_pair(int 0,Persoana a=0)>) : site(x), df(d),v(w){}
    Concurs_online()
    {
        site="";
        df={0,0,0};
    }
    void citire(istream &in)
    {
        this->Concurs::citire(in);
        in>>site>>df;
    }

    void afis(ostream & out)
    {
        this->Concurs::afis(out);
        out<<site<<" "<<df<<" ";
    }

};

void sortare_alfabetic_vector(vector<Persoana>&v)
{
    int i,j;
    for(i=0;i<v.size()-1;i++)
        for(j=i+1;j<v.size();j++)
        if(v[i].get_nume() > v[j].get_nume())
        {
            Persoana p;
            p=v[i];
            v[i]=v[j];
            v[j]=p ;
        }
}

int main()
{
    Curs CP1,CP2,CP3;
    Concurs_offline CT1,CT2;
    Concurs_online CT3,CT4;

    int i,n;
    Persoana P;

    fin>>CP1;
    CP1.add_n_persoane();

    fin>>CP2;
    CP2.add_n_persoane();

    fin>>CP3;
    CP3.add_n_persoane();

    fin>>CT1;
    CT1.add_n_persoane();

    fin>>CT2;
    CT2.add_n_persoane();

    fin>>CT3;
    CT3.add_n_persoane();

    fin>>CT4;
    CT4.add_n_persoane();

    vector<Persoana>w;
    Data D;
    fin>>D;

    CP1.aduna_persoane(w,D);
    CP2.aduna_persoane(w,D);
    CP3.aduna_persoane(w,D);
    CT1.aduna_persoane(w,D);


    sortare_alfabetic_vector(w);
for(int i=0;i<w.size();i++)
        cout<<w[i].get_nume()<<endl;

    return 0;
}
