#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

int main(void){

    //se abre el archivo
    FILE *ptrFile = fopen("procesos.txt", "r");

    //pId para guiar a los procesos
    pid_t child;

    //contenedores de los procesos, señales, y delays
    char procesoId[ 10 ], signal[ 10 ] , delay [ 10 ];

    //si se logra abrir el archivo...
    if(ptrFile == NULL){
        fputs("File error", stderr);
        exit(1);
    }
    else{
        //lectura del procesoId
        fscanf(ptrFile, "%s", procesoId);
        do{
            //lectura de la señal
            fscanf(ptrFile, "%s", signal);
            //lectura del delay
            fscanf(ptrFile, "%s", delay);
            //creacion del hijo
            child = fork();
            //si es el hijo entonces ejecutar lo sgte
            if( child ){
                //imprimesignal
                //efectuar el delay
                sleep(atoi(delay));

                //enviar señal
                kill(atoi(procesoId), atoi(signal));
                //lineas de prueba
                printf("Enviando señal %s al proceso %s ", signal, procesoId /*,startsig - startExec*/ );
                exit(0);
            }
            fscanf(ptrFile, "%s", procesoId);
        }while(!feof(ptrFile));
    }
    return 0;
}
