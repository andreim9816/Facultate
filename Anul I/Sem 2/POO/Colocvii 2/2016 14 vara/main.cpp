#include <iostream>
#include<vector>
#include<string>
using namespace std;

class Ingredient
{
    string denIng;
    double pretIng;
    int cantIng;
    string masIng;

public:

    int Get_cantIng()
    {
        return cantIng;
    }

    double Get_pretIng()
    {
        return pretIng;
    }

    Ingredient(string den="",double pret=0.0,int cant=0,string mas="") : denIng(den),pretIng(pret),cantIng(cant),masIng(mas) {}

    Ingredient(const Ingredient &x)
    {
        denIng=x.denIng;
        pretIng=x.pretIng;
        cantIng=x.cantIng;
        masIng=x.masIng;
    }

    Ingredient & operator=(const Ingredient &x)
    {
        if(this !=&x)
        {
            denIng=x.denIng;
            pretIng=x.pretIng;
            cantIng=x.cantIng;
            masIng=x.masIng;
        }
        return *this;
    }

    ~Ingredient()
    {
        denIng=masIng="";
        pretIng=0.0;
        cantIng=0;
    }

    friend istream & operator >> (istream &in, Ingredient&x)
    {
        in>>x.denIng>>x.pretIng>>x.cantIng>>x.masIng;
        return in;
    }

    friend ostream &operator <<(ostream &out, Ingredient &x)
    {
        out<<x.cantIng<<" "<<x.denIng <<" "<<x.pretIng<<" "<<x.masIng<<" ";
        return out;
    }

    friend Ingredient operator + (const Ingredient x, int y)
    {
        Ingredient aux=x;
        aux.cantIng+=y;
        return aux;
    }

    friend Ingredient operator - (const Ingredient x,int y)
    {
        Ingredient aux=x;
        aux.cantIng-=y;
        return aux;
    }

    friend Ingredient operator +(const Ingredient x, double y)
    {
        Ingredient aux=x;
        aux.pretIng+=y;
        return aux;
    }

    friend Ingredient operator -(const Ingredient x, double y)
    {
        Ingredient aux=x;
        aux.pretIng-=y;
        return aux;
    }

    friend Ingredient operator++(Ingredient &x,int ) // postfix
    {
        x.cantIng++;
        return x;
    }

    friend Ingredient operator--(Ingredient &x,int ) // postfix
    {
        x.cantIng--;
        return x;
    }

    friend Ingredient operator-=(Ingredient&x,int y)
    {
        x.cantIng-=y;
        return x;
    }

    friend Ingredient operator-=(Ingredient&x,double y)
    {
        x.pretIng-=y;
        return x;
    }

    friend bool operator == (const Ingredient &x, const Ingredient &y)
    {
        if(x.denIng == y.denIng )
            return true;
        return false;
    }

    void del()
    {
        denIng="";
        masIng="";
        cantIng=0;
        pretIng=0.0;
    }
};

class Pizza
{
    static int codPizza;
    string denPizza;
    vector<Ingredient>ingPizza;
    int nringPizza;
    bool vegPizza;
public:
    Pizza(string den="", vector<Ingredient>ing={Ingredient()},int nring=0,bool veg=false ) : denPizza(den),ingPizza(ing),nringPizza(nring),vegPizza(veg){codPizza++;}

    Pizza(const Pizza&x) : denPizza(x.denPizza), ingPizza(x.ingPizza), nringPizza(x.nringPizza),vegPizza(x.vegPizza) { }

    Pizza & operator= (const Pizza &x)
    {
        if(this != &x)
        {
            denPizza=x.denPizza;
            ingPizza=x.ingPizza;
            nringPizza=x.nringPizza;
            vegPizza=x.vegPizza;
        }
        return *this;
    }

    ~Pizza()
    {
        denPizza="";
        ingPizza.clear();
        nringPizza=0;
        vegPizza=false;
    }

    friend Pizza operator -(Pizza &x, Ingredient y)
    {
        int i;
        Pizza aux=x;

        for(i=0;i<aux.nringPizza;i++)
            if(aux.ingPizza[i] == y)
                {
                    aux.ingPizza.erase(aux.ingPizza.begin()+i);
                    aux.nringPizza--;
                    i--;
                }
        return aux;
    }

    friend Pizza operator+(Pizza &x, Ingredient &y)
    {
        Pizza aux=x;
        cout<<aux<<"\n";
        aux.nringPizza++;
        aux.ingPizza.push_back(y);
        cout<<aux;
        return aux;
    }

    string nume()
    {
        return denPizza;
    }

    double pret()
    {
        int i;
        double s=0;
        for(i=0;i<nringPizza;i++)
            s+= ingPizza[i].Get_cantIng() * ingPizza[i].Get_pretIng();
        return s;
    }

    friend ostream & operator <<(ostream &out, Pizza &x);
};
int Pizza :: codPizza=0;

ostream & operator <<(ostream &out, Pizza &x)
{
    out<<x.denPizza;
    if(x.vegPizza == true)
    out<<" vegetariana ";
    else out<<" NEvegetariana ";

    for(int i=0;i<x.nringPizza;i++)
        cout<<x.ingPizza[i]<<" ";

    return out;
}

int main()
{
    vector<Ingredient>lista;
    lista.resize(5);
    lista[1]=Ingredient("sare",0.75, 10, "gram");
    lista[0]=Ingredient("piept de pui", 15, 1, "kg");
    lista[2]=Ingredient("salam",1.5,5, "felii");
    lista[3]=lista[2];
    lista[4]=Ingredient();

  //  for (int i=0; i<5; i++)
   //     cout<<"Ingredient: "<<lista[i]<<endl;

    Ingredient i1("sunca", 3, 2, "felii");

    lista[3] = lista[3] + 3;
    lista[1]++;
    lista[0]-=2.5;
    lista[2].del();


    for (int i=0; i<5; i++)
        cout<<"Ingredient: "<<lista[i]<<endl;

    Pizza p1 ("Rustica", lista, 5, false);

    Pizza p2 = p1, p3;
    p2 = p2-lista[2];

    p3 = p2 + i1;
    cout<<p3;
    p3.nume("Prosciuto");

    cout<<"Pizza "<<p1.nume()<<" "<<p1.pret()<<" lei"<<endl;
    cout<<"Pizza "<<p2.nume()<<" "<<p2.pret()<<" lei"<<endl;
    cout<<"Pizza "<<p3.nume()<<" "<<p3.pret()<<" lei";

    return 0;
}