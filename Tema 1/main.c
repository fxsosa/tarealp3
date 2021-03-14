#include "head.h"

int main(int argc, char **argv){
    //variables de memoria compartida
    int shmid;
    key_t key = IPC_PRIVATE;

    //array numerico que apuntara a la memoria compartida
    int *arrayNumerico;

    //Se calcula la longitud del array numerico con el segundo argumento de ejecucion
    longitudArray = contarElementos(argv[ 2 ]);
    //variable que contendra la cantidad de procesos
    numeroProcesos = atoi( argv[ 1 ] );
    //Calculo para obtener la cantidad de niveles que tendra a partir del numero de procesos(nodos)
    nivelesArbol = log( numeroProcesos + 1 ) / log( 2 );

    //Memoria compartida para almacenar el array y compartir entre procesos, tiene un tamaño igual a la longitud del array mas los niveles del
    //arbol, ese plus se le asigna para coordinar los procesos
    size_t SHM_SIZE = (longitudArray + nivelesArbol) * sizeof( int );

    //Crea el segmento de memoria
    if ((shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666)) < 0)
    {
        perror("shmget");
        _exit(1);
    }

    // asigna a la variable el segmento de memoria
    if ((arrayNumerico = shmat(shmid, NULL, 0)) == (int *) -1)
    {
        perror("shmat");
        _exit(1);
    }
    //funcion para cargar los numeros ingresados al array
    parsearArray(argv, arrayNumerico);

    //ordenacion
    mergeSort(arrayNumerico);

    //imprime el array ordenado
    imprimirArray(arrayNumerico, 0, longitudArray - 1);

    //elimina la memoria
    if (shmdt(arrayNumerico) == -1)
    {
        perror("shmdt");
        _exit(1);
    }

    if (shmctl(shmid, IPC_RMID, NULL) == -1)
    {
        perror("shmctl");
        _exit(1);
    }
    printf("\n");
    return 0;
}
