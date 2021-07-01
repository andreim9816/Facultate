#include <iostream>
#include<fstream>
#include<cmath>
// problema 2

using namespace std;

int linie , coloana;

void divide(int N, int numar)
{
    if(numar >= 1 && numar <= 4) // N == 1
    {
        if(numar == 1)
        {
            linie++;
            coloana++;
        }
        else if (numar == 2)
        {
            linie += 2;
            coloana += 2;
        }

        else if(numar == 3)
        {
            linie += 1;
            coloana += 2;
        }

        else
        {
            linie += 2;
            coloana += 1;
        }

        return ;
    }
    else
    {
        int cadran1Min = 1;
        int cadran1Max = pow(2, 2*N-2);

        int cadran2Min = cadran1Max + 1;
        int cadran2Max = 2 * cadran1Max;

        int cadran3Min = cadran2Max + 1;
        int cadran3Max = 3 * cadran1Max;

        int cadran4Min = cadran3Max + 1;
        int cadran4Max = 4 * cadran1Max;

        // numar se afla in primul cadran
        if(numar >= cadran1Min && numar <= cadran1Max)
            {
                cout<<"Cadran 1\n";
                divide(N-1 , numar - cadran1Min + 1);

            }
        else if (numar >= cadran2Min && numar <= cadran2Max)
        {
            cout<<"Cadran 2\n";
            coloana += pow(2,N-1);
            linie += pow(2, N-1);
            divide(N-1 , numar - cadran2Min + 1);
        }
        else if(numar >= cadran3Min && numar <= cadran3Max)
        {
            cout<<"Cadran 3\n";
            coloana += pow(2 , N-1);
            divide(N-1 , numar - cadran3Min + 1);
        }
        else
        {
            cout<<"Cadran 4\n";
            linie += pow(2, N-1);
            divide(N-1 , numar - cadran4Min + 1);
        }
    }
}

int main()
{
    int x, N;
    cin >> N >> x;
    divide(N , x);
    cout<<linie<<" "<< coloana;
    return 0;
}
