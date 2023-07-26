#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

void mostrarLista(struct Nodo* cabeza) {
    struct Nodo* actual = cabeza;
    while (actual != NULL) {
        printf("%d ", actual->dato);
        actual = actual->siguiente;
    }
    printf("\n");
}

void eliminarNodosMayores(struct Nodo** cabeza, int valorMaximo) {
    while (*cabeza != NULL && (*cabeza)->dato > valorMaximo) {
        struct Nodo* temp = *cabeza;
        *cabeza = (*cabeza)->siguiente;
        free(temp);
    }

    if (*cabeza == NULL) {
        return;
    }

    struct Nodo* actual = *cabeza;
    struct Nodo* siguiente = actual->siguiente;

    while (siguiente != NULL) {
        if (siguiente->dato > valorMaximo) {
            actual->siguiente = siguiente->siguiente;
            free(siguiente);
            siguiente = actual->siguiente;
        } else {
            actual = siguiente;
            siguiente = siguiente->siguiente;
        }
    }
}

void liberarLista(struct Nodo* cabeza) {
    struct Nodo* actual = cabeza;
    while (actual != NULL) {
        struct Nodo* siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }
}

int main() {
    struct Nodo* cabeza = NULL;
    int cantidadElementos = 10;
    int valorMaximo = 50;

    srand(time(NULL));


    for (int i = 0; i < cantidadElementos; i++) {
        int numeroAleatorio = rand() % 100; 
        insertarNodo(&cabeza, numeroAleatorio);
    }

    printf("Lista enlazada generada:\n");
    mostrarLista(cabeza);

    eliminarNodosMayores(&cabeza, valorMaximo);

    printf("\nLista enlazada después de eliminar nodos mayores a %d:\n", valorMaximo);
    mostrarLista(cabeza);

    liberarLista(cabeza);

    return 0;
}
