#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

#include <time.h>

//time_t startExec;

int main(void){
    //lineas de prueba
    //startExec = time(NULL);// anota el segundo cuando se inicio el programa

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
                //lineas de prueba
                //time_t startsig;
                //startsig = time(NULL);

                //enviar señal
                //kill(atoi(procesoId), atoi(signal));
                //lineas de prueba
                printf("proceso: %s signal: %s delay calculado: ld\n", procesoId, signal/*,startsig - startExec*/ );
                exit(0);
            }
            fscanf(ptrFile, "%s", procesoId);
        }while(!feof(ptrFile));
    }
    return 0;
}
