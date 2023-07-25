#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100
#define MIN 1

void generarAleatrorios(int, int[]);
void mostrarArreglo(int, int[]);
int particionar(int[], int, int);
void intercambiar(int *, int *);
void quicksort(int, int[], int, int);

int main()
{
    srand(time(NULL));

    int n;

    printf("Digite la cantidad de valores: ");
    scanf("%d", &n);

    int arr[n];

    generarAleatrorios(n, arr);
    mostrarArreglo(n, arr);
    quicksort(n, arr, 0, n - 1);
    // printf("\n%d", particionar(arr, 0, n - 1));
    printf("\n");
    mostrarArreglo(n, arr);

    return 0;
}

void generarAleatrorios(int n, int arr[])
{
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % (MAX - MIN + 1) + MIN;
    }
}

void mostrarArreglo(int n, int arreglo[])
{
    for (int i = 0; i < n; i++)
    {
        printf("%d\n", arreglo[i]);
    }
}

int particionar(int arreglo[], int limI, int limS)
{
    // 1er paso: Elegir el pivote
    int pivote = arreglo[limS], i, indiceMenor = limI - 1;

    for (i = limI; i < limS; i++)
    {
        // si el valor en la posicion actual (i) es mayor
        // que el pivote, no hago nada

        // Si es menor, se hacen dos cosaS:
        // 1: mover el indice menor a la derecha.
        if (arreglo[i] < pivote)
        {
            indiceMenor++;
            intercambiar(&arreglo[indiceMenor], &arreglo[i]);
        }

        // 2: intercambiar el menor en la posicion actual
        // con el que está en el indice menor.
    }

    // Color el pviote donde corresponde:

    intercambiar(&arreglo[indiceMenor + 1], &arreglo[limS]);

    return indiceMenor + 1;
}

void intercambiar(int *primero, int *segundo)
{
    int burbuja;
    burbuja = *primero;
    *primero = *segundo;
    *segundo = burbuja;
}

void quicksort(int n, int arreglo[], int limI, int limS)
{
    int posicionPivote;

    // Caso base:
    if (limI >= limS)
        return;

    // Posicion pivote es donde quedo el pivote
    // despius de particionar.
    posicionPivote = particionar(arreglo, limI, limS);

    // llamar recursivamente quicksort, una para el
    // lado izquierdo del pivote y otra para el lado
    // derecho del pivote.

    // Lado izquierdo del pivote.
    quicksort(n, arreglo, limI, posicionPivote - 1);

    // Lado derecho del pivote.
    quicksort(n, arreglo, posicionPivote + 1, limS);
}