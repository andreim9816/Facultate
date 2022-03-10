#include <stdio.h>
#include <stdlib.h>
#include<time.h>

typedef struct
{
    unsigned char b;
    unsigned char g;
    unsigned char r;
}pixel;

void XorShift32(unsigned int **v,int latime,int inaltime,unsigned int seed)
{
    /* functie care va genera in vectorul v numere pseudo-aleatoare cu ajutorul
    algoritmului XORSHIFT32 */

    int n=2*inaltime*latime,i;
    unsigned int r;

    *v=(unsigned int *)malloc(sizeof(unsigned int)*n);
    if(!v)
    {
        printf("Eroare la alocarea de memorie pentru vectorul de numere aleatoare ");
        return;
    }

    (*v)[0]=seed;

    for(i=1;i<n;i++)
    {   r=(*v)[i-1];
        r=r^r<<13;
        r=r^r>>17;
        r=r^r<<5;
       (*v)[i]=r;
    }
}

void dimensiuni_imagine_header(unsigned char **header, char *nume_fisier,int *inaltime,int *latime,int *padding)
{
    FILE *f=fopen(nume_fisier,"rb");
    if(!f)
    {
        printf("Nu s-a gasit fisierul cu imaginea initiala: %s",nume_fisier);
        return;
    }

    fseek(f,18,SEEK_SET);
    fread(latime,sizeof(unsigned int),1,f);
    fread(inaltime,sizeof(unsigned int),1,f);

    if((*latime) % 4 != 0)
        *padding = 4 - (3 * (*latime)) % 4;
    else
        *padding = 0;

    fseek(f,0,SEEK_SET);

    // header

    int i;
    *header=(unsigned char*)malloc(sizeof(char)* 54);

    if(!header)
    {
        printf("Nu s-a putut aloca memorie pentru header");
        return;
    }

    for(i=0;i<54;i++)
        {
            unsigned char c;
            fread(&c,sizeof(unsigned char),1,f);
            (*header)[i]=c;
        }

    fclose(f);

}

void IncarcaImagine(pixel **v,int latime,int inaltime,int padding,char *fisier)
{

    *v=(pixel*)malloc(sizeof(pixel)*latime*inaltime);

    if(!(*v))
    {
         printf("Nu s-a putut aloca memorie pentru vector");
        return;
    }

    pixel*aux;
    aux=(pixel*)malloc(sizeof(pixel)*latime);

    if(!aux)
    {
        printf("Nu s-a putut aloca memorie pentru vector");
        return;
    }

    FILE*f=fopen(fisier,"rb");

    if(!f)
    {
        printf("Nu s-a gasit fisierul cu imaginea initiala: %s pentru liniarizarea ei",fisier);
        return;
    }

    fseek(f,sizeof(unsigned char)*54,SEEK_SET);

    int j,i,nr=latime*(inaltime-1);
    pixel pix;

    for(i=0;i<inaltime;i++)
    {
        for(j=0;j<latime;j++)
        {
            fread(&pix,sizeof(pixel),1,f);
            (*v)[nr++]=pix;
        }

        nr=nr-2*latime;
        fseek(f,sizeof(char)*padding,SEEK_CUR);
    }
    fclose(f);
}

void DescarcaImagine(pixel *v,int latime, int inaltime,int padding,char *fisier,unsigned char *header)
{
    int i,j,poz=latime*inaltime-latime;
    unsigned char c='0';

    FILE*f=fopen(fisier,"wb");

    fwrite(header,sizeof(unsigned char),54,f);
   // for(i=0;i<54;i++)
  //      fwrite(&header[i],sizeof(unsigned char),1,f);

    for(i=0;i<inaltime;i++)
    {
        for(j=0;j<latime;j++)
        {
         fwrite(&v[poz++],sizeof(pixel),1,f);
       /*  fwrite(&v[poz].b,sizeof(unsigned char),1,f);
         fwrite(&v[poz].g,sizeof(unsigned char),1,f);
         fwrite(&v[poz].r,sizeof(unsigned char),1,f);
         poz++;
         */
        }

            fwrite(&c,sizeof(unsigned char),padding,f);
        poz=poz-2*latime;
    }

    fclose(f);
}

void Durstenfeld(unsigned int **perm,int latime,int inaltime, unsigned int *R) /// BUN
{
    unsigned int r,aux,n;
    int i;

    n=latime*inaltime;

    *perm=(unsigned int*)malloc(sizeof(unsigned int)*n);

    if(!*perm)
    {
        printf("Eroare la alocarea de memorie a vectorului");
        return;
    }

    for(i=n-1;i>=0;i--)
        (*perm)[i]=i;

    for(i=n-1;i>=1;i--)
    {
        r=R[n-i]%(i+1);

        aux=(*perm)[r];
        (*perm)[r]=(*perm)[i];
        (*perm)[i]=aux;
    }
}

void permutarePixeli(pixel **imag_liniar_permutat,pixel*imag_liniar,unsigned int *perm,int latime,int inaltime)
{
    int i,n;
    n=latime*inaltime;
    *imag_liniar_permutat=(pixel*)malloc(sizeof(pixel)*n);

    if(!*imag_liniar_permutat)
    {
        printf("Eroare la alocarea de memorie a vectorului");
        return;
    }

    for(i=0;i<n;i++)
        (*imag_liniar_permutat)[perm[i]]=imag_liniar[i];
}

unsigned char octet_nr(unsigned int x,int nr)
{
    /// returneaza octetul nr
    unsigned char *p;
    p=(unsigned char*)&x;
    int i;
    for(i=0;i<nr;i++)
        p++;
    unsigned char y;
    y=*p;

    return y;
}

void xorFinal(pixel **imag_liniar_criptat,pixel *imag_liniar,unsigned int *R,int latime,int inaltime, unsigned int SV)
{
    int n=latime*inaltime,i;

    *imag_liniar_criptat=(pixel*)malloc(sizeof(pixel)*n);

    if(!*imag_liniar_criptat)
    {
        printf("Eroare la alocarea de memorie a vectorului");
        return;
    }

        (*imag_liniar_criptat)[0].b=(octet_nr(SV,0))^(imag_liniar[0].b)^(octet_nr(R[n],0));
        (*imag_liniar_criptat)[0].g=(octet_nr(SV,1))^(imag_liniar[0].g)^(octet_nr(R[n],1));
        (*imag_liniar_criptat)[0].r=(octet_nr(SV,2))^(imag_liniar[0].r)^(octet_nr(R[n],2));

    for(i=1;i<n;i++)
    {
        (*imag_liniar_criptat)[i].b = ( (*imag_liniar_criptat)[i-1].b ) ^ (imag_liniar[i].b) ^ (octet_nr(R[n+i],0));
        (*imag_liniar_criptat)[i].g = ( (*imag_liniar_criptat)[i-1].g ) ^ (imag_liniar[i].g) ^ (octet_nr(R[n+i],1));
        (*imag_liniar_criptat)[i].r = ( (*imag_liniar_criptat)[i-1].r ) ^ (imag_liniar[i].r) ^ (octet_nr(R[n+i],2));
    }
}

void criptareImag(char*imag_init,char*imag_final,char*fisier_cheie,int *ok)
{
    FILE*Init=fopen(imag_init,"r");
    FILE*Final=fopen(imag_final,"wb");
    FILE*Cheie=fopen(fisier_cheie,"r");

    if(!Init)
    {
        printf("Eroare la deschiderea imaginii %s \n",imag_init);
        (*ok)=0;
        return;
    }

    if(!Cheie)
    {
        printf("Eroare la deschiderea fisierului %s\n",fisier_cheie);
         (*ok)=0;
        return;
    }

    unsigned int *R,*Perm,R0,SV;

    pixel *imag_liniar_criptat;
    pixel *imag_liniar,*imag_liniar_permutat;

    int latime,inaltime,padding;
    unsigned char * header;

    fscanf(Cheie,"%u %u",&R0,&SV);
    dimensiuni_imagine_header(&header,imag_init,&inaltime,&latime,&padding);

    IncarcaImagine(&imag_liniar,latime,inaltime,padding,imag_init);  /// transforma imaginea in mod liniar

    XorShift32(&R,latime,inaltime,R0);          /// construieste prin XORSHIFT32 un set de numere pseudo-aleatoare

    Durstenfeld(&Perm,latime,inaltime,R);                 /// Prin alg lui Durstenfeld genereaza o permutare

    permutarePixeli(&imag_liniar_permutat,imag_liniar,Perm,latime,inaltime);    /// Se permuta pixelii

    xorFinal(&imag_liniar_criptat,imag_liniar_permutat,R,latime,inaltime,SV);

    DescarcaImagine(imag_liniar_criptat,latime,inaltime,padding,imag_final,header);

    fclose(Init);
    fclose(Final);
    fclose(Cheie);

}

void invers_perm(unsigned int **perm_invers,unsigned int *perm,int latime,int inaltime)
{
    int n=latime*inaltime,i;

    *perm_invers=(unsigned int*)malloc(sizeof(unsigned int)*n);

    if(!perm_invers)
        {
        printf("eroare");
        return;
        }

   for(i=0;i<n;i++)
    (*perm_invers)[perm[i]]=i;

}

void inversXOR(pixel **imag_liniar_decript, pixel*imag_liniar,int latime,int inaltime,unsigned int *R,unsigned int SV)
{
    int i,n=latime*inaltime;
    *imag_liniar_decript=(pixel*)malloc(sizeof(pixel)*n);

    if(!*imag_liniar_decript)
    {
        printf("Eroare");
        return;
    }

        (*imag_liniar_decript)[0].b=(octet_nr(SV,0))^(imag_liniar[0].b)^(octet_nr(R[n],0));
        (*imag_liniar_decript)[0].g=(octet_nr(SV,1))^(imag_liniar[0].g)^(octet_nr(R[n],1));
        (*imag_liniar_decript)[0].r=(octet_nr(SV,2))^(imag_liniar[0].r)^(octet_nr(R[n],2));

    for(i=1;i<n;i++)
    {
        (*imag_liniar_decript)[i].b = ( imag_liniar[i-1].b ) ^ (imag_liniar)[i].b ^ (octet_nr(R[n+i],0));
        (*imag_liniar_decript)[i].g = ( imag_liniar[i-1].g ) ^ (imag_liniar)[i].g ^ (octet_nr(R[n+i],1));
        (*imag_liniar_decript)[i].r = ( imag_liniar[i-1].r ) ^ (imag_liniar)[i].r ^ (octet_nr(R[n+i],2));
    }
}

void permutareFinala(pixel *imag_liniar_final,int latime,int inaltime,unsigned int *Perm_invers)
{
    int i,n=latime*inaltime;
    pixel *aux;

    aux=(pixel*)malloc(sizeof(pixel)*n);
    if(!aux)
    {
        printf("EROARE");
            return;
    }

    for(i=0;i<n;i++)
        aux[i]=imag_liniar_final[Perm_invers[i]];

    for(i=0;i<n;i++)
        imag_liniar_final[i]=aux[i];

    free(aux);
}

void decriptareImag(char*imag_init,char*imag_final,char*fisier_cheie,int *ok)
{
    FILE*Init=fopen(imag_init,"rb");
    FILE*Cheie=fopen(fisier_cheie,"r");
    FILE*Final=fopen(imag_final,"wb");
    if(!Init)
    {
        printf("Eroare la deschiderea imaginii");
        (*ok)=0;
        return;
    }

    if(!Cheie)
    {
        printf("Eroare la deschiderea fisierului ce contine cheia secreta");
        (*ok)=0;
        return;
    }

    int latime,inaltime,padding;
    unsigned char * header;
    unsigned int *R,*Perm,*Perm_invers,R0,SV;

    pixel *imag_liniar_xor;
    pixel *imag_liniar;
    pixel *imag_decript;

    fscanf(Cheie,"%u %u",&R0,&SV);

    dimensiuni_imagine_header(&header,imag_init,&inaltime,&latime,&padding);

    IncarcaImagine(&imag_liniar,latime,inaltime,padding,imag_init);   /// transforma imaginea in mod liniar

    XorShift32(&R,latime,inaltime,R0);          /// construieste prin XORSHIFT32 un set de numere pseudo-aleatoare

    Durstenfeld(&Perm,latime,inaltime,R);                 /// Prin alg lui Durstenfeld genereaza o permutare

    invers_perm(&Perm_invers,Perm,latime,inaltime);

    inversXOR(&imag_liniar_xor,imag_liniar,latime,inaltime,R,SV);

    permutarePixeli(&imag_decript,imag_liniar_xor,Perm_invers,latime,inaltime);

    DescarcaImagine(imag_decript,latime,inaltime,padding,imag_final,header);

    fclose(Final);
    fclose(Init);
    fclose(Cheie);
}

void chiTest(char*imag)
{
    FILE*f=fopen(imag,"rb");

    if(!f)
    {
        printf("Nu s-a gasit imaginea");
        return;
    }
    unsigned int *frecvR,*frecvG,*frecvB;
    double chi_r=0,chi_g=0,chi_b=0,fmed;
    int i,j,latime,inaltime,padding;
    unsigned char*header;
    pixel pix;

    dimensiuni_imagine_header(&header,imag,&inaltime,&latime,&padding);

    frecvR=(unsigned int*)calloc(256,sizeof(unsigned int));
    frecvG=(unsigned int*)calloc(256,sizeof(unsigned int));
    frecvB=(unsigned int*)calloc(256,sizeof(unsigned int));

    if(!frecvR)
    {
        printf("Nu s-a putut aloca memorie");
        return;
    }

    if(!frecvG)
    {
        printf("Nu s-a putut aloca memorie");
        return;
    }

    if(!frecvB)
    {
        printf("Nu s-a putut aloca memorie");
        return;
    }

    fmed=latime*inaltime/256;

   for(i=0;i<256;i++)
    frecvB[i]=frecvG[i]=frecvR[i]=0;

    fseek(f,sizeof(unsigned char)*54,SEEK_SET);

   for(i=0;i<inaltime;i++)
    {
    for(j=0;j<latime;j++)
    {
       fread(&pix,sizeof(pixel),1,f);
       frecvB[pix.b]++;
       frecvG[pix.g]++;
       frecvR[pix.r]++;
    }
    fseek(f,sizeof(char)*padding,SEEK_CUR);
    }

    for(i=0;i<256;i++)
    {
        chi_b=chi_b+(frecvB[i]-fmed)*(frecvB[i]-fmed);
        chi_g=chi_g+(frecvG[i]-fmed)*(frecvG[i]-fmed);
        chi_r=chi_r+(frecvR[i]-fmed)*(frecvR[i]-fmed);
    }

    chi_b/=fmed;
    chi_g/=fmed;
    chi_r/=fmed;

    printf("Pentru imaginea %s, testul are pe canalul rosu %.2f\n",imag,chi_r);
    printf("Pentru imaginea %s, testul are pe canalul verde %.2f\n",imag,chi_g);
    printf("Pentru imaginea %s, testul are pe canalul albastru %.2f\n\n",imag,chi_b);

}

void cript_decript_chi()
{
    char input[30],encript[30],output[30],secret_key[30];
    int ok1=1,ok2=1;

    FILE*fin1=fopen("imagini_criptare.txt","r");

    if(!fin1)
    {
        printf("Nu s-a putut gasi fisierul imagini_criptare.txt ");
        return;
    }

    FILE*fin2=fopen("imagini_decriptare.txt","r");

    if(!fin2)
    {
         printf("Nu s-a putut gasi fisierul imagini_decriptare.txt ");
        return;
    }

    fscanf(fin1,"%s",input);
    fscanf(fin1,"%s",encript);
    fscanf(fin1,"%s",secret_key);

    criptareImag(input,encript,secret_key,&ok1);

    fscanf(fin2,"%s",encript);
    fscanf(fin2,"%s",output);
    fscanf(fin2,"%s",secret_key);

    if(ok1==1)
        decriptareImag(encript,output,secret_key,&ok2);

    if(ok1+ok2==2)
    {
    chiTest(input);
    chiTest(encript);
    }
    else printf("Nu s-au efectuat testele chi pentru ca nu s-a putut face criptarea / decriptarea\n");

    fclose(fin1);
    fclose(fin2);
}

int main()
{
    cript_decript_chi();

    return 0;
}
