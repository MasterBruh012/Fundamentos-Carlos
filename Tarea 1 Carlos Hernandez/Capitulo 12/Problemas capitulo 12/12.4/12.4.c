#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float funcionF(float);
float funcionG(float);
float funcionZ(float);

int main()
{

    float (*funciones[])(float) = {funcionF, funcionG, funcionZ};

    float x, incremento;
    float limiteSuperior = 3.5;

    for (x = 0.0, incremento = 0.2; x < limiteSuperior; x += incremento)
    {
        printf("x = %.2f\n", x);

        for (int i = 0; i < sizeof(funciones) / sizeof(funciones[0]); i++)
        {
            float resultado = funciones[i](x);
            printf("f%d(x) = %.2f\n", i + 1, resultado);
        }

        printf("\n");
    }

    return 0;
}

float funcionF(float x)
{
    return 3 * exp(x) - 2 * x;
}

float funcionG(float x)
{
    return -x * sin(x) + 1.5;
}

float funcionZ(float x)
{
    return x * x - 2 * x + 3;
}
