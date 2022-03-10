#include <iostream>

using namespace std;

class Persoana
{
protected:
    string nume;
public:
    Persoana(string n="") : nume(n){}

    Persoana(Persoana &x)
    {
        cout<<"CC Persoana\n";
        nume=x.nume;
    }

    Persoana & operator=(Persoana &x)
    {

        nume=x.nume;
        return *this;
    }

    virtual void afisare()
    {
        cout<<nume<<" ";
    }

    virtual ~Persoana()
    {
        nume="";
    }
};

class Student : virtual public Persoana
{
protected:
    int an;
    string facultate;
public:
    Student(int a=0,string f="",string nume="") :Persoana(nume), an(a), facultate(f){}

    Student(Student &x) : Persoana(x)
    {
        cout<<"CC Student\n";
        an=x.an;
        facultate=x.facultate;
    }

    void afisare()
    {
        this->Persoana::afisare();
        cout<<an<<" "<<facultate<<endl;
    }
};

class Angajat : virtual public Persoana
{
protected:
    int salariu;
   public:
       Angajat(int s=0,string nume="") : Persoana(nume), salariu(s){}

       Angajat(Angajat &x) : Persoana(x)
       {    cout<<"CC Ang\n";
           salariu=x.salariu;
       }

       void afisare()
       {
           this->Persoana :: afisare();
           cout<<salariu <<" ";
       }
};

class Stud_ang : public Angajat, public Student
{
public:
    Stud_ang(int salar=0,int an=0,string fac="",string num=""): Persoana(num),Angajat(salar),Student(an,fac){}

    Stud_ang(Stud_ang &x) : Persoana(x),Angajat(x),Student(x)
    {
        cout<<"CC Stud_ang\n";
    }

    void afisare()
    {
        this->Persoana :: afisare();
        cout<<an<<" "<<facultate<<" "<<salariu<<endl;
    }
};

class animal
{
public:
    virtual ~animal()
    {

    }
};

class Pisica : public animal
{

};

class Caine : public animal
{

};

int main()
{

    Persoana *pisss=new Stud_ang;

    Stud_ang *aux=dynamic_cast<Stud_ang *>(pisss);
    if(aux)
        cout<<"DA";


    animal *p = new Pisica;

    Caine*c=dynamic_cast<Caine*>(p);
    if(c)
    {
        cout<<"ESTE Caine";
    }
    else
    {
        Pisica *pis=dynamic_cast<Pisica*>(p);
        if(pis)
            cout<<"ESTE Pisica";
    }
    return 0;
}
