#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int *digitos;
    int numDigitos;
} NumeroGrande;

NumeroGrande leerNumeroGrande();
NumeroGrande sumarNumerosGrandes(NumeroGrande num1, NumeroGrande num2);
void liberarNumeroGrande(NumeroGrande num);

int main()
{
    NumeroGrande numero1, numero2, resultado;

    printf("Ingrese el primer numero grande: ");
    numero1 = leerNumeroGrande();

    printf("Ingrese el segundo numero grande: ");
    numero2 = leerNumeroGrande();

    resultado = sumarNumerosGrandes(numero1, numero2);

    printf("La suma de los numeros grandes es: ");
    for (int i = 0; i < resultado.numDigitos; i++)
    {
        printf("%d", resultado.digitos[i]);
    }
    printf("\n");

    liberarNumeroGrande(numero1);
    liberarNumeroGrande(numero2);
    liberarNumeroGrande(resultado);

    return 0;
}

NumeroGrande leerNumeroGrande()
{
    char buffer[1000];
    NumeroGrande numero;

    fgets(buffer, sizeof(buffer), stdin);

    int numDigitos = 0;
    for (int i = 0; buffer[i] != '\0' && buffer[i] != '\n'; i++)
    {
        if (buffer[i] >= '0' && buffer[i] <= '9')
        {
            numDigitos++;
        }
    }

    numero.numDigitos = numDigitos;
    numero.digitos = (int *)malloc(numDigitos * sizeof(int));

    int j = 0;
    for (int i = 0; buffer[i] != '\0' && buffer[i] != '\n'; i++)
    {
        if (buffer[i] >= '0' && buffer[i] <= '9')
        {
            numero.digitos[j] = buffer[i] - '0';
            j++;
        }
    }

    return numero;
}

NumeroGrande sumarNumerosGrandes(NumeroGrande num1, NumeroGrande num2)
{
    NumeroGrande resultado;
    int maxDigitos = num1.numDigitos > num2.numDigitos ? num1.numDigitos : num2.numDigitos;

    resultado.numDigitos = maxDigitos + 1;
    resultado.digitos = (int *)calloc(resultado.numDigitos, sizeof(int));

    int acarreo = 0;
    int suma;

    for (int i = 0; i < maxDigitos; i++)
    {
        int digito1 = i < num1.numDigitos ? num1.digitos[num1.numDigitos - 1 - i] : 0;
        int digito2 = i < num2.numDigitos ? num2.digitos[num2.numDigitos - 1 - i] : 0;

        suma = digito1 + digito2 + acarreo;
        acarreo = suma / 10;
        resultado.digitos[resultado.numDigitos - 1 - i] = suma % 10;
    }

    if (acarreo > 0)
    {
        resultado.digitos[0] = acarreo;
    }
    else
    {

        resultado.numDigitos--;
        int *temp = (int *)malloc(resultado.numDigitos * sizeof(int));
        for (int i = 0; i < resultado.numDigitos; i++)
        {
            temp[i] = resultado.digitos[i + 1];
        }
        free(resultado.digitos);
        resultado.digitos = temp;
    }

    return resultado;
}

void liberarNumeroGrande(NumeroGrande num)
{
    free(num.digitos);
}
