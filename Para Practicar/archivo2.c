#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int id;
    char nombre[20];
} PERSONA;

void capturarPersona(PERSONA *, FILE *);
void mostrarPersona(PERSONA *, FILE *);

int main()
{
    char extension[] = "persona.txt";
    FILE *archivo = fopen(extension, "w+b");

    PERSONA *cliente;

    capturarPersona(cliente, archivo);

    mostrarPersona(cliente,archivo);

    fclose(archivo);

    return 0;
}

void capturarPersona(PERSONA *cliente, FILE *arch)
{
    printf("Digite el ID: ");
    scanf("%d", &cliente->id);

    printf("Digite el nombre: ");
    scanf("%s", &cliente->nombre);

    fwrite(cliente, sizeof(PERSONA), 1, arch);

    return;
}

void mostrarPersona(PERSONA *cliente, FILE *arch)
{
    fseek(arch, 0, SEEK_END);
    int tam = ftell(arch);
    fseek(arch, 0, SEEK_SET);

    while (ftell(arch) < tam)
    {
        fread(cliente, sizeof(PERSONA), 1, arch);
        printf("ID: %d\t\tNombre: %s",cliente->id,cliente->nombre);
    }
}