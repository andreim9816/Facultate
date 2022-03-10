#include <iostream>

using namespace std;

double Prima;

class Lucrativ;
class Plata_Ora;

class Data
{
    int zi,luna,an;
public:

    friend Lucrativ;
    friend Plata_Ora;

    Data(int x=0,int y=0,int z=0) : zi(x),luna(y),an(z){}
    Data & operator =(const Data&x)
    {
        if(this != &x){
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

    ~Data()
    {
        zi=luna=an=0;
    }

    friend istream & operator >> (istream &in, Data&x)
    {
        in>>x.zi>>x.luna>>x.an;
        return in;
    }

    friend ostream & operator <<(ostream &out, Data &x)
    {
        out<<x.zi<<"."<<x.luna<<"."<<x.an<<" ";
        return out;
    }
};

class Angajat
{
protected:
    string nume,prenume;
    double prima;
    Data d1;
public:

    Angajat(string n="",string prenume="",Data d={0,0,0})
    {
        nume=n;
        prenume=prenume;
        prima= Prima;
        d1=d;
    }

    Angajat(const Angajat& x)
    {
        nume=x.nume;
        prenume=x.prenume;
        prima =x.prima;
        d1=x.d1;
    }

    virtual void set_prima()=0;

    Angajat& operator= (const Angajat &x)
    {
        if(this !=&x)
        {
            nume=x.nume;
            prenume=x.prenume;
            prima = x.prima;
            d1=x.d1;
        }
        return *this;
    }

    virtual void citire(istream &in)
    {
        in>>nume>>prenume>>d1;
    }

    virtual void afisare(ostream &out)
    {
         out<<nume<<" "<<prenume<<" iar prima este "<<prima<<" "<<" Contractul incepe pe "<<d1<<" ";
    }

    friend ostream & operator<<(ostream &out,Angajat &x)
    {
        x.afisare(out);
        return out;
    }

    friend istream & operator >>(istream &in, Angajat &x)
    {
        x.citire(in);
        return in;
    }
};

class Permanent : public Angajat
{
public:

    void set_prima()=0;

    void citire(istream &in)
    {
        this->Angajat :: citire(in);
    }

    void afisare(ostream &out)
    {
        this->Angajat :: afisare(out);
    }

};

class TESA : public Permanent
{
    int weekend;
public:
    TESA(int we=0) : weekend(we){}

    TESA(const TESA&x) : Permanent(x)
    {
        weekend=x.weekend;
    }

    int Get_weekend()
    {
        return weekend;
    }

    TESA & operator=(const TESA &x)
    {
        if(this !=&x)
        {
            this->Permanent :: operator=(x);
            weekend=x.weekend;
        }
        return *this;
    }

    void citire(istream &in)
    {
        this->Permanent :: citire(in);
        in>>weekend;
        this->set_prima();
    }

    void afisare(ostream & out)
    {
        this->Permanent :: afisare(out);
        out << " weekend "<<weekend<<" ";
    }

    void set_prima()
    {
        prima=Prima;
    }

    ~TESA()
    {
        weekend=0;
    }
};

class Lucrativ : public Permanent
{
    int copii;
public:
    Lucrativ(int copii = 0) : copii(copii){}
    Lucrativ ( const Lucrativ & ob)
    {
        copii=ob.copii;
    }

    Lucrativ & operator=(const Lucrativ&x)
    {
        if(this != &x)
            {
                copii=x.copii;
            }
        return *this;
    }

    ~Lucrativ()
    {
        copii=0;
    }

    int Get_copii()
    {
        return copii;
    }

    void set_prima()
    {
        int ani_vech = 2019 - d1.an;
        double s=(copii*ani_vech*Prima) /100.0;
        prima=s+Prima;
    }

    void citire(istream &in)
    {
        this->Permanent :: citire(in);
        in>>copii;
        this->set_prima();
    }

    void afisare(ostream &out)
    {
        this->Permanent :: afisare(out);
        out<<copii<<" copii ";
    }

};

class Plata_Ora : public Angajat
{
    Data d2;
public:
    Plata_Ora(Data d={0,0,0}, double s=0.0) : d2(d) { }
    Plata_Ora(const Plata_Ora &x) : Angajat(x)
    {
        d2=x.d2;
    }

    Plata_Ora & operator=(const Plata_Ora &x)
    {
        if(this != &x)
        {
            this->Angajat :: operator=(x);
              d2=x.d2;
        }
        return *this;
    }

    void citire(istream &in)
    {
        this-> Angajat :: citire(in);
        in>>d2;
    }

    void afisare(ostream &out)
    {
        this->Angajat :: afisare(out);
        out<<"si se termina pe "<<d2;
    }

    void set_prima()
    {
        if(d2.an <=2019 && d2.luna<=12 && d2.zi<=31)
            prima=Prima/2.0;
        else prima=Prima;
    }

    int verif_martie_2005()
    {
        if(d2.luna == 3 && d2.an == 2005)
            return 1;
        return 0;
    }
};

int main()
{

    try{
    cout<<"Introduceti prima ";
    cin>>Prima;

    Angajat **v;
    int n,i;
    cout<<"Introduceti n";cin>>n;
    v=new Angajat*[n];
    if(!v)
        throw 1;
    for(i=0;i<n;i++)
    {
        cout<<"\n1. TESA\n2. Lucrativ\n3. Plata cu ora\n";
        int opt;
        cin>>opt;
        if(opt == 1)
            v[i] = new TESA;
        else if(opt == 2)
            v[i] = new Lucrativ;
        else if(opt == 3)
            v[i] = new Plata_Ora;
        else {cout<<"introduceti din nou un numar bun";i--;}

        cin>>*v[i];
    }

    int ok=1;

    while(ok)
    {
        cout<<"\n0.Iesire\n1.Afiseaza toti angajatii\n2. Angajatii lucrativi permanenti cu copii\n3. Angajatii care isi fac rezervare la munte in al doilea weekend\n4.\n";
        cin>>ok;
        switch(ok)
        {
        case 0: ok=0; break;
        case 1:
            {
                for(i=0;i<n;i++)
                    cout<<*v[i]<<" ";
                cout<<endl;

            } break;

        case 2:
            {
                for(i=0;i<n;i++)
                {
                    Lucrativ*aux=dynamic_cast<Lucrativ*>(v[i]);
                    if(aux)
                        if(aux->Get_copii() >0)
                        cout<<*v[i]<<"\n";
                }
            }
            break;
        case 3:
            {
                  for(i=0;i<n;i++)
                  {
                      TESA*aux=dynamic_cast<TESA*>(v[i]);
                      if(aux)
                        if(aux->Get_weekend() == 2)
                        cout<<*v[i]<<"\n";
                  }
            }
            break;
        case 4:
            {
                for(i=0;i<n;i++)
                {
                    Plata_Ora*aux=dynamic_cast<Plata_Ora*>(v[i]);
                    if(aux)
                        if(aux->verif_martie_2005())
                        cout<<*v[i]<<"\n";
                }
            }
            break;
        }
    }

    }
    catch(int e)
    {
        cout<<"nu s a putut aloca memorie";
    }
    return 0;
}
