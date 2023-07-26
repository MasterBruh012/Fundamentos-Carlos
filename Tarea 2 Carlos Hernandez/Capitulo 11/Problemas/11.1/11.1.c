#include <stdlib.h>
#include <stdio.h>

struct Fecha {
    int dia;
    int mes;
    int anio;
};

int calcularDias(struct Fecha fecha1, struct Fecha fecha2) {
    const int diasPorMes[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int totalDias1 = fecha1.dia;
    int totalDias2 = fecha2.dia;

    for (int i = 1; i < fecha1.anio; i++) {
        totalDias1 += (i % 4 == 0 && (i % 100 != 0 || i % 400 == 0)) ? 366 : 365;
    }
    for (int i = 1; i < fecha2.anio; i++) {
        totalDias2 += (i % 4 == 0 && (i % 100 != 0 || i % 400 == 0)) ? 366 : 365;
    }

    for (int i = 1; i < fecha1.mes; i++) {
        totalDias1 += diasPorMes[i - 1];
        if (i == 2 && (fecha1.anio % 4 == 0 && (fecha1.anio % 100 != 0 || fecha1.anio % 400 == 0))) {
            totalDias1++;
        }
    }
    for (int i = 1; i < fecha2.mes; i++) {
        totalDias2 += diasPorMes[i - 1];
        if (i == 2 && (fecha2.anio % 4 == 0 && (fecha2.anio % 100 != 0 || fecha2.anio % 400 == 0))) {
            totalDias2++;
        }
    }

    totalDias1 += fecha1.dia;
    totalDias2 += fecha2.dia;

    return totalDias2 - totalDias1;
}

int main() {
    struct Fecha fecha1, fecha2;

    printf("Ingrese la primera fecha (dia mes año): ");
    scanf("%d %d %d", &fecha1.dia, &fecha1.mes, &fecha1.anio);

    printf("Ingrese la segunda fecha (dia mes año): ");
    scanf("%d %d %d", &fecha2.dia, &fecha2.mes, &fecha2.anio);

    int diasEntreFechas = calcularDias(fecha1, fecha2);

    printf("El número de días entre las fechas es: %d\n", diasEntreFechas);

    return 0;
}
