#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    // 10551 = Juan (proceso original)
    printf("Soy Juan\n");

    pid_t julieta = fork();     // nace 10552

    if (julieta == 0) {
        // Soy Julieta (10552)
        printf("Soy Julieta\n");
        sleep(1);

        pid_t jennifer = fork(); // nace 10557

        if (jennifer == 0) {
            // Soy Jennifer (10557)
            printf("Soy Jennifer\n");
            sleep(1);
            exit(0);
        }

        exit(0);    // Julieta termina sin esperar a Jennifer
    }

    // Juan espera a que Julieta termine
    waitpid(-1, NULL, 0);  // wait4 en el strace

    pid_t jorge = fork();       // nace 10558

    if (jorge == 0) {
        // Soy Jorge (10558)
        printf("Soy Jorge\n");
        sleep(1);
        exit(0);
    }

    exit(0);    // Juan termina sin esperar a Jorge
}