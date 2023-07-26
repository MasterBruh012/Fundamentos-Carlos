#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 40

void sumarEnterosLargos(const char *, const char *, char *);

int main()
{
    char entero1[MAX + 1];   // +1 para el carácter nulo
    char entero2[MAX + 1];   // +1 para el carácter nulo
    char resultado[MAX + 2]; // +2 para posibles carry y el carácter nulo

    printf("Ingrese el primer entero largo (máximo 40 dígitos): ");
    scanf("%s", entero1);

    printf("Ingrese el segundo entero largo (máximo 40 dígitos): ");
    scanf("%s", entero2);

    sumarEnterosLargos(entero1, entero2, resultado);

    printf("Resultado: %s\n", resultado);

    return 0;
}

void sumarEnterosLargos(const char *entero1, const char *entero2, char *resultado)
{
    int carry = 0;
    int suma;

    int tam1 = strlen(entero1);
    int tam2 = strlen(entero2);
    int maxLen = tam1 > tam2 ? tam1 : tam2;

    int indice1 = tam1 - 1;
    int indice2 = tam2 - 1;
    int resultadoIndice = maxLen;
    resultado[resultadoIndice] = '\0';

    while (indice1 >= 0 || indice2 >= 0)
    {
        int digito1 = indice1 >= 0 ? entero1[indice1] - '0' : 0;
        int digito2 = indice2 >= 0 ? entero2[indice2] - '0' : 0;

        suma = digito1 + digito2 + carry;
        carry = suma / 10;
        resultado[--resultadoIndice] = (suma % 10) + '0';

        if (indice1 >= 0)
        {
            indice1--;
        }

        if (indice2 >= 0)
        {
            indice2--;
        }
    }

    if (carry > 0)
    {
        resultado[--resultadoIndice] = carry + '0';
    }
}