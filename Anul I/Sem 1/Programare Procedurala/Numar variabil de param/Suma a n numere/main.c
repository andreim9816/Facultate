#include <stdio.h>
#include <stdlib.h>
#include<stdarg.h>

int suma(int n, ...) {
    int i, s = 0;
    va_list lista;
    va_start(lista, n);

    for (i = 0; i < n; i++) {
        int x = va_arg(lista, int);
        s = s + x;
    }

    va_end(lista); /// !!!!!!!!!!!!!!!!!!
    return s;
}

int main() {
    int x;
    x = suma(4, 1, 2, 3, 4);
    printf("%d", x);
    return 0;
}
