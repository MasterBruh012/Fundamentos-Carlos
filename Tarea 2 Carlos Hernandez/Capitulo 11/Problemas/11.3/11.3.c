#include <stdio.h>
#include <string.h>

struct Cliente {
    char nombre[50];
    int unidades;
    float precio;
    char estado[20];
};

void mostrarClientesMorosos(struct Cliente clientes[], int numClientes) {
    printf("\nClientes en estado moroso:\n");
    for (int i = 0; i < numClientes; i++) {
        if (strcmp(clientes[i].estado, "moroso") == 0) {
            printf("Nombre: %s\n", clientes[i].nombre);
            printf("Unidades solicitadas: %d\n", clientes[i].unidades);
            printf("Precio por unidad: %.2f\n", clientes[i].precio);
            printf("Estado: %s\n", clientes[i].estado);
            printf("\n");
        }
    }
}

void mostrarClientesPagadosConMayorFactura(struct Cliente clientes[], int numClientes, float cantidad) {
    printf("\nClientes en estado pagado con facturas mayores a %.2f:\n", cantidad);
    for (int i = 0; i < numClientes; i++) {
        if (strcmp(clientes[i].estado, "pagado") == 0 && (clientes[i].unidades * clientes[i].precio) > cantidad) {
            printf("Nombre: %s\n", clientes[i].nombre);
            printf("Unidades solicitadas: %d\n", clientes[i].unidades);
            printf("Precio por unidad: %.2f\n", clientes[i].precio);
            printf("Estado: %s\n", clientes[i].estado);
            printf("Total a pagar: %.2f\n", clientes[i].unidades * clientes[i].precio);
            printf("\n");
        }
    }
}

int main() {
    int numClientes;

    printf("Ingrese el número de clientes: ");
    scanf("%d", &numClientes);

    while (getchar() != '\n');

    struct Cliente clientes[numClientes];

    for (int i = 0; i < numClientes; i++) {
        printf("\nCliente %d:\n", i + 1);

        printf("Ingrese el nombre del cliente: ");
        fgets(clientes[i].nombre, sizeof(clientes[i].nombre), stdin);
        clientes[i].nombre[strcspn(clientes[i].nombre, "\n")] = '\0'; 

        printf("Ingrese el número de unidades solicitadas: ");
        scanf("%d", &clientes[i].unidades);

        printf("Ingrese el precio de cada unidad: ");
        scanf("%f", &clientes[i].precio);

        while (getchar() != '\n');

        printf("Ingrese el estado del cliente (moroso, atrasado, pagado): ");
        fgets(clientes[i].estado, sizeof(clientes[i].estado), stdin);
        clientes[i].estado[strcspn(clientes[i].estado, "\n")] = '\0'; 
    }

    printf("\nFacturación de clientes:\n");
    for (int i = 0; i < numClientes; i++) {
        printf("\nCliente %d:\n", i + 1);
        printf("Nombre: %s\n", clientes[i].nombre);
        printf("Unidades solicitadas: %d\n", clientes[i].unidades);
        printf("Precio por unidad: %.2f\n", clientes[i].precio);
        printf("Estado: %s\n", clientes[i].estado);
    }

    mostrarClientesMorosos(clientes, numClientes);

    float cantidadDeterminada;
    printf("\nIngrese la cantidad determinada para filtrar los clientes pagados: ");
    scanf("%f", &cantidadDeterminada);
    mostrarClientesPagadosConMayorFactura(clientes, numClientes, cantidadDeterminada);

    return 0;
}
