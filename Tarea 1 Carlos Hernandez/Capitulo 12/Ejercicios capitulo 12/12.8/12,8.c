#include <stdio.h>
#include <stdlib.h>

/*
¿Qué diferencias se pueden encontrar entre
estas dos declaraciones?

float mt[5][5];
float *m[5];

¿Se podría hacer esas asignaciones?

m = mt;
m[1] = mt[1];
m[2] = &mt[2][0];
*/

int main()
{
    float mt[5][5];
    float *m[5];

    m = mt;           // no es posible
    m[1] = mt[1];     // si es posible
    m[2] = &mt[2][0]; // si es posible

    /*
    m = mt; Esto no es posible, ya que m es un arreglo de punteros a float,
    mientras que mt es una matriz bidimensional de float. Los tipos no
    coinciden, y no se puede asignar una matriz directamente a un puntero.

    m[1] = mt[1]; Esta asignación es posible, ya que m[1] es un puntero a float
    y mt[1] es la segunda fila de la matriz mt, que también es un puntero a float.
    Así que en esta asignación, se está copiando la dirección de inicio de la segunda fila de mt en m[1].

    m[2] = &mt[2][0]; Esta asignación también es posible. m[2] es un puntero a float,
    y &mt[2][0] es la dirección del primer elemento de la tercera fila de mt. Así que
    en esta asignación, se está copiando la dirección del primer elemento de la tercera fila de mt en m[2].
    */

    return 0;
}
