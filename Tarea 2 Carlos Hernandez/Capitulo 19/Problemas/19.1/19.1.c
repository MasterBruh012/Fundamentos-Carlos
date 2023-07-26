#include <stdio.h>
#include <stdlib.h>

struct Nodo {
    int dato;
    struct Nodo* siguiente;
};

struct Pila {
    struct Nodo* tope;
};

struct Pila* crearPila() {
    struct Pila* pila = (struct Pila*)malloc(sizeof(struct Pila));
    pila->tope = NULL;
    return pila;
}

int estaVacia(struct Pila* pila) {
    return pila->tope == NULL;
}

void apilar(struct Pila* pila, int dato) {
    struct Nodo* nuevoNodo = (struct Nodo*)malloc(sizeof(struct Nodo));
    nuevoNodo->dato = dato;
    nuevoNodo->siguiente = pila->tope;
    pila->tope = nuevoNodo;
}

int desapilar(struct Pila* pila) {
    if (estaVacia(pila)) {
        printf("La pila está vacía. No se puede desapilar.\n");
        return -1;
    }

    struct Nodo* nodoAEliminar = pila->tope;
    int dato = nodoAEliminar->dato;
    pila->tope = pila->tope->siguiente;
    free(nodoAEliminar);
    return dato;
}

void copiarPila(struct Pila* pilaFuente, struct Pila* pilaDestino) {
    struct Pila* pilaAuxiliar = crearPila();
    
    while (!estaVacia(pilaFuente)) {
        int dato = desapilar(pilaFuente);
        apilar(pilaAuxiliar, dato);
    }

    while (!estaVacia(pilaAuxiliar)) {
        int dato = desapilar(pilaAuxiliar);
        apilar(pilaFuente, dato);
        apilar(pilaDestino, dato);
    }

    free(pilaAuxiliar);
}

int main() {
    struct Pila* pilaFuente = crearPila();
    struct Pila* pilaDestino = crearPila();

    apilar(pilaFuente, 1);
    apilar(pilaFuente, 2);
    apilar(pilaFuente, 3);

    copiarPila(pilaFuente, pilaDestino);

    printf("Pila Fuente: ");
    while (!estaVacia(pilaFuente)) {
        printf("%d ", desapilar(pilaFuente));
    }
    printf("\n");

    printf("Pila Destino: ");
    while (!estaVacia(pilaDestino)) {
        printf("%d ", desapilar(pilaDestino));
    }
    printf("\n");

    free(pilaFuente);
    free(pilaDestino);

    return 0;
}
