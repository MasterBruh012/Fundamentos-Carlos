#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int idalmacen;
    char nombre[30];
} almacen;

typedef struct
{
    int idalmacen;
    int idarticulo;
    float existencia;
} existencia;

typedef struct
{
    int idarticulo;
    char nombre[30];
    float precio;
} articulo;

int MostrarMenu(int, int);
void capart(int, articulo *);
void captexist(int, int, int, almacen *, existencia *, articulo *);
void capturaralmacen(int, almacen *);
void showalmacen(int, almacen *);
void showarticulos(int, articulo *);
void showexistencia(int, existencia *);

int main()
{

    int cantart = 0, cantexist = 0, cantidadalmacen = 0, seleccion;
    articulo *listart = (articulo *)malloc(sizeof(articulo) * cantart);
    almacen *listadoalmacen = (almacen *)malloc(sizeof(almacen) * cantidadalmacen);
    existencia *listexist = (existencia *)malloc(sizeof(existencia) * cantexist);

    do
    {
        switch (seleccion = MostrarMenu(0, cantart))
        {
        case 1:
            // Registrar un nuevo almacen.
            cantidadalmacen++;
            listadoalmacen = (almacen *)realloc(listadoalmacen, sizeof(almacen) * cantidadalmacen);
            capturaralmacen(cantidadalmacen - 1, listadoalmacen);

            break;
        case 2:
            // Registrar nuevo articulo.
            cantart++;
            listart = (articulo *)realloc(listart, sizeof(articulo) * cantart);
            capart(cantart - 1, listart);

            break;
        case 3:
            // Establecer nueva existencia.
            cantexist++;
            listexist = (existencia *)realloc(listexist, sizeof(existencia) * cantexist);
            captexist(cantidadalmacen, cantexist - 1, cantart, listadoalmacen, listexist, listart);

            break;
        case 4:
            // Mostrar uno o todos los articulos y sus existencias.
            showexistencia(cantexist, listexist);
            break;
        default:
            break;
        }

    } while (seleccion != 0);

    showexistencia(cantexist, listexist);

    return 0;
}

int MostrarMenu(int cantidadalmacenes, int cantidadarticulos)
{
    char opcion;
    // system("cls"); // limpiar la pantalla.
    printf("\n\n--- Almacenes e Inventario ---");
    printf("\n\nSeleccione una opci%cn del men%c:\n", 162, 163);
    printf("\n\t\t1: Registrar un nuevo almac%cn", 130);
    printf("\n\t\t2: Registrar nuevo art%cculo", 161);
    printf("\n\t\t3: Establecer nueva existencia");
    printf("\n\t\t4: Mostrar uno o todos los art%cculos y sus existencias", 161);
    printf("\n\n\t\t0: Salir\n\n\t\tSeleccione: ");

    fflush(stdin);
    opcion = getchar();

    switch (opcion) // Esto se puede reemplazar por una sola línea.
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
    default:
        return 0;
    }

    return 0;
}

void capart(int indice, articulo *listadoarticulos)
{
    printf("Id_Art%cculo: ", 161);
    scanf("%d", &((listadoarticulos + indice)->idarticulo));

    printf("Nombre_Art%cculo: ", 161);
    fflush(stdin);
    gets((listadoarticulos + indice)->nombre);

    printf("Precio: ");
    scanf("%f", &((listadoarticulos + indice)->precio));

    return;
}

void capturaralmacen(int indice, almacen *listadoalmacen)
{
    printf("Id_Almac%cn: ", 130);
    scanf("%d", &((listadoalmacen + indice)->idalmacen));

    printf("Nombre_Almac%cn: ", 130);
    fflush(stdin);
    gets((listadoalmacen + indice)->nombre);

    return;
}

void captexist(int cantalmacenes, int cantexist, int cantarti, almacen *listadoalmacenes, existencia *listadoexistencia, articulo *listadoarticulos)
{
    int idalma = 0, idart = 0;

    do
    {
        if (cantalmacenes == 0)
        {
            printf("No hay almacenes en existencia\n");
            break;
        }

        else if (cantarti == 0)
        {
            printf("No hay articulos en existencia\n");
            break;
        }

        showalmacen(cantalmacenes, listadoalmacenes);
        printf("\nEscoja un almacen: ");
        scanf("%d", &idalma);
        (listadoexistencia + cantexist)->idalmacen = idalma;

    } while (idalma == 0);

    do
    {

        showarticulos(cantarti, listadoarticulos);
        printf("\nEscoja un articulo: ");
        scanf("%d", &idart);
        (listadoexistencia + cantexist)->idarticulo = idart;
    } while (idart == 0);

    printf("\nDigite la existencia en el almacen: ");
    scanf("%f", &((listadoexistencia + cantexist)->existencia));

    return;
}

void showalmacen(int cantalma, almacen *listadoalmacenes)
{

    printf("Id_Almacen \t\t Nombre_Almacen\n");
    for (int i = 0; i < cantalma; i++)
    {
        printf("%d \t\t\t %s\n", (*(listadoalmacenes + i)).idalmacen, (*(listadoalmacenes + i)).nombre);
    }

    return;
}

void showarticulos(int cantarti, articulo *listadoarticulos)
{

    printf("\n\nId_Articulo \t\t Nombre_Articulo \t\t Precio_Articulo\n");
    for (int i = 0; i < cantarti; i++)
    {
        printf("%d \t\t\t %s \t\t\t %.2f\n", (*(listadoarticulos + i)).idarticulo, (*(listadoarticulos + i)).nombre, (*(listadoarticulos + i)).precio);
    }

    return;
}

void showexistencia(int cantexist, existencia *listadoexistencia)
{
    if (cantexist == 0)
    {
        printf("No existen articulos en ningun almacen");
        return;
    }

    printf("\n\nId_Almacen \t\t Id_Articulo \t\t Existencia\n");
    for (int i = 0; i < cantexist; i++)
    {
        printf("%d \t\t\t %d \t\t\t %.2f\n\n", (*(listadoexistencia + i)).idalmacen, (*(listadoexistencia + i)).idarticulo, (*(listadoexistencia + i)).existencia);
    }

    return;
}