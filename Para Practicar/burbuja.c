#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int aleatorio(int a, int b);
void ordenar(int[]);
void burbuja(int[], int, int);

int main()
{
    srand(time(NULL));

    int array[5];

    for (int i = 0; i < 5; i++)
    {
        array[i] = aleatorio(1, 10);
    }

    for (int i = 0; i < 5; i++)
    {
        printf("%d\t", array[i]);
    }

    printf("\n");
    ordenar(array);

    for (int i = 0; i < 5; i++)
    {
        printf("%d\t", array[i]);
    }

    return 0;
}

int aleatorio(int a, int b)
{
    return rand() % (b - a + 1) + a;
}

void ordenar(int array[])
{
    int i, j;
    for (i = 0; i < 5; i++)
        for (j = 0; j < (5 - i - 1); j++)
            if (array[j] > array[j + 1])
                burbuja(array, j, j + 1);
}

void burbuja(int arr[], int a, int b)
{
    int burbuja;

    burbuja = arr[a];
    arr[a] = arr[b];
    arr[b] = burbuja;
}