#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
// sin waitpid, Abraham terminaría antes que Homero

pid_t homero = fork();        // Abraham crea a Homero
if (homero == 0) {
    sleep(2);          // Homero tarda 2 segundos
    printf("Homero\n");
    exit(0);
}
waitpid(homero, NULL, 0); // espera a que termine homero para printear abraham
printf("Abraham\n");
exit(0);    // Abraham termina instantáneo, sin esperar
}