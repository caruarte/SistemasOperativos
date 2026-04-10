#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


void system(const char *arg) { //system(cmd) ejecuta un comando en un proceso hijo y espera a que termine antes de retornar al proceso padre. El proceso padre sigue vivo durante todo ese tiempo.
//Entonces la implementación es simplemente: fork + exec + waitpid.

    pid_t hijo = fork();        // crear proceso hijo

    if (hijo == 0) {
        // Soy el hijo — reemplazo mi programa por el comando
        exec(arg);

        // Si exec() falla, el hijo termina con error
        // (si exec tiene éxito, esta línea nunca se ejecuta)
        exit(1);
    }

    // Soy el padre — espero a que el hijo termine
    waitpid(hijo, NULL, 0);
    exit(0)

    // Cuando waitpid retorna, el hijo ya terminó
    // y system() retorna al llamador
}