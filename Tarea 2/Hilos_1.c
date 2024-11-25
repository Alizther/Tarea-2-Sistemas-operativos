/*
Autor: Alberto J. Calderón Z
CI: 24198092
Trabajo para la materia de Sistemas Operativos

Programa en C que utiliza la llamada al sistema fork() para crear un nuevo proceso hijo. 
El proceso padre se enfoca en Sumar el acumulado de ejecuciones empezando en 0. 
El proceso Hijo se enfoca en Imprimir un mensaje. 

*/

#include <stdio.h>
#include <unistd.h>

int main() {

    int aux= 0; 

    pid_t pid = fork();

    if (pid < 0) {
        // Arroja un mensaje de error, si hay algun problema al crear el proceso hijo. 
        perror("Error al crear el proceso hijo con fork");
        return 1;
    } else if (pid == 0) {
        // Proceso hijo
        printf("Soy el proceso hijo con PID: %d\n", getpid());
        // Tarea del proceso hijo
        for (int i = 0; i < 10; i++) {
            printf("Hola papa soy tu hijo estoy imprimiendo por vez numero:  %d\n", i+1);
            sleep(1); // 
        }
    } else {
        // Proceso padre 
        printf("Soy el proceso padre con PID: %d y mi hijo tiene PID: %d\n", getpid(), pid);
        // Tarea del proceso padre
        for (int i = 0; i < 10; i++) {
            aux = aux+i;
            printf("Padre: Iteración %d\n", i+1);
            printf("Resultado Suma: %d\n", aux);
            sleep(1); // Simular trabajo
        }
    }
    return 0;
}