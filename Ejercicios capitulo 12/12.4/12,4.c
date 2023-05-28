#include <stdio.h>
#include <stdlib.h>

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

    ↓     ↓     ↓     ↓     ↓     ↓     ↓     ↓     ↓     ↓     ↓     ↓     ↓     ↓
    */

    int (*bipuntarr)[3];                              // Creamos un puntero para las filas.
    bipuntarr = malloc(3 * sizeof(*bipuntarr));       // Asignamos 3 espacios al puntero de las filas.

    for (int i = 0; i < 3; i++)
    {   
        for (int j = 0; j < 3; j++)
        {
            bipuntarr[i][j]=i+j;
            printf(" %d ", bipuntarr[i][j]);
        }

        printf("\n");
    }

    free(bipuntarr);

    return 0;
}