#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


struct Alumno {
    char nombre[50];
    int edad;
    char sexo;
};


struct Nodo {
    struct Alumno dato;
    struct Nodo* siguiente;
};


struct Nodo* crearNodo(struct Alumno alumno) {
    struct Nodo* nuevoNodo = (struct Nodo*)malloc(sizeof(struct Nodo));
    nuevoNodo->dato = alumno;
    nuevoNodo->siguiente = NULL;
    return nuevoNodo;
}


void insertarNodo(struct Nodo** cabeza, struct Alumno alumno) {
    struct Nodo* nuevoNodo = crearNodo(alumno);

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


struct Nodo* transformarLista(struct Nodo* cabeza) {
    if (cabeza == NULL) {
        return NULL;
    }


    bool primerAlumnoMasculino = cabeza->dato.sexo == 'M';

    struct Nodo* nuevaCabeza = cabeza;
    struct Nodo* actual = cabeza;
    struct Nodo* siguiente = cabeza->siguiente;
    bool siguienteEsFemenino = siguiente != NULL && siguiente->dato.sexo == 'F';

    while (siguiente != NULL) {
        if (siguienteEsFemenino) {

            actual = siguiente;
            siguiente = siguiente->siguiente;
        } else {

            actual->siguiente = siguiente->siguiente;
            siguiente->siguiente = nuevaCabeza->siguiente;
            nuevaCabeza->siguiente = siguiente;
            nuevaCabeza = siguiente;

            siguiente = actual->siguiente;
            siguienteEsFemenino = siguiente != NULL && siguiente->dato.sexo == 'F';
        }
    }

    return cabeza;
}

void imprimirLista(struct Nodo* cabeza) {
    struct Nodo* actual = cabeza;
    while (actual != NULL) {
        printf("Nombre: %s, Edad: %d, Sexo: %c\n", actual->dato.nombre, actual->dato.edad, actual->dato.sexo);
        actual = actual->siguiente;
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

    struct Alumno alumno1 = {"Juan", 20, 'M'};
    struct Alumno alumno2 = {"Ana", 22, 'F'};
    struct Alumno alumno3 = {"Pedro", 21, 'M'};
    struct Alumno alumno4 = {"María", 19, 'F'};
    struct Alumno alumno5 = {"Luis", 23, 'M'};

    insertarNodo(&cabeza, alumno1);
    insertarNodo(&cabeza, alumno2);
    insertarNodo(&cabeza, alumno3);
    insertarNodo(&cabeza, alumno4);
    insertarNodo(&cabeza, alumno5);

    printf("Lista original:\n");
    imprimirLista(cabeza);

    cabeza = transformarLista(cabeza);

    printf("\nLista transformada:\n");
    imprimirLista(cabeza);

    liberarLista(cabeza);

    return 0;
}
