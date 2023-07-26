#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 100

struct ColaCircular
{
    int frente;
    int final;
    int elementos[TAM];
};

void crearColaCircular(struct ColaCircular *cola)
{
    cola->frente = -1;
    cola->final = -1;
}

int estaVacia(struct ColaCircular *cola)
{
    return cola->frente == -1;
}

int estaLlena(struct ColaCircular *cola)
{
    return (cola->final + 1) % TAM == cola->frente;
}

void encolar(struct ColaCircular *cola, int elemento)
{
    if (estaLlena(cola))
    {
        printf("La cola está llena. No se puede encolar.\n");
        return;
    }

    if (estaVacia(cola))
    {
        cola->frente = 0;
    }

    cola->final = (cola->final + 1) % TAM;
    cola->elementos[cola->final] = elemento;
}

int desencolar(struct ColaCircular *cola)
{
    if (estaVacia(cola))
    {
        printf("La cola está vacía. No se puede desencolar.\n");
        return -1;
    }

    int elemento = cola->elementos[cola->frente];

    if (cola->frente == cola->final)
    {
        cola->frente = -1;
        cola->final = -1;
    }
    else
    {
        cola->frente = (cola->frente + 1) % TAM;
    }

    return elemento;
}

void crearColaNegativos(struct ColaCircular *colaOriginal, struct ColaCircular *colaNegativos)
{
    crearColaCircular(colaNegativos);

    while (!estaVacia(colaOriginal))
    {
        int elemento = desencolar(colaOriginal);
        if (elemento < 0)
        {
            encolar(colaNegativos, elemento);
        }
    }
}

int main()
{
    struct ColaCircular colaOriginal, colaNegativos;
    crearColaCircular(&colaOriginal);
    crearColaCircular(&colaNegativos);

    srand(time(0));
    for (int i = 0; i < 100; i++)
    {
        int numeroAleatorio = rand() % 51 - 25;
        encolar(&colaOriginal, numeroAleatorio);
    }

    crearColaNegativos(&colaOriginal, &colaNegativos);

    printf("Cola Original: ");
    while (!estaVacia(&colaOriginal))
    {
        int elemento = desencolar(&colaOriginal);
        printf("%d ", elemento);
    }
    printf("\n");

    printf("Cola Negativos: ");
    while (!estaVacia(&colaNegativos))
    {
        int elemento = desencolar(&colaNegativos);
        printf("%d ", elemento);
    }
    printf("\n");

    return 0;
}
