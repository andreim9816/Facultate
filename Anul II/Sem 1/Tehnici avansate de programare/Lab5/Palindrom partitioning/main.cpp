#include <iostream>
#include<fstream>
#include<cstring>
using namespace std;

stri

void afis_cuvant(char*cuv,int st,int dr)
{
    for(int i = st ; i <= dr ; i++)
        cout<<cuv[i];
    cout<<endl;
}

int nr_pali[100][100];

void afis_nrpali()
{
    int i,j;
    for(i=0;i<=7;i++)
    {
        for(j=0;j<=7;j++)
         cout<<nr_pali[i][j]<<" ";
        cout<<endl;
    }
}

void palindrom(bool pali[][100], char *cuv, int lung, int *vec)
{
    int i,j,L,st,dr;
    int prec[lung];

    // initializare matrice. Toate cuvintele formate dintr-o singura litera sunt palindroame
    for(i = 0 ; i < lung ; i++)
        {
            pali[i][i] = true;
            nr_pali[i][i] = 1;
        }

    // L - lungimea cuvantului
    // st - pozitia de inceput a cuvantului curent de lungime L
    // dr - pozitia de sfarsit a cuvantului curent de lungime L

    for(L = 2 ; L <= lung ; L++)
        for(st = 0 ; st <= lung - L +1 ; st++)
        {
            dr = st + L - 1;

            if(L == 2) // daca cuvantul e de lungime 2, doar comparam cele 2 litere
                if(cuv[st] == cuv[dr])
                    pali[st][dr] = true;
                else pali[st][dr] = false;

            else if(cuv[st] == cuv[dr] && pali[st+1][dr-1] == true) // altfel, intrebam daca are literele din capete egale si daca cuvantul fara acestea este palindrom
                    pali[st][dr] = true;
                else pali[st][dr] = false;

            nr_pali[st][dr] = nr_pali[st+1][dr] + nr_pali[st][dr-1] - nr_pali[st+1][dr-1];

            if(pali[st][dr] == true)
                nr_pali[st][dr]++;
        }

    for(i = 0 ; i < lung ; i++)
        if(pali[0][i] == true)
         {
             vec[i] = 0;
             prec[i] = -1;
         }
        else
        {

            vec[i] = 2e9;
            for(j = 0; j  < i ; j++)
                if(pali[j+1][i] == true && vec[j] + 1 <= vec[i])
                    {
                        vec[i] = vec[j] + 1;
                        prec[i] = j;
                    }
        }

    cout<<"In total sunt " <<nr_pali[0][lung-1]<<" siruri palidroame\n";
    cout<<"Numarul minim de siruri palindroame este " << vec[lung-1] + 1 <<" \n";

    int poz = lung-1;

    while(prec[poz] != -1)
    {
        afis_cuvant(cuv,prec[poz]+1,poz);
        poz = prec[poz];
    }

    afis_cuvant(cuv,0,poz);

   //  afis_nrpali();
}

int main()
{
    char cuv[]= "aaacaaba";
    int lung = strlen(cuv),i,j,vec[lung];
    bool pali[lung][100];
    palindrom(pali,cuv,lung,vec);

    return 0;
}
