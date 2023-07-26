#include <stdio.h>
#include <stdlib.h>

struct Nodo {
    int dato;
    struct Nodo* siguiente;
    struct Nodo* anterior;
};

struct Bicola {
    struct Nodo* frente;
    struct Nodo* final;
};

struct Bicola* crearBicola() {
    struct Bicola* bicola = (struct Bicola*)malloc(sizeof(struct Bicola));
    bicola->frente = NULL;
    bicola->final = NULL;
    return bicola;
}

void insertarFrente(struct Bicola* bicola, int dato) {
    struct Nodo* nuevoNodo = (struct Nodo*)malloc(sizeof(struct Nodo));
    nuevoNodo->dato = dato;
    nuevoNodo->siguiente = bicola->frente;
    nuevoNodo->anterior = NULL;

    if (bicola->frente == NULL) {
        bicola->final = nuevoNodo;
    } else {
        bicola->frente->anterior = nuevoNodo;
    }

    bicola->frente = nuevoNodo;
}

void insertarFinal(struct Bicola* bicola, int dato) {
    struct Nodo* nuevoNodo = (struct Nodo*)malloc(sizeof(struct Nodo));
    nuevoNodo->dato = dato;
    nuevoNodo->siguiente = NULL;
    nuevoNodo->anterior = bicola->final;

    if (bicola->final == NULL) {
        bicola->frente = nuevoNodo;
    } else {
        bicola->final->siguiente = nuevoNodo;
    }

    bicola->final = nuevoNodo;
}

void eliminarFrente(struct Bicola* bicola) {
    if (bicola->frente == NULL) {
        printf("La bicola está vacía. No se puede eliminar.\n");
        return;
    }

    struct Nodo* nodoAEliminar = bicola->frente;
    bicola->frente = bicola->frente->siguiente;

    if (bicola->frente == NULL) {
        bicola->final = NULL;
    } else {
        bicola->frente->anterior = NULL;
    }

    free(nodoAEliminar);
}

void eliminarFinal(struct Bicola* bicola) {
    if (bicola->final == NULL) {
        printf("La bicola está vacía. No se puede eliminar.\n");
        return;
    }

    struct Nodo* nodoAEliminar = bicola->final;
    bicola->final = bicola->final->anterior;

    if (bicola->final == NULL) {
        bicola->frente = NULL;
    } else {
        bicola->final->siguiente = NULL;
    }

    free(nodoAEliminar);
}

void liberarBicola(struct Bicola* bicola) {
    struct Nodo* actual = bicola->frente;
    while (actual != NULL) {
        struct Nodo* siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }
    free(bicola);
}

int main() {
    struct Bicola* bicola = crearBicola();

    insertarFrente(bicola, 1);
    insertarFrente(bicola, 2);
    insertarFinal(bicola, 3);
    insertarFinal(bicola, 4);

    printf("Bicola después de inserciones:\n");
    struct Nodo* actual = bicola->frente;
    while (actual != NULL) {
        printf("%d ", actual->dato);
        actual = actual->siguiente;
    }
    printf("\n");

    eliminarFrente(bicola);
    eliminarFinal(bicola);

    printf("Bicola después de eliminaciones:\n");
    actual = bicola->frente;
    while (actual != NULL) {
        printf("%d ", actual->dato);
        actual = actual->siguiente;
    }
    printf("\n");

    liberarBicola(bicola);

    return 0;
}
