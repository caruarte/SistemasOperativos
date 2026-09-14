#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

// Constants 0 and 1 for READ and WRITE
enum { READ, WRITE };

void cerrarpipes(int fd[3][2], int id){
    for (int i = 0; i < 3; i++){
        if (id == i){
            close(fd[i][READ]);      
        } else if (i == (id+2)%3){
            close(fd[i][WRITE]);
        } else {
            close(fd[i][READ]);    
            close(fd[i][WRITE]);    
        }
    }
}

int ejecutarhijo1(int fd[3][2]){
    int valor = 0;
    while(valor <= 50){
		read(fd[0][READ],&valor,sizeof(int));
        if (valor >= 50){
            write(fd[1][WRITE], &valor, sizeof(int));
            break;
        }
        valor += 1;
		printf("Hijo 1 envia Hijo 2 el valor %d\n", valor);
		fflush(stdout);
		write(fd[1][WRITE], &valor, sizeof(int));
    }
    close(fd[0][READ]);
    close(fd[1][WRITE]);
	exit(EXIT_SUCCESS);
}

int ejecutarhijo2(int fd[3][2]){
    int valor = 0;
    while(valor <= 50){
		read(fd[1][READ],&valor,sizeof(int));
        if (valor >=50 ){
            write(fd[2][WRITE], &valor, sizeof(int));
            break;
        }
        valor += 1;
		printf("Hijo 2 envia Padre el valor %d\n", valor);
		fflush(stdout);
		write(fd[2][WRITE], &valor, sizeof(int));
    }
    close(fd[1][READ]);
    close(fd[2][WRITE]);
	exit(EXIT_SUCCESS);
}

int main(){

    int fd[3][2];
    pipe(fd[0]);
    pipe(fd[1]);
    pipe(fd[2]);

    pid_t hijo1 = fork();
    if (hijo1 == 0){
        cerrarpipes(fd, 1);
        ejecutarhijo1(fd);
    }
    pid_t hijo2 = fork();
    if (hijo2 == 0){
        cerrarpipes(fd,2);
        ejecutarhijo2(fd);
    }

    int valor = 0;
    cerrarpipes(fd, 0);

    printf("Padre envia Hijo 1 el valor %d\n", valor);
    fflush(stdout);
	write(fd[0][WRITE], &valor, sizeof(int));
    

    while(valor <= 50){

		read(fd[2][READ],&valor,sizeof(int));
        if (valor >= 50){
            write(fd[0][WRITE], &valor, sizeof(int));
            break;
        }
        valor += 1;
		printf("Padre envia Hijo 1 el valor %d\n", valor);
		fflush(stdout);
		write(fd[0][WRITE], &valor, sizeof(int));
    }
    waitpid(hijo1, NULL, 0);
    waitpid(hijo2, NULL, 0);

    close(fd[2][READ]);
    close(fd[0][WRITE]);
    exit(EXIT_SUCCESS);
}

