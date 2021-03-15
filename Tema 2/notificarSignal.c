#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
void detectarSignal();
int main(void){
    pid_t proceso1, proceso2, proceso3;

    proceso1 = fork();
    if(proceso1){
        printf("pid: %d",getpid());
        detectarSignal();
        exit(0);
    }
    proceso2 = fork();
    if(proceso2){
        printf("pid: %d",getpid());
        detectarSignal();
        exit(0);
    }
    proceso3 = fork();
    if(proceso3){
        printf("pid: %d",getpid());
        detectarSignal();
        exit(0);
    }
        int status;

        // Esperando por los hijos izquierdo y derecho del nodo actual o proceso padre actual
        waitpid(proceso1, &status, 0);
        waitpid(proceso2, &status, 0);
        waitpid(proceso3, &status, 0);
    return 0;
}
void detectarSignal(){
    //conjunto de señales
    sigset_t mySet;

    //se llena con todas las señales posibles
    sigfillset(&mySet);
    //se asigna a la mascara y se bloquea todas las señales
    sigprocmask(SIG_BLOCK, &mySet, NULL);
    //Nbr de la señal
    int signalNbr;
    //espera de la señal
    sigwait(&mySet, &signalNbr);
    //si hubo un error entonces
    if (signalNbr == -1) {
        perror("Failed to wait using sigwait");
        return;
    } // End if
    else{
        fprintf(stderr, "se recibio la signal #%d\n", signalNbr);
    }
}
