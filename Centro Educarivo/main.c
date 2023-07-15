#include <stdio.h>
#include <stdlib.h>

typedef struct Calificacion
{
    int ID_Actividad;
    float Calificacion;
    short Inactivo;
    struct Calificacion *anterior;
    struct Calificacion *siguiente;
} CALIFICACION;

void cargarCalificacionesDesdeArchivo(CALIFICACION **);

int mostrarMenuCalificacion(CALIFICACION *);

int mostrarMenu();
int menuCalificacion();

void capturarCalificaciones(CALIFICACION **);

void modificarCalificacion(CALIFICACION *);

void mostrarCalificaciones(CALIFICACION *);

void estadoCalificacion(CALIFICACION *);

void guardarCalificacionEnArchivo(CALIFICACION *);

int main()
{
    CALIFICACION *listaCalificaciones = NULL;

    cargarCalificacionesDesdeArchivo(&listaCalificaciones);

    int seleccion;

    do
    {
        seleccion = mostrarMenu();

        switch (seleccion)
        {
        case 0:
            printf("Hasta luego!\n");
            break;
        case 1:

            break;
        case 2:

            break;
        case 3:

            break;
        case 4:
            mostrarMenuCalificacion(listaCalificaciones);
            break;
        case 5:

            break;
        case 6:

            break;
        case 7:

            break;
        case 8:

            break;
        case 9:

            break;
        }
    } while (seleccion != 0);

    return 0;
}

int mostrarMenu()
{
    int opcion;

    printf("\n1: Menu estudiante.\n");
    printf("2: Menu asignatura.\n");
    printf("3: Menu actividades.\n");
    printf("4: Menu calificaciones.\n");
    printf("0: Salir.\n");
    printf("Seleccione una opcion: ");
    fflush(stdin);
    scanf("%d", &opcion);

    return opcion;
}

int menuCalificacion()
{
    char opcion;

    printf("\n1: Capturar calificacion.\n");
    printf("2: Modificar registro de calificacion.\n");
    printf("3: Modificar estado de la calificación.\n");
    printf("4: Mostrar todas las calificaciones.\n");
    printf("\n0: Regresar.\n");
    printf("\nSeleccione: ");
    fflush(stdin);
    opcion = getchar();

    switch (opcion)
    {
    case '1':
        return 1;
    case '2':
        return 2;
    case '3':
        return 3;
    case '4':
        return 4;
    case '5':
        return 5;
    case '6':
        return 6;
    case '7':
        return 7;
    default:
        return 0;
    }
}

int mostrarMenuCalificacion(CALIFICACION *listaCalificaciones)
{
    int seleccion;

    do
    {
        seleccion = menuCalificacion();

        switch (seleccion)
        {
        case 0:
            break;
        case 1:
            capturarCalificaciones(&listaCalificaciones);
            break;
        case 2:
            modificarCalificacion(listaCalificaciones);
            break;
        case 3:
            estadoCalificacion(listaCalificaciones);
            break;
        case 4:
            mostrarCalificaciones(listaCalificaciones);
            break;
        }

    } while (seleccion != 0);

    guardarCalificacionEnArchivo(listaCalificaciones);
}

void cargarCalificacionesDesdeArchivo(CALIFICACION **listaCalificaciones)
{
    FILE *archivoCalificaciones = fopen("calificaiones.txt", "rb");

    if (archivoCalificaciones == NULL)
    {
        return;
    }

    CALIFICACION calificaion;
    fread(&calificaion, sizeof(CALIFICACION), 1, archivoCalificaciones);

    while (!feof(archivoCalificaciones))
    {
        CALIFICACION *nuevoCalificaion = (CALIFICACION *)malloc(sizeof(CALIFICACION));
        nuevoCalificaion->ID_Actividad = calificaion.ID_Actividad;
        nuevoCalificaion->Calificacion = calificaion.Calificacion;
        nuevoCalificaion->Inactivo = calificaion.Inactivo;
        nuevoCalificaion->anterior = NULL;
        nuevoCalificaion->siguiente = NULL;

        if (*listaCalificaciones == NULL)
        {
            *listaCalificaciones = nuevoCalificaion;
        }
        else
        {
            CALIFICACION *ultimaCalificaion = *listaCalificaciones;
            while (ultimaCalificaion->siguiente != NULL)
            {
                ultimaCalificaion = ultimaCalificaion->siguiente;
            }
            ultimaCalificaion->siguiente = nuevoCalificaion;
            nuevoCalificaion->anterior = ultimaCalificaion;
        }

        fread(&calificaion, sizeof(CALIFICACION), 1, archivoCalificaciones);
    }

    fclose(archivoCalificaciones);
}

void capturarCalificaciones(CALIFICACION **listaCalificaciones)
{
    CALIFICACION *nuevoCalificacion = (CALIFICACION *)malloc(sizeof(CALIFICACION));

    printf("Digite el ID: ");
    fflush(stdin);
    scanf("%d", &(nuevoCalificacion->ID_Actividad));

    printf("Digite la calificacion: ");
    fflush(stdin);
    scanf("%f", &(nuevoCalificacion->Calificacion));

    printf("Digite la inactividad: ");
    fflush(stdin);
    scanf("%hd", &(nuevoCalificacion->Inactivo));

    nuevoCalificacion->anterior = NULL;
    nuevoCalificacion->siguiente = NULL;

    if (*listaCalificaciones == NULL)
    {
        *listaCalificaciones = nuevoCalificacion;
    }
    else
    {
        CALIFICACION *ultimoCALIFICACION = *listaCalificaciones;
        while (ultimoCALIFICACION->siguiente != NULL)
        {
            ultimoCALIFICACION = ultimoCALIFICACION->siguiente;
        }
        ultimoCALIFICACION->siguiente = nuevoCalificacion;
        nuevoCalificacion->anterior = ultimoCALIFICACION;
    }
}

void modificarCalificacion(CALIFICACION *listaCalificaciones)
{
    mostrarCalificaciones(listaCalificaciones);

    int idBuscado;
    printf("\nIngrese el ID de la calificación a modificar: ");
    scanf("%d", &idBuscado);

    CALIFICACION *calificacionActual = listaCalificaciones;
    while (calificacionActual != NULL)
    {
        if (calificacionActual->ID_Actividad == idBuscado)
        {
            printf("Calificación encontrada.\n");
            printf("Ingrese la nueva calificación: ");
            scanf("%f", &(calificacionActual->Calificacion));

            printf("La calificación se ha modificado exitosamente.\n");
            return;
        }

        calificacionActual = calificacionActual->siguiente;
    }

    printf("No se encontró una calificación con el ID especificado.\n");
}

void estadoCalificacion(CALIFICACION *listaCalificaciones)
{
    mostrarCalificaciones(listaCalificaciones);

    int idBuscado;
    int estado;
    printf("\nIngrese el ID de la calificación a modificar: ");
    scanf("%d", &idBuscado);

    CALIFICACION *calificacionActual = listaCalificaciones;
    while (calificacionActual != NULL)
    {
        if (calificacionActual->ID_Actividad == idBuscado)
        {
            do
            {
                printf("\nIngrese el nuevo estado (0 Activo | 1 Inactivo): ");
                scanf("%hd", &(calificacionActual->Inactivo));

                if (calificacionActual->Inactivo != 0 && calificacionActual->Inactivo != 1)
                {
                    printf("El número ingresado es invalido\n");
                }

            } while (calificacionActual->Inactivo != 0 && calificacionActual->Inactivo != 1);

            printf("El estado de la calificación se ha modificado exitosamente.\n");
            return;
        }

        calificacionActual = calificacionActual->siguiente;
    }

    printf("No se encontró una calificación con el ID especificado.\n");
}

void mostrarCalificaciones(CALIFICACION *listaCalificaciones)
{
    CALIFICACION *calificacionActual = listaCalificaciones;

    printf("Calificaciones:\n");
    while (calificacionActual != NULL)
    {
        printf("ID: %d, Calificacion: %.2f, inactividad: %hd\n", calificacionActual->ID_Actividad, calificacionActual->Calificacion, calificacionActual->Inactivo);
        calificacionActual = calificacionActual->siguiente;
    }
}

void guardarCalificacionEnArchivo(CALIFICACION *listaCalificaciones)
{
    FILE *archivoCalificaciones = fopen("calificaiones.txt", "wb");
    CALIFICACION *calificacionActual = listaCalificaciones;

    while (calificacionActual != NULL)
    {
        fwrite(calificacionActual, sizeof(CALIFICACION), 1, archivoCalificaciones);
        calificacionActual = calificacionActual->siguiente;
    }

    fclose(archivoCalificaciones);
}
