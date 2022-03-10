#include<iostream>
using namespace std;
 struct nod
{
    int val;
    nod*urm;
};

void adi(nod*&prim,nod*&ultim,int val)
{
    nod*q;
    q=new nod;
    q->val=val;
    if(!prim)
        {
        prim=ultim=q;
        ultim->urm=NULL;
        }
    else
    {
        q->urm=prim;
        prim=q;
    }
}

void adf(nod*&prim,nod*&ultim,int val)
{
    nod *q;
    q=new nod;
    q->val=val;
    if(!prim)
        prim=ultim=q;
    else
    {
        ultim->urm=q;
        ultim=q;

    }
    ultim->urm=NULL;
}

void afis(nod*prim,nod*ultim)
{
     int ok=0;
    nod *q;
    q=new nod;
    for(q=prim;q!=NULL;q=q->urm)
        cout<<q->val<<' ',ok=1;
    if(!ok)
    cout<<"Lista vida";
}

int cv(nod*prim,nod*ultim,int val)
{
    nod*q;
    q=new nod;
    int contor=1;
    for(q=prim;q!=NULL;q=q->urm,contor++)
        if(q->val==val)
        return contor;
    return -1;
}

int cp(nod*prim,nod*ultim,int poz)
{
    int contor=1;
    nod*q;
    q=new nod;
    for(q=prim;contor!=poz && q!=NULL;q=q->urm)
        contor++;

    if(contor==poz)
        return q->val;
    else return -1;
}

void iv(nod*&prim,nod*&ultim,int poz,int val )
{
    nod*q,*r;
    q=new nod;
    for(q=prim;q!=NULL && q->val!=poz;q=q->urm);;
    if(q!=NULL)
    {

    if(q==ultim)
    {
        r=new nod;
        r->val=val;
        r->urm=NULL;
        ultim->urm=r;
        ultim=r;
    }
    else
    {
        r=new nod;
        r->val=val;
        r->urm=q->urm;
        q->urm=r;
    }
    }

}

void ip(nod*&prim,nod*&ultim,int poz,int val)
{
    int contor=1;
    nod*q;
    q=new nod;

    if(poz==0)
    {
        nod*r;
        r=new nod;
        r->val=val;
        r->urm=prim;
        prim=r;
    }
    for(q=prim;q!=NULL && contor!=poz;q=q->urm,contor++);
    if(contor==poz)
    {
        nod*r;
        r=new nod;
        r->val=val;
        r->urm=q->urm;
        q->urm=r;
    }

}

void sv(nod*&prim,nod*&ultim,int val)
{
    nod *q,*r;
    q=new nod;
    r=new nod;
    if(prim->val==val)
    {
        r=prim;
        prim=prim->urm;
        delete r;
    }
    else if(prim==ultim)
    {
        if(prim->val==val)
            prim=ultim=NULL;
    }
    else
    {   int ok=0;
        for(q=prim;q->urm!=NULL;q=q->urm)
            if(q->urm->val==val)
                {
                    ok=1;
                    r=q->urm;
                    q->urm=q->urm->urm;
                    delete r;
                    break;
                }
        if(ok==0)
            if(ultim->val==val)
                {for(q=prim;q->urm->urm;q=q->urm);
                    q->urm=NULL;
                }

    }
}

void sp(nod*&prim,nod*&ultim,int poz)
{
    int contor=1;
    nod *q,*r,*z;
    q=new nod;
    r=new nod;
    z=new nod;
    if(prim==ultim)
    {
        if(poz==1)
            prim=ultim=NULL;
    }
    else if(poz==1) ///prima pozitie
        {
            r=prim;
            prim=prim->urm;
            delete r;
        }
    else
    {
        for(q=prim;q->urm!=NULL && contor<poz-1;)
        {       z=q;
                q=q->urm;
                contor++;
        }
        if(contor ==(poz-1)) ///in interiorul listei
        {
            r=q->urm;
            q->urm=q->urm->urm;
            delete r;
        }
        else if(q->urm==NULL) ///ultimul element
        {
            ultim=z;
            delete q;
            ultim->urm=NULL;
        }

    }
}

int main()
{
    nod*prim,*ultim;
    prim=new nod;
    ultim=new nod;
    prim=ultim=NULL;

    int optiune,stop=0,x,val,poz;

    cout<<"Apasati 1 pentru a citi si adauga la inceput un element \n";
    cout<<"Apasati 2 pentru a citi si adauga la final un element \n";
    cout<<"Apasati 3 pentru a afisa lista \n";
    cout<<"Apasati 4 pentru a citi o valoare si a o cauta in lista \n";
    cout<<"Apasati 5 pentru a citi o pozitie si afisa elementul respectiv \n";
    cout<<"Apasati 6 pentru a insera un element dupa o pozitie data \n";
    cout<<"Apasati 7 pentru a insera un element pe o pozitie data \n";
    cout<<"Apasati 8 pentru a sterge prima aparitie a unui element \n";
    cout<<"Apasati 9 pentru a sterge elementul de pe o pozitie data \n";
    cout<<"Apasati 10 pentru a opri programul \n \n";

    while(!stop)
{
    cout<<"Optiunea este ";cin>>optiune;
    switch (optiune)
    {


        case 1 : cout<<"Elementul este "; cin>>val;   adi(prim,ultim,val); break;
        case 2 : cout<<"Elementul este ";cin>>val;    adf(prim,ultim,val); break;
        case 3 : afis(prim,ultim); cout<<"\n";                             break;
        case 4 : cout<<"Elementul este "; cin>>val;
                    x=cv(prim,ultim,val);
                    if(x==-1)
                    cout<<"NU se gaseste in lista \n";
                    else cout<<"Elementul se gaseste pe pozitia "<<cv(prim,ultim,val);
                    cout<<"\n";
                    break;

        case 5 : cout<<"Pozitia este "; cin>>val;
                x=cp(prim,ultim,val);

                if(x!=-1)   cout<<"Pe pozitia "<<val<<" se gaseste elementul "<<x;
                else cout<<"Pe pozitia "<<val<<" nu se gaseste niciun element";
                cout<<"\n";

                break;

        case 6 : cout<<"Pozitia de inserare este ";cin>>poz;
                 cout<<"Elementul de inserare este ";cin>>val;
                 iv(prim,ultim,poz,val);
                 cout<<"\n";
                 break;


        case 7 : cout<<"Insereaza pe pozitia \n ";cin>>poz;
                 cout<<"Elementul este ";cin>>val;
                 ip(prim,ultim,poz,val);
                 cout<<"\n";
                 break;


        case 8 : cout<<"Se sterge elementul ";cin>>val;
                 sv(prim,ultim,val);
                 cout<<"\n";
                 break;


        case 9 : cout<<"Se sterge elementul de pe pozitia ";
                 cin>>poz;
                 sp(prim,ultim,poz);
                 break;
        case 10: stop=1; break;

    cin>>optiune;
    }

}
    return 0;
}
