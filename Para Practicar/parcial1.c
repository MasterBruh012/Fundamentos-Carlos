#include <stdio.h>
#include <stdlib.h>

typedef struct sNodo
{
    int valor;
    struct Snodo *siguiente;
} NODO;

NODO *insertarLista(NODO *, int);
void mostrarlista(NODO *);

int main()
{
    NODO *lista = NULL;

    int valores;
    printf("Digite la cantidad de valores a escanear: ");
    scanf("%d", &valores);

    for (int i = 0; i < valores; i++)
    {
        int n;
        printf("Valor %d: ", i + 1);
        scanf("%d", &n);

        lista = insertarLista(lista, n);
    }

    mostrarlista(lista);

    return 0;
}

NODO *insertarLista(NODO *lista, int n)
{
    NODO *nodoActual, *nodoTemporal;

    nodoActual = (NODO *)malloc(sizeof(NODO *));

    nodoActual->valor = n;
    nodoActual->siguiente = NULL;

    while (lista == NULL)
    {
        lista = nodoActual;
        return lista;
    }

    nodoTemporal = lista;
    while (nodoTemporal->siguiente != NULL)
        nodoTemporal = nodoTemporal->siguiente;

    nodoTemporal->siguiente = nodoActual;

    return lista;
}

void mostrarlista(NODO *lista)
{
    NODO *nodoactual = lista;

    while (nodoactual != NULL)
    {
        printf("Numeros: %d\n", nodoactual->valor);
        nodoactual = nodoactual->siguiente;
    }
}
