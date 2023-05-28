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

    int arr[10];
    int *puntarr;                              // puntero unidimensional
    puntarr = (int *)malloc(10 * sizeof(int)); // Asignamos 10 espacios al puntero unidimensional

    for (int i = 0; i < 10; i++)
    {
        *(puntarr + i) = i + 1;
        arr[i]=i;

        printf(" %d \n", puntarr[i]);
    }

    free(puntarr);

    return 0;



    /*
    En este siguiente ejemplo, podemos ver como crear un puntero bidimensional
    utilizando aritmética, asignandole valores y moviendonos dentro del arreglo.

    ↓     ↓     ↓     ↓     ↓     ↓     ↓     ↓     ↓     ↓     ↓     ↓     ↓     ↓
    */
}