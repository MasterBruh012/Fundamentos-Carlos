#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int ID_Actividad;
    float Calificacion;
    short Inactivo;
} CALIFICACION;

typedef struct
{
    CALIFICACION calificacion;
    struct NodoCalificacion *siguiente;
    struct NodoCalificacion *anterior;

} NODOCALIFICACION;

void insertarCalificacion(NODOCALIFICACION *, CALIFICACION);


void leerCalificacion(FILE *, NODOCALIFICACION *);


void guardarCalificaion(FILE *, NODOCALIFICACION *);


void ingresarCalificaion(NODOCALIFICACION **);


int main()
{
    char rutaCalificaciones[] = "calificaciones.txt";

    NODOCALIFICACION *NodoCalificacion = NULL;

    FILE *archivoCalificaion = fopen(rutaCalificaciones, "w+b");

    ingresarCalificaion(&NodoCalificacion);
    guardarCalificaion(archivoCalificaion,NodoCalificacion);

    fclose(archivoCalificaion);

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

void insertarCalificacion(NODOCALIFICACION *lista, CALIFICACION calificacion)
{
    NODOCALIFICACION *nuevoNodo = crearNodo(calificacion);
    if (lista == NULL)
    {
        lista = nuevoNodo;
    }
    else
    {
        NODOCALIFICACION *temp = lista;
        while (temp->siguiente != NULL)
        {
            temp = temp->siguiente;
        }
        temp->siguiente = nuevoNodo;
        nuevoNodo->anterior = temp;
    }
}

void leerCalificaion(FILE *archivo, NODOCALIFICACION *nodoCalificaion)
{
    CALIFICACION CalificacionActual;

    fseek(archivo, 0, SEEK_END);
    int tamano = ftell(archivo);
    fseek(archivo, 0, SEEK_SET);

    while (ftell(archivo) < tamano) // reemplazando el feof().
    {
        fread(&CalificacionActual, sizeof(CALIFICACION), 1, archivo);

        insertarCalificacion(nodoCalificaion, CalificacionActual);
    }
}

void guardarCalificaion(FILE *archivoCalificaion, NODOCALIFICACION *nodocalificacion)
{
    NODOCALIFICACION *temp = nodocalificacion;
    while (temp != NULL)
    {
        fwrite(&temp->calificacion, sizeof(CALIFICACION), 1, archivoCalificaion);
        temp = temp->siguiente;
    }
}

void ingresarCalificaion(NODOCALIFICACION **NodoCalificaciones)
{
    CALIFICACION calificacion;
    printf("Ingrese el ID de la actividad: ");
    scanf("%d", &calificacion.ID_Actividad);

    printf("Ingrese la calificación: ");
    scanf("%f", &calificacion.Calificacion);

    printf("Ingrese el estado inactivo (0 o 1): ");
    scanf("%hd", &calificacion.Inactivo);

    insertarCalificacion(*NodoCalificaciones, calificacion);
}