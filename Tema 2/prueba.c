#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include <time.h>

time_t startExec;

int main(void){
    startExec = time(NULL);// anota el segundo cuando se inicio el programa

    FILE *ptrFile = fopen("procesos.txt", "r");

    pid_t child; //Id para guiar a los procesos
    char procesoId[ 10 ], signal[ 10 ] , delay [ 10 ];
    if(ptrFile == NULL){
        fputs("File error", stderr);
        exit(1);
    }
    else{
        fscanf(ptrFile, "%s", procesoId);
        do{
            fscanf(ptrFile, "%s", signal);
            fscanf(ptrFile, "%s", delay);
            child = fork();
            if( child ){
                //imprimesignal
                sleep(atoi(delay));
                time_t startsig;
                startsig = time(NULL);
                printf("proceso: %s signal: %s delay calculado: %ld\n", procesoId, signal, startsig - startExec);
                exit(0);
            }
            fscanf(ptrFile, "%s", procesoId);
        }while(!feof(ptrFile));
    }

    return 0;
}
