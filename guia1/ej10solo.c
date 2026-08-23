#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    printf("Soy Juan\n");
    pid_t julieta = fork();

    if(julieta == 0){
        printf("Soy Julieta\n");
        sleep(1);
        pid_t jennifer = fork();
        if (jennifer == 0){
            printf("Soy Jennifer\n");
            sleep(1);
            exit(0);
        }
        exit(0);
    }

    sleep(1);
    waitpid(-1, NULL, 0);
    pid_t jorge = fork();
    if(jorge == 0){
        printf("Soy Jorge\n");
        sleep(1);
        exit(0);
    }
    exit(0);


}