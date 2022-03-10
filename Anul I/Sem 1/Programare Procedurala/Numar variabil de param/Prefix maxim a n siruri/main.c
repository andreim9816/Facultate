#include <stdio.h>
#include <stdlib.h>
#include<stdarg.h>
#include<string.h>

char *prefix(int n, ...) {
    char *pref, *aux, *q, *curent;
    int i, max;

    va_list lista;
    va_start(lista, n);

    curent = va_arg(lista,
    char*);
    pref = (char *) malloc(sizeof(char) * (strlen(curent) + 1));

    if (!pref)
        return NULL;

    strcpy(pref, curent);
    max = strlen(curent);

    for (i = 2; i <= n; i++) {
        curent = va_arg(lista,char*);
        while (strstr(curent, pref) != curent) {
            if (max == 0) {
                free(pref);
                return NULL;
            }
            pref[--max] = '\0';
        }
        aux = realloc(pref, sizeof(char) * (max + 1));
        if (!aux)
            return NULL;
        pref = aux;
    }
    va_end(lista);
    return pref;

}

int main() {
    char *sir = prefix(5, "abecedar", "abeced", "abeca", "abec", "af");
    printf("%s", sir);
    return 0;
}
