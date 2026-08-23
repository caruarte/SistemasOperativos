#include <stdio.h> // printf()
#include <stdlib.h> //exit()
#include <unistd.h> // fork() pipe() write() read()
#include <sys/wait.h>

int main(){
// Comienza siendo Abraham
printf("Abraham\n");

pid_t homero = fork();   // Abraham crea a Homero

if (homero == 0) {
    // Soy Homero
    printf("Homero\n");

    pid_t bart = fork();      // Homero crea a Bart
    if (bart == 0) {
        printf("Bart\n");
        exit(EXIT_SUCCESS);            // Bart termina aquí — no hace más forks, 
    }                       // si lo saco, entonces dos procesos van a ejecutar lo que sigue

    pid_t lisa = fork();      // Homero crea a Lisa
    if (lisa == 0) {
        printf("Lisa\n");
        exit(EXIT_SUCCESS);            // Lisa termina aquí
    }

    pid_t maggie = fork();    // Homero crea a Maggie
    if (maggie == 0) {
        printf("Maggie\n");
        exit(EXIT_SUCCESS);            // Maggie termina aquí
    }

    exit(EXIT_SUCCESS);                // Homero termina
}

exit(EXIT_SUCCESS);                    // Abraham termina
}