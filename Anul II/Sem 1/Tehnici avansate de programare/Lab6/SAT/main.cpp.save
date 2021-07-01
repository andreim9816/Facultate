#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <cstdlib>
using namespace std;

vector<int>sol;
int ok;
int n, m;

struct var
{
    bool folosit;
    bool negat;
};

struct clauza
{
    vector<var>variab;
    int variabFolosite;
};

void bkt(list<clauza>&E, int k)
{
    int i;
    if(E.empty()) // E e vida, deci am gasit solutie
    {
        ok = 1;
        cout<<"Solutia este ";
        for(i = 0 ; i < k -1 ; i++)
            cout<< sol[i]<<" ";

        //completeaza ce e ramas, daca e cazul
        for(i = k -1 ; i < n ; i++)
            cout<<0<<" ";

        cout<<"\n";
     return;
    }

    bool valid;
    list<clauza>ESaved = E;
    list<clauza>::iterator elem;


    // Nu am gasit solutie, am depasit numarul de variabile
    if(k > n )
        return ;

    //bkt-ul
    for(i = 0 ; i < 2 ; i++)
    {
        elem = E.begin();
        valid = true;
        sol[k - 1 ] = i;


        while(E.end() != elem )
        {
            bool sters = false;
            if( (*elem).variab[k-1].folosit == true) // daca variabila K este folosita in clauza respectiva
            {
                if((*elem).variab[k-1].negat != (bool)i) // daca variabila e negata si iam dat valoarea 0 sau invers, atunci o scot din Expresie
                {
                    elem = E.erase(elem);
                    sters = true;
                }
                else
                {
                    if((*elem).variabFolosite > 1) // in clauza, variabila evaluata e negativa, nu ne ajuta cu nimic, o scoatem
                    {
                        (*elem).variab[k-1].folosit = false;
                        (*elem).variabFolosite--;
                    }
                    else if( (*elem).variabFolosite <= 1) // clauza vida, Expresia e nesatisfiabila
                    {
                        valid = false;
                        break;
                    }
                }
            }
            // daca am sters ceva, nu mai iteram
            if(!sters)
                elem++;
        }


        if(valid)
            bkt(E, k+1);

        E = ESaved; // restabilim
    }
}

int main()
{
    ifstream fin("date.in");
    int  i, j;
    fin>>n>>m;

    sol.resize(n , 0);

    // o expresie este formata din mai multe clauze
    list<clauza> E;

    for(int i = 0 ; i < m ;i++)
    {
        clauza C;
        for(int k = 0 ; k < n ; k++)
         C.variab.push_back({0,0});

        fin>>C.variabFolosite;

        for(j = 0 ; j < C.variabFolosite ; j++)
        {
            int value;
            fin>>value;

            if(value <0)
            {
                C.variab[-value - 1].folosit = true;
                C.variab[-value - 1].negat = true;
            }
            else C.variab[value - 1].folosit= true;
        }
        E.push_back(C);
    }

    bkt(E,1);

    if(!ok)
        cout<<"Nu este satisfiabila";
    return 0;
}
