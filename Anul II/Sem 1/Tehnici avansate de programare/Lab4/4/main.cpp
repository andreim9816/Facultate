#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <algorithm>

using namespace std;

struct punct
{
    long long x,y;
};

long long distanta(punct x, punct y)
{
    long long X = x.x - y.x;
    long long Y = x.y - y.y;

    return X*X + Y*Y;
}

void citire(vector <punct>&v, int &n)
{
    ifstream fin("cmap.in");

    fin>>n;
    v.resize(n);

    for(int i=0;i<n;i++)
        fin>>v[i].x>>v[i].y;

    fin.close();
}

bool cmp(punct x, punct y)
{
    if( x.x < y.x)
        return 1;
    if(x.x == y.x && x.y <y.y)
        return 1;
    return 0;
}


void interclasare(vector<punct>&v, int st, int m, int dr)
{
    int i = st, j= m+1;
    vector<punct>aux;

    while(i <=m && j <= dr)
    {
        if(v[i].y < v[j].y)
            aux.push_back(v[i++]);
        else aux.push_back(v[j++]);
    }

    while(i <= m)
        aux.push_back(v[i++]);

    while(j <= dr)
        aux.push_back(v[j++]);

    for(i = st, j = 0; i<= dr; i++,j++)
        v[i] = aux[j];
}

long long DIVIDE_ET_IMPERA( vector <punct> &v, int st, int dr)
{
    if(st>=dr)
        return 4e18;

    else if(dr-st==1)
    {
        long long minim = distanta(v[st],v[dr]);

        // sortez dupa ordonata
        if(v[st].y > v[dr].y)
            swap(v[st],v[dr]);

        return minim;

    }
    else if(dr-st==2) // sunt 3 puncte
    {
        long long d1 = distanta(v[st],v[st+1]);
        long long d2 = distanta(v[st+1],v[dr]);
        long long d3 = distanta(v[st],v[dr]);

        long long minim = d1;

        if(minim > d2)
         minim = d2;
        if(minim > d3)
         minim = d3;

        interclasare(v,st,st+1,dr);

        return minim;
    }

    else
    {
        int m = (st + dr)/2;

        long long minim = min(DIVIDE_ET_IMPERA(v,st,m),DIVIDE_ET_IMPERA(v,m+1,dr));

        //se sorteaza partea stanga si dreapta dupa ordonata, prin interclasare
        interclasare(v,st,m,dr);

        //punem intr-un vector punctele care se afla la distanta minim fata de "verticala"
        vector <punct> aux;
        for(int i=st ; i<=dr ; i++)
            if(abs(v[i].x - v[m].x) < minim)
               aux.push_back(v[i]);

        int aux_size=aux.size();

        //vedem daca exista o distanta intre doua puncte mai mica decat minim
        for(int i=0;i<aux_size-1;i++)
            for(int j=i+1; j<aux_size && j<=i+7; j++)
                minim = min( minim, distanta(aux[i], aux[j]));

        return minim;
    }
}

int main()
{
    int n;
    vector <punct> v;
    ofstream fout("cmap.out");

    citire(v,n);
    sort(v.begin(),v.end(),cmp);

    fout<<fixed<<setprecision(6)<<(double)sqrt( DIVIDE_ET_IMPERA(v,0,n-1));
    fout.close();

    return 0;
}
