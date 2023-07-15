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

int mostrarMenuCALIFICACION();
void capturarCalificaciones(CALIFICACION **listaCalificaciones);
void mostrarCalificaciones(CALIFICACION *listaCalificaciones);
void eliminarRegistroCalificacion(CALIFICACION **listaCalificaciones, int id);
void guardarCalificacionEnArchivo(CALIFICACION *listaCalificaciones);
void cargarCalificacionesDesdeArchivo(CALIFICACION **listaCalificaciones);

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

            break;
        case 5:
                capturarCalificaciones(&listaCalificaciones);
            break;
        case 6:

            break;
        case 7:
        
            break;
        case 8:
            mostrarCalificaciones(listaCalificaciones);
            break;
        case 9:
        
            break;
        }
    } while (seleccion != 0);




    eliminarRegistroCalificacion(&listaCalificaciones, 1);
    mostrarCalificaciones(listaCalificaciones);
    guardarCalificacionEnArchivo(listaCalificaciones);

    return 0;
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

void eliminarRegistroCalificacion(CALIFICACION **listaCalificaciones, int id)
{
    CALIFICACION *calificacionActual = *listaCalificaciones;
    CALIFICACION *calificacionAnterior = NULL;

    while (calificacionActual != NULL)
    {
        if (calificacionActual->ID_Actividad == id)
        {
            if (calificacionAnterior != NULL)
            {
                calificacionAnterior->siguiente = calificacionActual->siguiente;
                if (calificacionActual->siguiente != NULL)
                {
                    calificacionActual->siguiente->anterior = calificacionAnterior;
                }
            }
            else
            {
                *listaCalificaciones = calificacionActual->siguiente;
                if (calificacionActual->siguiente != NULL)
                {
                    calificacionActual->siguiente->anterior = NULL;
                }
            }
            free(calificacionActual);
            printf("Registro de CALIFICACION eliminado.\n");
            return;
        }

        calificacionAnterior = calificacionActual;
        calificacionActual = calificacionActual->siguiente;
    }

    printf("No se encontró un CALIFICACION con el ID especificado.\n");
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

int mostrarMenu()
{
    int opcion;

    printf("\n1: Capturar estudiante.\n");
    printf("2: Capturar asignatura.\n");
    printf("3: Capturar actividad.\n");
    printf("4: Registrar estudiante a una asignatura.\n");
    printf("5: Registrar una calificación.\n");
    printf("6: Mostrar estudiantes.\n");
    printf("7: Mostrar asignaturas.\n");
    printf("8: Mostrar calificaciones.\n");
    printf("9: Eliminar registro de estudiante.\n");
    printf("0: Salir.\n");
    printf("Seleccione una opcion: ");
    fflush(stdin);
    scanf("%d", &opcion);

    return opcion;
}

int menucalificacion()
{
    char opcion;

    printf("\n1: Capturar actividad.\n");
    printf("2: Modificar registro de actividad.\n");
    printf("3: Eliminar registro de actividad.\n");
    printf("4: Mostrar actividades.\n");
    printf("3: Todos los pasajeros especificando una compañia telefonica.\n");
    printf("4: Todos los pasajeros cuyo tiempo de viaje promedio esté en un rango.\n");
    printf("5: Todos los pasajeros cuyo monto con el que pagó esté en un rango.\n");
    printf("6: Todos los pasajeros cuyo monto del servicio esté en un rango.\n");
    printf("7: Todos los pasajeros cuya fecha y hora de servicio esté en un rango.\n");
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