#include <iostream>
#include<fstream>
#include<cmath>
using namespace std;

ifstream fin("date.in");

// verificare patrulater convex

struct Punct
{
    int x,y;
};

void citire(Punct &x)
{
    fin>>x.x>>x.y;
}

int determinant (Punct p, Punct q, Punct r)
{
    /*
      calculeaza determianntul pt matricea
        1  1  1
       p1 q1 r1
       p2 q2 r2
    */

    int p1 = p.x;
    int p2 = p.y;
    int q1 = q.x;
    int q2 = q.y;
    int r1 = r.x;
    int r2 = r.y;

    return q1 * r2 + p1 * q2 + r1 * p2 - q1 * p2 - r1 * q2 - p1 * r2;
}

int test_orientare(Punct p, Punct q, Punct r)
{
    // returneaza -1 daca r e la stanga lui PQ, altfel returneaza 1
    if(determinant(p,q,r) > 0 )
        return -1;
    return 1;
}

double norma(Punct x)
{
    return sqrt(x.x*x.x + x.y * x.y);
}

double prod_scalar(Punct x, Punct y)
{
    return x.x * y.x + x.y * y.y;
}

Punct vector_rezultat (Punct x, Punct y)
{
    Punct aux = {y.x - x.x , y.y - x.y};
    return aux;
}

void afis(Punct x)
{
    cout<<x.x <<" " <<x.y<<endl;
}

double unghi(Punct origine, Punct x, Punct y)
{
    Punct vect1, vect2;

    vect1 = vector_rezultat(origine, x);
    vect2 = vector_rezultat(origine, y);

   // afis(vect1);
  //  afis(vect2);

    double prod_sc = prod_scalar(vect1, vect2);
    double prod_norma = norma(vect1) * norma(vect2);

 //  cout<<prod_sc<<" "<<prod_norma<<endl;

    double rap = (double)prod_sc / prod_norma;
    return acos(rap);
}

int main()
{
    Punct A, B, C, D;

    citire(A);
    citire(B);
    citire(C);
    citire(D);


    if(abs(test_orientare(A,B,C) + test_orientare(B,C,D) + test_orientare(C,D,A) + test_orientare(D,A,B)) == 4)
       {
           cout<<" Patrulaterul este convex\n";

           double unghiBAC = unghi(B,A,C);
           double unghiCDA = unghi(D,A,C);

       //  cout<<unghiBAC << " " << unghiCDA ;

            if( unghiBAC + unghiCDA == atan(1)*4)
                cout << "Se afla pe cerc";

            else if ( unghiBAC + unghiCDA > atan(1)*4 )
                cout << "Se afla in interiorul cercului";

            else cout<<" Se afla in afara cercului";
       }
    else cout<<"Patrulaterul nu este convex\n";
    return 0;
}
