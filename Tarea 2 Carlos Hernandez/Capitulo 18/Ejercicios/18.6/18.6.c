#include <stdio.h>
#include <stdlib.h>

struct NodoDoble {
    float dato;
    struct NodoDoble* siguiente;
    struct NodoDoble* anterior;
};

struct NodoDoble* crearNodoDoble(float dato) {
    struct NodoDoble* nuevoNodo = (struct NodoDoble*)malloc(sizeof(struct NodoDoble));
    nuevoNodo->dato = dato;
    nuevoNodo->siguiente = NULL;
    nuevoNodo->anterior = NULL;
    return nuevoNodo;
}

void insertarEnOrden(struct NodoDoble** cabeza, float dato) {
    struct NodoDoble* nuevoNodo = crearNodoDoble(dato);

    if (*cabeza == NULL) {
        *cabeza = nuevoNodo;
    } else if ((*cabeza)->dato >= dato) {
        nuevoNodo->siguiente = *cabeza;
        (*cabeza)->anterior = nuevoNodo;
        *cabeza = nuevoNodo;
    } else {
        struct NodoDoble* actual = *cabeza;
        while (actual->siguiente != NULL && actual->siguiente->dato < dato) {
            actual = actual->siguiente;
        }

        nuevoNodo->siguiente = actual->siguiente;
        if (actual->siguiente != NULL) {
            actual->siguiente->anterior = nuevoNodo;
        }
        actual->siguiente = nuevoNodo;
        nuevoNodo->anterior = actual;
    }
}

void imprimirListaDoble(struct NodoDoble* cabeza) {
    struct NodoDoble* actual = cabeza;
    while (actual != NULL) {
        printf("%.2f ", actual->dato);
        actual = actual->siguiente;
    }
    printf("\n");
}

void liberarListaDoble(struct NodoDoble* cabeza) {
    struct NodoDoble* actual = cabeza;
    while (actual != NULL) {
        struct NodoDoble* siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }
}

int main() {
    struct NodoDoble* cabezaDoble = NULL;

    float datosListaSimple[] = {3.5, 1.2, 4.8, 2.0, 5.5};
    int numElementos = sizeof(datosListaSimple) / sizeof(datosListaSimple[0]);

    for (int i = 0; i < numElementos; i++) {
        insertarEnOrden(&cabezaDoble, datosListaSimple[i]);
    }

    printf("Lista doblemente enlazada ordenada: ");
    imprimirListaDoble(cabezaDoble);

    liberarListaDoble(cabezaDoble);

    return 0;
}
