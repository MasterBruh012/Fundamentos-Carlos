/*
    A la hora de ingresar una fecha.
    Se deberá colocar un "/" entre dato numero

    05 "/" 07 "/" 2023

    Lo mismo con las horas.
    Entre las horas se pondrá un ":"

    12 ":" 15 ":" 55


*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 50

typedef struct
{
    int id;
    char nombre[MAX];
    char trabajo[MAX];
    char num_celular[MAX];
    char comp_movil[MAX];
} Pasajeros;

typedef struct
{
    int ano;
    char marca[MAX];
    int ficha;
    char proprietario[MAX];
} Carros;

typedef struct
{
    int dia;
    int mes;
    int ano;
    int hora;
    int minutos;
    int segundos;
} FECHA;

typedef struct
{
    int fichaCarro;
    int idPasajero;
    int pago;
    int devuelta;
    FECHA fechaserv;
    int tiempo;
} Servicios;

int mostrarMenu();

int mostrarMenuPasajeros();
int mostrarMenuServicios();
int menuCarro();

void capturarPasajeros(FILE *, Pasajeros *);
void capturarcarro(FILE *, Carros *);
void capturarServicio(FILE *, FILE *, FILE *, Servicios *);

void mostrarPasajeros(FILE *, FILE *);
void mostrarCarros(FILE *, FILE *);
void mostrarServicios(FILE *, FILE *, FILE *);

int main()
{
    char rutaPasajeros[] = "pasajeros.dat";
    char rutaCarro[] = "carros.dat";
    char rutaServicio[] = "servicio.dat";

    Carros carro;
    Pasajeros pasajero;
    Servicios servicio;

    int seleccion;

    FILE *archivoCarro = fopen(rutaCarro, "a+b");
    FILE *archivoPasajeros = fopen(rutaPasajeros, "a+b");
    FILE *archivoServicio = fopen(rutaServicio, "a+b");

    do
    {
        seleccion = mostrarMenu();

        switch (seleccion)
        {
        case 0:
            printf("Hasta luego!");
            break;
        case 1:
            capturarPasajeros(archivoPasajeros, &pasajero);
            break;
        case 2:
            capturarcarro(archivoCarro, &carro);
            break;
        case 3:
            capturarServicio(archivoPasajeros, archivoCarro, archivoServicio, &servicio);
            break;
        case 4:
            mostrarPasajeros(archivoPasajeros, archivoServicio);
            break;
        case 5:
            mostrarCarros(archivoCarro, archivoServicio);
            break;
        case 6:
            mostrarServicios(archivoPasajeros, archivoCarro, archivoServicio);
            break;
        }
    } while (seleccion != 0);

    fclose(archivoCarro);
    fclose(archivoPasajeros);
    fclose(archivoServicio);

    return 0;
}

void capturarPasajeros(FILE *archivoPasajeros, Pasajeros *pasajero)
{
    printf("Digite el ID: ");
    fflush(stdin);
    scanf("%d", &pasajero->id);

    printf("Digite el nombre completo: ");
    fflush(stdin);
    gets(pasajero->nombre);

    printf("Digite el lugar de trabajo: ");
    fflush(stdin);
    gets(pasajero->trabajo);

    printf("Digite el numero de celular: ");
    fflush(stdin);
    gets(pasajero->num_celular);

    printf("Digite la compañia telefonica: ");
    fflush(stdin);
    gets(pasajero->comp_movil);

    fwrite(pasajero, sizeof(Pasajeros), 1, archivoPasajeros);
}

void capturarcarro(FILE *archivoCarro, Carros *carros)
{
    printf("Digite la ficha del carro: ");
    fflush(stdin);
    scanf("%d", &carros->ficha);

    printf("Digite el año del carro: ");
    fflush(stdin);
    scanf("%d", &carros->ano);

    printf("Digite la marca del carro: ");
    fflush(stdin);
    gets(carros->marca);

    printf("Digite el propietario del carro: ");
    fflush(stdin);
    gets(carros->proprietario);

    fwrite(carros, sizeof(Carros), 1, archivoCarro);
}

void capturarServicio(FILE *archivoPasajeros, FILE *archivoCarro, FILE *archivoServicio, Servicios *servicio)
{
    Pasajeros pasajeroActual;
    Carros carroActual;

    int comprobar = 0;

    fseek(archivoPasajeros, 0, SEEK_END);
    int tamanoPasajero = ftell(archivoPasajeros);
    fseek(archivoPasajeros, 0, SEEK_SET);

    fseek(archivoCarro, 0, SEEK_END);
    int tamanoCarro = ftell(archivoCarro);
    fseek(archivoCarro, 0, SEEK_SET);

    printf("\nPasajeros\n");
    while (ftell(archivoPasajeros) < tamanoPasajero)
    {
        fread(&pasajeroActual, sizeof(Pasajeros), 1, archivoPasajeros);

        printf("ID: %d\t\tNombre: %s\n",
               pasajeroActual.id, pasajeroActual.nombre);
    }

    printf("\nCarro\n");
    while (ftell(archivoCarro) < tamanoCarro)
    {
        fread(&carroActual, sizeof(Carros), 1, archivoCarro);

        printf("Ficha: %d\t\tPropietario: %s\n",
               carroActual.ficha, carroActual.proprietario);
    }

    do
    {

        fseek(archivoPasajeros, 0, SEEK_SET);

        printf("\nDigite el ID del pasajero: ");
        fflush(stdin);
        scanf("%d", &servicio->idPasajero);

        while (ftell(archivoPasajeros) < tamanoPasajero)
        {
            fread(&pasajeroActual, sizeof(Pasajeros), 1, archivoPasajeros);
            if (servicio->idPasajero == pasajeroActual.id)
            {
                comprobar = 1;
                break;
            }

            else
            {
                comprobar = -1;
            }
        }

        if (comprobar == -1)
        {
            printf("\nDebe digitar un id válido.\n");
        }

    } while (comprobar != 1);

    comprobar = 0;

    do
    {

        fseek(archivoCarro, 0, SEEK_SET);

        printf("\nDigite la ficha del carro: ");
        fflush(stdin);
        scanf("%d", &servicio->fichaCarro);

        while (ftell(archivoCarro) < tamanoCarro)
        {
            fread(&carroActual, sizeof(Carros), 1, archivoCarro);
            if (servicio->fichaCarro == carroActual.ficha)
            {
                comprobar = 1;
                break;
            }

            else
            {
                comprobar = -1;
            }
        }

        if (comprobar == -1)
        {
            printf("\nDebe digitar una ficha válida.\n");
        }

    } while (comprobar != 1);

    comprobar = 0;

    printf("Digite el monto pagado: ");
    fflush(stdin);
    scanf("%d", &servicio->pago);

    printf("Digite la devuelta: ");
    fflush(stdin);
    scanf("%d", &servicio->devuelta);

    printf("Digite la fecha de servicio (dd/mm/yyyy): ");
    fflush(stdin);
    scanf("%d/%d/%d", &servicio->fechaserv.dia, &servicio->fechaserv.mes, &servicio->fechaserv.ano);

    printf("Digite la hora de servicio (hh:mm:ss): ");
    fflush(stdin);
    scanf("%d:%d:%d", &servicio->fechaserv.hora, &servicio->fechaserv.minutos, &servicio->fechaserv.segundos);

    printf("Digite el tiempo estimado del viaje (minutos): ");
    fflush(stdin);
    scanf("%d", &servicio->tiempo);

    fwrite(servicio, sizeof(Servicios), 1, archivoServicio);
}

int mostrarMenu()
{
    char opcion;
    printf("\n1: Capturar Pasajero.\n");
    printf("2: Capturar Carro.\n");
    printf("3: Registrar Servicio.\n");
    printf("4: Menu Pasajeros.\n");
    printf("5: Menu Carros.\n");
    printf("6: Menu Servicios.\n");
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
    case '6':
        return 6;
    default:
        return 0;
    }
}

int mostrarMenuPasajeros()
{
    char opcion;

    printf("\n1: Mostrar Todos los pasajeros.\n");
    printf("2: Todos los pasajeros especificando un lugar de trabajo.\n");
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

int mostrarMenuServicios()
{
    char opcion;

    printf("\n1: Mostrar todos los servicios.\n");
    printf("2: Ficha del carro.\n");
    printf("3: Id del pasajero.\n");
    printf("4: Rango del monto del servicio.\n");
    printf("5: Rango de fecha y hora servicio.\n");
    printf("6: Rango de tiempo estimado del viaje.\n");
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

int menuCarro()
{
    int tomar;
    printf("\n1: Mostrar todos los carros\n");
    printf("2: Mostrar carros segun un rango de años\n");
    printf("3: Mostrar carros de una marca espicifica\n");
    printf("4: Mostrar carros cuyos costo esta en un rango\n");
    printf("5: Mostrar carros de un propietario especifico\n");
    printf("6: Mostrar carros montados en un rango de fecha\n");
    printf("0: para terminar\n");

    printf(" el numero de su selecion: ");
    scanf("%d", &tomar);

    return tomar;
}

void mostrarPasajeros(FILE *archivoPasajeros, FILE *archivoServicio)
{
    Pasajeros pasajeroActual;
    Servicios servicioActual;
    char ciudadFiltro[MAX];
    char compFiltro[MAX];
    int seleccion, liminf = 0, limsup = 0, comparacion;

    do
    {
        fseek(archivoPasajeros, 0, SEEK_END);
        int tamano = ftell(archivoPasajeros);
        fseek(archivoPasajeros, 0, SEEK_SET);

        fseek(archivoServicio, 0, SEEK_END);
        int tamanoServ = ftell(archivoServicio);
        fseek(archivoServicio, 0, SEEK_SET);

        seleccion = mostrarMenuPasajeros();

        switch (seleccion)
        {
        case 0:
            break;
        case 1:
            while (ftell(archivoPasajeros) < tamano)
            {
                fread(&pasajeroActual, sizeof(Pasajeros), 1, archivoPasajeros);

                printf("\nID: %d\nNombre: %s\nLugar de Trabajo: %s\nNumero Telefonico: %s\nCompañia Telefonica: %s\n",
                       pasajeroActual.id, pasajeroActual.nombre, pasajeroActual.trabajo, pasajeroActual.num_celular, pasajeroActual.comp_movil);
            }
            break;
        case 2:

            printf("Escriba un lugar de trabajo: ");
            scanf("%s", &ciudadFiltro);
            while (ftell(archivoPasajeros) < tamano)
            {
                fread(&pasajeroActual, sizeof(Pasajeros), 1, archivoPasajeros);
                if (strcmp(pasajeroActual.trabajo, ciudadFiltro) == 0)
                {
                    printf("\nID: %d\nNombre: %s\nLugar de Trabajo: %s\nNumero Telefonico: %s\nCompañia Telefonica: %s\n",
                           pasajeroActual.id, pasajeroActual.nombre, pasajeroActual.trabajo, pasajeroActual.num_celular, pasajeroActual.comp_movil);
                }
            }
            break;
        case 3:

            printf("Escriba una compaña telefonica: ");
            scanf("%s", &compFiltro);
            while (ftell(archivoPasajeros) < tamano)
            {
                fread(&pasajeroActual, sizeof(Pasajeros), 1, archivoPasajeros);
                if (strcmp(pasajeroActual.comp_movil, compFiltro) == 0)
                {
                    printf("\nID: %d\nNombre: %s\nLugar de Trabajo: %s\nNumero Telefonico: %s\nCompañia Telefonica: %s\n",
                           pasajeroActual.id, pasajeroActual.nombre, pasajeroActual.trabajo, pasajeroActual.num_celular, pasajeroActual.comp_movil);
                }
            }

            break;
        case 4:

            do
            {
                printf("Digite el limite inferior (maximo 60 minutos): ");
                scanf("%d", &liminf);
                printf("Digite el limite superior (maximo 60 minutos): ");
                scanf("%d", &limsup);
            } while (liminf >= limsup);

            while (ftell(archivoPasajeros) < tamano)
            {
                fread(&pasajeroActual, sizeof(Pasajeros), 1, archivoPasajeros);

                fseek(archivoServicio, 0, SEEK_END);
                int tamanoServ = ftell(archivoServicio);
                fseek(archivoServicio, 0, SEEK_SET);

                while (ftell(archivoServicio) < tamanoServ)
                {
                    fread(&servicioActual, sizeof(Servicios), 1, archivoServicio);
                    if (pasajeroActual.id == servicioActual.idPasajero)
                        if (servicioActual.tiempo >= liminf && servicioActual.tiempo <= limsup)
                        {
                            printf("\nID: %d\nNombre: %s\nLugar de Trabajo: %s\nNumero Telefonico: %s\nCompañia Telefonica: %s\nTiempo de viaje: %d\n",
                                   pasajeroActual.id, pasajeroActual.nombre, pasajeroActual.trabajo, pasajeroActual.num_celular, pasajeroActual.comp_movil, servicioActual.tiempo);
                        }
                }
            }

            break;
        case 5:

            do
            {
                do
                {
                    printf("Digite el limite inferior (Mayor que 35 pesos): ");
                    scanf("%d", &liminf);
                } while (liminf < 35);

                printf("Digite el limite superior: ");
                scanf("%d", &limsup);
            } while (liminf >= limsup);

            while (ftell(archivoPasajeros) < tamano)
            {
                fread(&pasajeroActual, sizeof(Pasajeros), 1, archivoPasajeros);

                fseek(archivoServicio, 0, SEEK_END);
                int tamanoServ = ftell(archivoServicio);
                fseek(archivoServicio, 0, SEEK_SET);

                while (ftell(archivoServicio) < tamanoServ)
                {
                    fread(&servicioActual, sizeof(Servicios), 1, archivoServicio);
                    if (pasajeroActual.id == servicioActual.idPasajero)
                        if (servicioActual.pago >= liminf && servicioActual.pago <= limsup)
                        {
                            printf("\nID: %d\nNombre: %s\nLugar de Trabajo: %s\nNumero Telefonico: %s\nCompañia Telefonica: %s\nMonto Pagado: %d\n",
                                   pasajeroActual.id, pasajeroActual.nombre, pasajeroActual.trabajo, pasajeroActual.num_celular, pasajeroActual.comp_movil, servicioActual.pago);
                        }
                }
            }

            break;

        case 6:

            do
            {
                do
                {
                    printf("Digite el limite inferior (Mayor que 35 pesos): ");
                    scanf("%d", &liminf);
                } while (liminf < 35);

                printf("Digite el limite superior: ");
                scanf("%d", &limsup);
            } while (liminf >= limsup);

            while (ftell(archivoPasajeros) < tamano)
            {
                fread(&pasajeroActual, sizeof(Pasajeros), 1, archivoPasajeros);

                fseek(archivoServicio, 0, SEEK_END);
                int tamanoServ = ftell(archivoServicio);
                fseek(archivoServicio, 0, SEEK_SET);

                while (ftell(archivoServicio) < tamanoServ)
                {
                    fread(&servicioActual, sizeof(Servicios), 1, archivoServicio);
                    if (pasajeroActual.id == servicioActual.idPasajero)
                        if ((servicioActual.pago - servicioActual.devuelta) >= liminf && (servicioActual.pago - servicioActual.devuelta) <= limsup)
                        {
                            printf("\nID: %d\nNombre: %s\nLugar de Trabajo: %s\nNumero Telefonico: %s\nCompañia Telefonica: %s\nMonto del Servicio: %d\n",
                                   pasajeroActual.id, pasajeroActual.nombre, pasajeroActual.trabajo, pasajeroActual.num_celular, pasajeroActual.comp_movil, (servicioActual.pago - servicioActual.devuelta));
                        }
                }
            }

            break;

        case 7:

            int dia, mes, ano;
            int d2, m2, an2;

            do
            {
                printf("Digite la fecha inicial (dd/mm/yyyy): ");
                scanf("%d/%d/%d", &dia, &mes, &ano);
                printf("Digite la fecha final (dd/mm/yyyy): ");
                scanf("%d/%d/%d", &d2, &m2, &an2);
            } while (mes > m2 || ano > an2);

            do
            {
                printf("Digite la hora inicial (Formato 24h): ");
                scanf("%d", &liminf);
                printf("Digite la hora final (Formato 24h): ");
                scanf("%d", &limsup);
            } while (liminf >= limsup);

            while (ftell(archivoPasajeros) < tamano)
            {
                fread(&pasajeroActual, sizeof(Pasajeros), 1, archivoPasajeros);

                fseek(archivoServicio, 0, SEEK_END);
                int tamanoservicio = ftell(archivoServicio);
                fseek(archivoServicio, 0, SEEK_SET);

                while (ftell(archivoServicio) < tamanoservicio)
                {
                    fread(&servicioActual, sizeof(Servicios), 1, archivoServicio);

                    if (pasajeroActual.id == servicioActual.idPasajero && servicioActual.fechaserv.ano >= ano && servicioActual.fechaserv.ano <= an2 && servicioActual.fechaserv.mes >= mes && servicioActual.fechaserv.mes <= m2 && servicioActual.fechaserv.dia >= dia && servicioActual.fechaserv.dia <= d2)
                    {
                        printf("\nID: %d\nNombre: %s\nLugar de Trabajo: %s\nNumero Telefonico: %s\nCompañia Telefonica: %s\nFecha del Servicio: %d/%d/%d\nHora del Servicio: %d:%d:%d\n",
                               pasajeroActual.id, pasajeroActual.nombre, pasajeroActual.trabajo, pasajeroActual.num_celular, pasajeroActual.comp_movil, servicioActual.fechaserv.dia, servicioActual.fechaserv.mes, servicioActual.fechaserv.ano, servicioActual.fechaserv.hora, servicioActual.fechaserv.minutos, servicioActual.fechaserv.segundos);
                    }
                }
            }

            break;
        }

    } while (seleccion != 0);
}

void mostrarServicios(FILE *archivoPasajeros, FILE *archivoCarro, FILE *archivoServicio)
{
    int selecion, liminf, limsup;
    Pasajeros pasajeroActual;
    Carros carroActual;
    Servicios servicioActual;

    do
    {

        fseek(archivoPasajeros, 0, SEEK_END);
        int tamPas = ftell(archivoPasajeros);
        fseek(archivoPasajeros, 0, SEEK_SET);

        fseek(archivoCarro, 0, SEEK_END);
        int tamCar = ftell(archivoCarro);
        fseek(archivoCarro, 0, SEEK_SET);

        fseek(archivoServicio, 0, SEEK_END);
        int tamServ = ftell(archivoServicio);
        fseek(archivoServicio, 0, SEEK_SET);

        selecion = mostrarMenuServicios();

        switch (selecion)
        {
        case 1:
            while (ftell(archivoServicio) < tamServ)
            {
                fread(&servicioActual, sizeof(Servicios), 1, archivoServicio);

                printf("\n ID Pasajero: %d  \n Ficha Carro: %d \n Monto Pagado: %d \n Devueltas: %d \n Fecha del servicio: %d/%d/%d \n Hora del Servicio: %d:%d:%d\n Tiempo Estimado: %d minutos\n",
                       servicioActual.idPasajero, servicioActual.fichaCarro, servicioActual.pago, servicioActual.devuelta,
                       servicioActual.fechaserv.dia, servicioActual.fechaserv.mes, servicioActual.fechaserv.ano,
                       servicioActual.fechaserv.hora, servicioActual.fechaserv.minutos, servicioActual.fechaserv.segundos,
                       servicioActual.tiempo);
            }
            break;

        case 2:

            while (ftell(archivoPasajeros) < tamPas)
            {
                fread(&pasajeroActual, sizeof(Pasajeros), 1, archivoPasajeros);

                fseek(archivoCarro, 0, SEEK_END);
                int tamCar = ftell(archivoCarro);
                fseek(archivoCarro, 0, SEEK_SET);

                while (ftell(archivoCarro) < tamCar)
                {
                    fread(&carroActual, sizeof(Carros), 1, archivoCarro);

                    fseek(archivoServicio, 0, SEEK_END);
                    int tamServ = ftell(archivoServicio);
                    fseek(archivoServicio, 0, SEEK_SET);

                    while (ftell(archivoServicio) < tamServ)
                    {
                        fread(&servicioActual, sizeof(Servicios), 1, archivoServicio);

                        if (pasajeroActual.id == servicioActual.idPasajero && carroActual.ficha == servicioActual.fichaCarro)
                        {
                            printf("\nID Pasajero: %d\nNombre del Pasajero: %s\nPropietario del Carro: %s \n Monto del Servicio: %d\n Fecha del servicio: %d/%d/%d \n Hora del Servicio: %d:%d:%d\n Tiempo Estimado: %d minutos\n",
                                   servicioActual.idPasajero, pasajeroActual.nombre, carroActual.proprietario, (servicioActual.pago - servicioActual.devuelta),
                                   servicioActual.fechaserv.dia, servicioActual.fechaserv.mes, servicioActual.fechaserv.ano,
                                   servicioActual.fechaserv.hora, servicioActual.fechaserv.minutos, servicioActual.fechaserv.segundos,
                                   servicioActual.tiempo);
                        }
                    }
                }
            }
            break;

        case 3:

            while (ftell(archivoPasajeros) < tamPas)
            {
                fread(&pasajeroActual, sizeof(Pasajeros), 1, archivoPasajeros);

                fseek(archivoCarro, 0, SEEK_END);
                int tamCar = ftell(archivoCarro);
                fseek(archivoCarro, 0, SEEK_SET);

                while (ftell(archivoCarro) < tamCar)
                {
                    fread(&carroActual, sizeof(Carros), 1, archivoCarro);

                    fseek(archivoServicio, 0, SEEK_END);
                    int tamServ = ftell(archivoServicio);
                    fseek(archivoServicio, 0, SEEK_SET);

                    while (ftell(archivoServicio) < tamServ)
                    {
                        fread(&servicioActual, sizeof(Servicios), 1, archivoServicio);

                        if (pasajeroActual.id == servicioActual.idPasajero && carroActual.ficha == servicioActual.fichaCarro)
                        {
                            printf("\nNombre del Pasajero: %s\nFicha del Carro: %d\nPropietario del Carro: %s \n Monto del Servicio: %d\n Fecha del servicio: %d/%d/%d \n Hora del Servicio: %d:%d:%d\n Tiempo Estimado: %d minutos\n",
                                   pasajeroActual.nombre, carroActual.ficha, carroActual.proprietario, (servicioActual.pago - servicioActual.devuelta),
                                   servicioActual.fechaserv.dia, servicioActual.fechaserv.mes, servicioActual.fechaserv.ano,
                                   servicioActual.fechaserv.hora, servicioActual.fechaserv.minutos, servicioActual.fechaserv.segundos,
                                   servicioActual.tiempo);
                        }
                    }
                }
            }
            break;

        case 4:

            do
            {
                printf("Digite el limite inferior (maximo 60 minutos): ");
                scanf("%d", &liminf);
                printf("Digite el limite superior (maximo 60 minutos): ");
                scanf("%d", &limsup);
            } while (liminf >= limsup);

            while (ftell(archivoPasajeros) < tamPas)
            {
                fread(&pasajeroActual, sizeof(Pasajeros), 1, archivoPasajeros);

                fseek(archivoServicio, 0, SEEK_END);
                int tamServ = ftell(archivoServicio);
                fseek(archivoServicio, 0, SEEK_SET);

                while (ftell(archivoServicio) < tamServ)
                {
                    fread(&servicioActual, sizeof(Servicios), 1, archivoServicio);

                    if (pasajeroActual.id == servicioActual.idPasajero && (servicioActual.pago - servicioActual.devuelta) >= liminf && (servicioActual.pago - servicioActual.devuelta) <= limsup)
                    {
                        printf("\nID del Pasajero: %d\nNombre del Pasajero: %s\nFicha del Carro: %d\n Monto del Servicio: %d\n Fecha del servicio: %d/%d/%d \n Hora del Servicio: %d:%d:%d\n Tiempo Estimado: %d minutos\n",
                               servicioActual.idPasajero, pasajeroActual.nombre, servicioActual.fichaCarro, (servicioActual.pago - servicioActual.devuelta),
                               servicioActual.fechaserv.dia, servicioActual.fechaserv.mes, servicioActual.fechaserv.ano,
                               servicioActual.fechaserv.hora, servicioActual.fechaserv.minutos, servicioActual.fechaserv.segundos,
                               servicioActual.tiempo);
                    }
                }
            }
            break;
        case 5:

            int dia, mes, ano;
            int d2, m2, an2;

            do
            {
                printf("Digite la fecha inicial (dd/mm/yyyy): ");
                scanf("%d/%d/%d", &dia, &mes, &ano);
                printf("Digite la fecha final (dd/mm/yyyy): ");
                scanf("%d/%d/%d", &d2, &m2, &an2);
            } while (mes > m2 || ano > an2);

            do
            {
                printf("Digite la hora inicial (hh): ");
                scanf("%d", &liminf);
                printf("Digite la hora final (hh): ");
                scanf("%d", &limsup);
            } while (liminf >= limsup);

            while (ftell(archivoPasajeros) < tamPas)
            {
                fread(&pasajeroActual, sizeof(Pasajeros), 1, archivoPasajeros);

                fseek(archivoServicio, 0, SEEK_END);
                int tamServ = ftell(archivoServicio);
                fseek(archivoServicio, 0, SEEK_SET);

                while (ftell(archivoServicio) < tamServ)
                {
                    fread(&servicioActual, sizeof(Servicios), 1, archivoServicio);

                    if (pasajeroActual.id == servicioActual.idPasajero)
                    {
                        if (pasajeroActual.id == servicioActual.idPasajero && servicioActual.fechaserv.ano >= ano && servicioActual.fechaserv.ano <= an2 && servicioActual.fechaserv.mes >= mes && servicioActual.fechaserv.mes <= m2 && servicioActual.fechaserv.dia >= dia && servicioActual.fechaserv.dia <= d2)
                        {
                            printf("\nID del Pasajero: %d\nNombre: %s\nFicha del Carro: %d\nMonto del Servicio: %d\nFecha del Servicio: %d/%d/%d\nHora del Servicio: %d/%d/%d\nTiempo estimado del Servicio: %d\n",
                                   servicioActual.idPasajero, pasajeroActual.nombre, servicioActual.fichaCarro, (servicioActual.pago - servicioActual.devuelta), servicioActual.fechaserv.dia, servicioActual.fechaserv.mes, servicioActual.fechaserv.ano, servicioActual.fechaserv.hora, servicioActual.fechaserv.minutos, servicioActual.fechaserv.segundos, servicioActual.tiempo);
                        }
                    }
                }
            }
            break;
        case 6:

            do
            {
                printf("Digite el limite inferior (maximo 60 minutos): ");
                scanf("%d", &liminf);
                printf("Digite el limite superior (maximo 60 minutos): ");
                scanf("%d", &limsup);
            } while (liminf >= limsup);

            while (ftell(archivoPasajeros) < tamPas)
            {
                fread(&pasajeroActual, sizeof(Pasajeros), 1, archivoPasajeros);

                fseek(archivoServicio, 0, SEEK_END);
                int tamanoServ = ftell(archivoServicio);
                fseek(archivoServicio, 0, SEEK_SET);

                while (ftell(archivoServicio) < tamanoServ)
                {
                    fread(&servicioActual, sizeof(Servicios), 1, archivoServicio);
                    if (pasajeroActual.id == servicioActual.idPasajero)
                        if (servicioActual.tiempo >= liminf && servicioActual.tiempo <= limsup)
                        {
                            printf("\nID del Pasajero: %d\nNombre: %s\nFicha del Carro: %d\nMonto del Servicio: %d\nFecha del Servicio: %d/%d/%d\nHora del Servicio: %d/%d/%d\nTiempo estimado del Servicio: %d\n",
                                   servicioActual.idPasajero, pasajeroActual.nombre, servicioActual.fichaCarro, (servicioActual.pago - servicioActual.devuelta), servicioActual.fechaserv.dia, servicioActual.fechaserv.mes, servicioActual.fechaserv.ano, servicioActual.fechaserv.hora, servicioActual.fechaserv.minutos, servicioActual.fechaserv.segundos, servicioActual.tiempo);
                        }
                }
            }
            break;
        }
    } while (selecion != 0);
}

void mostrarCarros(FILE *archivoCarro, FILE *archivoServicio)
{
    int selecion, comparacion;
    int rangoinf, rangosup;
    char marca[50], propietario[50];
    Carros carrosActual;
    Servicios servicioActual;

    do
    {

        fseek(archivoCarro, 0, SEEK_END);
        int tamano = ftell(archivoCarro);
        fseek(archivoCarro, 0, SEEK_SET);

        fseek(archivoServicio, 0, SEEK_END);
        int tamanoServ = ftell(archivoServicio);
        fseek(archivoServicio, 0, SEEK_SET);

        selecion = menuCarro();

        switch (selecion)
        {
        case 1:
            while (ftell(archivoCarro) < tamano)
            {
                fread(&carrosActual, sizeof(Carros), 1, archivoCarro);

                printf("\nFicha: %d\nAño: %d\nMarca: %s\nProprietario: %s\n", carrosActual.ficha, carrosActual.ano,
                       carrosActual.marca, carrosActual.proprietario);
            }
            break;
        case 2:
            do
            {
                printf("Digite el limite inferior: ");
                scanf("%d", &rangoinf);
                printf("Digite el limite superior: ");
                scanf("%d", &rangosup);
            } while (rangoinf >= rangosup);

            while (ftell(archivoCarro) < tamano)
            {
                fread(&carrosActual, sizeof(Carros), 1, archivoCarro);
                if (carrosActual.ano >= rangoinf && carrosActual.ano <= rangosup)
                {
                    printf("\nFicha: %d\nAño: %d\nMarca: %s\n", carrosActual.ficha, carrosActual.ano,
                           carrosActual.marca);
                }
            }
            break;
        case 3:
            printf("Digite la marca que busca: ");
            fflush(stdin);
            gets(marca);

            while (ftell(archivoCarro) < tamano)
            {
                fread(&carrosActual, sizeof(Carros), 1, archivoCarro);
                if ((comparacion = strcmp(marca, carrosActual.marca)) == 0)
                {
                    printf("\nFicha: %d\nAño: %d\nProprietario: %s\n", carrosActual.ficha, carrosActual.ano,
                           carrosActual.proprietario);
                }
            }
            break;
        case 4:
            do
            {
                do
                {
                    printf("Digite el limite inferior (Mayor que 35 pesos): ");
                    scanf("%d", &rangoinf);
                } while (rangoinf < 35);

                printf("Digite el limite superior: ");
                scanf("%d", &rangosup);
            } while (rangoinf >= rangosup);

            while (ftell(archivoCarro) < tamano)
            {
                fread(&carrosActual, sizeof(Carros), 1, archivoCarro);

                fseek(archivoServicio, 0, SEEK_END);
                int tamanoServ = ftell(archivoServicio);
                fseek(archivoServicio, 0, SEEK_SET);

                while (ftell(archivoServicio) < tamanoServ)
                {
                    fread(&servicioActual, sizeof(Servicios), 1, archivoServicio);

                    if (carrosActual.ficha == servicioActual.fichaCarro && servicioActual.pago >= rangoinf && servicioActual.pago <= rangosup)
                    {
                        printf("\nAño: %d\nFicha: %d\nMarca: %s\nProprietario: %s\nMonto Pagado: %d \n", carrosActual.ano, carrosActual.ficha,
                               carrosActual.marca, carrosActual.proprietario, servicioActual.pago);
                    }
                }
            }

            break;
        case 5:
            printf("Digite el nombre del proprietario: ");
            fflush(stdin);
            gets(propietario);

            while (ftell(archivoCarro) < tamano)
            {
                fread(&carrosActual, sizeof(Carros), 1, archivoCarro);
                if ((comparacion = strcmp(propietario, carrosActual.proprietario)) == 0)
                {
                    printf("\nFicha: %d\nAño: %d\nMarca: %s\n", carrosActual.ficha, carrosActual.ano,
                           carrosActual.marca);
                }
            }
            break;
        case 6:

            int dia, mes, ano;
            int d2, m2, an2;
            do
            {
                printf("Digite la fecha inicial (dd/mm/yyyy): ");
                scanf("%d/%d/%d", &dia, &mes, &ano);
                printf("Digite la fecha final (dd/mm/yyyy): ");
                scanf("%d/%d/%d", &d2, &m2, &an2);
            } while (mes > m2 || ano > an2);

            while (ftell(archivoCarro) < tamano)
            {
                fread(&carrosActual, sizeof(Carros), 1, archivoCarro);

                fseek(archivoServicio, 0, SEEK_END);
                int tamanoservicio = ftell(archivoServicio);
                fseek(archivoServicio, 0, SEEK_SET);

                while (ftell(archivoServicio) < tamanoservicio)
                {
                    fread(&servicioActual, sizeof(Servicios), 1, archivoServicio);

                    if (carrosActual.ficha == servicioActual.fichaCarro && servicioActual.fechaserv.ano >= ano && servicioActual.fechaserv.ano <= an2 && servicioActual.fechaserv.mes >= mes && servicioActual.fechaserv.mes <= m2 && servicioActual.fechaserv.dia >= dia && servicioActual.fechaserv.dia <= d2)
                    {
                        printf("\nAño: %d\nFicha: %d\nMarca: %s\nProprietario: %s\nFecha del servicio: %d/%d/%d\n", carrosActual.ano, carrosActual.ficha,
                               carrosActual.marca, carrosActual.proprietario, servicioActual.fechaserv.dia, servicioActual.fechaserv.mes, servicioActual.fechaserv.ano);
                    }
                }
            }

            break;
        }
    } while (selecion != 0);
}