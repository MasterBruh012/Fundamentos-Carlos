#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Estudiante
{
    int ID_Estudiante;
    char matricula[9];
    char nombres[50];
    char apellidos[50];
    char carrera[5];
    short inactivo;

    struct Estudiante *anterior;
    struct Estudiante *siguiente;
} ESTUDIANTE;

typedef struct Asignatura
{
    int ID_Asignatura;
    char codigo[10];
    char nombre[25];
    int credito;
    short inactivo;

    struct Asignatura *anterior;
    struct Asignatura *siguiente;
} ASIGNATURA;

typedef struct Calificacion
{
    int ID_Actividad;
    float Calificacion;
} CALIFICACION;

typedef struct Actividad
{
    int ID_Actividad;
    char nombre[25];
    short Inactivo;
    struct Actividad *anterior;
    struct Actividad *siguiente;
} ACTIVIDAD;

typedef struct EstudianteAsignatura
{
    int ID_Estudiante;
    int ID_Asignatura;
    CALIFICACION listaCalificacion;
    short inactivo;

    struct EstudianteAsignatura *anterior;
    struct EstudianteAsignatura *siguiente;
} ESTUDIANTEASIGNATURA;

void cargarEstudiante(ESTUDIANTE **);
void cargarAsignatura(ASIGNATURA **);
void cargarActividad(ACTIVIDAD **);
void cargarCalificacion(ESTUDIANTEASIGNATURA **);

int mostrarMenuEstudiantes(ESTUDIANTE *);
int mostrarMenuAsignaturas(ASIGNATURA *);
void mostrarMenuActividad(ACTIVIDAD *);
int mostrarMenuCalificacion(ACTIVIDAD *, ESTUDIANTEASIGNATURA *, ESTUDIANTE *, ASIGNATURA *);

int mostrarMenu();
int menuEstudiante();
int menuAsignatura();
int menuActividad();
int menuCalificacion();

void capturarEstudiante(ESTUDIANTE **);
void capturarAsignatura(ASIGNATURA **);
void capturarActividad(ACTIVIDAD **);
void capturarCalificaciones(ACTIVIDAD *, ESTUDIANTEASIGNATURA **, ESTUDIANTE *, ASIGNATURA *);

void modificarEstudiante(ESTUDIANTE *);
void modificarAsignatura(ASIGNATURA *);
void modificarActividad(ACTIVIDAD *);
void modificarCalificacion(ESTUDIANTEASIGNATURA *);

void mostrarEstudiantes(ESTUDIANTE *);
void mostrarAsignatura(ASIGNATURA *);
void mostrarActividad(ACTIVIDAD *);
void mostrarCalificaciones(ESTUDIANTEASIGNATURA *);

void estadoEstudiante(ESTUDIANTE *);
void estadoAsignatura(ASIGNATURA *);
void estadoActividad(ACTIVIDAD *);
void estadoCalificacion(ESTUDIANTEASIGNATURA *);

void guardarEstudiante(ESTUDIANTE *);
void guardarAsignatura(ASIGNATURA *);
void guardarActividad(ACTIVIDAD *);
void guardarCalificacion(ESTUDIANTEASIGNATURA *);

void mostrarEstudiantesActivos(ESTUDIANTE *);
void mostrarAsignaturaActiva(ASIGNATURA *);
void mostrarActividadActiva(ACTIVIDAD *);
void mostrarCalificacionesActiva(ESTUDIANTEASIGNATURA *);

void mostrarEstudiantesInactivos(ESTUDIANTE *);
void mostrarAsignaturaInactiva(ASIGNATURA *);
void mostrarActividadInactiva(ACTIVIDAD *);
void mostrarCalificacionesInactiva(ESTUDIANTEASIGNATURA *);

int main()
{
    ESTUDIANTE *listaEstudiantes = NULL;
    ASIGNATURA *listaAsignatura = NULL;
    ACTIVIDAD *listaActividad = NULL;
    ESTUDIANTEASIGNATURA *listaEstAsg = NULL;

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
            mostrarMenuEstudiantes(listaEstudiantes);
            break;
        case 2:
            mostrarMenuAsignaturas(listaAsignatura);
            break;
        case 3:
            mostrarMenuActividad(listaActividad);
            break;
        case 4:
            mostrarMenuCalificacion(listaActividad, listaEstAsg, listaEstudiantes, listaAsignatura);
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
    printf("\n0: Salir.\n");
    printf("\nSeleccione una opcion: ");
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
    printf("5: Mostrar todas las calificaciones activas.\n");
    printf("6: Mostrar todas las calificaciones inactivas.\n");
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
    default:
        return 0;
    }
}

int mostrarMenuCalificacion(ACTIVIDAD *listaActividad, ESTUDIANTEASIGNATURA *listaEstAsg, ESTUDIANTE *listaEstudiante, ASIGNATURA *listaAsignatura)
{
    int seleccion;
    cargarEstudiante(&listaEstudiante);
    cargarAsignatura(&listaAsignatura);
    cargarActividad(&listaActividad);
    cargarCalificacion(&listaEstAsg);

    do
    {
        seleccion = menuCalificacion();

        switch (seleccion)
        {
        case 0:
            break;
        case 1:
            capturarCalificaciones(listaActividad, &listaEstAsg, listaEstudiante, listaAsignatura);
            guardarCalificacion(listaEstAsg);
            break;
        case 2:
            modificarCalificacion(listaEstAsg);
            guardarCalificacion(listaEstAsg);
            break;
        case 3:
            estadoCalificacion(listaEstAsg);
            guardarCalificacion(listaEstAsg);
            break;
        case 4:
            mostrarCalificaciones(listaEstAsg);
            break;
        case 5:
            mostrarCalificacionesActiva(listaEstAsg);
            break;
        case 6:
            mostrarCalificacionesInactiva(listaEstAsg);
            break;
        }

    } while (seleccion != 0);
}

void cargarCalificacion(ESTUDIANTEASIGNATURA **listaCalificaciones)
{
    FILE *archivoCalificaciones = fopen("calificaciones.txt", "rb");

    if (archivoCalificaciones == NULL)
    {
        return;
    }

    ESTUDIANTEASIGNATURA calificaion;
    fread(&calificaion, sizeof(ESTUDIANTEASIGNATURA), 1, archivoCalificaciones);

    while (!feof(archivoCalificaciones))
    {
        ESTUDIANTEASIGNATURA *nuevoCalificaion = (ESTUDIANTEASIGNATURA *)malloc(sizeof(ESTUDIANTEASIGNATURA));
        nuevoCalificaion->ID_Estudiante = calificaion.ID_Estudiante;
        nuevoCalificaion->ID_Asignatura = calificaion.ID_Asignatura;
        nuevoCalificaion->listaCalificacion.ID_Actividad = calificaion.listaCalificacion.ID_Actividad;
        nuevoCalificaion->listaCalificacion.Calificacion = calificaion.listaCalificacion.Calificacion;
        nuevoCalificaion->inactivo = calificaion.inactivo;
        nuevoCalificaion->anterior = NULL;
        nuevoCalificaion->siguiente = NULL;

        if (*listaCalificaciones == NULL)
        {
            *listaCalificaciones = nuevoCalificaion;
        }
        else
        {
            ESTUDIANTEASIGNATURA *ultimaCalificaion = *listaCalificaciones;
            while (ultimaCalificaion->siguiente != NULL)
            {
                ultimaCalificaion = ultimaCalificaion->siguiente;
            }
            ultimaCalificaion->siguiente = nuevoCalificaion;
            nuevoCalificaion->anterior = ultimaCalificaion;
        }

        fread(&calificaion, sizeof(ESTUDIANTEASIGNATURA), 1, archivoCalificaciones);
    }

    fclose(archivoCalificaciones);

    return;
}

void capturarCalificaciones(ACTIVIDAD *listaActividad, ESTUDIANTEASIGNATURA **listaEstAsg, ESTUDIANTE *listaEstudiante, ASIGNATURA *listaAsignatura)
{
    int comprobante, id;

    ESTUDIANTEASIGNATURA *nuevoEstAsg = (ESTUDIANTEASIGNATURA *)malloc(sizeof(ESTUDIANTEASIGNATURA));

    if (listaEstudiante == NULL)
    {
        printf("No existen estudiantes");
        return;
    }

    if (listaAsignatura == NULL)
    {
        printf("No existen asignaturas");
        return;
    }

    if (listaActividad == NULL)
    {
        printf("No existen actividades");
        return;
    }

    do
    {
        mostrarEstudiantes(listaEstudiante);
        comprobante = 0;
        printf("\nID_Estudiante: ");
        fflush(stdin);
        scanf("%d", &id);

        for (ESTUDIANTE *estudiante = listaEstudiante; estudiante != NULL; estudiante = estudiante->siguiente)
        {
            if (id == estudiante->ID_Estudiante)
            {
                comprobante = 0;
                break;
            }
            if (estudiante != NULL)
            {
                comprobante = 1;
            }
        }

        if (comprobante == 1)
            printf("\nEl Id que esta ingresando no existe. por favor ingrese otro\n");

        nuevoEstAsg->ID_Estudiante = id;
    } while (comprobante != 0);

    do
    {
        mostrarAsignatura(listaAsignatura);
        comprobante = 0;
        printf("\nID_Asignatura: ");
        fflush(stdin);
        scanf("%d", &id);

        for (ASIGNATURA *asignatura = listaAsignatura; asignatura != NULL; asignatura = asignatura->siguiente)
        {
            if (id == asignatura->ID_Asignatura)
            {
                comprobante = 0;
                break;
            }
            if (asignatura != NULL)
            {
                comprobante = 1;
            }
        }

        if (comprobante == 1)
            printf("\nEl Id que esta ingresando no existe. por favor ingrese otro\n");

        nuevoEstAsg->ID_Asignatura = id;
    } while (comprobante != 0);

    do
    {
        mostrarActividad(listaActividad);
        comprobante = 0;
        printf("\nID_Actividad: ");
        fflush(stdin);
        scanf("%d", &id);

        for (ACTIVIDAD *actividad = listaActividad; actividad != NULL; actividad = actividad->siguiente)
        {
            if (id == actividad->ID_Actividad)
            {
                comprobante = 0;
                break;
            }
            if (actividad != NULL)
            {
                comprobante = 1;
            }
        }

        if (comprobante == 1)
            printf("\nEl Id que esta ingresando no existe. por favor ingrese otro\n");

        nuevoEstAsg->listaCalificacion.ID_Actividad = id;
    } while (comprobante != 0);

    printf("Digite la calificacion: ");
    fflush(stdin);
    scanf("%f", &(nuevoEstAsg->listaCalificacion.Calificacion));

    do
    {
        printf("Digite la inactividad (0 Activo | 1 Inactivo): ");
        fflush(stdin);
        scanf("%hd", &(nuevoEstAsg->inactivo));

        if (nuevoEstAsg->inactivo != 0 && nuevoEstAsg->inactivo != 1)
        {
            printf("El número ingresado es invalido\n");
        }

    } while (nuevoEstAsg->inactivo != 0 && nuevoEstAsg->inactivo != 1);

    nuevoEstAsg->anterior = NULL;
    nuevoEstAsg->siguiente = NULL;

    if (*listaEstAsg == NULL)
    {
        *listaEstAsg = nuevoEstAsg;
    }
    else
    {
        ESTUDIANTEASIGNATURA *ultimoEstAsg = *listaEstAsg;
        while (ultimoEstAsg->siguiente != NULL)
        {
            ultimoEstAsg = ultimoEstAsg->siguiente;
        }
        ultimoEstAsg->siguiente = nuevoEstAsg;
        nuevoEstAsg->anterior = ultimoEstAsg;
    }
    return;
}

void modificarCalificacion(ESTUDIANTEASIGNATURA *listaCalificaciones)
{
    if (listaCalificaciones == NULL)
    {
        printf("\nNo existen calificaciones\n");
        return;
    }

    mostrarCalificaciones(listaCalificaciones);

    int idBuscado;
    printf("\nIngrese el ID del estudiante a modificar: ");
    scanf("%d", &idBuscado);

    ESTUDIANTEASIGNATURA *calificacionActual = listaCalificaciones;
    while (calificacionActual != NULL)
    {
        if (calificacionActual->ID_Estudiante == idBuscado)
        {
            printf("Calificación encontrada.\n");
            printf("Ingrese la nueva calificación: ");
            scanf("%f", &(calificacionActual->listaCalificacion.Calificacion));

            printf("La calificación se ha modificado exitosamente.\n");
            return;
        }

        calificacionActual = calificacionActual->siguiente;
    }

    printf("No se encontró una calificación con el ID especificado.\n");

    return;
}

void estadoEstudiante(ESTUDIANTE *listaEstudiantes)
{
    if (listaEstudiantes == NULL)
    {
        printf("\nNo existen estudiantes\n");
        return;
    }

    mostrarEstudiantes(listaEstudiantes);

    int idBuscado;
    int estado;
    printf("\nIngrese el ID del estudiante a modificar: ");
    scanf("%d", &idBuscado);

    ESTUDIANTE *estudianteActual = listaEstudiantes;
    while (estudianteActual != NULL)
    {
        if (estudianteActual->ID_Estudiante == idBuscado)
        {
            do
            {
                printf("\nIngrese el nuevo estado (0 Activo | 1 Inactivo): ");
                scanf("%hd", &(estudianteActual->inactivo));

                if (estudianteActual->inactivo != 0 && estudianteActual->inactivo != 1)
                {
                    printf("El número ingresado es invalido\n");
                }

            } while (estudianteActual->inactivo != 0 && estudianteActual->inactivo != 1);

            printf("El estado del estudiante se ha modificado exitosamente.\n");
            return;
        }

        estudianteActual = estudianteActual->siguiente;
    }

    printf("No se encontró un estudiante con el ID especificado.\n");

    return;
}

void estadoCalificacion(ESTUDIANTEASIGNATURA *listaCalificaciones)
{
    if (listaCalificaciones == NULL)
    {
        printf("\nNo existen calificaciones\n");
        return;
    }

    mostrarCalificaciones(listaCalificaciones);

    int idBuscado;
    int estado;
    printf("\nIngrese el ID de la calificación a modificar: ");
    scanf("%d", &idBuscado);

    ESTUDIANTEASIGNATURA *calificacionActual = listaCalificaciones;
    while (calificacionActual != NULL)
    {
        if (calificacionActual->listaCalificacion.ID_Actividad == idBuscado)
        {
            do
            {
                printf("\nIngrese el nuevo estado (0 Activo | 1 Inactivo): ");
                scanf("%hd", &(calificacionActual->inactivo));

                if (calificacionActual->inactivo != 0 && calificacionActual->inactivo != 1)
                {
                    printf("El número ingresado es invalido\n");
                }

            } while (calificacionActual->inactivo != 0 && calificacionActual->inactivo != 1);

            printf("El estado de la calificación se ha modificado exitosamente.\n");
            return;
        }

        calificacionActual = calificacionActual->siguiente;
    }

    printf("No se encontró una calificación con el ID especificado.\n");

    return;
}

void estadoAsignatura(ASIGNATURA *listaAsignatura)
{
    if (listaAsignatura == NULL)
    {
        printf("\nNo existen asignaturas\n");
        return;
    }

    mostrarAsignatura(listaAsignatura);

    int idBuscado;
    int estado;
    printf("\nIngrese el ID de la asignatura a modificar: ");
    scanf("%d", &idBuscado);

    ASIGNATURA *asignaturaActual = listaAsignatura;
    while (asignaturaActual != NULL)
    {
        if (asignaturaActual->ID_Asignatura == idBuscado)
        {
            do
            {
                printf("\nIngrese el nuevo estado (0 Activo | 1 Inactivo): ");
                scanf("%hd", &(asignaturaActual->inactivo));

                if (asignaturaActual->inactivo != 0 && asignaturaActual->inactivo != 1)
                {
                    printf("El número ingresado es invalido\n");
                }

            } while (asignaturaActual->inactivo != 0 && asignaturaActual->inactivo != 1);

            printf("El estado de la asignatura se ha modificado exitosamente.\n");
            return;
        }

        asignaturaActual = asignaturaActual->siguiente;
    }

    printf("No se encontró una asignatura con el ID especificado.\n");
}

void mostrarCalificaciones(ESTUDIANTEASIGNATURA *listaCalificaciones)
{
    ESTUDIANTEASIGNATURA *calificacionActual = listaCalificaciones;

    if (listaCalificaciones == NULL)
    {
        printf("\nNo existen calificaciones\n");
        return;
    }

    printf("\nCalificaciones:\n\n");
    while (calificacionActual != NULL)
    {
        printf("ID_Estudiante: %d\t\t\tID_Asignatura: %d\t\t\tID_Actividad: %d\t\t\tCalificacion: %.2f\t\t\tInactividad: %hd\n", calificacionActual->ID_Estudiante, calificacionActual->ID_Asignatura, calificacionActual->listaCalificacion.ID_Actividad, calificacionActual->listaCalificacion.Calificacion, calificacionActual->inactivo);
        calificacionActual = calificacionActual->siguiente;
    }
}

void guardarCalificacion(ESTUDIANTEASIGNATURA *listaCalificaciones)
{
    FILE *archivoCalificaciones = fopen("calificaciones.txt", "wb");
    ESTUDIANTEASIGNATURA *calificacionActual = listaCalificaciones;

    while (calificacionActual != NULL)
    {
        fwrite(calificacionActual, sizeof(ESTUDIANTEASIGNATURA), 1, archivoCalificaciones);
        calificacionActual = calificacionActual->siguiente;
    }

    fclose(archivoCalificaciones);
}

void capturarAsignatura(ASIGNATURA **listaAsignatura)
{
    int comprobante, id;

    ASIGNATURA *nuevaAsignatura = (ASIGNATURA *)malloc(sizeof(ASIGNATURA));

    do
    {
        mostrarAsignatura(*listaAsignatura);

        comprobante = 0;
        printf("\nId: ");
        fflush(stdin);
        scanf("%d", &id);

        if (id <= 0)
        {
            printf("\nEl ID debe ser mayor que 0\n");
            comprobante = 1;
        }

        else
        {
            ASIGNATURA *asignatura = *listaAsignatura;
            while (asignatura != NULL)
            {
                if (id == asignatura->ID_Asignatura)
                {
                    comprobante = 1;
                    printf("\nEl Id que esta ingresando ya existe. por favor ingrese otro\n");
                    break;
                }
                asignatura = asignatura->siguiente;
            }
            nuevaAsignatura->ID_Asignatura = id;
        }

    } while (comprobante != 0);

    printf("Código: ");
    fflush(stdin);
    gets(nuevaAsignatura->codigo);

    printf("Nombre: ");
    fflush(stdin);
    gets(nuevaAsignatura->nombre);

    printf("Créditos: ");
    fflush(stdin);
    scanf("%d", &(nuevaAsignatura->credito));

    do
    {
        printf("Digite la inactividad (0 Activo | 1 Inactivo): ");
        fflush(stdin);
        scanf("%hd", &(nuevaAsignatura->inactivo));

        if (nuevaAsignatura->inactivo != 0 && nuevaAsignatura->inactivo != 1)
        {
            printf("El número ingresado es invalido\n");
        }

    } while (nuevaAsignatura->inactivo != 0 && nuevaAsignatura->inactivo != 1);

    nuevaAsignatura->anterior = NULL;
    nuevaAsignatura->siguiente = NULL;

    if (*listaAsignatura == NULL)
    {
        *listaAsignatura = nuevaAsignatura;
    }
    else
    {
        ASIGNATURA *ultimoAsignatura = *listaAsignatura;
        while (ultimoAsignatura->siguiente != NULL)
        {
            ultimoAsignatura = ultimoAsignatura->siguiente;
        }
        ultimoAsignatura->siguiente = nuevaAsignatura;
        nuevaAsignatura->anterior = ultimoAsignatura;
    }
}

void mostrarAsignatura(ASIGNATURA *listaAsignatura)
{
    if (listaAsignatura == NULL)
    {
        printf("\nNo existen asignaturas\n");
        return;
    }

    ASIGNATURA *asignatura = listaAsignatura;

    printf("\nAsignaturas:\n\n");
    while (asignatura != NULL)
    {
        printf("ID: %d\t\tCódigo: %s\t\tNombre: %s\t\tCréditos: %d\t\tInactividad: %hd\n", asignatura->ID_Asignatura, asignatura->codigo, asignatura->nombre, asignatura->credito, asignatura->inactivo);
        asignatura = asignatura->siguiente;
    }
}

int menuAsignatura()
{
    char opcion;
    printf("\n1: Capturar asignatura.\n");
    printf("2: Modificar asignatura.\n");
    printf("3: Modificar estado de la asignatura.\n");
    printf("4: Mostrar todas las asignaturas.\n");
    printf("5: Mostrar todas las asignaturas activas.\n");
    printf("6: Mostrar todas las asignaturas inactivas.\n");
    printf("\n0: Regresar \n");

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
    default:
        return 0;
    }
}

int menuEstudiante()
{
    char opcion;
    printf("\n1: Capturar estudiante.\n");
    printf("2: Modificar estudiante.\n");
    printf("3: Modificar estado de un estudiante.\n");
    printf("4: Mostrar todos las estudiante.\n");
    printf("5: Mostrar todos las estudiante activos.\n");
    printf("6: Mostrar todos las estudiante inactivos.\n");
    printf("\n0: Regresar\n");

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
    default:
        return 0;
    }
}

int mostrarMenuEstudiantes(ESTUDIANTE *listaEstudiantes)
{
    int seleccion;
    cargarEstudiante(&listaEstudiantes);

    do
    {
        seleccion = menuEstudiante();

        switch (seleccion)
        {
        case 1:
            capturarEstudiante(&listaEstudiantes);
            guardarEstudiante(listaEstudiantes);
            break;
        case 2:
            modificarEstudiante(listaEstudiantes);
            guardarEstudiante(listaEstudiantes);
            break;
        case 3:
            estadoEstudiante(listaEstudiantes);
            guardarEstudiante(listaEstudiantes);
            break;
        case 4:
            mostrarEstudiantes(listaEstudiantes);
            break;
        case 5:
            mostrarEstudiantesActivos(listaEstudiantes);
            break;
        case 6:
            mostrarEstudiantesInactivos(listaEstudiantes);
            break;
        case 0:
            break;
        }
    } while (seleccion != 0);
}

int mostrarMenuAsignaturas(ASIGNATURA *listaAsignatura)
{
    int seleccion;
    cargarAsignatura(&listaAsignatura);

    do
    {
        seleccion = menuAsignatura();

        switch (seleccion)
        {
        case 1:
            capturarAsignatura(&listaAsignatura);
            guardarAsignatura(listaAsignatura);
            break;
        case 2:
            modificarAsignatura(listaAsignatura);
            guardarAsignatura(listaAsignatura);
            break;
        case 3:
            estadoAsignatura(listaAsignatura);
            guardarAsignatura(listaAsignatura);
            break;
        case 4:
            mostrarAsignatura(listaAsignatura);
            break;
        case 5:
            mostrarAsignaturaActiva(listaAsignatura);
            break;
        case 6:
            mostrarAsignaturaInactiva(listaAsignatura);
            break;
        case 0:
            break;
        }
    } while (seleccion != 0);
}

void modificarAsignatura(ASIGNATURA *listaAsignatura)
{
    if (listaAsignatura == NULL)
    {
        printf("\nNo existen asignaturas\n");
        return;
    }

    mostrarAsignatura(listaAsignatura);

    int idBuscado;
    printf("\nIngrese el ID de la asignatura a modificar: ");
    scanf("%d", &idBuscado);

    ASIGNATURA *asignaturaActual = listaAsignatura;
    while (asignaturaActual != NULL)
    {
        if (asignaturaActual->ID_Asignatura == idBuscado)
        {
            printf("Asignatura encontrada.\n");
            printf("Ingrese nuevo nombre: ");
            fflush(stdin);
            gets(asignaturaActual->nombre);

            printf("Ingrese nuevo código: ");
            fflush(stdin);
            gets(asignaturaActual->codigo);

            printf("Ingrese nueva cantidad de créditos: ");
            fflush(stdin);
            scanf("%d", &(asignaturaActual->credito));

            printf("La asignatura se ha modificado.\n");
            return;
        }

        asignaturaActual = asignaturaActual->siguiente;
    }

    printf("No se encontró una asignatura con el ID especificado.\n");
}

void cargarAsignatura(ASIGNATURA **listaAsignaturas)
{
    FILE *archivoAsignaturas = fopen("asignaturas.txt", "rb");
    if (archivoAsignaturas == NULL)
    {
        return;
    }

    ASIGNATURA asignatura;
    fread(&asignatura, sizeof(ASIGNATURA), 1, archivoAsignaturas);

    while (!feof(archivoAsignaturas))
    {
        ASIGNATURA *nuevaAsignatura = (ASIGNATURA *)malloc(sizeof(ASIGNATURA));
        nuevaAsignatura->ID_Asignatura = asignatura.ID_Asignatura;
        strcpy(nuevaAsignatura->codigo, asignatura.codigo);
        strcpy(nuevaAsignatura->nombre, asignatura.nombre);
        nuevaAsignatura->credito = asignatura.credito;
        nuevaAsignatura->inactivo = asignatura.inactivo;

        nuevaAsignatura->anterior = NULL;
        nuevaAsignatura->siguiente = NULL;

        if (*listaAsignaturas == NULL)
        {
            *listaAsignaturas = nuevaAsignatura;
        }
        else
        {
            ASIGNATURA *ultimaAsignatura = *listaAsignaturas;
            while (ultimaAsignatura->siguiente != NULL)
            {
                ultimaAsignatura = ultimaAsignatura->siguiente;
            }
            ultimaAsignatura->siguiente = nuevaAsignatura;
            nuevaAsignatura->anterior = ultimaAsignatura;
        }

        fread(&asignatura, sizeof(ASIGNATURA), 1, archivoAsignaturas);
    }

    fclose(archivoAsignaturas);
}

void guardarAsignatura(ASIGNATURA *listaAsignaturas)
{
    FILE *archivoAsignaturas = fopen("asignaturas.txt", "wb");
    if (archivoAsignaturas == NULL)
    {
        printf("No se pudo guardar el archivo.\n");
        return;
    }

    ASIGNATURA *asignaturaActual = listaAsignaturas;

    while (asignaturaActual != NULL)
    {
        fwrite(asignaturaActual, sizeof(ASIGNATURA), 1, archivoAsignaturas);
        asignaturaActual = asignaturaActual->siguiente;
    }

    fclose(archivoAsignaturas);
}

void cargarEstudiante(ESTUDIANTE **listaEstudiantes)
{
    FILE *archivoEstudiantes = fopen("estudiante.txt", "rb");
    if (archivoEstudiantes == NULL)
    {
        return;
    }

    ESTUDIANTE estudiante;
    fread(&estudiante, sizeof(ESTUDIANTE), 1, archivoEstudiantes);

    while (!feof(archivoEstudiantes))
    {
        ESTUDIANTE *nuevoEstudiante = (ESTUDIANTE *)malloc(sizeof(ESTUDIANTE));
        nuevoEstudiante->ID_Estudiante = estudiante.ID_Estudiante;
        strcpy(nuevoEstudiante->matricula, estudiante.matricula);
        strcpy(nuevoEstudiante->nombres, estudiante.nombres);
        strcpy(nuevoEstudiante->apellidos, estudiante.apellidos);
        strcpy(nuevoEstudiante->carrera, estudiante.carrera);
        nuevoEstudiante->inactivo = estudiante.inactivo;

        nuevoEstudiante->anterior = NULL;
        nuevoEstudiante->siguiente = NULL;

        if (*listaEstudiantes == NULL)
        {
            *listaEstudiantes = nuevoEstudiante;
        }
        else
        {
            ESTUDIANTE *ultimoEstudiante = *listaEstudiantes;
            while (ultimoEstudiante->siguiente != NULL)
            {
                ultimoEstudiante = ultimoEstudiante->siguiente;
            }
            ultimoEstudiante->siguiente = nuevoEstudiante;
            nuevoEstudiante->anterior = ultimoEstudiante;
        }

        fread(&estudiante, sizeof(ESTUDIANTE), 1, archivoEstudiantes);
    }

    fclose(archivoEstudiantes);
}

void capturarEstudiante(ESTUDIANTE **listaEstudiantes)
{
    int comprobante, id;

    ESTUDIANTE *nuevoEstudiante = (ESTUDIANTE *)malloc(sizeof(ESTUDIANTE));
    do
    {
        mostrarEstudiantes(*listaEstudiantes);
        comprobante = 0;
        printf("\nId: ");
        fflush(stdin);
        scanf("%d", &id);

        if (id <= 0)
        {
            printf("\nEl ID debe ser mayor que 0\n");
            comprobante = 1;
        }

        else
        {
            ESTUDIANTE *estudiante = *listaEstudiantes;
            while (estudiante != NULL)
            {
                if (id == estudiante->ID_Estudiante)
                {
                    comprobante = 1;
                    printf("\nEl Id que esta ingresando ya existe. por favor ingrese otro\n");
                    break;
                }
                estudiante = estudiante->siguiente;
            }
            nuevoEstudiante->ID_Estudiante = id;
        }

    } while (comprobante != 0);

    printf("Matrícula: ");
    fflush(stdin);
    gets(nuevoEstudiante->matricula);

    printf("Nombres: ");
    fflush(stdin);
    gets(nuevoEstudiante->nombres);

    printf("Apellidos: ");
    fflush(stdin);
    gets(nuevoEstudiante->apellidos);

    printf("Carrera (Máximo 5 caracteres): ");
    fflush(stdin);
    gets(nuevoEstudiante->carrera);

    do
    {
        printf("Digite la inactividad (0 Activo | 1 Inactivo): ");
        fflush(stdin);
        scanf("%hd", &(nuevoEstudiante->inactivo));

        if (nuevoEstudiante->inactivo != 0 && nuevoEstudiante->inactivo != 1)
        {
            printf("El número ingresado es invalido\n");
        }

    } while (nuevoEstudiante->inactivo != 0 && nuevoEstudiante->inactivo != 1);

    nuevoEstudiante->anterior = NULL;
    nuevoEstudiante->siguiente = NULL;

    if (*listaEstudiantes == NULL)
    {
        *listaEstudiantes = nuevoEstudiante;
    }
    else
    {
        ESTUDIANTE *ultimoEstudiante = *listaEstudiantes;
        while (ultimoEstudiante->siguiente != NULL)
        {
            ultimoEstudiante = ultimoEstudiante->siguiente;
        }
        ultimoEstudiante->siguiente = nuevoEstudiante;
        nuevoEstudiante->anterior = ultimoEstudiante;
    }
}

void modificarEstudiante(ESTUDIANTE *listaEstudiantes)
{

    if (listaEstudiantes == NULL)
    {
        printf("\nNo existen estudiantes\n");
        return;
    }
    mostrarEstudiantes(listaEstudiantes);

    int idBuscado;
    printf("\nIngrese el ID del estudiante a modificar: ");
    scanf("%d", &idBuscado);

    ESTUDIANTE *estudianteActual = listaEstudiantes;
    while (estudianteActual != NULL)
    {
        if (estudianteActual->ID_Estudiante == idBuscado)
        {
            printf("Estudiante encontrado.\n");
            printf("Ingrese nueva matrícula: ");
            fflush(stdin);
            gets(estudianteActual->matricula);

            printf("Ingrese nuevos nombres: ");
            fflush(stdin);
            gets(estudianteActual->nombres);

            printf("Ingrese nuevos apellidos: ");
            fflush(stdin);
            gets(estudianteActual->apellidos);

            printf("Ingrese nueva carrera: ");
            fflush(stdin);
            gets(estudianteActual->carrera);

            printf("El estudiante se ha modificado.\n");
            return;
        }

        estudianteActual = estudianteActual->siguiente;
    }

    printf("No se encontró un estudiante con el ID especificado.\n");
}

void mostrarEstudiantes(ESTUDIANTE *listaEstudiantes)
{
    if (listaEstudiantes == NULL)
    {
        printf("\nNo existen estudiantes\n");
        return;
    }

    ESTUDIANTE *estudiante = listaEstudiantes;

    printf("\nEstudiantes:\n\n");
    while (estudiante != NULL)
    {
        printf("ID: %d\t\tMatrícula: %s\t\tNombres: %s\nApellidos: %s\t\tCarrera: %s\t\tInactividad: %hd\n\n", estudiante->ID_Estudiante, estudiante->matricula, estudiante->nombres, estudiante->apellidos, estudiante->carrera, estudiante->inactivo);
        estudiante = estudiante->siguiente;
    }
}

void guardarEstudiante(ESTUDIANTE *listaEstudiantes)
{
    FILE *archivoEstudiante = fopen("estudiante.txt", "wb");
    ESTUDIANTE *estudianteActual = listaEstudiantes;

    while (estudianteActual != NULL)
    {
        fwrite(estudianteActual, sizeof(ESTUDIANTE), 1, archivoEstudiante);
        estudianteActual = estudianteActual->siguiente;
    }

    fclose(archivoEstudiante);
}

void capturarActividad(ACTIVIDAD **listaActividad)
{
    int comprobante, id;
    ACTIVIDAD *nuevaActividad = (ACTIVIDAD *)malloc(sizeof(ACTIVIDAD));

    do
    {
        mostrarActividad(*listaActividad);
        comprobante = 0;
        printf("\nId: ");
        fflush(stdin);
        scanf("%d", &id);

        if (id <= 0)
        {
            printf("\nEl ID debe ser mayor que 0\n");
            comprobante = 1;
        }

        else
        {
            ACTIVIDAD *actividad = *listaActividad;
            while (actividad != NULL)
            {
                if (id == actividad->ID_Actividad)
                {
                    comprobante = 1;
                    printf("\nEl Id que esta ingresando ya existe. por favor ingrese otro\n");
                    break;
                }
                actividad = actividad->siguiente;
            }
            nuevaActividad->ID_Actividad = id;
        }
    } while (comprobante != 0);

    printf("Nombre: ");
    fflush(stdin);
    gets(nuevaActividad->nombre);

    do
    {
        printf("Digite la inactividad (0 Activo | 1 Inactivo): ");
        fflush(stdin);
        scanf("%hd", &(nuevaActividad->Inactivo));

        if (nuevaActividad->Inactivo != 0 && nuevaActividad->Inactivo != 1)
        {
            printf("El número ingresado es invalido\n");
        }

    } while (nuevaActividad->Inactivo != 0 && nuevaActividad->Inactivo != 1);

    nuevaActividad->anterior = NULL;
    nuevaActividad->siguiente = NULL;

    if (*listaActividad == NULL)
    {
        *listaActividad = nuevaActividad;
    }
    else
    {
        ACTIVIDAD *ultimaActividad = *listaActividad;
        while (ultimaActividad->siguiente != NULL)
        {
            ultimaActividad = ultimaActividad->siguiente;
        }
        ultimaActividad->siguiente = nuevaActividad;
        nuevaActividad->anterior = ultimaActividad;
    }
}

int menuActividad()
{
    char opcion;
    printf("\n1: Capturar actividad.\n");
    printf("2: Modificar actividad.\n");
    printf("3: Modificar estado de la actividad.\n");
    printf("4: Mostrar las actividades.\n");
    printf("5: Mostrar las actividades activas.\n");
    printf("6: Mostrar las actividades inactivas.\n");
    printf("\n0: Regresar \n");

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
    default:
        return 0;
    }
}

void mostrarMenuActividad(ACTIVIDAD *listaActividad)
{
    int seleccion;
    cargarActividad(&listaActividad);

    do
    {
        seleccion = menuActividad();

        switch (seleccion)
        {
        case 1:
            capturarActividad(&listaActividad);
            guardarActividad(listaActividad);
            break;
        case 2:
            modificarActividad(listaActividad);
            guardarActividad(listaActividad);
            break;
        case 3:
            estadoActividad(listaActividad);
            guardarActividad(listaActividad);
            break;
        case 4:
            mostrarActividad(listaActividad);
            break;
        case 5:
            mostrarActividadActiva(listaActividad);
            break;
        case 6:
            mostrarActividadInactiva(listaActividad);
            break;
        case 0:
            break;
        }
    } while (seleccion != 0);

    return;
}

void modificarActividad(ACTIVIDAD *listaActividad)
{
    if (listaActividad == NULL)
    {
        printf("\nNo existen actividades\n");
        return;
    }

    mostrarActividad(listaActividad);

    int idBuscado;
    printf("\nIngrese el ID de la calificación a modificar: ");
    scanf("%d", &idBuscado);

    ACTIVIDAD *actividadActual = listaActividad;
    while (actividadActual != NULL)
    {
        if (actividadActual->ID_Actividad == idBuscado)
        {
            printf("Actividad encontrada.\n");
            printf("Ingrese nuevo nombre: ");
            fflush(stdin);
            gets(actividadActual->nombre);

            printf("se ha modificado.\n");
            return;
        }

        actividadActual = actividadActual->siguiente;
    }
    printf("No se encontró una actividad con el ID especificado.\n");
}

void mostrarActividad(ACTIVIDAD *listaActividad)
{
    if (listaActividad == NULL)
    {
        printf("\nNo existen actividades\n");
        return;
    }

    ACTIVIDAD *actividad = listaActividad;

    printf("\nActividad:\n\n");
    while (actividad != NULL)
    {
        printf("ID: %d\t\tNombre: %s\t\tInactividad: %hd\n", actividad->ID_Actividad, actividad->nombre, actividad->Inactivo);
        actividad = actividad->siguiente;
    }
}

void cargarActividad(ACTIVIDAD **listaActividad)
{
    FILE *archivoActividad = fopen("actividad.txt", "rb");

    if (archivoActividad == NULL)
    {
        return;
    }

    ACTIVIDAD actividad;
    fread(&actividad, sizeof(ACTIVIDAD), 1, archivoActividad);

    while (!feof(archivoActividad))
    {
        ACTIVIDAD *nuevaActividad = (ACTIVIDAD *)malloc(sizeof(ACTIVIDAD));
        nuevaActividad->ID_Actividad = actividad.ID_Actividad;
        strcpy(nuevaActividad->nombre, actividad.nombre);
        nuevaActividad->Inactivo = actividad.Inactivo;

        nuevaActividad->anterior = NULL;
        nuevaActividad->siguiente = NULL;

        if (*listaActividad == NULL)
        {
            *listaActividad = nuevaActividad;
        }
        else
        {
            ACTIVIDAD *ultimaActividad = *listaActividad;
            while (ultimaActividad->siguiente != NULL)
            {
                ultimaActividad = ultimaActividad->siguiente;
            }
            ultimaActividad->siguiente = nuevaActividad;
            nuevaActividad->anterior = ultimaActividad;
        }

        fread(&actividad, sizeof(ACTIVIDAD), 1, archivoActividad);
    }

    fclose(archivoActividad);
}

void guardarActividad(ACTIVIDAD *listaActividad)
{
    FILE *archivoActividad = fopen("actividad.txt", "wb");
    ACTIVIDAD *actividadActual = listaActividad;

    while (actividadActual != NULL)
    {
        fwrite(actividadActual, sizeof(ACTIVIDAD), 1, archivoActividad);
        actividadActual = actividadActual->siguiente;
    }

    fclose(archivoActividad);
}

void estadoActividad(ACTIVIDAD *listaActividad)
{
    if (listaActividad == NULL)
    {
        printf("\nNo existen actividades\n");
        return;
    }

    mostrarActividad(listaActividad);

    int idBuscado;
    int estado;
    printf("\nIngrese el ID del estudiante a modificar: ");
    scanf("%d", &idBuscado);

    ACTIVIDAD *actividadActual = listaActividad;
    while (actividadActual != NULL)
    {
        if (actividadActual->ID_Actividad == idBuscado)
        {
            do
            {
                printf("\nIngrese el nuevo estado (0 Activo | 1 Inactivo): ");
                scanf("%hd", &(actividadActual->Inactivo));

                if (actividadActual->Inactivo != 0 && actividadActual->Inactivo != 1)
                {
                    printf("El número ingresado es invalido\n");
                }

            } while (actividadActual->Inactivo != 0 && actividadActual->Inactivo != 1);

            printf("El estado de la actividad se ha modificado exitosamente.\n");
            return;
        }

        actividadActual = actividadActual->siguiente;
    }

    printf("No se encontró un estudiante con el ID especificado.\n");

    return;
}

void mostrarEstudiantesActivos(ESTUDIANTE *listaEstudiantes)
{
    if (listaEstudiantes == NULL)
    {
        printf("\nNo existen estudiantes\n");
        return;
    }

    ESTUDIANTE *estudiante = listaEstudiantes;
    int comprobar = 1;

    printf("\nEstudiantes:\n\n");
    while (estudiante != NULL)
    {
        if (estudiante->inactivo == 0)
        {
            printf("ID: %d\t\tMatrícula: %s\t\tNombres: %s\nApellidos: %s\t\tCarrera: %s\t\tInactividad: %hd\n\n", estudiante->ID_Estudiante, estudiante->matricula, estudiante->nombres, estudiante->apellidos, estudiante->carrera, estudiante->inactivo);
        }

        if (estudiante->inactivo == 1)
        {
            comprobar = 0;
        }
        estudiante = estudiante->siguiente;
    }
    if (comprobar == 0)
    {
        printf("No existen estudiantes Activos\n");
    }
}

void mostrarEstudiantesInactivos(ESTUDIANTE *listaEstudiantes)
{
    if (listaEstudiantes == NULL)
    {
        printf("\nNo existen estudiantes\n");
        return;
    }

    ESTUDIANTE *estudiante = listaEstudiantes;
    int comprobar = 0;

    printf("\nEstudiantes:\n\n");
    while (estudiante != NULL)
    {
        if (estudiante->inactivo == 1)
        {
            printf("ID: %d\t\tMatrícula: %s\t\tNombres: %s\nApellidos: %s\t\tCarrera: %s\t\tInactividad: %hd\n\n", estudiante->ID_Estudiante, estudiante->matricula, estudiante->nombres, estudiante->apellidos, estudiante->carrera, estudiante->inactivo);
        }

        if (estudiante->inactivo == 0)
        {
            comprobar = 1;
        }
        estudiante = estudiante->siguiente;
    }
    if (comprobar == 1)
    {
        printf("No existen estudiantes Inactivos\n");
    }
}

void mostrarAsignaturaInactiva(ASIGNATURA *listaAsignatura)
{
    if (listaAsignatura == NULL)
    {
        printf("\nNo existen asignaturas\n");
        return;
    }

    ASIGNATURA *asignatura = listaAsignatura;
    int comprobar = 0;

    printf("\nAsignaturas:\n\n");
    while (asignatura != NULL)
    {
        if (asignatura->inactivo == 1)
        {
            printf("ID: %d\t\tCódigo: %s\t\tNombre: %s\t\tCréditos: %d\t\tInactividad: %hd\n", asignatura->ID_Asignatura, asignatura->codigo, asignatura->nombre, asignatura->credito, asignatura->inactivo);
        }

        if (asignatura->inactivo == 0)
        {
            comprobar = 1;
        }
        asignatura = asignatura->siguiente;
    }

    if (comprobar == 1)
    {
        printf("No existen asignaturas inactivas\n");
    }
}

void mostrarAsignaturaActiva(ASIGNATURA *listaAsignatura)
{
    if (listaAsignatura == NULL)
    {
        printf("\nNo existen asignaturas\n");
        return;
    }

    ASIGNATURA *asignatura = listaAsignatura;
    int comprobar = 1;

    printf("\nAsignaturas:\n\n");
    while (asignatura != NULL)
    {
        if (asignatura->inactivo == 0)
        {
            printf("ID: %d\t\tCódigo: %s\t\tNombre: %s\t\tCréditos: %d\t\tInactividad: %hd\n", asignatura->ID_Asignatura, asignatura->codigo, asignatura->nombre, asignatura->credito, asignatura->inactivo);
        }

        if (asignatura->inactivo == 1)
        {
            comprobar = 0;
        }
        asignatura = asignatura->siguiente;
    }

    if (comprobar == 0)
    {
        printf("No existen asignaturas activas\n");
    }
}

void mostrarActividadActiva(ACTIVIDAD *listaActividad)
{
    if (listaActividad == NULL)
    {
        printf("\nNo existen actividades\n");
        return;
    }

    ACTIVIDAD *actividad = listaActividad;
    int comprobar = 1;

    printf("\nActividad:\n\n");
    while (actividad != NULL)
    {
        if (actividad->Inactivo == 0)
        {
            printf("ID: %d\t\tNombre: %s\t\tInactividad: %hd\n", actividad->ID_Actividad, actividad->nombre, actividad->Inactivo);
        }

        if (actividad->Inactivo == 1)
        {
            comprobar = 0;
        }

        actividad = actividad->siguiente;
    }

    if (comprobar == 0)
    {
        printf("No existen actividades activas\n");
    }
}

void mostrarActividadInactiva(ACTIVIDAD *listaActividad)
{
    if (listaActividad == NULL)
    {
        printf("\nNo existen actividades\n");
        return;
    }

    ACTIVIDAD *actividad = listaActividad;
    int comprobar = 0;

    printf("\nActividad:\n\n");
    while (actividad != NULL)
    {
        if (actividad->Inactivo == 1)
        {
            printf("ID: %d\t\tNombre: %s\t\tInactividad: %hd\n", actividad->ID_Actividad, actividad->nombre, actividad->Inactivo);
        }

        if (actividad->Inactivo == 0)
        {
            comprobar = 1;
        }

        actividad = actividad->siguiente;
    }

    if (comprobar == 1)
    {
        printf("No existen actividades inactivas\n");
    }
}

void mostrarCalificacionesActiva(ESTUDIANTEASIGNATURA *listaCalificaciones)
{
    ESTUDIANTEASIGNATURA *calificacionActual = listaCalificaciones;
    int comprobar = 1;

    if (listaCalificaciones == NULL)
    {
        printf("\nNo existen calificaciones\n");
        return;
    }

    printf("\nCalificaciones:\n\n");
    while (calificacionActual != NULL)
    {
        if (calificacionActual->inactivo == 0)
        {
            printf("ID_Estudiante: %d\t\t\tID_Asignatura: %d\t\t\tID_Actividad: %d\t\t\tCalificacion: %.2f\t\t\tInactividad: %hd\n", calificacionActual->ID_Estudiante, calificacionActual->ID_Asignatura, calificacionActual->listaCalificacion.ID_Actividad, calificacionActual->listaCalificacion.Calificacion, calificacionActual->inactivo);
        }

        if (calificacionActual->inactivo == 1)
        {
            comprobar = 0;
        }

        calificacionActual = calificacionActual->siguiente;
    }

    if (comprobar == 0)
    {
        printf("No existen calificaciones activas\n");
    }
}

void mostrarCalificacionesInactiva(ESTUDIANTEASIGNATURA *listaCalificaciones)
{
    ESTUDIANTEASIGNATURA *calificacionActual = listaCalificaciones;
    int comprobar = 0;

    if (listaCalificaciones == NULL)
    {
        printf("\nNo existen calificaciones\n");
        return;
    }

    printf("\nCalificaciones:\n\n");
    while (calificacionActual != NULL)
    {
        if (calificacionActual->inactivo == 1)
        {
            printf("ID_Estudiante: %d\t\t\tID_Asignatura: %d\t\t\tID_Actividad: %d\t\t\tCalificacion: %.2f\t\t\tInactividad: %hd\n", calificacionActual->ID_Estudiante, calificacionActual->ID_Asignatura, calificacionActual->listaCalificacion.ID_Actividad, calificacionActual->listaCalificacion.Calificacion, calificacionActual->inactivo);
        }

        if (calificacionActual->inactivo == 0)
        {
            comprobar = 1;
        }

        calificacionActual = calificacionActual->siguiente;
    }

    if (comprobar == 1)
    {
        printf("No existen calificaciones inactivas\n");
    }
}