#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

void detectarSignal();

int main(void){
    int status = 0;
    int cantidadProcesos = 0;
    int signal, delay;
    FILE *ptrArchivo;
    pid_t child = 1;

    ptrArchivo = fopen("procesos.txt", "w+");

    printf("Insertar cantidad de procesos a crear:\n");
    scanf("%d", &cantidadProcesos);

    for(int i = 0; i < cantidadProcesos; i++){
        child = fork();
        if(child == 0){
            detectarSignal();
            exit(0);
        }
        else if(child < 0){
            perror("Error en el fork");
            exit(-1);
        }
        else{
            printf("Proceso numero %d, ingrese la senhal y el delay\n", i + 1);
            scanf("%d", &signal);
            scanf("%d", &delay);
            fprintf(ptrArchivo, "%d\t%d\t%d\n", child, signal, delay);
        }
    }
    fclose(ptrArchivo);
    child = fork();
    if(child == 0){
        char *args[]={"./enviarSignal",NULL};
        execv(args[0],args);
        exit(0);
    }
    else if(child < 0){
        perror("Error en el fork");
        exit(-1);
    }

    while (( wait(&status)) > 0);
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
        fprintf(stdout, "se recibio la signal #%d\n", signalNbr);
    }
}
