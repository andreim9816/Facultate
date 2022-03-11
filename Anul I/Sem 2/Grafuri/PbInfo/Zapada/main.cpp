#include <iostream>
#include<vector>
#include<algorithm>
#include<fstream>
using namespace std;

ifstream fin("zapada.in");
ofstream fout("zapada.out");

vector<pair<int,pair<int,int> > >E; // vector de muchii
vector<int>tata,grad;
vector<pair<int,int > >APCM;
vector<int>strazi;

int n,m,nr_much,cost_total;

/*
    Pe primele 2 cazuri pe pbinfo merge kruskal chior
    Cazul al 3lea contine muchii care comunica intre ele - ar putea face chiar un ciclu - si de aceea while-ul din kruskal
    va rula pana toate nodurile sunt vizitate, caci altfel, daca nu faceam asta si ma opream la n-1 muchii, riscam sa nu fie
    conex in final APCM-ul */

int viz[101];
int sum_viz=0;

void init()
{
    int i;
    for(i=1;i<=n;i++)
        tata[i]=i;
}

int find_(int x)
{
    if(tata[x] == x)
        return x;
    return find_(tata[x]);
}

void union_(int x,int y)
{
    int r1,r2;
    r1=find_(x);
    r2=find_(y);

    if(grad[r1] > grad[r2])
        tata[r2]=r1;
    else if(grad[r1] < grad[r2])
        tata[r1]=r2;
    else
    {
        tata[r2]=r1;
        grad[r1]++;
    }
}

void citire()
{
    fin>>n>>m;

    tata.resize(n+1);
    grad.resize(n+1,0);
    E.resize(m+1);

    for(int i=1;i<=m;i++)
    {
        fin>>E[i].second.first>>E[i].second.second>>E[i].first;
    }

    fin>>nr_much; // nr de muchii care trebuie deja introduse in APCM

    init();

    for(int i=1;i<=nr_much;i++)
    {
        int x,y;
        fin>>x; // strada care trb dezapezita
        strazi.push_back(x);



        if(!viz[E[x].second.first])
            {viz[E[x].second.first]=1;sum_viz+=1;}

        if(!viz[E[x].second.second])
            {viz[E[x].second.second]=1;sum_viz++;}

        union_(E[x].second.first,E[x].second.second);
        cost_total+=E[x].first;

    }
    sort(E.begin(),E.end());
}

void kruskal()
{
    int x,y,c,i=1;
    while(sum_viz != n || nr_much<n-1)
    {
        c=E[i].first;
        x=E[i].second.first;
        y=E[i].second.second;

        if(find_(x) != find_(y))
        {
            if(!viz[x])
            {
                viz[x]=1;
                sum_viz++;
            }
            if(!viz[y])
            {
                viz[y]=1;
                sum_viz++;
            }

            nr_much++;
            APCM.push_back({x,y});
            union_(x,y);
            cost_total+=c;
        }
        i++;
    }
    fout<<cost_total;
}

int main()
{
    citire();
    kruskal();

    return 0;
}