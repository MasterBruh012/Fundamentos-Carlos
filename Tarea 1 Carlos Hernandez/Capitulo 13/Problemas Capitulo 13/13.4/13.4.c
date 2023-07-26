#include <stdio.h>
#include <stdlib.h>

#define FILAS 20
#define COLUMNAS 20

int** crearMatrizDinamica(int filas, int columnas) {
    int** matriz = (int**)malloc(filas * sizeof(int*));
    for (int i = 0; i < filas; i++) {
        matriz[i] = (int*)malloc(columnas * sizeof(int));
    }
    return matriz;
}

void liberarMatrizDinamica(int** matriz, int filas) {
    for (int i = 0; i < filas; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

void mostrarMatriz(int** matriz, int filas, int* numColumnas) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < numColumnas[i]; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int matrizOriginal[FILAS][COLUMNAS];

    printf("Ingrese la matriz de 20x20 elementos:\n");
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            scanf("%d", &matrizOriginal[i][j]);
        }
    }

    int** matrizNoRepetidos = crearMatrizDinamica(FILAS, COLUMNAS);
    int numColumnas[FILAS] = {0};


    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            int elementoActual = matrizOriginal[i][j];
            int esRepetido = 0;

            for (int k = 0; k < numColumnas[i]; k++) {
                if (matrizNoRepetidos[i][k] == elementoActual) {
                    esRepetido = 1;
                    break;
                }
            }

            if (!esRepetido) {
                matrizNoRepetidos[i][numColumnas[i]] = elementoActual;
                numColumnas[i]++;
            }
        }
    }

    printf("Matriz de elementos no repetidos:\n");
    mostrarMatriz(matrizNoRepetidos, FILAS, numColumnas);

    liberarMatrizDinamica(matrizNoRepetidos, FILAS);

    return 0;
}
