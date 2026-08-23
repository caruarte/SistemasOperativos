#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t julieta = fork();

    if (julieta == 0){
        // Soy Julieta
        printf("Soy Julieta\n");
        sleep(1);
        pid_t jennifer = fork();
        if (jennifer == 0){
            // soy jennifer
            printf("Soy Jennifer\n");
            sleep(1);
            exit(EXIT_SUCCESS);
        }
        exit(EXIT_SUCCESS);
    }

    printf("Soy Juan\n");
    sleep(1);
    wait(NULL);

    pid_t jorge = fork();
    if (jorge == 0){
        // Soy Jorge
        printf("Soy Jorge\n");
        sleep(1);
        exit(EXIT_SUCCESS);
    }
    exit(EXIT_SUCCESS);

}