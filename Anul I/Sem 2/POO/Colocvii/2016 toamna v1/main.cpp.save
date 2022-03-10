#include <iostream>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>
using namespace std;

ifstream fin("date.in");

class Cerere
{
protected:
     int video,ecran,tabla;
public:
    Cerere(int video = 0,int ecran = 1, int tabla = 0) : video(video),ecran(ecran),tabla(tabla) {}
    Cerere(const Cerere &x) : video(x.video),ecran(x.ecran),tabla(x.tabla){}
    Cerere & operator = (const Cerere &x)
    {
        if(this != &x)
        {
            video=x.video;
            tabla=x.tabla;
            ecran=x.ecran;
        }
        return *this;
    }
    friend istream & operator >> (istream &in, Cerere&x)
    {
        x.citire(in);
        return in;
    }

    virtual void citire(istream &in)
    {
        in>>video>>ecran>>tabla;
    }

    int get_ecran()
    {
        return ecran;
    }

    int get_tabla()
    {
        return tabla;
    }

    int get_video()
    {
        return video;
    }
};

class Home : public Cerere
{
public:
    Home(int video = 0,int ecran = 1, int tabla = 0) : Cerere(video,ecran,tabla){}
    Home (const Home & x) : Cerere(x.video,x.ecran,x.tabla){}
    Home & operator = (const Home &x) /// ATENTIE TRB  PUS MEREU CONST
    {
        if(this != &x)
        {
            this-> Cerere :: operator=(x);
        }
        return *this;
    }

    void citire(istream &in)
    {
        this-> Cerere::citire(in);
    }

    string Home_verificare()
    {
        if(video == 1 && ecran ==1 && tabla == 0)
            return "OK";
        if(video == 0 && ecran == 0 && tabla == 1)
            return "OK";
        if(video == 0 && ecran == 0 && tabla == 0)
            return "OK";
        return "Nu am inteles cerinta!";
    }

    void Home_opreste(string x)
    {
        if(x == "tabla")
            tabla = 0;
        else if(x == "ecran")
            ecran = 0;
        else if(x == "video")
            video = 0;
    }

    void Home_porneste(string x)
    {
        if(x == "tabla")
            tabla = 1;
        if(x == "ecran")
            ecran = 1;
        if(x == "video")
            video = 1;
    }

    friend Home operator +(Home &ob, int x)
    {
        if(x==1)
           ob.Home_porneste("video");
        else if(x==2)
            ob.Home_porneste("ecran");
        else if(x==3)
            ob.Home_porneste("tabla");

        return ob;
    }

    friend Home operator -(Home &x,int nr)
    {
        if(nr==1)
           x.Home_opreste("video");
        else if(nr==2)
            x.Home_opreste("ecran");
        else if(nr==3)
            x.Home_opreste("tabla");

        return x;
    }

    friend Home operator + (Home&x, char c)
    {
        if(c=='E')
            x.Home_porneste("ecran");
        else if(c=='T')
            x.Home_porneste("tabla");
        else if(c=='V')
            x.Home_porneste("video");
        return x;
    }

    friend Home operator - (Home&x, char c)
    {
        if(c=='E')
            x.Home_opreste("ecran");
        else if(c=='T')
            x.Home_opreste("tabla");
        else if(c=='V')
            x.Home_opreste("video");
        return x;
    }
};

class Education : public Cerere
{
public:
    Education(Education &x) : Cerere(x){}
    Education(int video=0, int ecran = 0, int tabla =0) : Cerere(video,ecran,tabla){}
    Education & operator = (const Education &x)
    {
        if(this != &x)
        {
            this->Cerere::operator=(x);
        }
        return *this;
    }
    string Edu_Trivia(string x)
    {
        string aux="Cautare"+x;
        return aux;
    }

    string Edu_Lectie(string x,int y)
    {
        if(this->get_ecran() == 1 && this->get_tabla()==0 && this->get_video() == 1)
        {
            string aux;
            string aux2;
            ostringstream convert;
            convert << y;
            aux2=convert.str();
            aux="Download - " + x + " - Curs " + aux2;
            return aux;
        }
        return "Eroare componenta hardware";
    }

    void citire(istream &in)
    {
        this->Cerere::citire(in);
    }
};

int main()
{
    Home h1,h2(1),h3(0,0,1);
    cin>>h1;
    h2.Home_opreste("tabla");
    Home h4(h2),h5=h2;
    h4=h4+1;
    h4=h4+'E';

    cout<<h1.Home_verificare()<<" "<<h2.Home_verificare()<<" "<<h4.Home_verificare();

    Education e1,e2(1),e3(1,1,0),e4(e3);
    cin>>e1;
    cout<<endl<<e4.Edu_Lectie("Algebra",3);
    cout<<endl<<e2.Edu_Trivia("Data structures");
    cout<<endl<<e2.Edu_Lectie("POO",2);

    Cerere *c=new Cerere[4];
    c[0]=;
    c[1]=h4;
    c[2]=e3;
    c[3]=e4;
    for(int i =0;i<4;i++)
        cout<<c[i].get_video()<<" "<<c[i].get_ecran()<<" "<<c[i].get_tabla()<<endl;

    return 0;
}
