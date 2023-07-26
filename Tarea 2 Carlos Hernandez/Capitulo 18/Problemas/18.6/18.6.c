#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Nodo
{
    char caracter;
    struct Nodo *siguiente;
    struct Nodo *anterior;
};

struct Nodo *crearNodo(char caracter)
{
    struct Nodo *nuevoNodo = (struct Nodo *)malloc(sizeof(struct Nodo));
    nuevoNodo->caracter = caracter;
    nuevoNodo->siguiente = NULL;
    nuevoNodo->anterior = NULL;
    return nuevoNodo;
}

void insertarNodo(struct Nodo **cabeza, char caracter)
{
    struct Nodo *nuevoNodo = crearNodo(caracter);

    if (*cabeza == NULL)
    {
        *cabeza = nuevoNodo;
    }
    else
    {
        struct Nodo *actual = *cabeza;
        while (actual->siguiente != NULL)
        {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevoNodo;
        nuevoNodo->anterior = actual;
    }
}

void intercambiarNodos(struct Nodo *nodo1, struct Nodo *nodo2)
{
    char temp = nodo1->caracter;
    nodo1->caracter = nodo2->caracter;
    nodo2->caracter = temp;
}

void ordenarLista(struct Nodo *cabeza)
{
    int intercambiado;
    struct Nodo *actual;
    struct Nodo *ultimo = NULL;

    if (cabeza == NULL)
    {
        return;
    }

    do
    {
        intercambiado = 0;
        actual = cabeza;

        while (actual->siguiente != ultimo)
        {
            if (actual->caracter > actual->siguiente->caracter)
            {
                intercambiarNodos(actual, actual->siguiente);
                intercambiado = 1;
            }
            actual = actual->siguiente;
        }
        ultimo = actual;
    } while (intercambiado);
}

void imprimirLista(struct Nodo *cabeza)
{
    struct Nodo *actual = cabeza;
    while (actual != NULL)
    {
        printf("%c ", actual->caracter);
        actual = actual->siguiente;
    }
    printf("\n");
}

void liberarLista(struct Nodo *cabeza)
{
    struct Nodo *actual = cabeza;
    while (actual != NULL)
    {
        struct Nodo *siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }
}

int main()
{
    char cadena[100];
    printf("Ingrese una cadena de caracteres: ");
    fgets(cadena, sizeof(cadena), stdin);

    struct Nodo *cabeza = NULL;

    for (int i = 0; i < strlen(cadena); i++)
    {
        if (cadena[i] != '\n')
        {
            insertarNodo(&cabeza, cadena[i]);
        }
    }

    printf("\nLista doblemente enlazada original: ");
    imprimirLista(cabeza);

    ordenarLista(cabeza);

    printf("\nLista doblemente enlazada ordenada: ");
    imprimirLista(cabeza);

    liberarLista(cabeza);

    return 0;
}
