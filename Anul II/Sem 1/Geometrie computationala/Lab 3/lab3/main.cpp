#include <iostream>
#include<fstream>
using namespace std;

ifstream fin("date.in");

struct Punct
{
    double x,y;
};

void citire(Punct &x)
{
    fin>>x.x>>x.y;
}

double determinant(double x1, double x2, double y1,double y2)
{
    /* calculeaza determinantul pentru matricea
    x1 x2
    y1 y2
    */

    return x1 * y2 - y1* x2;
}

Punct maxim(Punct x, Punct y)
{
     if(x.x > y.x || x.x == y.x && x.y > y.y)
        return x;
    return y;
}

Punct minim(Punct x, Punct y)
{
    if(x.x < y.x || x.x == y.x && x.y < y.y)
        return x;
    return y;
}
void afis(Punct x)
{
    cout<<x.x<<" "<<x.y<<endl;
}
int main()
{
   Punct A,B,C,D;

   // citim cele 4 puncte
    citire(A);
    citire(B);
    citire(C);
    citire(D);

       Punct min1, min2, max1, max2;

    min1 = minim(A,B);
    min2 = minim(C,D);
    max1 = maxim(A,B);
    max2 = maxim(C,D);

    A = min1;
    B = max1;
    C = min2;
    D = max2;

    // aflam coeficienii din ecuatia dreptelor
    // AB: a1 *X + b1 *Y + c1 = 0
    // CD: a2 *X + b2 *Y + c2 = 0

   /*
    afis(A);
    afis(B);
    afis(C);
    afis(D);
   */

    double a1 = A.y - B.y;
    double a2 = C.y - D.y;
    double b1 = B.x - A.x;
    double b2 = D.x - C.x;
    double c1 = A.x * B.y - A.y * B.x;
    double c2 = C.x * D.y - D.x * C.y;

   // cout<<a1<<" "<<a2<<" "<<b1<< " "<<b2<<endl;

    double delta  = determinant(a1, b1, a2, b2);
    // daca delta != 0, am solutie unica. Aflam solutiile si verificam daca se afla pe cele 2 segmente

    if(delta != 0)
    {
        double x = (double)determinant(-c1, b1, -c2, b2) / delta * 1.0;
        double y = (double)determinant(a1, -c1, a2, -c2) / delta * 1.0;

      //  cout <<x <<" "<<y<<endl;

      /*  if( x >= min1.x && x <= max1.x && x >= min2.x && x <= max2.x)
            if( y >= min1.y && y <= max1.y && y >= min2.y && y <= max2.y)
                cout<< "1Segmentele se intersecteaza in punctul "<<x<<" "<<y<<endl;
            else cout<< "2Segmentele nu se intersecteaza";
        else cout<< "3Segmentele nu se intersecteaza";
        */

        if( x >= min(min1.x,min2.x) && x <= max(max1.x,max2.x) && y >= min(min1.y,min2.y) && y<=max(max1.y,max2.y))
            cout<< "1Segmentele se intersecteaza in punctul "<<x<<" "<<y<<endl;
        else cout<< "2Segmentele nu se intersecteaza";
    }
    // daca delta == 0 verificam ca rangul matricei extinse sa fie egal cu cel al matricei
    else
    {
        int det1 = determinant(a1, c1, a2, c2);
        int det2 = determinant(b1, c1, b2, c2);

        if(det1 != 0 || det2 != 0 )
        {
            // daca rangul matricei extinse este 2, cel al matricei este 1, deci nu are solutii
            cout<<"4Segmentele nu se intersecteaza";
        }
        else
        {
            // punctele sunt coliniare
            // sortam punctele dupa x  => min1 max1 min2 max2
            if(min1.x > min2.x)
            {
                Punct aux;
                aux = min1;
                min1 = min2;
                min2 = aux;

                aux = max1;
                max1 = max2;
                max2 = aux;
            }

         //   afis(min1);
          //  afis(max1);
          //  afis(min2);
          //  afis(max2);

            if(min2.x <= min1.x && max1.x <= max2.x)
            {
                // daca un segment este prins cu totul in altul
                cout<<"ASegmentele se intersecteaza in segmentul " << min1.x <<" "<<min1.y<<" "<<max1.x<<" "<<max1.y<<endl;
            }
            else if(min2.x >= min1.x && max2.x <=max1.x)
            {
                cout<<"BSegmentele se intersecteaza in segmentul " << min2.x <<" "<<min2.y<<" "<<max2.x<<" "<<max2.y<<endl;
            }
            else if(max1.x > min2.x)
                cout<<"CSegmentele se intersecteaza in segmentul " << min2.x <<" "<<min2.y<<" "<< max1.x <<" "<<max1.y;
            else if( max1.x == min2.x)
                cout<<"DSegmentele se intersecteaza in punctul " << max1.x<<" "<<max1.y;
            else cout<<"ESegmentele nu se intersecteaza ";
        }

    }
    return 0;
}
