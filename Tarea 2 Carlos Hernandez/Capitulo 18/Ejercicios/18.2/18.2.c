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

int contarNodos(struct Nodo* cabeza) {
    int contador = 0;
    struct Nodo* actual = cabeza;

    while (actual != NULL) {
        contador++;
        actual = actual->siguiente;
    }

    return contador;
}

int main() {

    struct Nodo* cabeza = crearNodo(1);
    cabeza->siguiente = crearNodo(2);
    cabeza->siguiente->siguiente = crearNodo(3);
    cabeza->siguiente->siguiente->siguiente = crearNodo(4);
    cabeza->siguiente->siguiente->siguiente->siguiente = crearNodo(5);

    int numNodos = contarNodos(cabeza);

    printf("El número de nodos en la lista enlazada es: %d\n", numNodos);

    return 0;
}
