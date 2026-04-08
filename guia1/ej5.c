#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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
        exit(0);            // Bart termina aquí — no hace más forks, 
    }                       // si lo saco, entonces dos procesos van a ejecutar lo que sigue

    pid_t lisa = fork();      // Homero crea a Lisa
    if (lisa == 0) {
        printf("Lisa\n");
        exit(0);            // Lisa termina aquí
    }

    pid_t maggie = fork();    // Homero crea a Maggie
    if (maggie == 0) {
        printf("Maggie\n");
        exit(0);            // Maggie termina aquí
    }

    exit(0);                // Homero termina
}

exit(0);                    // Abraham termina
}