
// Definición de la estructura para representar un nodo de la pila
struct Nodo {
    int dato;
    struct Nodo* siguiente;
};

// Definición de la estructura para representar la pila
struct Pila {
    struct Nodo* tope;
};

// Prototipos de las operaciones básicas sobre la pila

// Función para crear una pila vacía
struct Pila* crearPila();

// Función para comprobar si la pila está vacía
int estaVacia(struct Pila* pila);

// Función para apilar un elemento en la pila
void apilar(struct Pila* pila, int dato);

// Función para desapilar un elemento de la pila
int desapilar(struct Pila* pila);

// Función para obtener el elemento del tope de la pila sin desapilarlo
int obtenerTope(struct Pila* pila);

// Función para liberar la memoria de la pila
void liberarPila(struct Pila* pila);

