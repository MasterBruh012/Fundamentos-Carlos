#include <stdio.h>
#include <stdlib.h>

#define N 3
#define M 3

int main()
{

    /*
    Un array unidimensional se puede indexar con la aritmética de punteros
    ¿Qué tipo de puntero habría que definir para indexar un array bidimencional?
    */

    /*
    Como bien conocemos, este ejemplo indica como crear un array unidimensional
    utilizando aritmética de punteros y asignandole valores al mismo.

    ↓     ↓     ↓     ↓     ↓     ↓     ↓     ↓     ↓     ↓     ↓     ↓     ↓     ↓
    */

    /*
    int *puntarr;                              // puntero unidimensional.
    puntarr = (int *)malloc(10 * sizeof(int)); // Asignamos 10 espacios al puntero unidimensional.

    for (int i = 0; i < 10; i++)
    {
        *(puntarr + i) = i + 1;

        printf(" %d \n", puntarr[i]);
    }

    free(puntarr);

    return 0;
    */

    /*
    En este siguiente ejemplo, podemos ver como crear un puntero bidimensional
    utilizando aritmética, asignandole valores y moviendonos dentro del arreglo.

    La primera forma, solamente creamos un puntero para las filas
    ↓     ↓     ↓     ↓     ↓     ↓     ↓     ↓     ↓     ↓     ↓     ↓     ↓     ↓
    */

    /*
    int(*filpuntarr)[3];                         // Creamos un puntero para las filas.
    filpuntarr = malloc(3 * sizeof(*filpuntarr)); // Asignamos 3 espacios al puntero de las filas.

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            filpuntarr[i][j] = i + j;
            printf(" %d ", filpuntarr[i][j]);
        }

        printf("\n");
    }

    free(filpuntarr);

    return 0;
    */

    /*
    La segunda forma, creamos un solo punteor que manejará
    las filas y las columnas.
    ↓     ↓     ↓     ↓     ↓     ↓     ↓     ↓     ↓     ↓     ↓     ↓     ↓     ↓
    */

    int *bipuntarr;                                 // Creamos un puntero.
    bipuntarr = (int *)malloc(N * M * sizeof(int)); // Asignamos los espacios de las filas y las colimnas.

    // Accedemos a los elementos utilizando arimética de punteros.
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            *(bipuntarr + i * M + j) = i + j;         // Asignamos valores a los elementos.
            printf(" %d ", *(bipuntarr + i * M + j)); // imprimimos los valores.
        }

        printf("\n");
    }

    free(bipuntarr);

    return 0;
}