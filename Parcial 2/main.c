#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int dia;
    int mes;
    int agno;
} FECHA;

typedef struct
{
    FECHA fecha;
    int milimetros;
    float latitud;
    float longitud;
} LECTURA;

void capturarZona(LECTURA *, int);
void trimestre(LECTURA *,int,float, float);
void cuatrimestre(LECTURA *,int,float, float);
void semestre(LECTURA *,int,float, float);
void quicksort(int n, int arreglo[], int limI, int limS);
void intercambiar(int *primero, int *segundo);
int particionar(int arreglo[], int limI, int limS);

int main()
{
    LECTURA *zonaActual;
    zonaActual = (LECTURA*)malloc(sizeof(LECTURA));


    int cantVals,periodo;
    float lon,lat;

        printf("Bienvenido a ONAMET\n");

        printf("\nDigite la longitud: ");
        scanf("%f",&lon);

        printf("\nDigite la latitud: ");
        scanf("%f",&lat);

        do
        {
            printf("\nDigite el periodo (3, 4 o 6): ");
            scanf("%d",&periodo);

            if (periodo < 3 || periodo > 6 || periodo == 5)
                printf("\nEl valor del periodo debe ser entre 3, 4 o 6\n");

        } while (periodo < 3 || periodo > 6 || periodo == 5);

        do
        {
            printf("\nDigite la cantidad de lluvias registradas (1 a 100): \n");
            scanf("%d",&cantVals);

            if (cantVals <= 0 || cantVals >= 100)
                printf("La cantidad debe estar entre 1 y 100");
        } while (cantVals <= 0 || cantVals >= 100);


        zonaActual = (LECTURA*)realloc(zonaActual, sizeof(LECTURA) * cantVals);


        capturarZona(zonaActual,cantVals);

        printf("\n");

        if (periodo==3)
            trimestre(zonaActual,cantVals,lon,lat);

        if (periodo==4)
            cuatrimestre(zonaActual,cantVals,lon,lat);

        if (periodo==6)
            semestre(zonaActual,cantVals,lon,lat);


    return 0;
}

void capturarZona(LECTURA *zona,int n)
{
    for (int i = 0 ; i < n ; i++)
    {
        printf("\n%d:\n",i+1);

        printf("Digite el dia: ");
        scanf("%d", &((zona+i)->fecha.dia));

        printf("Digite el mes: ");
        scanf("%d", &((zona+i)->fecha.mes));

        printf("Digite el a%co: ",164);
        scanf("%d", &((zona+i)->fecha.agno));

        printf("Digite los milimetros: ");
        scanf("%d", &((zona+i)->milimetros));

        printf("Digite la longitud: ");
        scanf("%f", &((zona+i)->longitud));

        printf("Digite la longitud: ");
        scanf("%f", &((zona+i)->latitud));
    }
}

void trimestre(LECTURA *zona,int n,float longi, float latitud)
{
    int pritri=0,seguntri=0,tercertri=0,cuartotri=0;

    for (int i = 0 ; i < n ; i++)
    {
        if((zona+i)->fecha.mes >= 1 && (zona+i)->fecha.mes <= 3)
        {
            if ((zona+i)->milimetros >= 1000 && (zona+i)->longitud == longi && (zona+i)->latitud == latitud)
                pritri++;
        }

        if((zona+i)->fecha.mes >= 4 && (zona+i)->fecha.mes <= 6)
        {
            if ((zona+i)->milimetros >= 1000 && (zona+i)->longitud == longi && (zona+i)->latitud == latitud)
                seguntri++;
        }

        if((zona+i)->fecha.mes >= 7 && (zona+i)->fecha.mes <= 9)
        {
            if ((zona+i)->milimetros >= 1000 && (zona+i)->longitud == longi && (zona+i)->latitud == latitud)
                tercertri++;
        }

        if((zona+i)->fecha.mes >= 10 && (zona+i)->fecha.mes <= 12)
        {
            if ((zona+i)->milimetros >= 1000 && (zona+i)->longitud == longi && (zona+i)->latitud == latitud)
                cuartotri++;
        }
    }

    printf("\nTrimestre 1: %d\n", pritri);
    printf("Trimestre 2: %d\n", seguntri);
    printf("Trimestre 3: %d\n", tercertri);
    printf("Trimestre 4: %d\n", cuartotri);
}

void cuatrimestre(LECTURA *zona,int n,float longi, float latitud)
{
    int pricuatri=0,seguncuatri=0,tercercuatri=0;

    for (int i = 0 ; i < n ; i++)
    {
        if((zona+i)->fecha.mes >= 1 && (zona+i)->fecha.mes <= 4)
        {
            if ((zona+i)->milimetros >= 1000 && (zona+i)->longitud == longi && (zona+i)->latitud == latitud)
                pricuatri++;
        }

        if((zona+i)->fecha.mes >= 4 && (zona+i)->fecha.mes <= 8)
        {
            if ((zona+i)->milimetros >= 1000 && (zona+i)->longitud == longi && (zona+i)->latitud == latitud)
                seguncuatri++;
        }

        if((zona+i)->fecha.mes >= 8 && (zona+i)->fecha.mes <= 12)
        {
            if ((zona+i)->milimetros >= 1000 && (zona+i)->longitud == longi && (zona+i)->latitud == latitud)
                tercercuatri++;
        }
    }

    printf("\nCuatrimestre 1: %d\n", pricuatri);
    printf("Cuatrimestre  2: %d\n", seguncuatri);
    printf("Cuatrimestre  3: %d\n", tercercuatri);
}

void semestre(LECTURA *zona,int n,float longi, float latitud)
{
    int semes[1];

    for (int i = 0 ; i < n ; i++)
    {
        for(int j = 0 ; j < n ; j++)


            if((zona+i)->fecha.mes >= 1 && (zona+i)->fecha.mes <= 4)
            {
                if ((zona+i)->milimetros >= 1000 && (zona+i)->longitud == longi && (zona+i)->latitud == latitud)
                    semes[0]++;
            }

            if((zona+i)->fecha.mes >= 4 && (zona+i)->fecha.mes <= 8)
            {
                if ((zona+i)->milimetros >= 1000 && (zona+i)->longitud == longi && (zona+i)->latitud == latitud)
                    semes[1]++;
            }
    }



    quicksort(n, semes, 0, n-1);
    printf("\nSemestre 1: %d\n", semes[0]);
    printf("Semestre 2: %d\n", semes[1]);
}

void intercambiar(int *primero, int *segundo)
{
    int burbuja;
    burbuja = *primero;
    *primero = *segundo;
    *segundo = burbuja;
}

int particionar(int arreglo[], int limI, int limS)
{
    int pivote = arreglo[limI], i, indiceMenor = limS - 1;

    for(i=limS; i<limI; i++)
    {

        if(arreglo[i] > pivote)
        {
            indiceMenor++;

            intercambiar(&arreglo[indiceMenor], &arreglo[i]);
        }
    }

    intercambiar(&arreglo[indiceMenor+1], &arreglo[limS]);
    return indiceMenor+1;
}

void quicksort(int n, int arreglo[], int limI, int limS)
{
    int posicionPivote;
    if(limI >= limS)
        return;

    posicionPivote = particionar(arreglo, limI, limS);

    quicksort(n, arreglo, limI, posicionPivote - 1);

    quicksort(n, arreglo, posicionPivote + 1, limS);
}

