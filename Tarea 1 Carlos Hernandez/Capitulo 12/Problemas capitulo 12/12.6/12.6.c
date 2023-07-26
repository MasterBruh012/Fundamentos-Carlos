#include <stdio.h>
#include <stdlib.h>

double convertirAReal(const char* cadena) {
    return strtod(cadena, NULL);
}

int main() {
    char cadena[] = "25.26";

    double numeroReal = convertirAReal(cadena);

    printf("El valor real es: %.2f\n", numeroReal);

    return 0;
}
