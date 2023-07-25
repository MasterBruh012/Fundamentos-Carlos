#include <stdio.h>
#include <stdlib.h>

// Lista

typedef struct Nodo
{
    int num;
    struct Nodo *siguiente;
} NODOTOTAL;

NODOTOTAL *insertarlista(NODOTOTAL *, int);
void mostrarlista(NODOTOTAL *);

int main()
{
    NODOTOTAL *lista = NULL;

    int n;

    printf("Digite un numero: ");
    scanf("%d", &n);

    lista = insertarlista(lista, n);

    printf("Digite un numero: ");
    scanf("%d", &n);

    lista = insertarlista(lista, n);

    mostrarlista(lista);

    return 0;
}

NODOTOTAL *insertarlista(NODOTOTAL *lista, int n)
{
    NODOTOTAL *nodoactual = (NODOTOTAL *)malloc(sizeof(NODOTOTAL *));

    nodoactual->num = n;
    nodoactual->siguiente = NULL;

    NODOTOTAL *nodoSiguiente;

    if (lista == NULL)
    {
        lista = nodoactual;
        return lista;
    }

    nodoSiguiente = lista;
    while (nodoSiguiente->siguiente != NULL)
        nodoSiguiente = nodoSiguiente->siguiente;

    nodoSiguiente->siguiente = nodoactual;

    return lista;
}

void mostrarlista(NODOTOTAL *lista)
{
    NODOTOTAL *nodoactual = lista;

    while (nodoactual != NULL)
    {
        printf("valor: %d\n", nodoactual->num);
        nodoactual = nodoactual->siguiente;
    }
}
