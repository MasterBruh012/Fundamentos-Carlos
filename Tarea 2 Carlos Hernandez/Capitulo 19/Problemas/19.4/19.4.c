#include <stdio.h>
#include <stdlib.h>

struct Nodo {
    char dato;
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

void apilar(struct Pila* pila, char caracter) {
    struct Nodo* nuevoNodo = (struct Nodo*)malloc(sizeof(struct Nodo));
    nuevoNodo->dato = caracter;
    nuevoNodo->siguiente = pila->tope;
    pila->tope = nuevoNodo;
}

char desapilar(struct Pila* pila) {
    if (estaVacia(pila)) {
        return '\0'; 
    }

    struct Nodo* nodoAEliminar = pila->tope;
    char caracter = nodoAEliminar->dato;
    pila->tope = pila->tope->siguiente;
    free(nodoAEliminar);
    return caracter;
}

int verificarEquilibrio(const char* expresion) {
    struct Pila* pila = crearPila();

    for (int i = 0; expresion[i] != '\0'; i++) {
        if (expresion[i] == '(' || expresion[i] == '{' || expresion[i] == '[') {
            apilar(pila, expresion[i]);
        } else if (expresion[i] == ')' || expresion[i] == '}' || expresion[i] == ']') {
            char caracterApilado = desapilar(pila);
            if ((expresion[i] == ')' && caracterApilado != '(') ||
                (expresion[i] == '}' && caracterApilado != '{') ||
                (expresion[i] == ']' && caracterApilado != '[')) {
                free(pila);
                return 0; 
            }
        }
    }

    int equilibrado = estaVacia(pila);
    free(pila);
    return equilibrado;
}

int main() {
    const char* expresion1 = "((a+b)*5)-7";
    const char* expresion2 = "2*[(a+b)/2.5+x-7*y";

    if (verificarEquilibrio(expresion1)) {
        printf("La expresión 1 tiene los paréntesis, llaves y corchetes equilibrados.\n");
    } else {
        printf("La expresión 1 tiene paréntesis, llaves o corchetes desequilibrados.\n");
    }

    if (verificarEquilibrio(expresion2)) {
        printf("La expresión 2 tiene los paréntesis, llaves y corchetes equilibrados.\n");
    } else {
        printf("La expresión 2 tiene paréntesis, llaves o corchetes desequilibrados.\n");
    }

    return 0;
}
