#include <stdio.h>
#include <stdlib.h>

struct Nodo {
    int dato;
    struct Nodo* siguiente;
};

struct Nodo* crearNodo(int dato) {
    struct Nodo* nuevoNodo = (struct Nodo*)malloc(sizeof(struct Nodo));
    nuevoNodo->dato = dato;
    nuevoNodo->siguiente = NULL;
    return nuevoNodo;
}

void insertarNodo(struct Nodo** cabeza, int dato) {
    struct Nodo* nuevoNodo = crearNodo(dato);

    if (*cabeza == NULL) {
        *cabeza = nuevoNodo;
    } else {
        struct Nodo* actual = *cabeza;
        while (actual->siguiente != NULL) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevoNodo;
    }
}

void eliminarNodo(struct Nodo** cabeza, int posicion) {
    if (*cabeza == NULL) {
        printf("La lista está vacía.\n");
        return;
    }

    if (posicion == 0) {
        struct Nodo* temp = *cabeza;
        *cabeza = (*cabeza)->siguiente;
        free(temp);
        return;
    }

    struct Nodo* actual = *cabeza;
    int contador = 0;

    while (actual != NULL && contador < posicion - 1) {
        actual = actual->siguiente;
        contador++;
    }

    if (actual == NULL || actual->siguiente == NULL) {
        printf("La posición ingresada no existe en la lista.\n");
        return;
    }

    struct Nodo* nodoAEliminar = actual->siguiente;
    actual->siguiente = nodoAEliminar->siguiente;
    free(nodoAEliminar);
}

void imprimirLista(struct Nodo* cabeza) {
    struct Nodo* actual = cabeza;
    while (actual != NULL) {
        printf("%d ", actual->dato);
        actual = actual->siguiente;
    }
    printf("\n");
}

int main() {
    struct Nodo* cabeza = NULL;

    insertarNodo(&cabeza, 1);
    insertarNodo(&cabeza, 2);
    insertarNodo(&cabeza, 3);
    insertarNodo(&cabeza, 4);
    insertarNodo(&cabeza, 5);

    printf("Lista original: ");
    imprimirLista(cabeza);

    int posicionAEliminar = 2;

    eliminarNodo(&cabeza, posicionAEliminar);

    printf("Lista después de eliminar el nodo en la posición %d: ", posicionAEliminar);
    imprimirLista(cabeza);

    return 0;
}
