#include <stdio.h>
#include <stdlib.h>

#define N 4
#define M 5

/*
En el siguiente código se accede a los elementos
de una matriz. Acceder a los mismos elementos
con aritmética de punteros.
*/

/*
Código original.
↓       ↓       ↓
*/

/*
int main()
{
    int f, c;
    double mt[N][M];

    for (f = 0; f < N; f++)
    {
        for (c = 0; c < M; c++)
        {
            mt[f][c] = f + c;
            printf(" %lf ", mt[f][c]);
        }

        printf("\n");
    }

    return 0;

}
*/

/*
Código con punteros.
↓       ↓       ↓
*/

int main()
{
    int f, c;
    double *puntero;                                    // Creamos un puntero.
    puntero = (double *)malloc(N * M * sizeof(double)); // Asignamos el tamaño de las filas y columnas al puntero.

    for (f = 0; f < N; f++)
    {
        for (c = 0; c < M; c++)
        {
            *(puntero + f * M + c) = f + c;          // Acceder a los valores del puntero y llenarlos.
            printf(" %lf ", *(puntero + f * M + c)); // Imprimir los valores del puntero.
        }

        printf("\n");
    }

    return 0;
}