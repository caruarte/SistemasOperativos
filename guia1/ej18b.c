#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

enum {READ, WRITE};

void handler1(){

}

void handler2(){

}

int main(){
    int fd[2];
    pipe(fd);
    pid_t hijo = fork();
    if (hijo == 0){
        close(fd[READ]);
        getppid();
        signal(SIGINT, handler1);
        signal(SIGHUP, handler2);
    }

    
    
}