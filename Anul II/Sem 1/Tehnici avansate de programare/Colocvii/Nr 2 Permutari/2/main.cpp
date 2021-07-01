#include <iostream>
#include<vector>
#include<fstream>
using namespace std;

/* structura este o matrice 3-dimensionala, de forma matrix[n][4][4]
 * avand cei n vectori care au cate 4 elemente si care pot fi permutati
 * in 4 moduri diferite
 */
vector<vector<vector<int>>>matrix;
int n;

struct poz
{
    int vectorNr; // al cate-lea vector din cei n
    int nrPermut; // a cata permutare a vectorului respectiv
};

void permutaVector(vector<int> &v)
{
    /* functie care permuta la stanga un vector */
    int i , x = v[0];

    for(i = 0 ; i < 3 ; i++)
        v[i] = v[i+1];
    v[3] = x;
}

void citire()
{
    /* functie de citire*/
    ifstream fin("date.in");
    int i ,j;
    fin >> n;
    matrix.resize(n);

    for(i = 0 ; i < n ; i++)
    {
        matrix[i].resize(4);
        for(int j = 0 ; j < 4 ; j++)
        {
            int x;
            fin>>x;
            matrix[i][0].push_back(x);
        }

        vector<int>copiere = matrix[i][0];

        for(j = 1 ; j <= 3 ; j++)
        {
            permutaVector(copiere);
            matrix[i][j] = copiere;
        }
    }
    fin.close();
}

int valid(vector<int> v, vector<int> w)
{
    /* functie care returneaza 1 daca se respecta cerinta */
    return (v[1] <= w[1] && v[3] >= w[3]);
}

void tipPermutare(int tip)
{
    /* functie care spune tipul unei permutari */
    if(tip == 0)
        cout << " nepermutat";
    else if(tip == 1)
        cout << " permutare b c d a";
    else if(tip == 2)
        cout << " permutare c d a b";
    else cout << " permutare d a b c";
}

void PD()
{
    /* functia de programare dinamica */
    int i , j , k , l, lungTotal = -1;
    poz lungPoz;

    /* matrice care pentru lung[i][j] memoreaza lungimea unei secvente maxima din care face parte
     * vectorul i si permutarea j, j ={0,1,2,3}
    */
    vector<vector<int>>lung;
    lung.resize(n);
    for(i = 0 ; i <= n - 1 ; i++)
        lung[i].resize(4 , 0);

    /* vector in care pentru prec[i][j](vectorul i, permutarea j) memoreaza date despre urmatorul vector in secventa maximala */
    vector<vector<poz>>prec;
    prec.resize(n);
    for(i = 0 ; i <= n - 1 ; i++)
        prec[i].resize(4 , {-1,0});

    /* vector in care pentru tipPermut[i][j] (vectorul i, permutarea j) memoreaza tipul de permutare ( 0, 1, 2 ,3 ) */
    vector<vector<int>>tipPermut;
    tipPermut.resize(n);
    for(i = 0 ; i <= n - 1 ; i++)
        tipPermut[i].resize(4 , 0);

    /// aplicam rationamentul sirului crescator maximal

    int lungMaximTotal = -1;
    int pozMaximTotal = - 1;

    // pentru fiecare indice < n - 1, si pentru fiecare permutare a sa
    for(i = n - 2 ; i >= 0 ; i--)
     for(j = 0 ; j < 4 ; j++)
     {
         int lungMax = -1;

        // pentru fiecare alt indice in dreapta indicelui i si pentru fiecare permutare a sa
         for(k = n - 1 ; k >= i + 1 ; k--)
            for(l = 0 ; l < 4 ; l++)
         {
             // intreaba daca se respecta cerinta
             if(valid(matrix[i][j] , matrix[k][l]) == 1)
                // daca am gasit o secventa valida de lungime mai mare ( pentru indicele curent)
                if(lung[k][l] > lungMax)
             {
                 lungMax = lung[k][l]; // memoreaza lungimea
                 if(lungMax > lungTotal) // lungimea maxima globala, memoreaza al cate-lea vector si a cata permutare
                 {
                     lungTotal = lungMax;
                     lungPoz.vectorNr = k;
                     lungPoz.nrPermut = l;
                 }

                 lung[i][j] = lungMax + 1;
                 prec[i][j] = {k,l}; // vectorul k, permutarea l
             }
         }
     }
   // afisarea

    cout << "Lungimea maxima este "  <<  lungTotal + 1 << "\n";

    while(lung[lungPoz.vectorNr][lungPoz.nrPermut] != 0)
    {
        cout << lungPoz.vectorNr << ". "; // al cate-lea vector
        for(i = 0 ; i < 4; i++)
            cout << matrix[lungPoz.vectorNr][lungPoz.nrPermut][i] << " "; // afiseaza elementele din permutarea respectiva

        tipPermutare(lungPoz.nrPermut); // afiseaza tipul de permutare
        cout << endl;
        lungPoz = prec[lungPoz.vectorNr][lungPoz.nrPermut]; // trece la urmatorul
    }

    // pentru ultimul vector facem afisare separata
    cout << lungPoz.vectorNr << ". ";
    for(i = 0 ;i < 4 ; i++)
        cout << matrix[lungPoz.vectorNr][lungPoz.nrPermut][i] << " ";
     tipPermutare(lungPoz.nrPermut);
}

int main()
{
    citire();
    PD();
    return 0;
}
