#include <stdio.h>
#include <stdlib.h>

/*
Escribir una funcion con un argumento de tipo puntero a double y otro argumento de tipo int.
El primer argumento se debe corresponder con un array y el segundo con el numero de elementos
del array. La funcion ha de ser de tipo puntero a double para devolver la direccion del elemento menor.

Código.
↓       ↓       ↓       ↓       ↓       ↓       ↓       ↓       ↓       ↓       ↓       ↓       ↓       ↓
*/

double *funcionmenor(double *, int); // Llamada de la función.

int main()
{
    double punterodoble[] = {4.5, 2.3, 6.7, 1.2, 3.9};
    int n_elementos = sizeof(punterodoble) / sizeof(double); // Este pedazo de código saca el tamaño del arreglo que al cual estamos apuntando.
                                                             // En este caso estamos sacando el tamaño de un double, por eso dividimos por el sizeof() de un double.

    double *punteroMenor = funcionmenor(punterodoble, n_elementos);

    if (punteroMenor != NULL)
    {
        printf("El elemento menor es: %.2f\n", *punteroMenor);
    }
    else
    {
        printf("Array vacío o puntero inválido.\n");
    }

    return 0;
}

/*
    Función: funcionmenor
    Argumentos:
        double *arreglo: Puntero que apunta a un arreglo.
        int n_elementos: Tamaño de arreglo.
    Objetivo: Encontrar el número menor dentro del arreglo que nos proporcionan.
    Retorno: El número menor dentro del arreglo (double menor).
*/

double *funcionmenor(double *arreglo, int n_elementos) // Argumentos que reciben la función, puntero a double y un entero.
{
    double *menor = arreglo; // Se declara un puntero double que tendrá el primer valor del arreglo que usaremos, este asumirá que el rol del menor inicialmente.

    for (int i = 0; i < n_elementos; i++) // El ciclo for estará corriendo hasta llegar al número de elementos de la matriz.
    {
        if (*(arreglo + i) < *menor) // La condición dice que si encontramos un número que sea menor al primer número menor que teniamos ↓     ↓.
        {
            menor = &*(arreglo + i); // La variable double menor, cambiará al nuevo menor que hemos encontrado.
        }
    }

    return menor; // Tras finalizar este ciclo, retornaremos el menor dentro del arreglo inspeccionado.
}