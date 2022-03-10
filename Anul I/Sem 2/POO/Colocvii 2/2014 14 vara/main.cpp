#include <iostream>
#include<fstream>
#include<vector>
using namespace std;

ifstream fin("date.in");

class Data
{
    int zi,luna,an;
public:
    Data(int x=0,int y=0,int z=0) :zi(x),luna(y),an(z){}

    Data & operator = (const Data &ob)
    {
        if(this != &ob)
        {
            zi=ob.zi;
            luna=ob.luna;
            an=ob.an;
        }
        return *this;
    }

    Data (const Data &x)
    {
        zi=x.zi;
        an=x.an;
        luna=x.luna;
    }

    ~Data()
    {
        zi=luna=an=0;
    }

    friend istream & operator >> (istream &in, Data&x)
    {
        in>>x.zi>>x.luna>>x.an;
        return in;
    }

    friend ostream & operator << (ostream &out, Data &x)
    {
        out<<x.zi<<" "<<x.luna<<" "<<x.an;
        return out;
    }
};

class Referinta
{
public:
    Referinta(){}
    ~Referinta(){}

    virtual void citire(istream &in)=0;
    virtual void afisare(ostream & out)=0;

    virtual string get_nume_clasa()
    {
        return "Referinta";
    }

    virtual int verif_an(int x)
    {
        return 0;
    }

    virtual int verif_nume(string nume)
    {
        return 0;
    }

    friend istream & operator >> (istream &in, Referinta &ob)
    {

        ob.citire(in);
        return in;
    }

    friend ostream & operator << (ostream &out, Referinta &ob)
    {
        ob.afisare(out);
        return out;
    }
};


class Bibliografie : public Referinta
{
protected:
    vector<pair<string,string> >v;
    string titlu;
    int an;

public:



    string get_nume_clasa()
    {
        return "Bibliografie";
    }
    int verif_an(int an1)
    {
        return an == an1;
    }

    int verif_nume(string nume)
    {
        int i;
        for(i=0;i<v.size();i++)
            if(nume == v[i].first)
            return 1;
        return 0;
    }

    Bibliografie(vector<pair<string,string> >w, string nume="",int an=0) :titlu(nume),an(an){v =w;}
    Bibliografie()
    {
        titlu=an=0;

    }
    Bibliografie & operator = (const Bibliografie &x)
    {
        if(this != &x)
        {
            this->Referinta :: operator =(x);
            titlu=x.titlu;
            an=x.an;
            v=x.v;
        }
        return *this;
    }

    Bibliografie (const Bibliografie &x) : Referinta(x)
    {
        an=x.an;
        titlu=x.titlu;
        v=x.v;

    }

    ~Bibliografie()
    {
        an=0;
        titlu="";
        v.clear();
    }

  void citire(istream &in)
    {
    //    this->Referinta :: citire(in);

        int x,i;
        string nume,prenume;
        cout<<"Cati autori : ";in>>x;
   //     in.get();

        for(i=1;i<=x;i++)
        {
            in>>nume>>prenume;
            v.push_back({nume,prenume});
        }

        cout<<"Introduceti titlul si anul :";
         in>>titlu;
         in>>an;
    }

    void afisare(ostream &out)
    {
  //      this->Referinta :: afisare(out);

        for (auto p:v)
            out<<p.first<<" "<<p.second[0]<<" ";
        out<<titlu<<" "<<an<<" ";
    }
};

class Articol : public Bibliografie
{
    string nume_revista;
    int nr;
    int pag1,pag2;
public:
    Articol(string nume="",int nr=0,int pag1=0,int pag2=0) : nume_revista(nume),nr(nr),pag1(pag1),pag2(pag2) { }

    string get_nume_clasa()
    {
        return "Articol";
    }

    Articol & operator = (const Articol &x)
    {
        if(this != &x)
        {
            this->Bibliografie :: operator=(x);
            nume_revista=x.nume_revista;
            nr=x.nr;
            pag1=x.pag1;
            pag2=x.pag2;
        }
        return *this;
    }

    Articol (const Articol &x) : Bibliografie(x), nume_revista(x.nume_revista),nr(x.nr), pag1(x.pag1),pag2(x.pag2){}

    void citire(istream &in)
    {
        this->Bibliografie :: citire(in);
        cout<<"Introduceti numele revistei, numarul si paginile ";

        in >> nume_revista>>nr>>pag1>>pag2;
    }

    void afisare(ostream &out)
    {
        this->Bibliografie :: afisare(out);
        out<<nume_revista<<","<<nr<<","<<pag1<<"-"<<pag2<<" ";
    }

};

class Carte : public Bibliografie
{
    string nume_editura,oras;
public:
    Carte(string nume="",string oras="") : Bibliografie(), nume_editura(nume),oras(oras) { }

    string get_nume_clasa()
    {
        return "Carte";
    }

    Carte( const Carte &x) : Bibliografie(x)
    {
        nume_editura = x.nume_editura;
        oras = x.oras;
    }

    Carte & operator= (const Carte &x)
    {
        if(this != &x)
        {
            this->Bibliografie :: operator=(x);
            nume_editura = x.nume_editura;
            oras = x.oras;
        }
        return *this;
    }

    void citire(istream &in)
    {
        this->Bibliografie :: citire(in);
        cout<<"Introduceti numele_editurii si orasul ";
        in>>nume_editura>>oras;
    }

    void afisare(ostream &out)
    {
        this->Bibliografie :: afisare(out);
        out<<nume_editura<<","<<oras<<" ";
    }
};

class Web : public Referinta
{
    string nume,titlu,URL;
    Data d;
public:

    int verif_nume(string x)
    {   cout<<"DA";
        return x == nume;
    }

    Web(string titlu="",string URL="",Data d={0,0,0}, string nume="***") : nume(nume),titlu(titlu),URL(URL),d(d) {}

    Web & operator = (const Web &ob)
    {
        if(this !=&ob)
        {
            nume=ob.nume;
            titlu=ob.titlu;
            URL=ob.URL;
            d=ob.d;
        }

        return *this;
    }

    Web (const Web & ob)
    {
        nume=ob.nume;
        titlu=ob.titlu;
        URL=ob.URL;
        d=ob.d;
    }

    void citire(istream &in)
    { cout<<"2 ";
      //  this->Referinta :: citire(in);
        cout<<"Introduceti numele, titlul,URL-ul si data";
        in>>nume>>titlu>>URL>>d;
    }

    void afisare(ostream &out)
    {
    //    this->Referinta :: afisare(out);
        out<<nume<<" "<<titlu<<" "<<URL<<" accesat pe "<<d;
    }

};


int main()
{

 try
 {

    Referinta **v;
    int n,i;
    cout<<"Introduceti numarul de referinte ";cin>>n;

    v=new Referinta*[n];
    if(!v)
        throw 1;
    for(i=1;i<=n;i++)
    {
        cout<<"1.Articol\n2.Carte\n3.Web\n";
        int tip;
        cin>>tip;

        if(tip == 1)
            v[i]=new Articol;
        else if(tip == 2)
            v[i] = new Carte;
        else v[i] = new Web;

        cin>>*v[i];

    }
        cout<<endl;
        for(i=1;i<=n;i++)
        cout<<*v[i]<<" "<<v[i]->get_nume_clasa()<<endl;

    bool ok=true;
    while(ok)
    {
        cout<<"1. Afisare toate referinte\n2.Afisare referinte tiparite dintr-un an\n3.Afisare referinta tiparite care au un anumit autor(dat prin nume)\n";
        cout<<"4. Afisare toate toate referintele web care au un anumit proprietar(dat prin nume)\n";
        int alegere;
        cin>>alegere;

        if(alegere  == 1)
        {
            for(i=1;i<=n;i++)
                cout<<*v[i]<<" ";
        }

        else if(alegere == 2)
        {
            int an;
            cout<<"Introduceti anul ";cin>>an;
            for(i=1;i<=n;i++)
                if( (v[i])->get_nume_clasa()== "Articol" ||(v[i])->get_nume_clasa()== "Carte")
                    if(v[i]->verif_an(an))
                        cout<<*v[i]<<" ";
        }
        else if(alegere == 3)
        {
            string nume;
            cout<<"Introduceti numele ";
            cin>>nume;
            for(i=1;i<=n;i++)
                 if( (v[i])->get_nume_clasa()== "Articol" ||(v[i])->get_nume_clasa()== "Carte")
                 if(v[i]->verif_nume(nume))
                    cout<<*v[i]<<" ";
        }
        else if(alegere == 4)
        {
            string nume;
            cout<<"Introduceti numele";cin>>nume;
            for(i=1;i<=n;i++)
                if(v[i]->get_nume_clasa() == "Web")
                if(v[i]->verif_nume(nume))
                    cout<<*v[i]<<" ";
        }
        else break;
    }
}
 catch(int e)
 {
     cout<<"Nu s-a putut aloca";
 }

    return 0;

}
