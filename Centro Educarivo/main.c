#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int ID_Actividad;
    float Calificacion;
    short Inactivo;
} CALIFICACION;

typedef struct NODOCALIFICACION
{
    CALIFICACION calificacion;
    struct NODOCALIFICACION *siguiente;
    struct NODOCALIFICACION *anterior;
} NODOCALIFICACION;

void insertarCalificacion(NODOCALIFICACION **, CALIFICACION);
void leerCalificacion(FILE *, NODOCALIFICACION *);
void guardarCalificacion(FILE *, NODOCALIFICACION *);
void ingresarCalificacion(NODOCALIFICACION **);

int main()
{
    char rutaCalificaciones[] = "calificaciones.txt";

    NODOCALIFICACION *NodoCalificacion = NULL;

    FILE *archivoCalificacion = fopen(rutaCalificaciones, "w+b");

    ingresarCalificacion(&NodoCalificacion);
    guardarCalificacion(archivoCalificacion, NodoCalificacion);

    fclose(archivoCalificacion);

    return 0;
}

NODOCALIFICACION *crearNodo(CALIFICACION calificacion)
{
    NODOCALIFICACION *nuevoNodo = (NODOCALIFICACION *)malloc(sizeof(NODOCALIFICACION));
    nuevoNodo->calificacion = calificacion;
    nuevoNodo->siguiente = NULL;
    nuevoNodo->anterior = NULL;
    return nuevoNodo;
}

void insertarCalificacion(NODOCALIFICACION **lista, CALIFICACION calificacion)
{
    NODOCALIFICACION *nuevoNodo = crearNodo(calificacion);
    if (*lista == NULL)
    {
        *lista = nuevoNodo;
    }
    else
    {
        NODOCALIFICACION *temp = *lista;
        while (temp->siguiente != NULL)
        {
            temp = temp->siguiente;
        }
        temp->siguiente = nuevoNodo;
        nuevoNodo->anterior = temp;
    }
}

void leerCalificacion(FILE *archivo, NODOCALIFICACION *nodoCalificacion)
{
    CALIFICACION CalificacionActual;

    fseek(archivo, 0, SEEK_END);
    int tamano = ftell(archivo);
    fseek(archivo, 0, SEEK_SET);

    while (ftell(archivo) < tamano)
    {
        fread(&CalificacionActual, sizeof(CALIFICACION), 1, archivo);
        insertarCalificacion(&(*nodoCalificacion), CalificacionActual);
    }
}

void guardarCalificacion(FILE *archivoCalificacion, NODOCALIFICACION *nodocalificacion)
{
    NODOCALIFICACION *temp = nodocalificacion;
    while (temp != NULL)
    {
        fwrite(&temp->calificacion, sizeof(CALIFICACION), 1, archivoCalificacion);
        temp = temp->siguiente;
    }
}

void ingresarCalificacion(NODOCALIFICACION **NodoCalificaciones)
{
    CALIFICACION calificacion;
    printf("Ingrese el ID de la actividad: ");
    scanf("%d", &calificacion.ID_Actividad);

    printf("Ingrese la calificación: ");
    scanf("%f", &calificacion.Calificacion);

    printf("Ingrese el estado inactivo (0 o 1): ");
    scanf("%hd", &calificacion.Inactivo);

    insertarCalificacion(&(*NodoCalificaciones), calificacion);
}
