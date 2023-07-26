#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float areaTrianguloRectangulo(float base, float altura);
float areaTrianguloIsosceles(float base, float altura);
float areaCuadrado(float lado);
float areaTrapecio(float baseMayor, float baseMenor, float altura);
float areaCirculo(float radio);

int main() {
    float (*funcionesArea[])(float, float) = {
        areaTrianguloRectangulo,
        areaTrianguloIsosceles,
        areaCuadrado,
        areaTrapecio,
        areaCirculo
    };

    int opcion;
    float resultado;
    int valores[3];

    printf("Selecciona una figura para calcular el área:\n");
    printf("1. Triángulo rectángulo\n");
    printf("2. Triángulo isósceles\n");
    printf("3. Cuadrado\n");
    printf("4. Trapecio\n");
    printf("5. Círculo\n");
    printf("Opción: ");
    scanf("%d", &opcion);

    if (opcion < 1 || opcion > 5) {
        printf("Opción inválida.\n");
        return 1;
    }

    for (int i = 0; i < 3; i++) {
        printf("Ingrese el valor %d: ", i + 1);
        scanf("%d", &valores[i]);
    }

    resultado = funcionesArea[opcion - 1](valores[0], valores[1]);

    printf("El área es: %.2f\n", resultado);

    return 0;
}


float areaTrianguloRectangulo(float base, float altura) {
    return base * altura / 2.0;
}

float areaTrianguloIsosceles(float base, float altura) {
    return base * altura / 2.0;
}

float areaCuadrado(float lado) {
    return lado * lado;
}

float areaTrapecio(float baseMayor, float baseMenor, float altura) {
    return (baseMayor + baseMenor) * altura / 2.0;
}

float areaCirculo(float radio) {
    return M_PI * radio * radio;
}
