/*
    Este programa se encarga de registrar:
    - Cliente
    - Auto
    - Alquiler

    El menu principal se pueden realizar:
    Registro de un cliente, auto, alquiler y acceso a
    los menus de los clientes y automoviles.

    En el menu de clientes se puede realizar:

    - Ver todos los clientes.
    - Filtrar los clientes por la ciudad.
    - Mostrar los alquileres mayor a una semana.
    - Mostrar los alquileres entre 1 semana y 10 dias.
    - Mostrar los alquieres con un valor total mayor de 10 mil.

    En el menu de automoviles se puede realizar:

    - Ver todos los automoviles.
    - Filtrar los automoviles de una marca.
    - Mostrar los alquileres mayor a una semana.
    - Mostrar los alquileres entre 1 semana y 10 dias.
    - Mostrar los alquieres con un valor total mayor de 10 mil
    y filtrado de la forma especificada en el pdf.

    *NOTA*

    Al momento de buscar un cliente por su ciudad, solo filtrará
    a las personas pertenecientes de la ciudad de Santiago.

    Al momento de buscar un automovil por una marca en especifico,
    solo filtrará los vehiculos que son Ford.

    Esto debido al tiempo poco tiempo que nos quedaba, lamentamos
    el inconveniente.

                                        - Carlos y Diaurys.

*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct
{
    int id;
    char marca[50];
} Automovil;

typedef struct
{
    int id;
    char nombre[50];
    char ciudad[50];
} Cliente;

typedef struct
{
    int idCliente;
    int idVehiculo;
    int dias;
    float precio;
} Alquiler;

int mostrarMenu();
int mostrarMenuCliente();
int mostrarMenuVehiculos();
void capturarCliente(FILE *, Cliente *);
void capturarAutomoviles(FILE *, Automovil *);
void capturarAlquileres(FILE *, FILE *, FILE *, Alquiler *);
void mostrarClientes(FILE *, FILE *);
void mostrarAutomovil(FILE *, FILE *);
void mostrarAlquileresMayorSemana(FILE *);
void mostrarAlquileresEntreSemana(FILE *);
void mostrarAlquileresMayorMonto(FILE *);

int main()
{
    char rutaClientes[] = "clientes.dat";
    char rutaAutomovil[] = "automovil.dat";
    char rutaAlquiler[] = "alquiler.dat";
    Cliente cliente;
    Automovil automovil;
    Alquiler alquiler;
    int seleccion;
    FILE *archivoClientes = fopen(rutaClientes, "a+b");
    FILE *archivoAutomovil = fopen(rutaAutomovil, "a+b");
    FILE *archivoAlquiler = fopen(rutaAlquiler, "a+b");

    do
    {
        seleccion = mostrarMenu();

        switch (seleccion)
        {
        case 0:
            printf("Hasta luego!");
            break;
        case 1:
            capturarCliente(archivoClientes, &cliente);
            break;
        case 2:
            capturarAutomoviles(archivoAutomovil, &automovil);
            break;
        case 3:
            capturarAlquileres(archivoClientes, archivoAutomovil, archivoAlquiler, &alquiler);
            break;
        case 4:
            mostrarClientes(archivoClientes, archivoAlquiler);
            break;
        case 5:
            mostrarAutomovil(archivoAutomovil, archivoAlquiler);
            break;
        }
    } while (seleccion != 0);

    return 0;
}

void capturarCliente(FILE *archivoClientes, Cliente *cliente)
{
    printf("Digite el ID: ");
    fflush(stdin);
    scanf("%d", &cliente->id);

    printf("Digite el nombre: ");
    fflush(stdin);
    gets(cliente->nombre);

    printf("Digite la ciudad: ");
    fflush(stdin);
    gets(cliente->ciudad);

    fwrite(cliente, sizeof(Cliente), 1, archivoClientes);
}

void capturarAutomoviles(FILE *archivoAutomovil, Automovil *automovil)
{
    printf("Digite el ID: ");
    fflush(stdin);
    scanf("%d", &automovil->id);

    printf("Digite la marca: ");
    fflush(stdin);
    gets(automovil->marca);

    fwrite(automovil, sizeof(Automovil), 1, archivoAutomovil);
}

void capturarAlquileres(FILE *archivoClientes, FILE *archivoAutomovil, FILE *archivoAlquiler, Alquiler *alquiler)
{
    Cliente clienteActual;
    Automovil vehiculoActual;

    fseek(archivoClientes, 0, SEEK_END);
    int tamanoCliente = ftell(archivoClientes);
    fseek(archivoClientes, 0, SEEK_SET);

    fseek(archivoAutomovil, 0, SEEK_END);
    int tamanoAutomovil = ftell(archivoAutomovil);
    fseek(archivoAutomovil, 0, SEEK_SET);

    printf("\nClientes\n");
    while (ftell(archivoClientes) < tamanoCliente)
    {
        fread(&clienteActual, sizeof(Cliente), 1, archivoClientes);

        printf("\nID: %d\t\tNombre: %s\n",
               clienteActual.id, clienteActual.nombre);
    }

    printf("\nAutomovil\n");
    while (ftell(archivoAutomovil) < tamanoAutomovil)
    {
        fread(&vehiculoActual, sizeof(Automovil), 1, archivoAutomovil);

        printf("\nID: %d\t\tMarca: %s\n",
               vehiculoActual.id, vehiculoActual.marca);
    }

    printf("Digite el ID del cliente: ");
    fflush(stdin);
    scanf("%d", &alquiler->idCliente);

    printf("Digite el ID del automovil: ");
    fflush(stdin);
    scanf("%d", &alquiler->idVehiculo);

    printf("Digite los dias: ");
    fflush(stdin);
    scanf("%d", &alquiler->dias);

    printf("Digite el precio: ");
    fflush(stdin);
    scanf("%f", &alquiler->precio);

    fwrite(alquiler, sizeof(Alquiler), 1, archivoAlquiler);
}

int mostrarMenu()
{
    char opcion;
    printf("\n1: Capturar cliente.\n");
    printf("2: Capturar automovil.\n");
    printf("3: Registrar alquiler.\n");
    printf("4: Menu Cliente.\n");
    printf("5: Menu Automovil.\n");
    printf("\n0: Salir.\n");
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
    default:
        return 0;
    }
}

int mostrarMenuCliente()
{
    char opcion;

    printf("\n1: Mostrar Todos los clientes.\n");
    printf("2: Todos los clientes de Santiago.\n");
    printf("3: Todos los alquileres mayores de una semana.\n");
    printf("4: Todos los alquileres por entre una semana y 10 días, agrupándolos por la ciudad del cliente.\n");
    printf("5: Todos los alquileres por un valor total superior a $10,000, agrupándolos por la cantidad de días.\n");
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
    default:
        return 0;
    }
}

int mostrarMenuVehiculos()
{
    char opcion;
    printf("\n1: Mostrar Todos los automóviles.\n");
    printf("2: Todos los automóviles de una marca específica.\n");
    printf("3: Todos los alquileres mayores de una semana.\n");
    printf("4: Todos los alquileres por entre una semana y 10 días\n");
    printf("5: Todos los alquileres por un valor total superior a $10,000.\n");
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
    default:
        return 0;
    }
}

void mostrarClientes(FILE *archivoClientes, FILE *archivoAlquiler)
{
    Cliente clienteActual;
    Alquiler alquilerActual;
    char ciudadFiltro[] = "Santiago";
    int seleccion;

    do
    {
        fseek(archivoClientes, 0, SEEK_END);
        int tamano = ftell(archivoClientes);
        fseek(archivoClientes, 0, SEEK_SET);

        fseek(archivoAlquiler, 0, SEEK_END);
        int tamanoAlquiler = ftell(archivoAlquiler);
        fseek(archivoAlquiler, 0, SEEK_SET);

        seleccion = mostrarMenuCliente();

        switch (seleccion)
        {
        case 0:
            break;
        case 1:
            while (ftell(archivoClientes) < tamano)
            {
                fread(&clienteActual, sizeof(Cliente), 1, archivoClientes);

                printf("\nID: %d\nNombre: %s\nCiudad: %s\n",
                       clienteActual.id, clienteActual.nombre, clienteActual.ciudad);
            }
            break;
        case 2:
            while (ftell(archivoClientes) < tamano)
            {
                fread(&clienteActual, sizeof(Cliente), 1, archivoClientes);
                if (strcmp(clienteActual.ciudad, ciudadFiltro) == 0)
                {
                    printf("\nID: %d\nNombre: %s\nCiudad: %s\n",
                           clienteActual.id, clienteActual.nombre, clienteActual.ciudad);
                }
            }
            break;
        case 3:

            while (ftell(archivoAlquiler) < tamanoAlquiler)
            {
                fread(&alquilerActual, sizeof(Alquiler), 1, archivoAlquiler);
                if (alquilerActual.dias >= 7)
                {
                    printf("\nID cliente: %d\nID Automovil: %d\nDias: %d\n",
                           alquilerActual.idCliente, alquilerActual.idVehiculo, alquilerActual.dias);
                }
            }
            break;
        case 4:

            while (ftell(archivoAlquiler) < tamanoAlquiler)
            {
                fread(&alquilerActual, sizeof(Alquiler), 1, archivoAlquiler);
                if (alquilerActual.dias >= 7 && alquilerActual.dias <= 10)
                {
                    printf("\nID cliente: %d\nID Automovil: %d\nDias: %d\nCiudad: %s\n",
                           alquilerActual.idCliente, alquilerActual.idVehiculo, alquilerActual.dias);
                }
            }
            break;
        case 5:

            printf("\nEntre 1 a 7 dias\n");

            while (ftell(archivoAlquiler) < tamanoAlquiler)
            {
                fread(&alquilerActual, sizeof(Alquiler), 1, archivoAlquiler);
                if (alquilerActual.precio > 10000 && alquilerActual.dias >= 1 && alquilerActual.dias <= 7)
                {
                    printf("\nID cliente: %d\nID Automovil: %d\nDias: %d\nPrecio: %.2f\n",
                           alquilerActual.idCliente, alquilerActual.idVehiculo, alquilerActual.dias, alquilerActual.precio);
                }
            }

            fseek(archivoAlquiler, 0, SEEK_END);
            int tamanoAl1 = ftell(archivoAlquiler);
            fseek(archivoAlquiler, 0, SEEK_SET);

            printf("\nEntre 8 a 10 dias\n");

            while (ftell(archivoAlquiler) < tamanoAl1)
            {
                fread(&alquilerActual, sizeof(Alquiler), 1, archivoAlquiler);
                if (alquilerActual.precio > 10000 && alquilerActual.dias >= 8 && alquilerActual.dias <= 10)
                {
                    printf("\nID cliente: %d\nID Automovil: %d\nDias: %d\nPrecio: %.2f\n",
                           alquilerActual.idCliente, alquilerActual.idVehiculo, alquilerActual.dias, alquilerActual.precio);
                }
            }

            fseek(archivoAlquiler, 0, SEEK_END);
            int tamanoAl2 = ftell(archivoAlquiler);
            fseek(archivoAlquiler, 0, SEEK_SET);

            printf("\nPor mas de 10 dias\n");

            while (ftell(archivoAlquiler) < tamanoAl2)
            {
                fread(&alquilerActual, sizeof(Alquiler), 1, archivoAlquiler);
                if (alquilerActual.precio > 10000 && alquilerActual.dias > 10)
                {
                    printf("\nID cliente: %d\nID Automovil: %d\nDias: %d\nPrecio: %.2f\n",
                           alquilerActual.idCliente, alquilerActual.idVehiculo, alquilerActual.dias, alquilerActual.precio);
                }
            }
            break;
        }

    } while (seleccion != 0);
}

void mostrarAutomovil(FILE *archivoAutomovil, FILE *archivoAlquiler)
{
    Automovil vehiculoActual;
    char autoFiltro[] = "Ford";
    int seleccion;

    do
    {

        fseek(archivoAutomovil, 0, SEEK_END);
        int tamano = ftell(archivoAutomovil);
        fseek(archivoAutomovil, 0, SEEK_SET);

        fseek(archivoAlquiler, 0, SEEK_END);
        int tamanoAlquiler = ftell(archivoAlquiler);
        fseek(archivoAlquiler, 0, SEEK_SET);

        seleccion = mostrarMenuVehiculos();

        switch (seleccion)
        {
        case 0:
            break;
        case 1:
            while (ftell(archivoAutomovil) < tamano)
            {
                fread(&vehiculoActual, sizeof(Automovil), 1, archivoAutomovil);

                printf("\nID: %d\nMarca: %s\n",
                       vehiculoActual.id, vehiculoActual.marca);
            }
            break;
        case 2:
            while (ftell(archivoAutomovil) < tamano)
            {
                fread(&vehiculoActual, sizeof(Automovil), 1, archivoAutomovil);

                if (strcmp(vehiculoActual.marca, autoFiltro) == 0)
                {
                    printf("\nID: %d\nMarca: %s\n",
                           vehiculoActual.id, vehiculoActual.marca);
                }
            }
            break;
        case 3:
            mostrarAlquileresMayorSemana(archivoAlquiler);
            break;
        case 4:
            mostrarAlquileresEntreSemana(archivoAlquiler);
            break;
        case 5:
            mostrarAlquileresMayorMonto(archivoAlquiler);
            break;
        }
    } while (seleccion != 0);
}

void mostrarAlquileresMayorSemana(FILE *archivoAlquiler)
{
    Alquiler alquiler;
    fseek(archivoAlquiler, 0, SEEK_SET);

    printf("Alquileres mayores a una semana:\n");

    while (fread(&alquiler, sizeof(Alquiler), 1, archivoAlquiler) == 1)
    {
        if (alquiler.dias > 7)
        {
            printf("ID Cliente: %d, ID Vehiculo: %d, Precio: $%.2f\n", alquiler.idCliente, alquiler.idVehiculo, alquiler.precio);
        }
    }

    printf("\n");
}

void mostrarAlquileresEntreSemana(FILE *archivoAlquiler)
{
    Alquiler alquiler;
    fseek(archivoAlquiler, 0, SEEK_SET);

    printf("Alquileres entre una semana y 10 días:\n");

    while (fread(&alquiler, sizeof(Alquiler), 1, archivoAlquiler) == 1)
    {
        if (alquiler.dias >= 7 && alquiler.dias <= 10)
        {
            printf("ID Cliente: %d, ID Vehiculo: %d, Precio: $%.2f\n", alquiler.idCliente, alquiler.idVehiculo, alquiler.precio);
        }
    }

    printf("\n");
}

void mostrarAlquileresMayorMonto(FILE *archivoAlquiler)
{
    Alquiler alquiler;
    fseek(archivoAlquiler, 0, SEEK_SET);

    printf("Alquileres con un monto total superior a $10,000:\n");

    while (fread(&alquiler, sizeof(Alquiler), 1, archivoAlquiler) == 1)
    {
        if (alquiler.precio > 10000)
        {
            printf("ID Cliente: %d, ID Vehiculo: %d, Dias: %d, Precio: %.2f\n", alquiler.idCliente, alquiler.idVehiculo, alquiler.dias, alquiler.precio);
        }
    }

    printf("\n");
}
