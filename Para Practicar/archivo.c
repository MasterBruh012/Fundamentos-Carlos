#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int num;

} NUMERO;

int main()
{
    char prueba[] = "Prueba.txt";
    FILE *archivoPrueba = fopen(prueba, "a+b");

    NUMERO *num;
    int n;

    printf("Digite un numero: ");
    scanf("%d", &n);

    num->num = n;

    fwrite(num, sizeof(NUMERO), 1, archivoPrueba);

    printf("Digite un numero: ");
    scanf("%d", &n);

    num->num = n;

    fwrite(num, sizeof(NUMERO), 1, archivoPrueba);

    fseek(archivoPrueba, 0, SEEK_END);
    int tam = ftell(archivoPrueba);
    fseek(archivoPrueba, 0, SEEK_SET);

    while (ftell(archivoPrueba) < tam)
    {
        fread(num, sizeof(NUMERO), 1, archivoPrueba);
        printf("Valor: %d\n", num->num);
    }

    return 0;
}
