#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int contarVocales(const char *linea)
{
    int numVocales = 0;
    char caracter;

    while ((caracter = *linea++) != '\0')
    {
        caracter = tolower(caracter);
        if (caracter == 'a' || caracter == 'e' || caracter == 'i' || caracter == 'o' || caracter == 'u')
        {
            numVocales++;
        }
    }

    return numVocales;
}

int main()
{
    char linea[81];
    int numLineas = 20;
    int numVocales;

    printf("Ingrese 20 lineas de texto (maximo 80 caracteres por linea):\n");

    for (int i = 0; i < numLineas; i++)
    {
        printf("Linea %d: ", i + 1);
        fgets(linea, sizeof(linea), stdin);

        if (linea[0] == '\n')
        {
            printf("La linea esta vacia.\n");
            continue;
        }

        numVocales = contarVocales(linea);

        printf("Numero de vocales: %d\n", numVocales);
    }

    return 0;
}
