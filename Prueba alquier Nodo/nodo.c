#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct cliente
{
    int id;
    char nombre[50];
    char ciudad[50];
    struct cliente *anterior;
    struct cliente *siguiente;
} Cliente;

typedef struct automovil
{
    int id;
    char marca[50];
    struct automovil *anterior;
    struct automovil *siguiente;
} Automovil;

typedef struct alquiler
{
    int idCliente;
    int idVehiculo;
    int dias;
    float precio;
    struct alquiler *anterior;
    struct alquiler *siguiente;
} Alquiler;

int mostrarMenu();
int mostrarMenuCliente();
int mostrarMenuVehiculos();
void capturarCliente(Cliente **listaClientes);
void capturarAutomoviles(Automovil **listaAutomoviles);
void capturarAlquileres(Cliente *listaClientes, Automovil *listaAutomoviles, Alquiler **listaAlquileres);
void mostrarClientes(Cliente *listaClientes, Alquiler *listaAlquileres);
void mostrarAutomovil(Automovil *listaAutomoviles, Alquiler *listaAlquileres);
void mostrarAlquileresMayorSemana(Alquiler *listaAlquileres);
void mostrarAlquileresEntreSemana(Alquiler *listaAlquileres);
void mostrarAlquileresMayorMonto(Alquiler *listaAlquileres);
void eliminarRegistroCliente(Cliente **listaClientes, int id);
void eliminarRegistroAutomovil(Automovil **listaAutomoviles, int id);
void liberarMemoria(Cliente *listaClientes, Automovil *listaAutomoviles, Alquiler *listaAlquileres);
void guardarClientesEnArchivo(Cliente *listaClientes);
void guardarAutomovilesEnArchivo(Automovil *listaAutomoviles);
void guardarAlquileresEnArchivo(Alquiler *listaAlquileres);
void cargarClientesDesdeArchivo(Cliente **listaClientes);
void cargarAutomovilesDesdeArchivo(Automovil **listaAutomoviles);
void cargarAlquileresDesdeArchivo(Alquiler **listaAlquileres);

int main()
{
    Cliente *listaClientes = NULL;
    Automovil *listaAutomoviles = NULL;
    Alquiler *listaAlquileres = NULL;

    cargarClientesDesdeArchivo(&listaClientes);
    cargarAutomovilesDesdeArchivo(&listaAutomoviles);
    cargarAlquileresDesdeArchivo(&listaAlquileres);

    int seleccion, idcliente = 0, idauto = 0;

    do
    {
        seleccion = mostrarMenu();

        switch (seleccion)
        {
        case 0:
            printf("Hasta luego!\n");
            break;
        case 1:
            capturarCliente(&listaClientes);
            break;
        case 2:
            capturarAutomoviles(&listaAutomoviles);
            break;
        case 3:
            capturarAlquileres(listaClientes, listaAutomoviles, &listaAlquileres);
            break;
        case 4:
            mostrarClientes(listaClientes, listaAlquileres);
            break;
        case 5:
            mostrarAutomovil(listaAutomoviles, listaAlquileres);
            break;
        case 6:
            do
            {
                printf("Ingrese el ID que desea eliminar: ");
                scanf("%d", &idcliente);
            } while (idcliente <= 0);

            eliminarRegistroCliente(&listaClientes, idcliente); // Puedes proporcionar el ID del cliente a eliminar
            break;
        case 7:
            do
            {
                printf("Ingrese el ID que desea eliminar: ");
                scanf("%d", &idauto);
            } while (idauto <= 0);

            eliminarRegistroAutomovil(&listaAutomoviles, idauto); // Puedes proporcionar el ID del automóvil a eliminar
            break;
        }
    } while (seleccion != 0);

    guardarClientesEnArchivo(listaClientes);
    guardarAutomovilesEnArchivo(listaAutomoviles);
    guardarAlquileresEnArchivo(listaAlquileres);
    liberarMemoria(listaClientes, listaAutomoviles, listaAlquileres);

    return 0;
}

int mostrarMenu()
{
    int opcion;

    printf("\n1: Capturar cliente.\n");
    printf("2: Capturar automovil.\n");
    printf("3: Registrar alquiler.\n");
    printf("4: Mostrar clientes.\n");
    printf("5: Mostrar automoviles.\n");
    printf("6: Eliminar registro de cliente.\n");
    printf("7: Eliminar registro de automovil.\n");
    printf("0: Salir.\n");
    printf("Seleccione una opcion: ");
    fflush(stdin);
    scanf("%d", &opcion);

    return opcion;
}

void capturarCliente(Cliente **listaClientes)
{
    Cliente *nuevoCliente = (Cliente *)malloc(sizeof(Cliente));

    printf("Digite el ID: ");
    fflush(stdin);
    scanf("%d", &(nuevoCliente->id));

    printf("Digite el nombre: ");
    fflush(stdin);
    gets(nuevoCliente->nombre);

    printf("Digite la ciudad: ");
    fflush(stdin);
    gets(nuevoCliente->ciudad);

    nuevoCliente->anterior = NULL;
    nuevoCliente->siguiente = NULL;

    if (*listaClientes == NULL)
    {
        *listaClientes = nuevoCliente;
    }
    else
    {
        Cliente *ultimoCliente = *listaClientes;
        while (ultimoCliente->siguiente != NULL)
        {
            ultimoCliente = ultimoCliente->siguiente;
        }
        ultimoCliente->siguiente = nuevoCliente;
        nuevoCliente->anterior = ultimoCliente;
    }
}

void capturarAutomoviles(Automovil **listaAutomoviles)
{
    Automovil *nuevoAutomovil = (Automovil *)malloc(sizeof(Automovil));

    printf("Digite el ID: ");
    fflush(stdin);
    scanf("%d", &(nuevoAutomovil->id));

    printf("Digite la marca: ");
    fflush(stdin);
    gets(nuevoAutomovil->marca);

    nuevoAutomovil->anterior = NULL;
    nuevoAutomovil->siguiente = NULL;

    if (*listaAutomoviles == NULL)
    {
        *listaAutomoviles = nuevoAutomovil;
    }
    else
    {
        Automovil *ultimoAutomovil = *listaAutomoviles;
        while (ultimoAutomovil->siguiente != NULL)
        {
            ultimoAutomovil = ultimoAutomovil->siguiente;
        }
        ultimoAutomovil->siguiente = nuevoAutomovil;
        nuevoAutomovil->anterior = ultimoAutomovil;
    }
}

void capturarAlquileres(Cliente *listaClientes, Automovil *listaAutomoviles, Alquiler **listaAlquileres)
{
    Alquiler *nuevoAlquiler = (Alquiler *)malloc(sizeof(Alquiler));
    Cliente *clienteActual = listaClientes;
    Automovil *automovilActual = listaAutomoviles;

    printf("Clientes:\n");
    while (clienteActual != NULL)
    {
        printf("ID: %d, Nombre: %s\n", clienteActual->id, clienteActual->nombre);
        clienteActual = clienteActual->siguiente;
    }

    printf("Digite el ID del cliente: ");
    fflush(stdin);
    scanf("%d", &(nuevoAlquiler->idCliente));

    printf("Automoviles:\n");
    while (automovilActual != NULL)
    {
        printf("ID: %d, Marca: %s\n", automovilActual->id, automovilActual->marca);
        automovilActual = automovilActual->siguiente;
    }

    printf("Digite el ID del automovil: ");
    fflush(stdin);
    scanf("%d", &(nuevoAlquiler->idVehiculo));

    printf("Digite los dias: ");
    fflush(stdin);
    scanf("%d", &(nuevoAlquiler->dias));

    printf("Digite el precio: ");
    fflush(stdin);
    scanf("%f", &(nuevoAlquiler->precio));

    nuevoAlquiler->anterior = NULL;
    nuevoAlquiler->siguiente = NULL;

    if (*listaAlquileres == NULL)
    {
        *listaAlquileres = nuevoAlquiler;
    }
    else
    {
        Alquiler *ultimoAlquiler = *listaAlquileres;
        while (ultimoAlquiler->siguiente != NULL)
        {
            ultimoAlquiler = ultimoAlquiler->siguiente;
        }
        ultimoAlquiler->siguiente = nuevoAlquiler;
        nuevoAlquiler->anterior = ultimoAlquiler;
    }
}

void mostrarClientes(Cliente *listaClientes, Alquiler *listaAlquileres)
{
    Cliente *clienteActual = listaClientes;

    printf("Clientes:\n");
    while (clienteActual != NULL)
    {
        printf("ID: %d, Nombre: %s, Ciudad: %s\n", clienteActual->id, clienteActual->nombre, clienteActual->ciudad);
        clienteActual = clienteActual->siguiente;
    }

    printf("\nAlquileres por cliente:\n");
    while (listaAlquileres != NULL)
    {
        printf("ID Cliente: %d, ID Vehiculo: %d, Dias: %d, Precio: %.2f\n",
               listaAlquileres->idCliente, listaAlquileres->idVehiculo, listaAlquileres->dias, listaAlquileres->precio);
        listaAlquileres = listaAlquileres->siguiente;
    }
}

void mostrarAutomovil(Automovil *listaAutomoviles, Alquiler *listaAlquileres)
{
    Automovil *automovilActual = listaAutomoviles;

    printf("Automoviles:\n");
    while (automovilActual != NULL)
    {
        printf("ID: %d, Marca: %s\n", automovilActual->id, automovilActual->marca);
        automovilActual = automovilActual->siguiente;
    }

    printf("\nAlquileres por automovil:\n");
    while (listaAlquileres != NULL)
    {
        printf("ID Cliente: %d, ID Vehiculo: %d, Dias: %d, Precio: %.2f\n",
               listaAlquileres->idCliente, listaAlquileres->idVehiculo, listaAlquileres->dias, listaAlquileres->precio);
        listaAlquileres = listaAlquileres->siguiente;
    }
}

void eliminarRegistroCliente(Cliente **listaClientes, int id)
{
    Cliente *clienteActual = *listaClientes;
    Cliente *clienteAnterior = NULL;

    while (clienteActual != NULL)
    {
        if (clienteActual->id == id)
        {
            if (clienteAnterior != NULL)
            {
                clienteAnterior->siguiente = clienteActual->siguiente;
                if (clienteActual->siguiente != NULL)
                {
                    clienteActual->siguiente->anterior = clienteAnterior;
                }
            }
            else
            {
                *listaClientes = clienteActual->siguiente;
                if (clienteActual->siguiente != NULL)
                {
                    clienteActual->siguiente->anterior = NULL;
                }
            }
            free(clienteActual);
            printf("Registro de cliente eliminado.\n");
            return;
        }

        clienteAnterior = clienteActual;
        clienteActual = clienteActual->siguiente;
    }

    printf("No se encontró un cliente con el ID especificado.\n");
}

void eliminarRegistroAutomovil(Automovil **listaAutomoviles, int id)
{
    Automovil *automovilActual = *listaAutomoviles;
    Automovil *automovilAnterior = NULL;

    while (automovilActual != NULL)
    {
        if (automovilActual->id == id)
        {
            if (automovilAnterior != NULL)
            {
                automovilAnterior->siguiente = automovilActual->siguiente;
                if (automovilActual->siguiente != NULL)
                {
                    automovilActual->siguiente->anterior = automovilAnterior;
                }
            }
            else
            {
                *listaAutomoviles = automovilActual->siguiente;
                if (automovilActual->siguiente != NULL)
                {
                    automovilActual->siguiente->anterior = NULL;
                }
            }
            free(automovilActual);
            printf("Registro de automovil eliminado.\n");
            return;
        }

        automovilAnterior = automovilActual;
        automovilActual = automovilActual->siguiente;
    }

    printf("No se encontró un automovil con el ID especificado.\n");
}

void liberarMemoria(Cliente *listaClientes, Automovil *listaAutomoviles, Alquiler *listaAlquileres)
{
    Cliente *clienteActual = listaClientes;
    Cliente *clienteSiguiente = NULL;
    while (clienteActual != NULL)
    {
        clienteSiguiente = clienteActual->siguiente;
        free(clienteActual);
        clienteActual = clienteSiguiente;
    }

    Automovil *automovilActual = listaAutomoviles;
    Automovil *automovilSiguiente = NULL;
    while (automovilActual != NULL)
    {
        automovilSiguiente = automovilActual->siguiente;
        free(automovilActual);
        automovilActual = automovilSiguiente;
    }

    Alquiler *alquilerActual = listaAlquileres;
    Alquiler *alquilerSiguiente = NULL;
    while (alquilerActual != NULL)
    {
        alquilerSiguiente = alquilerActual->siguiente;
        free(alquilerActual);
        alquilerActual = alquilerSiguiente;
    }
}

void guardarClientesEnArchivo(Cliente *listaClientes)
{
    FILE *archivoClientes = fopen("clientes.dat", "wb");
    Cliente *clienteActual = listaClientes;

    while (clienteActual != NULL)
    {
        fwrite(clienteActual, sizeof(Cliente), 1, archivoClientes);
        clienteActual = clienteActual->siguiente;
    }

    fclose(archivoClientes);
}

void guardarAutomovilesEnArchivo(Automovil *listaAutomoviles)
{
    FILE *archivoAutomoviles = fopen("automoviles.dat", "wb");
    Automovil *automovilActual = listaAutomoviles;

    while (automovilActual != NULL)
    {
        fwrite(automovilActual, sizeof(Automovil), 1, archivoAutomoviles);
        automovilActual = automovilActual->siguiente;
    }

    fclose(archivoAutomoviles);
}

void guardarAlquileresEnArchivo(Alquiler *listaAlquileres)
{
    FILE *archivoAlquileres = fopen("alquileres.dat", "wb");
    Alquiler *alquilerActual = listaAlquileres;

    while (alquilerActual != NULL)
    {
        fwrite(alquilerActual, sizeof(Alquiler), 1, archivoAlquileres);
        alquilerActual = alquilerActual->siguiente;
    }

    fclose(archivoAlquileres);
}

void cargarClientesDesdeArchivo(Cliente **listaClientes)
{
    FILE *archivoClientes = fopen("clientes.dat", "rb");

    if (archivoClientes == NULL)
    {
        return;
    }

    Cliente cliente;
    fread(&cliente, sizeof(Cliente), 1, archivoClientes);

    while (!feof(archivoClientes))
    {
        Cliente *nuevoCliente = (Cliente *)malloc(sizeof(Cliente));
        nuevoCliente->id = cliente.id;
        strcpy(nuevoCliente->nombre, cliente.nombre);
        strcpy(nuevoCliente->ciudad, cliente.ciudad);
        nuevoCliente->anterior = NULL;
        nuevoCliente->siguiente = NULL;

        if (*listaClientes == NULL)
        {
            *listaClientes = nuevoCliente;
        }
        else
        {
            Cliente *ultimoCliente = *listaClientes;
            while (ultimoCliente->siguiente != NULL)
            {
                ultimoCliente = ultimoCliente->siguiente;
            }
            ultimoCliente->siguiente = nuevoCliente;
            nuevoCliente->anterior = ultimoCliente;
        }

        fread(&cliente, sizeof(Cliente), 1, archivoClientes);
    }

    fclose(archivoClientes);
}

void cargarAutomovilesDesdeArchivo(Automovil **listaAutomoviles)
{
    FILE *archivoAutomoviles = fopen("automoviles.dat", "rb");

    if (archivoAutomoviles == NULL)
    {
        return;
    }

    Automovil automovil;
    fread(&automovil, sizeof(Automovil), 1, archivoAutomoviles);

    while (!feof(archivoAutomoviles))
    {
        Automovil *nuevoAutomovil = (Automovil *)malloc(sizeof(Automovil));
        nuevoAutomovil->id = automovil.id;
        strcpy(nuevoAutomovil->marca, automovil.marca);
        nuevoAutomovil->anterior = NULL;
        nuevoAutomovil->siguiente = NULL;

        if (*listaAutomoviles == NULL)
        {
            *listaAutomoviles = nuevoAutomovil;
        }
        else
        {
            Automovil *ultimoAutomovil = *listaAutomoviles;
            while (ultimoAutomovil->siguiente != NULL)
            {
                ultimoAutomovil = ultimoAutomovil->siguiente;
            }
            ultimoAutomovil->siguiente = nuevoAutomovil;
            nuevoAutomovil->anterior = ultimoAutomovil;
        }

        fread(&automovil, sizeof(Automovil), 1, archivoAutomoviles);
    }

    fclose(archivoAutomoviles);
}

void cargarAlquileresDesdeArchivo(Alquiler **listaAlquileres)
{
    FILE *archivoAlquileres = fopen("alquileres.dat", "rb");

    if (archivoAlquileres == NULL)
    {
        return;
    }

    Alquiler alquiler;
    fread(&alquiler, sizeof(Alquiler), 1, archivoAlquileres);

    while (!feof(archivoAlquileres))
    {
        Alquiler *nuevoAlquiler = (Alquiler *)malloc(sizeof(Alquiler));
        nuevoAlquiler->idCliente = alquiler.idCliente;
        nuevoAlquiler->idVehiculo = alquiler.idVehiculo;
        nuevoAlquiler->dias = alquiler.dias;
        nuevoAlquiler->precio = alquiler.precio;
        nuevoAlquiler->anterior = NULL;
        nuevoAlquiler->siguiente = NULL;

        if (*listaAlquileres == NULL)
        {
            *listaAlquileres = nuevoAlquiler;
        }
        else
        {
            Alquiler *ultimoAlquiler = *listaAlquileres;
            while (ultimoAlquiler->siguiente != NULL)
            {
                ultimoAlquiler = ultimoAlquiler->siguiente;
            }
            ultimoAlquiler->siguiente = nuevoAlquiler;
            nuevoAlquiler->anterior = ultimoAlquiler;
        }

        fread(&alquiler, sizeof(Alquiler), 1, archivoAlquileres);
    }

    fclose(archivoAlquileres);
}
