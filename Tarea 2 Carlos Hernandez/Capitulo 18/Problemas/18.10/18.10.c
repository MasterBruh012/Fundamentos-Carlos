#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Pasajero {
    char nombre[50];
    int edad;
    char destino[50];
};

struct Nodo {
    struct Pasajero pasajero;
    struct Nodo* siguiente;
    struct Nodo* anterior;
};

struct Nodo* crearNodo(struct Pasajero pasajero) {
    struct Nodo* nuevoNodo = (struct Nodo*)malloc(sizeof(struct Nodo));
    nuevoNodo->pasajero = pasajero;
    nuevoNodo->siguiente = NULL;
    nuevoNodo->anterior = NULL;
    return nuevoNodo;
}

void insertarNodo(struct Nodo** cabeza, struct Nodo** ultimo, struct Pasajero pasajero) {
    struct Nodo* nuevoNodo = crearNodo(pasajero);

    if (*cabeza == NULL) {
        *cabeza = nuevoNodo;
        *ultimo = nuevoNodo;
    } else {
        (*ultimo)->siguiente = nuevoNodo;
        nuevoNodo->anterior = *ultimo;
        *ultimo = nuevoNodo;
    }
}

void mostrarPasajero(struct Pasajero pasajero) {
    printf("Nombre: %s\n", pasajero.nombre);
    printf("Edad: %d\n", pasajero.edad);
    printf("Destino: %s\n", pasajero.destino);
}

void buscarPasajero(struct Nodo* cabeza, const char* nombreBuscado) {
    struct Nodo* actual = cabeza;
    while (actual != NULL) {
        if (strcmp(actual->pasajero.nombre, nombreBuscado) == 0) {
            printf("Datos del pasajero encontrado:\n");
            mostrarPasajero(actual->pasajero);
            return;
        }
        actual = actual->siguiente;
    }
    printf("Pasajero no encontrado.\n");
}

void eliminarPasajero(struct Nodo** cabeza, struct Nodo** ultimo, const char* nombreEliminar) {
    struct Nodo* actual = *cabeza;

    while (actual != NULL) {
        if (strcmp(actual->pasajero.nombre, nombreEliminar) == 0) {
            if (actual->anterior != NULL) {
                actual->anterior->siguiente = actual->siguiente;
            } else {
                *cabeza = actual->siguiente;
            }

            if (actual->siguiente != NULL) {
                actual->siguiente->anterior = actual->anterior;
            } else {
                *ultimo = actual->anterior;
            }

            free(actual);
            printf("Pasajero eliminado.\n");
            return;
        }
        actual = actual->siguiente;
    }
    printf("Pasajero no encontrado para eliminar.\n");
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
    struct Nodo* ultimo = NULL;

    int opcion;
    do {
        printf("\nMenu:\n");
        printf("1. Mostrar datos de un pasajero\n");
        printf("2. Insertar un pasajero\n");
        printf("3. Eliminar un pasajero\n");
        printf("4. Salir\n");
        printf("Ingrese su opción: ");
        scanf("%d", &opcion);
        getchar();

        switch (opcion) {
            case 1:
                printf("Ingrese el nombre del pasajero a buscar: ");
                char nombreBuscado[50];
                fgets(nombreBuscado, sizeof(nombreBuscado), stdin);
                nombreBuscado[strcspn(nombreBuscado, "\n")] = '\0';
                buscarPasajero(cabeza, nombreBuscado);
                break;
            case 2:
                printf("Ingrese el nombre del pasajero: ");
                struct Pasajero nuevoPasajero;
                fgets(nuevoPasajero.nombre, sizeof(nuevoPasajero.nombre), stdin);
                nuevoPasajero.nombre[strcspn(nuevoPasajero.nombre, "\n")] = '\0'; 
                printf("Ingrese la edad del pasajero: ");
                scanf("%d", &nuevoPasajero.edad);
                getchar(); 
                printf("Ingrese el destino del pasajero: ");
                fgets(nuevoPasajero.destino, sizeof(nuevoPasajero.destino), stdin);
                nuevoPasajero.destino[strcspn(nuevoPasajero.destino, "\n")] = '\0'; 
                insertarNodo(&cabeza, &ultimo, nuevoPasajero);
                printf("Pasajero insertado.\n");
                break;
            case 3:
                printf("Ingrese el nombre del pasajero a eliminar: ");
                char nombreEliminar[50];
                fgets(nombreEliminar, sizeof(nombreEliminar), stdin);
                nombreEliminar[strcspn(nombreEliminar, "\n")] = '\0'; 
                eliminarPasajero(&cabeza, &ultimo, nombreEliminar);
                break;
            case 4:
                
                break;
            default:
                printf("Opción inválida. Intente nuevamente.\n");
                break;
        }

    } while (opcion != 4);

    liberarLista(cabeza);

    return 0;
}
