/*
    ¿Que diferencias existe entre las siguientes declaraciones?

char *c[15];
char **c;
char c[15][12];


char *c[15]; Es un arreglo de 15 punteros a caracteres, utilizado 
para almacenar 15 direcciones de cadenas de caracteres.

char **c; Es un puntero a un puntero de caracteres, comúnmente 
utilizado para crear arreglos dinámicos de punteros a cadenas.

char c[15][12]; Es una matriz bidimensional de caracteres, 
utilizada para almacenar 15 cadenas de caracteres con una longitud máxima 
de 11 caracteres más el carácter nulo '\0'.

*/