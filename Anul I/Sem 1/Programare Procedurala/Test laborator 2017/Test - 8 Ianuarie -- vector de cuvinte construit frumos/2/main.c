#include <stdio.h>
#include <stdlib.h>
#include<string.h>

typedef struct
{
    char *cuv;
    int majuscule;
}vect;

void citire( char **text , int *lungt,char **w ,int *lungw)
{
    *lungw=1;
    *lungt=0;
    char c,*p,*aux;
    FILE*f=fopen("cuvinte.in","r");

    *w='\0';
        // titlul
    while((c=fgetc(f))!='\n' && c!=' ' && c!=EOF)
    {
        (*lungw)++;

        aux=realloc(*w,sizeof(char)*(*lungw));
        if(!aux)
        {
            printf("eroare");
            free(*text);
            free(*w);
            return;
        }

        *w=aux;
        (*w)[*lungw-2]=c;
        (*w)[*lungw-1]='\0';
    }
    printf("titlul este %s\n",*w);


    char *aux1;
    *text='\0';

    while(1)
    {
        c=fgetc(f);
      //  printf("%c",c);
        (*lungt)++;
        aux1=realloc(*text,sizeof(char)*(*lungt));

        if(!aux1)
        {
            printf("eroare");
            free(*text);
            free(*w);
            return;
        }

        *text=aux1;
        (*text)[*lungt-1]=c;

        if(feof(f))
            break;

    }
/// trebuie facut lungt-- cred ca pune \n, NULL sau altceva in plus NU STIU DE CE
    (*lungt)--;
    (*text)[*lungt]='\0';
    fclose(f);

}

void afis(char*text,int n)
{
    int i;
    for(i=0;i<n;i++)
        printf("%c",text[i]);
}

void construct_vect(char *text,int l,vect **v,int *n)
{
   *v='\0';
   *n=0;
   char *p,*copie;

   copie=(char*)malloc(sizeof(char)*l);
   strcpy(copie,text);

   p=strtok(copie," \n ");

   while(p)
   {

        (*n)++;
        vect *aux;
        aux=realloc(*v,sizeof(vect)*(*n));

       if(!aux)
       {
           printf("EROARE");
           free(*v);
           free(text);
           free(aux);
           return;
       }

       *v=aux;
       (*v)[*n-1].cuv=malloc(sizeof(char)*strlen(p));
       strcpy((*v)[*n-1].cuv,p);

       p=strtok(NULL," \n  ");
   }

}


void afis_vect(vect*v,int n)
{
    int i;
    for(i=0;i<n;i++)
        printf("%s\n",v[i].cuv);
}

int cmpcresc(const void*a,const void*b)
{
    vect x,y;
    x=*(vect*)a;
    y=*(vect*)b;

    if(strlen(x.cuv) < strlen(y.cuv))
        return -1;
    else if(strlen(x.cuv) > strlen(y.cuv))
        return 1;
    else
    {
        if(x.cuv[0]>='A' && x.cuv[0]<='Z')
            return -1;
        if(y.cuv[0]>='A' && y.cuv[0]<='Z')
            return 1;
        return 0;
    }
}

void sortarare_cuv_lungime(vect *v,int n)
{
    qsort(v,n,sizeof(vect),cmpcresc);
}

int main()
{
    char *w,*text;
    int lungw,lungt,lungv;
    vect *v;

    citire(&text,&lungt,&w,&lungw); afis(text,lungt);


    construct_vect(text,lungt,&v,&lungv);
   // sortarare_cuv_lungime(v,lungv);
    afis_vect(v,lungv);


    free(w);
    free(v);
    free(text);

    return 0;
}
