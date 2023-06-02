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
void capturarArticulos(int, articulo *);
void capturarExistencia(int, int, int, almacen *, existencia *, articulo *);
void capturarAlmacen(int, almacen *);
void showAlmacen(int, almacen *);
void showArticulos(int, articulo *);
void showExistencia(int, existencia *);

int main()
{

    int cantidadArticulos = 0, cantidadExistencia = 0, cantidadAlmacenes = 0, seleccion;
    articulo *listaArticulos = (articulo *)malloc(sizeof(articulo) * cantidadArticulos);
    almacen *listaAlmacen = (almacen *)malloc(sizeof(almacen) * cantidadAlmacenes);
    existencia *listaExistencia = (existencia *)malloc(sizeof(existencia) * cantidadExistencia);

    do
    {
        switch (seleccion = MostrarMenu(cantidadAlmacenes, cantidadArticulos))
        {
        case 1:
            // Registrar un nuevo almacen.
            cantidadAlmacenes++;
            listaAlmacen = (almacen *)realloc(listaAlmacen, sizeof(almacen) * cantidadAlmacenes);
            capturarAlmacen(cantidadAlmacenes - 1, listaAlmacen);

            break;
        case 2:
            // Registrar nuevo articulo.
            cantidadArticulos++;
            listaArticulos = (articulo *)realloc(listaArticulos, sizeof(articulo) * cantidadArticulos);
            capturarArticulos(cantidadArticulos - 1, listaArticulos);

            break;
        case 3:
            // Establecer nueva existencia.
            cantidadExistencia++;
            listaExistencia = (existencia *)realloc(listaExistencia, sizeof(existencia) * cantidadExistencia);
            capturarExistencia(cantidadAlmacenes, cantidadExistencia - 1, cantidadArticulos, listaAlmacen, listaExistencia, listaArticulos);

            break;
        case 4:
            // Mostrar todos los articulos y sus existencias.
            showExistencia(cantidadExistencia, listaExistencia);
            break;
        default:
            break;
        }

    } while (seleccion != 0);

    showExistencia(cantidadExistencia, listaExistencia);

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
    printf("\n\t\t4: Mostrar todos los art%cculos y sus existencias", 161);
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

void capturarArticulos(int cantidadarticulos, articulo *listadoarticulos)
{
    printf("Id_Art%cculo: ", 161);
    scanf("%d", &((listadoarticulos + cantidadarticulos)->idarticulo));

    printf("Nombre_Art%cculo: ", 161);
    fflush(stdin);
    gets((listadoarticulos + cantidadarticulos)->nombre);

    printf("Precio: ");
    scanf("%f", &((listadoarticulos + cantidadarticulos)->precio));

    return;
}

void capturarAlmacen(int cantidadalmacen, almacen *listadoalmacen)
{
    printf("Id_Almac%cn: ", 130);
    scanf("%d", &((listadoalmacen + cantidadalmacen)->idalmacen));

    printf("Nombre_Almac%cn: ", 130);
    fflush(stdin);
    gets((listadoalmacen + cantidadalmacen)->nombre);

    return;
}

void capturarExistencia(int cantalmacenes, int cantexist, int cantarti, almacen *listadoalmacenes, existencia *listadoexistencia, articulo *listadoarticulos)
{
    int idalma = 0, idart = 0;

    if (cantalmacenes == 0)
    {
        printf("No hay almacenes en existencia\n");
        return;
    }

    else if (cantarti == 0)
    {
        printf("No hay articulos en existencia\n");
        return;
    }

    do
    {
        showAlmacen(cantalmacenes, listadoalmacenes);
        printf("\nEscoja un almacen: ");
        scanf("%d", &idalma);
        (listadoexistencia + cantexist)->idalmacen = idalma;

    } while (idalma == 0);

    do
    {
        showArticulos(cantarti, listadoarticulos);
        printf("\nEscoja un articulo: ");
        scanf("%d", &idart);
        (listadoexistencia + cantexist)->idarticulo = idart;
    } while (idart == 0);

    printf("\nDigite la existencia en el almacen: ");
    scanf("%f", &((listadoexistencia + cantexist)->existencia));

    return;
}

void showAlmacen(int cantalma, almacen *listadoalmacenes)
{

    printf("Id_Almacen \t\t Nombre_Almacen\n");
    for (int i = 0; i < cantalma; i++)
    {
        printf("%d \t\t\t %s\n", (*(listadoalmacenes + i)).idalmacen, (*(listadoalmacenes + i)).nombre);
    }

    return;
}

void showArticulos(int cantarti, articulo *listadoarticulos)
{

    printf("\n\nId_Articulo \t\t Nombre_Articulo \t\t Precio_Articulo\n");
    for (int i = 0; i < cantarti; i++)
    {
        printf("%d \t\t\t %s \t\t\t %.2f\n", (*(listadoarticulos + i)).idarticulo, (*(listadoarticulos + i)).nombre, (*(listadoarticulos + i)).precio);
    }

    return;
}

void showExistencia(int cantexist, existencia *listadoexistencia)
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