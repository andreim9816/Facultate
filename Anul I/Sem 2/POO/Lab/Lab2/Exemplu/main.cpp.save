#include <iostream>
using namespace std;

class A 
{
public:
    A() { cout << "ca" << endl; } // constructor default 
    A(int x): x(x) { cout << "ca1" << endl; } // constructor cu un parametru
    A(const A& other) { cout << "cca" << endl; } // constructor de copiere 
    ~A() { cout << "da" << endl; } // destructor 

    const A& operator = (const A& other /*am pus const & ca sa nu se mai copieze obiectul*/);  // a = b;

    int operator - (const A& obj);    // a - b definit ca metoda 
    friend int operator + (const A& ob1, const A& ob2); // a + b definit ca functie friend

    friend istream& operator >> (istream& in, A& obj); // cin >> a sau f >> a unde f e fisier 
    friend ostream& operator << (ostream& out, const A& obj); // cout << a sau f << a unde f e fisier 
    
private:
    int x; 
};

const A& A::operator = (const A& other)
{
    cout << "operator =" << endl;
    x = other.x;
    return *this;
}

int A::operator - (const A& obj)
{
    return this->x - obj.x;   // x - obj.x 
}

istream& operator >> (istream& in, A& obj)
{
    return in >> obj.x;
}

ostream & operator << (ostream& out, const A& obj)
{
    return out << obj.x;
}

int operator + (const A& obj1, const A& obj2)
{
    return obj1.x + obj2.x;
}

void functie_copiere (A ob)
{
    // aici ob e un obiect temporar ca se distruge la finalul functiei
    // ob este initializat apeland constructorul de copiere
    cout << "functie_copiere" << endl;
}

void functie_referinta(A& ob)
{
    // aici ob e referinta la cine e dat ca parametru
    // nu se mai apeleaza constructorul de copiere 
    cout << "functie_referinta" << endl;
}

A functie_return()
{
    // la return, din ob se creaza un nou obiect temporar folosind constructorul de copiere 
    cout << "functie_return" << endl;
    A ob;
    return ob;
}

int main()
{
    A obj1, obj2;
    cin >> obj1 >> obj2;
    cout << obj1 << " " <<  obj2;

    cout << "sum: " << obj1 + obj2 << endl;
    cout << "diff: " << obj1 - obj2 << endl;

    A obj3 = obj1; // cand initializam asa se apeleaza constructorul de copiere 
    A obj4;
    obj4 = obj2; // aici se apeleaza opeatorul = 

    functie_copiere(obj1);
    functie_referinta(obj2);
    functie_return();
    A obj5 = functie_return();

    return 0;
}