#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

int main(void){
    time_t tiempoInicio, tiempoActual;
    tiempoInicio = time(NULL);
    printf("Leyendo el archivo de procesos...\n");
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
            if(child == 0){
                //imprimesignal
                //efectuar el delay
                sleep(atoi(delay));
                int signalInt = atoi(signal);
                if(signalInt > 0 && signalInt <= 62){ //si esta dentro del rango
                    tiempoActual = time(NULL);
                    printf("Intentando enviar la señal %s al proceso %s \n", signal, procesoId );
                    if(signalInt == 9){
                        printf("Se mando la senal SIGKILL al proceso %s, en %ld segundos\n", procesoId, tiempoActual - tiempoInicio);
                        kill(atoi(procesoId), signalInt);
                        exit(0);
                    }
                    else if(signalInt == 19){
                        printf("Se mando la senal SIGSTOP al proceso %s, en %ld segundos\n", procesoId, tiempoActual - tiempoInicio);
                        kill(atoi(procesoId), signalInt);
                        kill(atoi(procesoId), 9); // para que el proceso pueda continuar
                        exit(0);
                    }
                    else if (kill(atoi(procesoId), signalInt)) {
                        printf("El proceso con pid:%s no se ha encontrado\n",procesoId);
                        exit(0);
                    }
                    printf("Segundos transcurridos desde la ejecucion del enviador de senhal: %ld\n", tiempoActual - tiempoInicio);
                }else{
                    printf("Senal no valida\n");
                    exit(0);
                }
                //enviar señal
                exit(0);
            }
            else if(child < 0){
                perror("Error en el fork");
                exit(-1);
            }
            fscanf(ptrFile, "%s", procesoId);
        }while(!feof(ptrFile));
    }
    return 0;
}
