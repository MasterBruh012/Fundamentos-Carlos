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
    short Inactivo;

    struct Calificacion *anterior;
    struct Calificacion *siguiente;
} CALIFICACION;

typedef struct Actividad
{
    int ID_Actividad;
    char nombre[25];
    short Inactivo;
    struct Actividad *anterior;
    struct Actividad *siguiente;
} ACTIVIDAD;

void cargarEstudiante(ESTUDIANTE **);
void cargarAsignatura(ASIGNATURA **);
void cargarActividad(ACTIVIDAD **);
void cargarCalificacion(CALIFICACION **);

int mostrarMenuEstudiantes(ESTUDIANTE *);
int mostrarMenuAsignaturas(ASIGNATURA *);
void mostrarMenuActividad(ACTIVIDAD *);
int mostrarMenuCalificacion(CALIFICACION *);

int mostrarMenu();
int menuEstudiante();
int menuAsignatura();
int menuActividad();
int menuCalificacion();

void capturarEstudiante(ESTUDIANTE **);
void capturarAsignatura(ASIGNATURA **);
void capturarActividad(ACTIVIDAD **);
void capturarCalificaciones(CALIFICACION **);

void modificarEstudiante(ESTUDIANTE *);
void modificarAsignatura(ASIGNATURA *);
void modificarActividad(ACTIVIDAD *);
void modificarCalificacion(CALIFICACION *);

void mostrarEstudiantes(ESTUDIANTE *);
void mostrarAsignatura(ASIGNATURA *);
void mostrarActividad(ACTIVIDAD *);
void mostrarCalificaciones(CALIFICACION *);

void estadoEstudiante(ESTUDIANTE *);
void estadoAsignatura(ASIGNATURA *);
void estadoCalificacion(CALIFICACION *);

void guardarEstudiante(ESTUDIANTE *);
void guardarAsignatura(ASIGNATURA *);
void guardarActividad(ACTIVIDAD *);
void guardarCalificacion(CALIFICACION *);

int main()
{
    ESTUDIANTE *listaEstudiantes = NULL;
    ASIGNATURA *listaAsignatura = NULL;
    ACTIVIDAD *listaActividad = NULL;
    CALIFICACION *listaCalificaciones = NULL;

    cargarEstudiante(&listaEstudiantes);
    cargarAsignatura(&listaAsignatura);
    cargarActividad(&listaActividad);
    cargarCalificacion(&listaCalificaciones);

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
            mostrarMenuCalificacion(listaCalificaciones);
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

    guardarCalificacion(listaCalificaciones);
}

void cargarCalificacion(CALIFICACION **listaCalificaciones)
{
    FILE *archivoCalificaciones = fopen("calificaciones.txt", "rb");

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

    return;
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

    do
    {
        printf("Digite la inactividad (0 Activo | 1 Inactivo): ");
        fflush(stdin);
        scanf("%hd", &(nuevoCalificacion->Inactivo));

        if (nuevoCalificacion->Inactivo != 0 && nuevoCalificacion->Inactivo != 1)
        {
            printf("El número ingresado es invalido\n");
        }

    } while (nuevoCalificacion->Inactivo != 0 && nuevoCalificacion->Inactivo != 1);

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
    return;
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

    return;
}

void estadoEstudiante(ESTUDIANTE *listaEstudiantes)
{
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

            printf("El estado de la calificación se ha modificado exitosamente.\n");
            return;
        }

        estudianteActual = estudianteActual->siguiente;
    }

    printf("No se encontró un estudiante con el ID especificado.\n");

    return;
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

    return;
}

void estadoAsignatura(ASIGNATURA *listaAsignatura)
{
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

            printf("El estado de la calificación se ha modificado exitosamente.\n");
            return;
        }

        asignaturaActual = asignaturaActual->siguiente;
    }

    printf("No se encontró una asignatura con el ID especificado.\n");
}

void mostrarCalificaciones(CALIFICACION *listaCalificaciones)
{
    CALIFICACION *calificacionActual = listaCalificaciones;

    printf("Calificaciones:\n");
    while (calificacionActual != NULL)
    {
        printf("ID: %d\t\t\tCalificacion: %.2f\t\t\tInactividad: %hd\n", calificacionActual->ID_Actividad, calificacionActual->Calificacion, calificacionActual->Inactivo);
        calificacionActual = calificacionActual->siguiente;
    }
}

void guardarCalificacion(CALIFICACION *listaCalificaciones)
{
    FILE *archivoCalificaciones = fopen("calificaciones.txt", "wb");
    CALIFICACION *calificacionActual = listaCalificaciones;

    while (calificacionActual != NULL)
    {
        fwrite(calificacionActual, sizeof(CALIFICACION), 1, archivoCalificaciones);
        calificacionActual = calificacionActual->siguiente;
    }

    fclose(archivoCalificaciones);
}

void capturarAsignatura(ASIGNATURA **listaAsignatura)
{
    ASIGNATURA *nuevaAsignatura = (ASIGNATURA *)malloc(sizeof(ASIGNATURA));
    printf("Id: ");
    fflush(stdin);
    scanf("%d", &(nuevaAsignatura->ID_Asignatura));

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
    ASIGNATURA *asignatura = listaAsignatura;

    printf("Asignaturas:\n");
    while (asignatura != NULL)
    {
        printf("ID: %d\t\tCódigo: %s\t\tNombre: %s\t\tCréditos: %d\t\tInactividad: %hd\n", asignatura->ID_Asignatura, asignatura->codigo, asignatura->nombre, asignatura->credito, asignatura->inactivo);
        asignatura = asignatura->siguiente;
    }
}

int menuAsignatura()
{
    char opcion;
    printf("\n1: Capturar asignatura\n");
    printf("2: Modificar asignatura\n");
    printf("3: Modificar estado de la asignatura.\n");
    printf("4: Mostrar todas las asignaturas\n");
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
    default:
        return 0;
    }
}

int menuEstudiante()
{
    char opcion;
    printf("\n1: Capturar estudiante\n");
    printf("2: Modificar estudiante\n");
    printf("3: Modificar estado de un estudiante.\n");
    printf("4: Mostrar todos las estudiante\n");
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
    default:
        return 0;
    }
}

int mostrarMenuEstudiantes(ESTUDIANTE *listaEstudiantes)
{
    int seleccion;

    do
    {
        seleccion = menuEstudiante();

        switch (seleccion)
        {
        case 1:
            capturarEstudiante(&listaEstudiantes);
            break;
        case 2:
            modificarEstudiante(listaEstudiantes);
            break;
        case 3:
            estadoEstudiante(listaEstudiantes);
            break;
        case 4:
            mostrarEstudiantes(listaEstudiantes);
            break;
        case 0:
            break;
        }
    } while (seleccion != 0);

    guardarEstudiante(listaEstudiantes);
}

int mostrarMenuAsignaturas(ASIGNATURA *listaAsignatura)
{
    int seleccion;

    do
    {
        seleccion = menuAsignatura();

        switch (seleccion)
        {
        case 1:
            capturarAsignatura(&listaAsignatura);
            break;
        case 2:
            modificarAsignatura(listaAsignatura);
            break;
        case 3:
            estadoAsignatura(listaAsignatura);
            break;
        case 4:
            mostrarAsignatura(listaAsignatura);
            break;
        case 0:
            break;
        }
    } while (seleccion != 0);

    guardarAsignatura(listaAsignatura);
}

void modificarAsignatura(ASIGNATURA *listaAsignatura)
{
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
    ESTUDIANTE *nuevoEstudiante = (ESTUDIANTE *)malloc(sizeof(ESTUDIANTE));
    printf("Id: ");
    fflush(stdin);
    scanf("%d", &(nuevoEstudiante->ID_Estudiante));

    printf("Matrícula: ");
    fflush(stdin);
    gets(nuevoEstudiante->matricula);

    printf("Nombres: ");
    fflush(stdin);
    gets(nuevoEstudiante->nombres);

    printf("Apellidos: ");
    fflush(stdin);
    gets(nuevoEstudiante->apellidos);

    printf("Carrera: ");
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

            printf("La asignatura se ha modificado.\n");
            return;
        }

        estudianteActual = estudianteActual->siguiente;
    }

    printf("No se encontró un estudiante con el ID especificado.\n");
}

void mostrarEstudiantes(ESTUDIANTE *listaEstudiantes)
{
    ESTUDIANTE *estudiante = listaEstudiantes;

    printf("Estudiantes:\n");
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
    ACTIVIDAD *nuevaActividad = (ACTIVIDAD *)malloc(sizeof(ACTIVIDAD));

    printf("ID: ");
    fflush(stdin);
    scanf("%d", &(nuevaActividad->ID_Actividad));

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
    printf("1: Capturar actividad \n");
    printf("2: Modificar actividad\n");
    printf("3: Mostrar las actividades \n");
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
    default:
        return 0;
    }
}

void mostrarMenuActividad(ACTIVIDAD *listaActividad)
{
    int seleccion;

    do
    {
        seleccion = menuActividad();

        switch (seleccion)
        {
        case 1:
            capturarActividad(&listaActividad);
            break;
        case 2:
            modificarActividad(listaActividad);
            break;
        case 3:
            mostrarActividad(listaActividad);
            break;
        case 0:
            break;
        }
    } while (seleccion != 0);

    guardarActividad(listaActividad);

    return;
}

void modificarActividad(ACTIVIDAD *listaActividad)
{
    mostrarActividad(listaActividad);

    int idBuscado;
    printf("\nIngrese el ID de la calificación a modificar: ");
    scanf("%d", &idBuscado);

    ACTIVIDAD *actividadActual = listaActividad;
    while (actividadActual != NULL)
    {
        if (actividadActual->ID_Actividad == idBuscado)
        {
            printf("asignatura encontrada.\n");
            printf("Ingrese nuevo nombre: ");
            fflush(stdin);
            gets(actividadActual->nombre);

            printf("Inactivo o activo: ");
            fflush(stdin);
            scanf("%hd", &(actividadActual->Inactivo));

            printf("se ha modificado.\n");
            return;
        }

        actividadActual = actividadActual->siguiente;
    }
    printf("No se encontró una actividad con el ID especificado.\n");
}

void mostrarActividad(ACTIVIDAD *listaActividad)
{
    ACTIVIDAD *actividad = listaActividad;

    printf("actividad: \n");
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
