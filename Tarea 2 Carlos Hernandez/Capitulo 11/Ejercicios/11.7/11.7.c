#include <stdio.h>
#include <string.h>

// Definición de la estructura para representar a un alumno
struct Alumno {
    char nombre[50];
    int curso;
    int edad;
    char direccion[100];
    float notas[10];
};

// Definición de la estructura para representar a un profesor
struct Profesor {
    char nombre[50];
    char asignaturas[5][50];
    char direccion[100];
};

// Definición de la estructura que representa a un profesor o un alumno utilizando una unión
union ProfesorAlumno {
    struct Alumno alumno;
    struct Profesor profesor;
};

int main() {
    union ProfesorAlumno persona;

    // Acceder y asignar valores para el caso de alumno
    strcpy(persona.alumno.nombre, "Juan Perez");
    persona.alumno.curso = 4;
    persona.alumno.edad = 16;
    strcpy(persona.alumno.direccion, "Calle 123, Ciudad");
    // Asignar notas
    for (int i = 0; i < 10; i++) {
        persona.alumno.notas[i] = 8.5;
    }

    // Acceder y asignar valores para el caso de profesor
    strcpy(persona.profesor.nombre, "Ana Lopez");
    strcpy(persona.profesor.asignaturas[0], "Matemáticas");
    strcpy(persona.profesor.asignaturas[1], "Física");
    strcpy(persona.profesor.asignaturas[2], "Química");
    strcpy(persona.profesor.direccion, "Av. Principal, Ciudad");

    // Mostrar los datos del alumno
    printf("Datos del alumno:\n");
    printf("Nombre: %s\n", persona.alumno.nombre);
    printf("Curso: %d\n", persona.alumno.curso);
    printf("Edad: %d\n", persona.alumno.edad);
    printf("Dirección: %s\n", persona.alumno.direccion);
    printf("Notas:\n");
    for (int i = 0; i < 10; i++) {
        printf("Asignatura %d: %.2f\n", i + 1, persona.alumno.notas[i]);
    }

    // Mostrar los datos del profesor
    printf("\nDatos del profesor:\n");
    printf("Nombre: %s\n", persona.profesor.nombre);
    printf("Asignaturas que imparte: %s, %s, %s\n",
           persona.profesor.asignaturas[0],
           persona.profesor.asignaturas[1],
           persona.profesor.asignaturas[2]);
    printf("Dirección: %s\n", persona.profesor.direccion);

    return 0;
}
