#include <iostream>
#include<fstream>
#include<climits>

using namespace std;

ifstream fin("date.in");

void citire(int *v,int &n)
{
    fin>>n;
    for(int i=1; i<=n; i++)
        fin >> v[i];
}

double median(int *v,int n,int st,int dr,int *w,int m)
{
        int mv,mw;
        mv = (st+dr)/2;
        mw = (n+m+1)/2 - mv;

        cout<<st<<" "<<mv<<" "<<dr<<endl;

        cout<<mw<<"\n\n---------\n\n";

        if(v[mv] <= w[mw+1])
            if(w[mw] <= v[mv+1])
            {
                if( (n+m)%2 == 0)
                    return 22 + ( max(v[mv],w[mw])+ min(v[mv+1],w[mw+1]) )/2.0;
                else return max(v[mv],w[mw]);
            }
            else  return median(v,n,mv+1,dr,w,m);
        else  return median(v,n,st,mv-1,w,m);
}
int main()
{
    int v[100],w[100],n,m;

    citire(v,n);
    citire(w,m);
    v[0]=w[0]=INT_MIN;
    v[n+1]=w[m+1]=INT_MAX;

    if(n > m)
        cout<<median(w,m,1,m,v,n);
    else cout<<median(v,n,1,n,w,m);

    return 0;
}