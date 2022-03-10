#include <stdio.h>
#include <stdlib.h>
#include<math.h>
#include<string.h>

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

void grayscale_image(char *nume_fisier_sursa, char *nume_fisier_destinatie) {
    FILE *fin, *fout;
    unsigned int dim_img, latime_img, inaltime_img;
    unsigned char pRGB[3], aux;

    //  printf("nume_fisier_sursa = %s \n",nume_fisier_sursa);

    fin = fopen(nume_fisier_sursa, "rb");
    if (fin == NULL) {
        printf("Nu am gasit imaginea sursa din care citesc \n");
        return;
    }

    fout = fopen(nume_fisier_destinatie, "wb+");

    fseek(fin, 2, SEEK_SET);
    fread(&dim_img, sizeof(unsigned int), 1, fin);
    // printf("Dimensiunea imaginii in octeti: %u\n", dim_img);

    fseek(fin, 18, SEEK_SET);
    fread(&latime_img, sizeof(unsigned int), 1, fin);
    fread(&inaltime_img, sizeof(unsigned int), 1, fin);
    //  printf("Dimensiunea imaginii in pixeli (latime x inaltime): %u x %u\n",latime_img, inaltime_img);

    //copiaza octet cu octet imaginea initiala in cea noua
    fseek(fin, 0, SEEK_SET);
    unsigned char c;
    while (fread(&c, 1, 1, fin) == 1) {
        fwrite(&c, 1, 1, fout);
        fflush(fout);
    }
    fclose(fin);

    //calculam padding-ul pentru o linie
    int padding;
    if (latime_img % 4 != 0)
        padding = 4 - (3 * latime_img) % 4;
    else
        padding = 0;

    fseek(fout, 54, SEEK_SET);
    int i, j;
    for (i = 0; i < inaltime_img; i++) {
        for (j = 0; j < latime_img; j++) {
            //citesc culorile pixelului
            fread(pRGB, 3, 1, fout);
            //fac conversia in pixel gri
            aux = 0.299 * pRGB[2] + 0.587 * pRGB[1] + 0.114 * pRGB[0];
            pRGB[0] = pRGB[1] = pRGB[2] = aux;
            fseek(fout, -3, SEEK_CUR);
            fwrite(pRGB, 3, 1, fout);
            fflush(fout);
        }
        fseek(fout, padding, SEEK_CUR);
    }
    fclose(fout);
}

void dimensiuni_imagine(char *nume_fisier, int *inaltime, int *latime, int *padding) {
    FILE *f = fopen(nume_fisier, "rb");
    if (!f) {
        printf("Nu s-a gasit fisierul cu imaginea initiala: %s \n", nume_fisier);
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

    fclose(f);

}

void imagToMatrice(char *imag, pixel ***v, int inaltime, int latime, int padding) {
    // functie care primind o imagine, o transforma in matrice
    int i, j;
    pixel c;

    *v = (pixel **) malloc(sizeof(pixel *) * inaltime);

    if (!*v) {
        printf("Eroare la alocarea de memorie \n");
        return;
    }

    FILE *fin = fopen(imag, "rb");

    if (!fin) {
        printf("Nu s-a putut gasi imaginea %s \n", imag);
        return;
    }

    fseek(fin, 54 * sizeof(char), SEEK_SET);

    for (i = inaltime - 1; i >= 0; i--) {
        (*v)[i] = (pixel *) malloc(sizeof(pixel) * latime);

        if (!(*v)[i]) {
            printf("Eroare la alocarea de memorie\n");

            for (j = inaltime - 1; j >= i; j--)
                free((*v)[j]);
            free(*v);

            return;
        }
        for (j = 0; j < latime; j++) {
            fread(&c, sizeof(pixel), 1, fin);
            (*v)[i][j].b = c.b;
            (*v)[i][j].g = c.g;
            (*v)[i][j].r = c.r;
        }
        fseek(fin, padding, SEEK_CUR);
    }

    fclose(fin);

}

void matriceToimagine(char *imag_init, char *imag_fin, pixel **v, int inaltime, int latime, int padding) {

    FILE *fin, *fout;
    fin = fopen(imag_init, "rb");
    fout = fopen(imag_fin, "wb");

    if (fin == NULL) {
        printf("Nu s-a gasit imaginea %s \n", imag_init);
        return;
    }


    int i, j;
    pixel pix = {'0', '0', '0'};
    char c;

    for (i = 0; i < 54; i++) {
        fread(&c, sizeof(char), 1, fin);
        fwrite(&c, sizeof(char), 1, fout);
    }

    for (i = inaltime - 1; i >= 0; i--) {
        for (j = 0; j < latime; j++) {
            fwrite(&v[i][j].b, sizeof(unsigned char), 1, fout);
            fwrite(&v[i][j].g, sizeof(unsigned char), 1, fout);
            fwrite(&v[i][j].r, sizeof(unsigned char), 1, fout);

        }
        fwrite(&pix, sizeof(pixel), padding, fout);
    }

    fclose(fin);
    fclose(fout);
}

float medie_pixeli(pixel **v, int inaltime, int latime, int linie, int coloana) {
    float S = 0;
    int i, j;

    for (i = linie + 0; i < linie + inaltime; i++)
        for (j = coloana + 0; j < coloana + latime; j++)
            S = S + v[i][j].r;

    S = S / latime;
    S = S / inaltime;

    return S;
}

float deviatie_standard(pixel **v, int inaltime, int latime, float med, int linie, int coloana) {
    int i, j;
    float S = 0;
    for (i = linie + 0; i < inaltime + linie; i++)
        for (j = coloana + 0; j < coloana + latime; j++)
            S = S + (v[i][j].r - med) * (v[i][j].r - med);

    S = S / (latime * inaltime - 1);
    S = sqrt(S);

    return S;
}

float corelatie(pixel **imag_matrice, pixel **sablon_matrice, int inaltime, int latime, int linie,
                int coloana, float f_med, float s_med, float deviatie_mat, float deviatie_sablon) {
    int i, j;
    float S = 0;

    for (i = 0; i < inaltime; i++)
        for (j = 0; j < latime; j++)
            S = S + (imag_matrice[linie + i][coloana + j].r - f_med) * (sablon_matrice[i][j].r - s_med);


    S = S / deviatie_mat;
    S = S / deviatie_sablon;
    S = S / (latime * inaltime);

    return S;

}

void template_matching_sablon(char *imag, pixel **imag_matrice, char *sablon, int nr_sablon, float prag, fereastra **D,
                              int *n) {

    FILE *finI = fopen(imag, "rb");
    FILE *finS = fopen(sablon, "rb");

    if (!finI) {
        printf("Nu s-a putut gasi imaginea %s \n", imag);
        return;
    }

    if (!finS) {
        printf("Nu s-a putut gasi imaginea %s \n", sablon);
        return;
    }

    int latime_imag, inaltime_imag;
    int latime_sablon, inaltime_sablon;
    int pad_imag, pad_sablon, i, j;
    float S_med, f_med, S_dev, f_dev, corr;

    pixel **sablon_matrice;

    dimensiuni_imagine(imag, &inaltime_imag, &latime_imag, &pad_imag);
    dimensiuni_imagine(sablon, &inaltime_sablon, &latime_sablon, &pad_sablon);

    char sablon_gray[35];
    // creeaza denumirea imaginii noi care va fi transformata in grayscale
    strcpy(sablon_gray, sablon);
    strcpy(sablon_gray + strlen(sablon_gray) - 4, "_grey.bmp");
    sablon_gray[strlen(sablon_gray)] = '\0';

    grayscale_image(sablon, sablon_gray); // transforma sablonul grayscale

    imagToMatrice(sablon_gray, &sablon_matrice, inaltime_sablon, latime_sablon,
                  pad_sablon); // transforma sablonul in matrice

    S_med = medie_pixeli(sablon_matrice, inaltime_sablon, latime_sablon, 0,
                         0);    // intensitatea medie a pixelilor a sablonului
    S_dev = deviatie_standard(sablon_matrice, inaltime_sablon, latime_sablon, S_med, 0,
                              0); // deviatia standard a sablonului

    for (i = 0; i <= inaltime_imag - inaltime_sablon; i++)
        for (j = 0; j < latime_imag - latime_sablon; j++) {
            f_med = medie_pixeli(imag_matrice, inaltime_sablon, latime_sablon, i,
                                 j); // intensitatea medie a pixelilor pentru o portiune din matrice
            f_dev = deviatie_standard(imag_matrice, inaltime_sablon, latime_sablon, f_med, i,
                                      j); // deviatia standard a pixelilor pentru o portiune din matrice

            corr = corelatie(imag_matrice, sablon_matrice, inaltime_sablon, latime_sablon, i, j, f_med, S_med, f_dev,
                             S_dev); // corelatia pentru coord (i,j)

            if (corr >= prag) // daca corelatia este mai mare decat pragul, se adauga in tabloul unidimensional *D
            {
                fereastra *aux = NULL;
                aux = (fereastra *) realloc(*D, sizeof(fereastra) * (*n + 1));

                if (!aux) {
                    printf("Eroare la alocarea de memorie\n ");
                    for (i = 0; i < *n; i++)
                        free((D)[i]);
                    return;
                }
                *D = aux;
                (*D)[*n].c = j;
                (*D)[*n].l = i;
                (*D)[*n].corr = corr;
                (*D)[*n].imagine = nr_sablon;

                (*n)++;
            }
        }

}

void deseneaza_contur(pixel **imag_matrice, int inaltime_sablon, int latime_sablon, pixel culoare, fereastra x) {
    int i;
    int l = x.l;
    int c = x.c;

    for (i = l; i < l + inaltime_sablon; i++) {
        imag_matrice[i][c] = culoare;
        imag_matrice[i][c + latime_sablon - 1] = culoare;
    }

    for (i = c; i < c + latime_sablon; i++) {
        imag_matrice[l][i] = culoare;
        imag_matrice[l + inaltime_sablon - 1][i] = culoare;
    }
}

void marcheaza_cifre(pixel **imag_matrice, int inaltime, int latime, fereastra *D, int n) {
    int i;
    pixel culoare;
    for (i = 0; i < n; i++) {

        switch (D[i].imagine) {
            case 0:
                culoare.r = 255;
                culoare.g = 0;
                culoare.b = 0;
                break;
            case 1:
                culoare.r = 255;
                culoare.g = 255;
                culoare.b = 0;
                break;
            case 2:
                culoare.r = 0;
                culoare.g = 255;
                culoare.b = 0;
                break;
            case 3:
                culoare.r = 0;
                culoare.g = 255;
                culoare.b = 255;
                break;
            case 4:
                culoare.r = 255;
                culoare.g = 0;
                culoare.b = 255;
                break;
            case 5:
                culoare.r = 0;
                culoare.g = 0;
                culoare.b = 255;
                break;
            case 6:
                culoare.r = 192;
                culoare.g = 192;
                culoare.b = 192;
                break;
            case 7:
                culoare.r = 255;
                culoare.g = 140;
                culoare.b = 0;
                break;
            case 8:
                culoare.r = 128;
                culoare.g = 0;
                culoare.b = 128;
                break;
            case 9:
                culoare.r = 128;
                culoare.g = 0;
                culoare.b = 0;
                break;
                break;
        }
        deseneaza_contur(imag_matrice, inaltime, latime, culoare, D[i]);
    }
}

int min(int x, int y) {
    if (x < y)
        return x;
    return y;
}

int max(int x, int y) {
    if (x > y)
        return x;
    return y;
}

int intersect_ferestre(fereastra x, fereastra y, int inaltime_sablon, int latime_sablon) {
    punct StUp1, StDw1, DrUp1, DrDw1;
    punct StUp2, StDw2, DrUp2, DrDw2;

    StUp1.x = x.l;
    StUp1.y = x.c;

    DrDw1.x = StUp1.x + inaltime_sablon - 1;
    DrDw1.y = StUp1.y + latime_sablon - 1;

    DrUp1.x = StUp1.x;
    DrUp1.y = StUp1.y + latime_sablon - 1;

    StDw1.x = StUp1.x + inaltime_sablon - 1;
    StDw1.y = StUp1.y;

    StUp2.x = y.l;
    StUp2.y = y.c;

    DrDw2.x = StUp2.x + inaltime_sablon - 1;
    DrDw2.y = StUp2.y + latime_sablon - 1;

    DrUp2.x = StUp2.x;
    DrUp2.y = StUp2.y + latime_sablon - 1;

    StDw2.x = StUp2.x + inaltime_sablon - 1;
    StDw2.y = StUp2.y;

    int ok = 0;
    int a, b;

    if (StUp2.x >= StUp1.x && StUp2.x <= DrDw1.x && StUp2.y >= StUp1.y && StUp2.y <= DrDw1.y)
        ok = 1;

    if (DrUp2.x >= StUp1.x && DrUp2.x <= DrDw1.x && DrUp2.y >= StUp1.y && DrUp2.y <= DrDw1.y)
        ok = 1;

    if (StDw2.x >= StUp1.x && StDw2.x <= DrDw1.x && StDw2.y >= StUp1.y && StDw2.y <= DrDw1.y)
        ok = 1;

    if (DrDw2.x >= StUp1.x && DrDw2.x <= DrDw1.x && DrDw2.y >= StUp1.y && DrDw2.y <= DrDw1.y)
        ok = 1;


    if (StUp1.x >= StUp2.x && StUp1.x <= DrDw2.x && StUp1.y >= StUp2.y && StUp1.y <= DrDw2.y)
        ok = 1;

    if (DrUp1.x >= StUp2.x && DrUp1.x <= DrDw2.x && DrUp1.y >= StUp2.y && DrUp1.y <= DrDw2.y)
        ok = 1;

    if (StDw1.x >= StUp2.x && StDw1.x <= DrDw2.x && StDw1.y >= StUp2.y && StDw1.y <= DrDw2.y)
        ok = 1;

    if (DrDw1.x >= StUp2.x && DrDw1.x <= DrDw2.x && DrDw1.y >= StUp2.y && DrDw1.y <= DrDw2.y)
        ok = 1;
    if (ok == 0)
        return 0;

    a = min(DrDw1.x, DrDw2.x) - max(StUp1.x, StUp2.x) + 1;
    b = min(DrDw1.y, DrDw2.y) - max(StUp1.y, StUp2.y) + 1;

    return a * b;
}

float suprapunere(fereastra x, fereastra y, int inaltime_sablon, int latime_sablon) {
    float sup;
    float intersectie;

    intersectie = intersect_ferestre(x, y, inaltime_sablon, latime_sablon);

    sup = intersectie / (2.0 * inaltime_sablon * latime_sablon - intersectie);

    return sup;

}

void eliminare(fereastra *D, int n, int poz) {
    int i;
    for (i = poz; i < n - 1; i++)
        D[i] = D[i + 1];
}

void elim_non_maxime(fereastra *D, int *n, int inaltime, int latime) {
    int i, j;
    float d;
    for (i = 0; i < *n - 1; i++)
        for (j = i + 1; j < *n; j++) {
            d = suprapunere(D[i], D[j], inaltime, latime);
            if (d > 0.2) {
                eliminare(D, *n, j);
                (*n)--;
                j--;
            }
        }
}

int cmpdescresc(const void *a, const void *b) {
    fereastra x = *(fereastra *) a;
    fereastra y = *(fereastra *) b;

    if (x.corr < y.corr)
        return 1;
    if (x.corr == y.corr)
        return 0;
    return -1;
}

void sortare_corelatii(fereastra *D, int n) {
    qsort(D, n, sizeof(fereastra), cmpdescresc);
}

int main() {

    fereastra *D = NULL;
    float prag = 0.5;
    int n = 0, i;
    int inaltime_sablon, latime_sablon, padding_sablon;
    int inaltime, latime, pad;
    char *imagineI, *imagineI_gray;
    pixel **imagineI_matrice, **imagineI_matrice_gray;


    imagineI = (char *) malloc(sizeof(char) * 30);

    if (!imagineI) {
        printf("Nu s-a putut aloca memorie\n");
        return 0;
    }

    imagineI_gray = (char *) malloc(sizeof(char) * 35);

    if (!imagineI_gray) {
        printf("Nu s-a putut aloca memorie\n");
        return 0;
    }

    FILE *f = fopen("imagini.txt", "r");

    if (!f) {
        printf("Nu s-a putut deschide fisierul imagini.txt \n");
        return 0;
    }

    fscanf(f, "%s", imagineI); // citeste numele imaginii mari, peste care va avea loc operatia de template matching

    strcpy(imagineI_gray, imagineI);
    strcpy(imagineI_gray + strlen(imagineI) - 4, "_gray.bmp");

    grayscale_image(imagineI, imagineI_gray); // transforma imaginea in grayscale

    dimensiuni_imagine(imagineI_gray, &inaltime, &latime, &pad); // principalele caracteristici ale imaginii

    imagToMatrice(imagineI_gray, &imagineI_matrice_gray, inaltime, latime,
                  pad); // transforma imaginea grayscale in matrice
    imagToMatrice(imagineI, &imagineI_matrice, inaltime, latime, pad); // transforma imaginea initiala in matrice

    for (i = 0; i <= 9; i++) // pentru fiecare sablon are loc operatia de template matching
    {
        char cifra_sablon[30];

        fscanf(f, "%s", cifra_sablon);

        FILE *fin = fopen(cifra_sablon, "rb");

        if (!fin) {
            printf("Nu s-a putut deschide sablonul %s \n", cifra_sablon);
            return 0;
        }

        dimensiuni_imagine(cifra_sablon, &inaltime_sablon, &latime_sablon,
                           &padding_sablon); // principalele caracteristici ale imaginii

        // operatia de template matching dintre imaginea grayscale si cea a sablonului
        template_matching_sablon(imagineI_gray, imagineI_matrice_gray, cifra_sablon, i, prag, &D, &n);

        fclose(fin);
    }

    sortare_corelatii(D, n); // functie care sorteaza tabloul D cu n elemente descrescator dupa corelatia ferestrelor

    elim_non_maxime(D, &n, inaltime_sablon,
                    latime_sablon); // functie care elimina din tabloul D cu n elemente non_maximele

    marcheaza_cifre(imagineI_matrice, inaltime_sablon, latime_sablon, D,
                    n); // contureaza ferestrele ramase dupa eliminarea non-maximelor

    matriceToimagine(imagineI, "template_final.bmp", imagineI_matrice, inaltime, latime,
                     pad); // salveaza in memoria externa noua imagine

    fclose(f);
    free(D);
    free(imagineI);
    free(imagineI_gray);

    for (i = 0; i < inaltime; i++)
        free(imagineI_matrice[i]);
    free(imagineI_matrice);

    for (i = 0; i < inaltime; i++)
        free(imagineI_matrice_gray[i]);
    free(imagineI_matrice_gray);

    return 0;
}
