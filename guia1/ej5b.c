#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {

    // Soy Abraham
    printf("Abraham\n");

    pid_t homero = fork();        // Abraham crea a Homero

    if (homero == 0) {
        // Soy Homero
        printf("Homero\n");

        pid_t bart = fork();
        if (bart == 0) {
            printf("Bart\n");
            exit(0);
        }

        pid_t lisa = fork();
        if (lisa == 0) {
            printf("Lisa\n");
            exit(0);
        }

        pid_t maggie = fork();
        if (maggie == 0) {
            printf("Maggie\n");
            exit(0);
        }

        // Homero espera a sus tres hijos
        waitpid(bart,   NULL, 0);
        waitpid(lisa,   NULL, 0);
        waitpid(maggie, NULL, 0);

        exit(0);    // Homero termina después que sus hijos
    }

    // Abraham espera a Homero
    waitpid(homero, NULL, 0);

    exit(0);        // Abraham termina último
}