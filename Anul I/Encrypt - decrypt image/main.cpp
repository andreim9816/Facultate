#include
<stdio.h>
#include
<stdlib.h>
#include
<math.h>
#include
<string.h>

typedef struct {
unsigned char b;
unsigned char g;
unsigned char r;
} pixel;

typedef struct {
int l;
int c;
float corr;
int imagine;
} fereastra;

typedef struct {
int x, y;
} punct;

void XorShift32(unsigned int **v, int latime, int inaltime, unsigned int seed) {
/* functie care va genera in vectorul v numere pseudo-aleatoare cu ajutorul
algoritmului XORSHIFT32 */

int n = 2 * inaltime * latime, i;
unsigned int r;

*v = (unsigned int *) malloc(sizeof(unsigned int) * n);
if (!v) {
printf("Eroare la alocarea de memorie pentru vectorul de numere aleatoare ");
return;
}

(*v)[0] = seed;

for (i = 1; i < n; i++) {
r = (*v)[i - 1];
r = r ^ r << 13;
r = r ^ r >> 17;
r = r ^ r << 5;
(*v)[i] = r;
}
}

void dimensiuni_imagine_header(unsigned char **header, char *nume_fisier, int *inaltime, int *latime, int *padding) {
/* functie care retine headerul, latimea,inaltimea si paddingul unei imagini */
FILE *f = fopen(nume_fisier, "rb");
if (!f) {
printf("Nu s-a gasit fisierul cu imaginea initiala: %s", nume_fisier);
return;
}

fseek(f, 18, SEEK_SET);
fread(latime, sizeof(unsigned int), 1, f);
fread(inaltime, sizeof(unsigned int), 1, f);

if ((*latime) % 4 != 0)
*padding = 4 - (3 * (*latime)) % 4;
else
*padding = 0;

fseek(f, 0, SEEK_SET);

// header

int i;
*header = (unsigned char *) malloc(sizeof(char) * 54);

if (!header) {
printf("Nu s-a putut aloca memorie pentru header");
return;
}

for (i = 0; i < 54; i++) {
unsigned char c;
fread(&c, sizeof(unsigned char), 1, f);
(*header)[i] = c;
}

fclose(f);

}

void IncarcaImagine(pixel **v, int latime, int inaltime, int padding, char *fisier) {
/* functie care liniarizeaza o imagine */
*v = (pixel *) malloc(sizeof(pixel) * latime * inaltime);

if (!(*v)) {
printf("Nu s-a putut aloca memorie pentru vector");
return;
}

FILE *f = fopen(fisier, "rb");

if (!f) {
printf("Nu s-a gasit fisierul cu imaginea initiala: %s pentru liniarizarea ei", fisier);
return;
}

fseek(f, sizeof(unsigned char) * 54, SEEK_SET);

int j, i, nr = latime * (inaltime - 1);
pixel pix;

for (i = 0; i < inaltime; i++) {
for (j = 0; j < latime; j++) {
fread(&pix, sizeof(pixel), 1, f);
(*v)[nr++] = pix;
}

nr = nr - 2 * latime;
fseek(f, sizeof(char) * padding, SEEK_CUR);
}
fclose(f);
}

void DescarcaImagine(pixel *v, int latime, int inaltime, int padding, char *fisier, unsigned char *header) {
/* functie care deliniarizeaza o imagine */
int i, j, poz = latime * inaltime - latime;
unsigned char c = '0';

FILE *f = fopen(fisier, "wb");

fwrite(header, sizeof(unsigned char), 54, f);

for (i = 0; i < inaltime; i++) {
for (j = 0; j < latime; j++)
fwrite(&v[poz++], sizeof(pixel), 1, f);

fwrite(&c, sizeof(unsigned char), padding, f);
poz = poz - 2 * latime;
}

fclose(f);
}

void Durstenfeld(unsigned int **perm, int latime, int inaltime, unsigned int *R) {
/* functie care genereaza o permutarea aleatoare, prin intermediul algoritmului lui Durstenfeld */
unsigned int r, aux, n;
int i;
n = latime * inaltime;

*perm = (unsigned int *) malloc(sizeof(unsigned int) * n);

if (!*perm) {
printf("Eroare la alocarea de memorie a vectorului");
return;
}

for (i = n - 1; i >= 0; i--)
(*perm)[i] = i;

for (i = n - 1; i >= 1; i--) {
r = R[n - i] % (i + 1);

aux = (*perm)[r];
(*perm)[r] = (*perm)[i];
(*perm)[i] = aux;
}

}

void permutarePixeli(pixel **imag_liniar_permutat, pixel *imag_liniar, unsigned int *perm, int latime, int inaltime) {
/*functie care permuta pixelii imaginii liniarizate, pe baza unei permutari date */
int i, n;
n = latime * inaltime;
*imag_liniar_permutat = (pixel *) malloc(sizeof(pixel) * n);

if (!*imag_liniar_permutat) {
printf("Eroare la alocarea de memorie a vectorului");
return;
}

for (i = 0; i < n; i++)
(*imag_liniar_permutat)[perm[i]] = imag_liniar[i];
}

unsigned char octet_nr(unsigned int x, int nr) {
/* functie care returneaza octetul nr al unui numar x */
unsigned char *p;
p = (unsigned char *) &x;
int i;
for (i = 0; i < nr; i++)
p++;
unsigned char y;
y = *p;

return y;
}

void
xorFinal(pixel **imag_liniar_criptat, pixel *imag_liniar, unsigned int *R, int latime, int inaltime, unsigned int SV) {
/* functie care aplica operatia xor pe pixelii liniarizati ai unei matrice */
int n = latime * inaltime, i;
*imag_liniar_criptat = (pixel *) malloc(sizeof(pixel) * n);

if (!*imag_liniar_criptat) {
printf("Eroare la alocarea de memorie a vectorului");
return;
}

(*imag_liniar_criptat)[0].b = (octet_nr(SV, 0)) ^ (imag_liniar[0].b) ^ (octet_nr(R[n], 0));
(*imag_liniar_criptat)[0].g = (octet_nr(SV, 1)) ^ (imag_liniar[0].g) ^ (octet_nr(R[n], 1));
(*imag_liniar_criptat)[0].r = (octet_nr(SV, 2)) ^ (imag_liniar[0].r) ^ (octet_nr(R[n], 2));

for (i = 1; i < n; i++) {
(*imag_liniar_criptat)[i].b = ((*imag_liniar_criptat)[i - 1].b) ^ (imag_liniar[i].b) ^ (octet_nr(R[n + i], 0));
(*imag_liniar_criptat)[i].g = ((*imag_liniar_criptat)[i - 1].g) ^ (imag_liniar[i].g) ^ (octet_nr(R[n + i], 1));
(*imag_liniar_criptat)[i].r = ((*imag_liniar_criptat)[i - 1].r) ^ (imag_liniar[i].r) ^ (octet_nr(R[n + i], 2));

}

}

void criptareImag(char *imag_init, char *imag_final, char *fisier_cheie, int *ok) {
/* functia principala care cripteaza o imagine */

FILE *Init = fopen(imag_init, "r");
FILE *Final = fopen(imag_final, "wb");
FILE *Cheie = fopen(fisier_cheie, "r");

if (!Init) {
printf("Eroare la deschiderea imaginii %s \n", imag_init);
(*ok) = 0;
return;
}

if (!Cheie) {
printf("Eroare la deschiderea fisierului %s\n", fisier_cheie);
(*ok) = 0;
return;
}

unsigned int *R, *Perm, R0, SV;

pixel *imag_liniar_criptat;
pixel *imag_liniar, *imag_liniar_permutat;

int latime, inaltime, padding;
unsigned char *header;

fscanf(Cheie, "%u %u", &R0, &SV); // citeste din fisier cheia secreta si seed-ul pentru algoritmul lui Durstenfeld

dimensiuni_imagine_header(&header, imag_init, &inaltime, &latime, &padding);

IncarcaImagine(&imag_liniar, latime, inaltime, padding, imag_init);  // transforma imaginea in mod liniar

XorShift32(&R, latime, inaltime, R0);     // construieste prin XORSHIFT32 un set de numere pseudo-aleatoare

Durstenfeld(&Perm, latime, inaltime, R);          // Prin alg lui Durstenfeld genereaza o permutare

permutarePixeli(&imag_liniar_permutat, imag_liniar, Perm, latime, inaltime);   // Se permuta pixelii

xorFinal(&imag_liniar_criptat, imag_liniar_permutat, R, latime, inaltime, SV); // se xor-eaza pixelii

DescarcaImagine(imag_liniar_criptat, latime, inaltime, padding, imag_final,
header); // se deliniarizeaza imaginea si se salveaza in memoria externa

fclose(Init);
fclose(Final);
fclose(Cheie);

free(R);
free(Perm);
free(imag_liniar);
free(imag_liniar_criptat);
free(imag_liniar_permutat);

}

void invers_perm(unsigned int **perm_invers, unsigned int *perm, int latime, int inaltime) {
/* functie care genereaza inversa unei permutari */
int n = latime * inaltime, i;

*perm_invers = (unsigned int *) malloc(sizeof(unsigned int) * n);

if (!perm_invers) {
printf("eroare");
return;
}

for (i = 0; i < n; i++)
(*perm_invers)[perm[i]] = i;

}

void
inversXOR(pixel **imag_liniar_decript, pixel *imag_liniar, int latime, int inaltime, unsigned int *R, unsigned int SV) {
/* functie care aplica operatia xor pe pixelii liniarizati ai matricei, obtinand astfel varianta nemodificata
a acestora */

int i, n = latime * inaltime;
*imag_liniar_decript = (pixel *) malloc(sizeof(pixel) * n);

if (!*imag_liniar_decript) {
printf("Eroare");
return;
}

(*imag_liniar_decript)[0].b = (octet_nr(SV, 0)) ^ (imag_liniar[0].b) ^ (octet_nr(R[n], 0));
(*imag_liniar_decript)[0].g = (octet_nr(SV, 1)) ^ (imag_liniar[0].g) ^ (octet_nr(R[n], 1));
(*imag_liniar_decript)[0].r = (octet_nr(SV, 2)) ^ (imag_liniar[0].r) ^ (octet_nr(R[n], 2));

for (i = 1; i < n; i++) {
(*imag_liniar_decript)[i].b = (imag_liniar[i - 1].b) ^ (imag_liniar)[i].b ^ (octet_nr(R[n + i], 0));
(*imag_liniar_decript)[i].g = (imag_liniar[i - 1].g) ^ (imag_liniar)[i].g ^ (octet_nr(R[n + i], 1));
(*imag_liniar_decript)[i].r = (imag_liniar[i - 1].r) ^ (imag_liniar)[i].r ^ (octet_nr(R[n + i], 2));
}
}

void decriptareImag(char *imag_init, char *imag_final, char *fisier_cheie, int *ok) {
FILE *Init = fopen(imag_init, "rb");
FILE *Cheie = fopen(fisier_cheie, "r");
FILE *Final = fopen(imag_final, "wb");
if (!Init) {
printf("Eroare la deschiderea imaginii");
(*ok) = 0;
return;
}

if (!Cheie) {
printf("Eroare la deschiderea fisierului ce contine cheia secreta");
(*ok) = 0;
return;
}

int latime, inaltime, padding;
unsigned char *header;
unsigned int *R, *Perm, *Perm_invers, R0, SV;

pixel *imag_liniar_xor;
pixel *imag_liniar;
pixel *imag_decript;

fscanf(Cheie, "%u %u", &R0, &SV);

dimensiuni_imagine_header(&header, imag_init, &inaltime, &latime, &padding);

IncarcaImagine(&imag_liniar, latime, inaltime, padding, imag_init);   // transforma imaginea in mod liniar

XorShift32(&R, latime, inaltime, R0);          // construieste prin XORSHIFT32 un set de numere pseudo-aleatoare

Durstenfeld(&Perm, latime, inaltime, R);                 // Prin alg lui Durstenfeld genereaza o permutare

invers_perm(&Perm_invers, Perm, latime, inaltime);  // se genereaza permutarea inversa

inversXOR(&imag_liniar_xor, imag_liniar, latime, inaltime, R, SV); // se xor-eaza pixelii

permutarePixeli(&imag_decript, imag_liniar_xor, Perm_invers, latime,
inaltime); // se permuta pixelii pe baza permutarii inverse

DescarcaImagine(imag_decript, latime, inaltime, padding, imag_final, header); // se deliniarizeaza imaginea

fclose(Final);
fclose(Init);
fclose(Cheie);

free(R);
free(Perm);
free(Perm_invers);
free(imag_decript);
free(imag_liniar);
free(imag_liniar_xor);
free(header);

}

void chiTest(char *imag) {
FILE *f = fopen(imag, "rb");

if (!f) {
printf("Nu s-a gasit imaginea");
return;
}
unsigned int *frecvR, *frecvG, *frecvB;
double chi_r = 0, chi_g = 0, chi_b = 0, fmed;
int i, j, latime, inaltime, padding;
unsigned char *header;
pixel pix;

dimensiuni_imagine_header(&header, imag, &inaltime, &latime, &padding);

frecvR = (unsigned int *) calloc(256, sizeof(unsigned int));
frecvG = (unsigned int *) calloc(256, sizeof(unsigned int));
frecvB = (unsigned int *) calloc(256, sizeof(unsigned int));

if (!frecvR) {
printf("Nu s-a putut aloca memorie");
return;
}

if (!frecvG) {
printf("Nu s-a putut aloca memorie");
return;
}

if (!frecvB) {
printf("Nu s-a putut aloca memorie");
return;
}

fmed = latime * inaltime / 256;

fseek(f, sizeof(unsigned char) * 54, SEEK_SET);

for (i = 0; i < inaltime; i++) {
for (j = 0; j < latime; j++) {
fread(&pix, sizeof(pixel), 1, f);
frecvB[pix.b]++;
frecvG[pix.g]++;
frecvR[pix.r]++;
}
fseek(f, sizeof(char) * padding, SEEK_CUR);
}

for (i = 0; i < 256; i++) {
chi_b = chi_b + (frecvB[i] - fmed) * (frecvB[i] - fmed);
chi_g = chi_g + (frecvG[i] - fmed) * (frecvG[i] - fmed);
chi_r = chi_r + (frecvR[i] - fmed) * (frecvR[i] - fmed);
}

chi_b /= fmed;
chi_g /= fmed;
chi_r /= fmed;

printf("Pentru imaginea %s, testul are pe canalul rosu %.2f\n", imag, chi_r);
printf("Pentru imaginea %s, testul are pe canalul verde %.2f\n", imag, chi_g);
printf("Pentru imaginea %s, testul are pe canalul albastru %.2f\n\n", imag, chi_b);

free(frecvB);
free(frecvG);
free(frecvR);
free(header);

}


int main() {

char *input, *encript, *output, *secret_key;
int ok1 = 1, ok2 = 1;

input = (char *) malloc(sizeof(char) * 30);
if (!input) {
printf("Nu s-a putut aloca memorie");
return 0;
}

encript = (char *) malloc(sizeof(char) * 30);
if (!encript) {
printf("Nu s-a putut aloca memorie");
return 0;
}

output = (char *) malloc(sizeof(char) * 30);
if (!output) {
printf("Nu s-a putut aloca memorie");
return 0;
}

secret_key = (char *) malloc(sizeof(char) * 30);
if (!secret_key) {
printf("Nu s-a putut aloca memorie");
return 0;
}

FILE *fin1 = fopen("imagini_criptare.txt", "r");

if (!fin1) {
printf("Nu s-a putut gasi fisierul imagini_criptare.txt ");
return 0;
}

FILE *fin2 = fopen("imagini_decriptare.txt", "r");

if (!fin2) {
printf("Nu s-a putut gasi fisierul imagini_decriptare.txt ");
return 0;
}

fscanf(fin1, "%s", input);
fscanf(fin1, "%s", encript);
fscanf(fin1, "%s", secret_key);

criptareImag(input, encript, secret_key, &ok1);

fscanf(fin2, "%s", encript);
fscanf(fin2, "%s", output);
fscanf(fin2, "%s", secret_key);

if (ok1 == 1)
decriptareImag(encript, output, secret_key, &ok2);

if (ok2 == 1) {
chiTest(input);
chiTest(encript);
} else {
printf("Nu s-au efectuat testele chi pentru ca nu s-a putut face criptarea / decriptarea\n");
return 0;
}

fclose(fin1);
fclose(fin2);

free(input);
free(output);
free(encript);
free(secret_key);

return 0;
}
