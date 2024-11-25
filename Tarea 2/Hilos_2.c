/*
Autor: Alberto J. Calderón Z
CI: 24198092
Trabajo para la materia de Sistemas Operativos

Programa en C que usa la biblioteca <pthread.h> para realizar la ejecuccion multi hilos de varias tareas
En total son 4 hilos con una variable global compartida
Cada hilo con una tarea diferente
Se utiliza un mutex para proteger el dato compartido en cada tarea. 
*/

#include <stdio.h>
#include <pthread.h>

// Variable compartida
int contador_general = 0;
pthread_mutex_t mutex;

/*
Se procede a definir 4 funciones, donde cada uno es la tarea que ejecutaria un hilo. 
*/

// Tarea del primer hilo 
void* tarea1(void* arg) {
    pthread_mutex_lock(&mutex); // Bloquea el acceso a la variable compartida
    contador_general++;
    pthread_mutex_unlock(&mutex); // Libera el acceso a la variable compartida
    printf("Hilo 1 ejecutando, Contador General %d\n",contador_general);
    pthread_exit(NULL);
}

// Función para el segundo hilo (suma iteraciones)
void* tarea2(void* arg) {
    pthread_mutex_lock(&mutex); 
    contador_general++;
    pthread_mutex_unlock(&mutex); 
    int suma = 0;
    for (int i = 0; i < 10; i++) {
        suma += i;
    }
    printf("Hilo 2 Ejecutando: La suma es %d\n", suma);
    printf("Hilo 2 Ejecutando: Contador General %d\n", contador_general);
    pthread_exit(NULL);
}

// Función para el tercer hilo (incrementa contador general)
void* tarea3(void* arg) {
    for (int i = 0; i < 5; ++i) {
        pthread_mutex_lock(&mutex); 
        contador_general++;
        pthread_mutex_unlock(&mutex); 
    }
    printf("Hilo 3 Ejecutando: Aumente Contador general mas que mis hermanos= %d\n", contador_general);
    pthread_exit(NULL);
}

// Función para el cuarto hilo (imprime un mensaje diferente)
void* tarea4(void* arg) {
    pthread_mutex_lock(&mutex); 
    contador_general++;
    pthread_mutex_unlock(&mutex); 
    printf("Hilo 4 Ejecutando: Soy el ultimo y no se me ocurrio que hacer, El contador general es: %d\n", contador_general);
    pthread_exit(NULL);
}

int main() {

    pthread_t hilos[4]; // Se crea un arreglo que guardara los 4 hilos 
    printf("Valor Inicial de la variable compartida: %d\n", contador_general);

    // Se inicializa el mutex
    pthread_mutex_init(&mutex, NULL);

    // Creacion de los hilos , se inician individualmente ya que cada hilo tiene distintas tareas. 
    pthread_create(&hilos[0], NULL, tarea1, NULL);
    pthread_create(&hilos[1], NULL, tarea2, NULL);
    pthread_create(&hilos[2], NULL, tarea3, NULL);
    pthread_create(&hilos[3], NULL, tarea4, NULL);

    // Ejercucion de los 4 hilos por medio del recorrido en el arreglo.
    for (int i = 0; i < 4; i++) {
        pthread_join(hilos[i], NULL);
    }

    // Destruye el mutex
    pthread_mutex_destroy(&mutex);

    printf("Valor final del la variable compartida: %d\n", contador_general);
    

    return 0;
}