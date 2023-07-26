#include <stdlib.h>
#include <stdio.h>

struct Complejo
{
    float real;
    float imaginario;
};

struct Complejo sumaComplejos(struct Complejo c1, struct Complejo c2)
{
    struct Complejo resultado;
    resultado.real = c1.real + c2.real;
    resultado.imaginario = c1.imaginario + c2.imaginario;
    return resultado;
}

struct Complejo restaComplejos(struct Complejo c1, struct Complejo c2)
{
    struct Complejo resultado;
    resultado.real = c1.real - c2.real;
    resultado.imaginario = c1.imaginario - c2.imaginario;
    return resultado;
}

struct Complejo multiplicaComplejos(struct Complejo c1, struct Complejo c2)
{
    struct Complejo resultado;
    resultado.real = (c1.real * c2.real) - (c1.imaginario * c2.imaginario);
    resultado.imaginario = (c1.real * c2.imaginario) + (c1.imaginario * c2.real);
    return resultado;
}

struct Complejo divideComplejos(struct Complejo c1, struct Complejo c2)
{
    struct Complejo resultado;
    float divisor = (c2.real * c2.real) + (c2.imaginario * c2.imaginario);
    resultado.real = ((c1.real * c2.real) + (c1.imaginario * c2.imaginario)) / divisor;
    resultado.imaginario = ((c1.imaginario * c2.real) - (c1.real * c2.imaginario)) / divisor;
    return resultado;
}

int main()
{
    struct Complejo num1, num2, resultado;
    char operacion;

    printf("Ingrese el primer número complejo (parte real parte imaginaria): ");
    scanf("%f %f", &num1.real, &num1.imaginario);

    printf("Ingrese el segundo número complejo (parte real parte imaginaria): ");
    scanf("%f %f", &num2.real, &num2.imaginario);

    printf("Ingrese la operación a realizar (+, -, *, /): ");
    scanf(" %c", &operacion);

    switch (operacion)
    {
    case '+':
        resultado = sumaComplejos(num1, num2);
        break;
    case '-':
        resultado = restaComplejos(num1, num2);
        break;
    case '*':
        resultado = multiplicaComplejos(num1, num2);
        break;
    case '/':
        resultado = divideComplejos(num1, num2);
        break;
    default:
        printf("Operación no válida.\n");
        return 1;
    }

    printf("El resultado de la operación es: %.2f + %.2fi\n", resultado.real, resultado.imaginario);

    return 0;
}
