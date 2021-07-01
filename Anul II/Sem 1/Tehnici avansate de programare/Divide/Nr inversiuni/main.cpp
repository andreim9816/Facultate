#include <iostream>

using namespace std;

int interclasare(int v[] , int st, int m ,int dr)
{
    int i = st;
    int j = m + 1;
    int k = 0;
    int contor = 0;
    int aux[dr - st + 1];

    while(i <= m && j <= dr)
    {
        if(v[i] <= v[j])
            aux[contor++] = v[i++];
        else
        {
            aux[contor++] = v[j++];
            k += (m - i + 1);
        }
    }

    while(i <= m)
        aux[contor++] = v[i++];
    while(j <= dr)
        aux[contor++] = v[j++];

    for(i = st , j = 0 ; i <= dr ; i++ , j++)
        v[i] = aux[j];

    return k;
}

int nrInversiuni(int v[] , int st, int dr)
{
    if(st == dr)
        return 0;
    else
    {
        int m = (st + dr) /2;

        int nr1 = nrInversiuni(v , st, m);
        int nr2 = nrInversiuni(v , m + 1 , dr);

        return nr1 + nr2 + interclasare(v , st , m , dr);
    }
}



int main()
{
    int v[] = { 1 , 2 , 11 , 9 , 4 ,6 };
    cout<<nrInversiuni(v, 0 , 5);
    return 0;
}
