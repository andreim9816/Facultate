#include <iostream>
#include<cstring>
#include<fstream>
using namespace std;

ifstream fin("date.in");

void citire_matrice(char mat[][127][127],int &nr_stari, int &nr_muchii, char &stare_init, char stari_finale[],int &nr_stari_finale)
{
    char a,b,c;
    int i,j;

    for(i=0;i<127;i++)
    for(j=0;j<127;j++)
        mat[i][j][0]='\0';

  //  cout<<"Introduceti numarul starilor = ";
  fin>>nr_stari;
    //cout<<"\n Introduceti numarul de muchii = ";
    fin>>nr_muchii;
   // cout<<"\n Introduceti starea initiala = ";
   fin>>stare_init;
   // cout<<"\n Introduceti numarul de stari finale = ";
   fin>>nr_stari_finale;
    //cout<<"\n Introduceti starile finale: ";

    for(i=0;i<nr_stari_finale;i++)
        fin>>stari_finale[i];

//    cout<<"\n Introduceti muchiile\n";

    for(i=1;i<=nr_muchii;i++)
    {
        fin>>a>>c>>b;
        int l=strlen(mat[a-'0'][b-'0']);
        mat[a-'0'][b-'0'][l]=c;
        mat[a-'0'][b-'0'][l+1]='\0';

    }
}

void verif(char mat[][127][127],char stare,char stari_finale[],int n,char *t,int &ok)
{
    int i,j;
   // cout<<t<<endl;
    if(strlen(t)==0)
    {
        for(i=0;i<n;i++)
            if((stari_finale[i])==stare)
            {
                ok=1;
                return;
            }
    }

    for(i=0;i<127;i++)
    {
        int l=strlen(mat[stare-'0'][i-'0']);
        for(j=0;j<l;j++)
            if(t[0] == mat[stare-'0'][i][j])
               verif(mat,i,stari_finale,n,t+1,ok);
    }

}

int main()
{
    char mat[127][127][127];
    int nr_stari,nr_muchii,nr_stari_finale;
    char stare_init;
    char stari_finale[127];
    int ok=0;

    citire_matrice(mat,nr_stari,nr_muchii,stare_init,stari_finale,nr_stari_finale);

    verif(mat,stare_init,stari_finale,nr_stari_finale,"ac",ok);
    if(ok)
        cout<<"Cuvantul este acceptat";
    else cout<<"Cuvantul NU este acceptat";

    return 0;
}
