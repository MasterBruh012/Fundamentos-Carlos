#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX 100

void eliminarBlancos(char*);

int main() {
    int n;
    printf("Ingrese la cantidad de cadenas a leer: ");
    scanf("%d", &n);

    while (getchar() != '\n');

    char cadenas[n][MAX];
    char cadenasTransformadas[n][MAX];

    for (int i = 0; i < n; i++) {
        printf("Ingrese la cadena %d: ", i + 1);
        fgets(cadenas[i], MAX, stdin);

        cadenas[i][strcspn(cadenas[i], "\n")] = '\0';
    }

    for (int i = 0; i < n; i++) {
        strcpy(cadenasTransformadas[i], cadenas[i]);
        eliminarBlancos(cadenasTransformadas[i]);
    }

    printf("\nCadenas leídas:\n");
    for (int i = 0; i < n; i++) {
        printf("%d: %s\n", i + 1, cadenas[i]);
    }

    printf("\nCadenas transformadas:\n");
    for (int i = 0; i < n; i++) {
        printf("%d: %s\n", i + 1, cadenasTransformadas[i]);
    }

    return 0;
}

void eliminarBlancos(char* cadena) {
    int i, j;
    int longitud = strlen(cadena);

    for (i = 0, j = 0; i < longitud; i++) {
        if (cadena[i] != ' ') {
            cadena[j] = cadena[i];
            j++;
        }
    }

    cadena[j] = '\0';
}