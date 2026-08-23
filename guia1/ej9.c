#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h> // señales
#include <sys/wait.h>

// Flag volátil: se activa cuando llega SIGUSR1
int señal_recibida = 0;

void handler(int sig) {
    señal_recibida = 1;
}

// Espera activa hasta que llegue la señal
void esperar_señal() {
    while (!señal_recibida); // espera a que señal recibida sea 1
    señal_recibida = 0; // lo vuelve a poner en 0
}

int main() {
    // Registrar el handler para ambos procesos antes del fork
    signal(SIGUSR1, handler);

    pid_t hijo = fork();
    if (hijo == -1) exit(EXIT_FAILURE);

    if (hijo == 0) {
        // ── HIJO ──────────────────────────────────────
        pid_t padre = getppid();

        while (1) {
            esperar_señal();                        // espera ping del padre
            printf("pong %d\n", getpid());
            kill(padre, SIGUSR1);                   // avisa al padre
        }

    } else {
        // ── PADRE ─────────────────────────────────────
        char respuesta[10];

        while (1) {
            // 3 rondas de ping-pong
            for (int i = 0; i < 3; i++) {
                printf("ping %d\n", getpid());
                kill(hijo, SIGUSR1);                // avisa al hijo
                esperar_señal();                    // espera pong del hijo
            }

            // Preguntar al usuario
            printf("¿Querés finalizar? (si/xno): ");
            scanf("%s", respuesta);

            if (respuesta[0] == 's') {
                kill(hijo, SIGKILL);                // termina al hijo, no se elimina su entrada en tabla de procesos
                waitpid(hijo, NULL, 0);             // recoge al hijo
                printf("Finalizando.\n");
                exit(EXIT_SUCCESS);
            }
            // si responde "no", el while vuelve a empezar
        }
    }
}