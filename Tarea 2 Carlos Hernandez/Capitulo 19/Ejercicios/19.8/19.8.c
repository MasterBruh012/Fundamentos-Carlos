#include <stdio.h>
#include <stdlib.h>

struct Nodo
{
    int dato;
    struct Nodo *siguiente;
};

struct Pila
{
    struct Nodo *tope;
};

struct Cola
{
    struct Nodo *frente;
    struct Nodo *final;
};

struct Pila *crearPila()
{
    struct Pila *pila = (struct Pila *)malloc(sizeof(struct Pila));
    pila->tope = NULL;
    return pila;
}

int estaVacia(struct Pila *pila)
{
    return pila->tope == NULL;
}

void apilar(struct Pila *pila, int dato)
{
    struct Nodo *nuevoNodo = (struct Nodo *)malloc(sizeof(struct Nodo));
    nuevoNodo->dato = dato;
    nuevoNodo->siguiente = pila->tope;
    pila->tope = nuevoNodo;
}

int desapilar(struct Pila *pila)
{
    if (estaVacia(pila))
    {
        printf("La pila está vacía. No se puede desapilar.\n");
        return -1;
    }

    struct Nodo *nodoAEliminar = pila->tope;
    int dato = nodoAEliminar->dato;
    pila->tope = pila->tope->siguiente;
    free(nodoAEliminar);
    return dato;
}

struct Cola *crearCola()
{
    struct Cola *cola = (struct Cola *)malloc(sizeof(struct Cola));
    cola->frente = NULL;
    cola->final = NULL;
    return cola;
}

int estaVaciaCola(struct Cola *cola)
{
    return cola->frente == NULL;
}

void encolar(struct Cola *cola, int dato)
{
    struct Nodo *nuevoNodo = (struct Nodo *)malloc(sizeof(struct Nodo));
    nuevoNodo->dato = dato;
    nuevoNodo->siguiente = NULL;

    if (estaVaciaCola(cola))
    {
        cola->frente = nuevoNodo;
    }
    else
    {
        cola->final->siguiente = nuevoNodo;
    }

    cola->final = nuevoNodo;
}

int desencolar(struct Cola *cola)
{
    if (estaVaciaCola(cola))
    {
        printf("La cola está vacía. No se puede desencolar.\n");
        return -1;
    }

    struct Nodo *nodoAEliminar = cola->frente;
    int dato = nodoAEliminar->dato;
    cola->frente = cola->frente->siguiente;
    free(nodoAEliminar);

    if (cola->frente == NULL)
    {
        cola->final = NULL;
    }

    return dato;
}

int esPar(int numero)
{
    return numero % 2 == 0;
}

int main()
{
    struct Pila *pila = crearPila();
    struct Cola *cola = crearCola();

    apilar(pila, 1);
    apilar(pila, 2);
    apilar(pila, 3);
    apilar(pila, 4);
    apilar(pila, 5);

    struct Pila *pilaAuxiliar = crearPila();
    while (!estaVacia(pila))
    {
        int dato = desapilar(pila);
        if (esPar(dato))
        {
            encolar(cola, dato);
        }
        apilar(pilaAuxiliar, dato);
    }

    while (!estaVacia(pilaAuxiliar))
    {
        int dato = desapilar(pilaAuxiliar);
        apilar(pila, dato);
    }

    printf("Elementos pares en la cola: ");
    while (!estaVaciaCola(cola))
    {
        int dato = desencolar(cola);
        printf("%d ", dato);
    }
    printf("\n");

    free(pila);
    free(cola);
    free(pilaAuxiliar);

    return 0;
}
