#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
int longitudArray;
int numeroProcesos;
int nivelesArbol;

int contarElementos(char *arrayArgv);
void parsearArray(char **arrayArgv, int *arrayNumerico);

void mergeSort(int array[]);
void sortSubArray(int array[], int low, int high, int nivelActual);
void merge(int array[], int left, int middle1, int middle2, int right);

void imprimirArray(int array[], int inicio, int fin);
void imprimirArbol(int array[]);
