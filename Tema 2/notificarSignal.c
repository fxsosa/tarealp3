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
    printf("Id proceso:%d\n", getpid());
    detectarSignal();
    printf("Id proceso:%d\n", getpid());
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
