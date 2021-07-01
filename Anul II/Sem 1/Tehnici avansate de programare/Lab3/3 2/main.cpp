#include <iostream>
#include<vector>
#include<fstream>
#include<algorithm>
#include<queue>
using namespace std;

int gr[100];
int select[100];

void citire(int *t,int *gr,int &n,int &m)
{
    ifstream fin("date.in");
/*
Updatez gradele fiecarui nod, si in solutia finala vor fi sigur frunzele arborelui
*/
    fin>>n>>m;
    int i,x,y;

    fin>>x>>y;
    t[y]=x;
    t[x]=0;
    gr[x]++;
    gr[y]++;

    for(i=2;i<=m;i++)
    {
        fin>>x>>y;

        gr[x]++;
        gr[y]++;

        t[y]=x;
    }

    fin.close();
}

void greedy(int *t,int n)
{
    int i,T=0,nr=0;
/*
Vectorul select[] are valorile 1 sau 0: 1 daca a fost selectat deja si nu poate fi solutie, sau 0
*/
    vector<int>v;
    queue<int>q; /// coada in care vor fi introdusi tatii nodurilor care fac parte din solutie

    if(n==2)
    {
        cout<<"1\n1";
    }
    else
    {

    for(i=1;i<=n;i++)
        if(gr[i] == 1) // este frunza,deci face parte din solutie
    {
        nr++;

        v.push_back(i);
        select[i]=1;

        if(!select[t[i]] && t[i]!=0) // daca tatal  nu a mai fost selectat, il selectez caci nu poate face parte din solutia finala
                                     // (nu s-ar resepcta regula cerintei) si il pun in coada
        {
            q.push(t[i]);
            select[t[i]]=1;

        }
    }

    T=nr;

    while(nr!=0) /// cat timp la pasul anterior am adaugat noduri in coada !!!!!!!!!!!!!
    {
        nr=0;
        while(q.size()>0)
        {
            int x=q.front();
            if(select[t[x]] == 0 && t[t[x]]==0) // daca tatal nodului nu a mai fost selectat, va face parte din solutie
            {
                v.push_back(t[x]);
                nr++;
                select[t[x]]=1;
            }
            q.pop();
        }

        for(i=T;i<T+nr;i++) // din nodurile  !! nou-adaugate !! la solutie, verificam tatii si ii introducem in coada
            if(select[v[i]]==0)
        {
            select[v[i]]=1;
            q.push(t[v[i]]);
        }
        T+=nr;
    }

    cout<<T<<'\n';

    for(auto p:v)
        cout<<p<<" ";
    }
}
int main()
{
    int t[100],n,m;
    citire(t,gr,n,m);
    greedy(t,n);
    return 0;
}

