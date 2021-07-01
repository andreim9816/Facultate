#include <iostream>
#include<fstream>
#include<algorithm>

using namespace std;

ifstream fin("date.in");

struct job
{
    int st,dr,p;
};

int cmp(job x, job y)
{
    if(x.dr < y.dr)
        return 1;
    return 0;
}

void citire(job job[],int &n)
{
    fin>>n;
    for(int i = 0 ; i < n ; i++)
     fin>>job[i].st>>job[i].dr>>job[i].p;
}

int cauta_bin(job v[],int n,int poz)
{
    int st = 0;
    int dr = n-1;

    while(st<=dr)
    {
        int m = (st+dr)/2;

        if(v[m].dr <= v[poz].st)
        {
            if(v[m+1].dr <= v[poz].st)
                st = m + 1;
            else return m;
        }
        else dr = m-1;
    }
    return -1;
}

void pd(job v[],int n)
{
    int i,poz,prec[100],profit[100],profit_inclusiv,current[100];
    profit[0] = v[0].p; // vectorul table[] de pe geeks
    prec[0] = -1;       // vectorul de precedent
    current[0] = 1;

    for(i = 1 ; i < n ; i++)
    {
        profit_inclusiv = v[i].p;

        poz = cauta_bin(v, i, i);
        if(poz != -1)
            profit_inclusiv = profit_inclusiv + profit[poz];
        else prec[i] = -1;

        if(profit[i-1] > profit_inclusiv)
        {
            prec[i] = i-1;
            profit[i] = profit[i-1];
            current[i] = 0;
        }
        else
        {
            prec[i] = poz;
            profit[i] = profit_inclusiv;
            current[i] = 1;
        }
    }
/*
    for(i=0;i<n;i++)
     cout<<profit[i]<<" ";
    cout<<endl;
    for(i=0;i<n;i++)
        cout<<prec[i]<<" ";
*/
    cout<<"Profitul este "<<profit[n-1]<<"\n";

//    int profit_max = profit[n-1];
//    int last_profit = profit[n-1];
    poz = n-1;

    while(prec[poz] !=-1)
    {
       if(current[poz] == 1)
       {
           cout<<v[poz].st<<" "<<v[poz].dr<<endl;
   //         profit_max-=v[poz].p;
       }
  //     cout<<poz<<" ";
       poz = prec[poz];
    }
    cout<<v[poz].st<<" "<<v[poz].dr;
}

int main()
{
    int n;
    job v[100];
    citire(v,n);
    sort(v,v+n,cmp);
    pd(v,n);
    return 0;
}
