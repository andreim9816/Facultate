#include <stdio.h>
#include <stdlib.h>
#include<stdarg.h>

int maxim(int n, ...) {
    int maxi;
    va_list lista;
    va_start(lista, n);

    maxi = va_arg(lista, sint);

    int i;
    for (i = 2; i <= n; i++) {
        int x;
        x = va_arg(lista, int);
        if (x > maxi) {
            maxi = x;
        }
    }

    return maxi;
}

int main() {
    int maxi = maxim(5, 2, 3, 4, 5, 8);
    printf("%d", maxi);
    return 0;
}