/*
Encuentre los errores en la siguiente declaracion de estrcutura y posterior definicion de variable.

struct hormiga
{
int patas;
char especie[41];
float tiempo;
} hormiga colonia [100];

El problema es que se está tratando de declarar y definir una variable llamada 
"hormiga colonia[100]" dentro de la estructura. Esto no es válido en C. 
La definición de la variable "colonia" debe estar fuera de la declaración de la estructura.

*/