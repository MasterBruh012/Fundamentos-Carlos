#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NOMBRE 30
#define MAXCARACTERES 150

typedef struct Entrada
{
    char palabra[NOMBRE];
    char definicion[MAXCARACTERES];
    int longitud;
    long posbytes;
} ENTRADA;

int mostrarMenu();

void cargarDiccionario(ENTRADA *, FILE *, int, int *);
void guardarDiccionario(ENTRADA *, char *, int);
void nuevaEntrada(ENTRADA *, int *);
void imprimirEntrada(ENTRADA *, int);
void imprimirPalabra(ENTRADA *, int);
void eliminarEntrada(ENTRADA *, int *);
void buscarPalabra(ENTRADA *, int);
void quicksort(ENTRADA *, int, int, int (*)(ENTRADA *, ENTRADA *));
int particionar(ENTRADA *, int, int, int (*)(ENTRADA *, ENTRADA *));
int ordenAlfabetico(ENTRADA *, ENTRADA *);
int ordenLongitud(ENTRADA *, ENTRADA *);

int main()
{
    ENTRADA *diccionario = (ENTRADA *)malloc(sizeof(ENTRADA)), *alfabetico, *longitud;

    int cantEntradas = 0;
    char nomArch[] = "diccionario.txt";

    FILE *archDiccionario = fopen(nomArch, "r");

    if (archDiccionario == NULL)
    {
        archDiccionario = fopen(nomArch, "w");
        if (archDiccionario == NULL)
        {
            printf("Error al crear el archivo.\n");
            return 0;
        }
    }

    fseek(archDiccionario, 0, SEEK_END);
    int entradasActuales = ftell(archDiccionario);
    fseek(archDiccionario, 0, SEEK_SET);

    diccionario = (ENTRADA *)realloc(diccionario, sizeof(ENTRADA) * entradasActuales);

    cargarDiccionario(diccionario, archDiccionario, entradasActuales, &cantEntradas);

    ENTRADA *ordenOriginal = (ENTRADA *)malloc(sizeof(ENTRADA) * cantEntradas);
    for (int i = 0; i < cantEntradas; i++)
    {
        ordenOriginal[i] = diccionario[i];
    }
    alfabetico = longitud = diccionario;

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

            for (int i = 0; i < cantEntradas; i++)
            {
                imprimirPalabra(ordenOriginal, i);
            }

            buscarPalabra(diccionario, cantEntradas);
            break;
        case 2:

            nuevaEntrada(diccionario, &cantEntradas);
            guardarDiccionario(diccionario, nomArch, cantEntradas);

            ordenOriginal = (ENTRADA *)malloc(sizeof(ENTRADA) * cantEntradas);
            for (int i = 0; i < cantEntradas; i++)
            {
                ordenOriginal[i] = diccionario[i];
            }

            break;
        case 3:

            for (int i = 0; i < cantEntradas; i++)
            {
                imprimirPalabra(ordenOriginal, i);
            }

            eliminarEntrada(diccionario, &cantEntradas);
            guardarDiccionario(diccionario, nomArch, cantEntradas);

            ordenOriginal = (ENTRADA *)malloc(sizeof(ENTRADA) * cantEntradas);
            for (int i = 0; i < cantEntradas; i++)
            {
                ordenOriginal[i] = diccionario[i];
            }

            break;
        case 4:

            for (int i = 0; i < cantEntradas; i++)
            {
                imprimirEntrada(ordenOriginal, i);
            }

            break;
        case 5:

            quicksort(alfabetico, 0, cantEntradas - 1, ordenAlfabetico);

            for (int i = 0; i < cantEntradas; i++)
            {
                imprimirEntrada(alfabetico, i);
            }

            break;
        case 6:

            quicksort(longitud, 0, cantEntradas - 1, ordenLongitud);

            for (int i = 0; i < cantEntradas; i++)
            {
                imprimirEntrada(longitud, i);
            }
            
            break;
        }

    } while (seleccion != 0);

    return 0;
}

int mostrarMenu()
{
    int opcion;

    printf("\nDiccionario:\n");
    printf("\n1. Buscar el significado de una palabra\n");
    printf("2. Agregar una nueva entrada\n");
    printf("3. Eliminar una entrada\n");
    printf("4. Mostrar las entradas en el mismo orden del archivo\n");
    printf("5. Mostrar las entradas ordenadas alfabéticamente\n");
    printf("6. Mostrar las entradas ordenadas por longitud de palabra\n");

    printf("\n0: Salir.\n");

    printf("\nSeleccione una opcion: ");

    fflush(stdin);

    scanf("%d", &opcion);

    return opcion;
}

void cargarDiccionario(ENTRADA *diccionario, FILE *archDiccionario, int entradasActuales, int *cantEntradas)
{
    while ((*cantEntradas) < entradasActuales && fscanf(archDiccionario, "%s %[^\n]", diccionario[*cantEntradas].palabra, diccionario[*cantEntradas].definicion) == 2)
    {
        diccionario[*cantEntradas].longitud = strlen(diccionario[*cantEntradas].palabra);
        diccionario[*cantEntradas].posbytes = ftell(archDiccionario);
        (*cantEntradas)++;
    }

    fclose(archDiccionario);
}

void guardarDiccionario(ENTRADA *diccionario, char *nomArch, int cantEntradas)
{
    FILE *archDiccionario = fopen(nomArch, "w");

    for (int i = 0; i < cantEntradas; i++)
    {
        fprintf(archDiccionario, "%s\n%s\n", diccionario[i].palabra, diccionario[i].definicion);
    }

    fclose(archDiccionario);
}

void nuevaEntrada(ENTRADA *diccionario, int *cantEntradas)
{
    int comparacion;
    do
    {
        comparacion = 0;
        printf("\nIngrese la nueva palabra: ");
        fflush(stdin);
        scanf("%s", diccionario[*cantEntradas].palabra);

        for (int i = 0; diccionario[*cantEntradas].palabra[i]; i++)
        {
            diccionario[*cantEntradas].palabra[i] = tolower(diccionario[*cantEntradas].palabra[i]);
        }

        for (int i = 0; i < *cantEntradas; i++)
        {
            if (strcmp(diccionario[i].palabra, diccionario[*cantEntradas].palabra) == 0)
                comparacion = 1;
        }

        if (comparacion == 1)
            printf("\nLa palabra ya existe en el diccionario.\n");

    } while (comparacion == 1);

    printf("Ingrese la definición de la palabra: ");
    fflush(stdin);
    scanf(" %[^\n]", diccionario[*cantEntradas].definicion);

    for (int i = 0; diccionario[*cantEntradas].definicion[i]; i++)
    {
        diccionario[*cantEntradas].definicion[i] = tolower(diccionario[*cantEntradas].definicion[i]);
    }

    int len = strlen(diccionario[*cantEntradas].definicion);
    if (len > 0 && diccionario[*cantEntradas].definicion[len - 1] != '.')
    {
        strcat(diccionario[*cantEntradas].definicion, ".");
    }

    diccionario[*cantEntradas].longitud = strlen(diccionario[*cantEntradas].palabra);
    diccionario[*cantEntradas].posbytes = -1;

    (*cantEntradas)++;
    printf("Nueva entrada agregada al diccionario.\n");
}

void imprimirEntrada(ENTRADA *diccionario, int entradaActual)
{
    printf("\nPalabra: %s\nDefinición: %s\n", diccionario[entradaActual].palabra, diccionario[entradaActual].definicion);
}

void imprimirPalabra(ENTRADA *diccionario, int entradaActual)
{
    printf("\n%d- %s", entradaActual + 1, diccionario[entradaActual].palabra);
}

void eliminarEntrada(ENTRADA *diccionario, int *cantEntradas)
{
    char palabra[NOMBRE];
    int sinEncontrar = -1;

    printf("\n\nIngrese la palabra a eliminar: ");
    fflush(stdin);
    scanf("%s", palabra);

    for (int i = 0; palabra[i]; i++)
    {
        palabra[i] = tolower(palabra[i]);
    }

    for (int i = 0; i < *cantEntradas; i++)
    {
        if (strcmp(palabra, diccionario[i].palabra) == 0)
        {
            sinEncontrar = i;
            break;
        }
    }

    if (sinEncontrar == -1)
    {
        printf("\nPalabra no encontrada en el diccionario.\n");
        return;
    }

    for (int i = sinEncontrar; i < *cantEntradas - 1; i++)
    {
        diccionario[i] = diccionario[i + 1];
    }

    (*cantEntradas)--;
    printf("Palabra eliminada del diccionario.\n");
}

void buscarPalabra(ENTRADA *diccionario, int cantEntradas)
{
    char palabra[NOMBRE];

    printf("\n\nIngrese la palabra a buscar: ");
    fflush(stdin);
    scanf("%s", palabra);

    for (int i = 0; palabra[i]; i++)
    {
        palabra[i] = tolower(palabra[i]);
    }

    for (int i = 0; i < cantEntradas; i++)
    {
        if (strcmp(palabra, diccionario[i].palabra) == 0)
        {
            imprimirEntrada(diccionario, i);
            return;
        }
    }

    printf("La palabra no fue encontrada en el diccionario.\n");
}

void quicksort(ENTRADA *diccionario, int limI, int limS, int (*funcion)(ENTRADA *, ENTRADA *))
{
    int posicionPivote;

    if (limI < limS)
    {
        posicionPivote = particionar(diccionario, limI, limS, funcion);
        quicksort(diccionario, limI, posicionPivote - 1, funcion);
        quicksort(diccionario, posicionPivote + 1, limS, funcion);
    }
}

int particionar(ENTRADA *diccionario, int limI, int limS, int (*funcion)(ENTRADA *, ENTRADA *))
{
    ENTRADA pivote = diccionario[limS];
    int i = limI - 1;

    for (int j = limI; j <= limS - 1; j++)
    {
        if (funcion(&diccionario[j], &pivote) < 0)
        {
            i++;
            ENTRADA temp = diccionario[i];
            diccionario[i] = diccionario[j];
            diccionario[j] = temp;
        }
    }

    ENTRADA temp = diccionario[i + 1];
    diccionario[i + 1] = diccionario[limS];
    diccionario[limS] = temp;

    return i + 1;
}

int ordenAlfabetico(ENTRADA *a, ENTRADA *b)
{
    return strcmp(a->palabra, b->palabra);
}

int ordenLongitud(ENTRADA *a, ENTRADA *b)
{
    return a->longitud - b->longitud;
}