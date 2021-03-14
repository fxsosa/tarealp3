#include "head.h"

//conteo de elementos
int contarElementos(char *arrayArgv){
    int i = 0;
    int elementos = 0;

    while(arrayArgv[ i ] != '\0'){
        if(arrayArgv[ i ] == ','){
            elementos++;
        }
        i++;
    }
    return elementos + 1;
}
//Parsea los valores del string para convertirlo en un array numerico
void parsearArray(char **arrayArgv, int *arrayNumerico){
    const char delimitador[2] = ",";
    char *token = strtok( arrayArgv[ 2 ], delimitador );

    for( int i = 0; i < longitudArray; i++ ){
        arrayNumerico[ i ] = atoi(token);
        token = strtok(NULL, delimitador);
    }
}

//Impresion normal de un array
void imprimirArray(int array[], int inicio, int fin){
    for(int i = inicio; i <= fin; i++){
        printf("%d ", array[ i ]);
    }
    printf("\n");
}

// unir 2 subarrays ordenados en un solo array ordenado
void merge(int array[], int left, int middle1, int middle2, int right)
{
    int leftIndex = left; // indice del array de la izquierda
    int rightIndex = middle2; // indice del array de la derecha
    int combinedIndex = left; // indice del array temporal
    int tempArray[longitudArray]; // temporary array
    // output two subarrays before merging
    // merge the subarrays until the end of one is reached
    while (leftIndex <= middle1 && rightIndex <= right) {
    // place the smaller of the two current elements in result
    // and move to the next space in the subarray
        if (array[leftIndex] <= array[rightIndex]) {
            tempArray[combinedIndex++] = array[leftIndex++];
        }
        else {
            tempArray[combinedIndex++] = array[rightIndex++];
        }
    }
    if (leftIndex == middle2) { // if at end of left subarray ...
        while (rightIndex <= right) { // copy the right subarray
            tempArray[combinedIndex++] = array[rightIndex++];
        }
    }
    else { // if at end of right subarray...
        while (leftIndex <= middle1) { // copy the left subarray
            tempArray[combinedIndex++] = array[leftIndex++];
        }
    }
    // copy values back into original array
    for (int i = left; i <= right; i++) {
        array[i] = tempArray[i];
    }
    // output merged subarray
}
// funcion que recibe el array a ordenar, el indice bajo, alto y el nivelActual respectivo del arbol
void sortSubArray(int array[], int low, int high, int nivelActual)
{
    // caso base si el array tiene una longitud de 1
    if ((high - low) >= 1) {
        int middle1 = (low + high) / 2;
        int middle2 = middle1 + 1;

        //si el nivel actual del arbol de procesos es mayor que su nivel impuesto por la cantidad de nodos
        //ordenacion normal del merge, sin procesos
        if( nivelActual + 1 > nivelesArbol ){
            sortSubArray(array, low, middle1, 0);
            sortSubArray(array, middle2, high, 0);

            merge(array, low, middle1, middle2, high);
            return;
        }
        // impresion de comprobacion
        //imprimirArray(array, longitudArray, longitudArray + nivelesArbol - 1);

        // variables que contendran los pid de los hijos izquierdo y derecho
        pid_t lpid,rpid;

        //creacion del proceso hijo izquierdo
        lpid = fork();
        if (lpid<0)
        {
            //Si el hijo no se creo...
            perror("Left Child Proc. not created\n");
            _exit(-1);
        }
        else if (lpid==0)
        {
            //si el lpid es 0, corresponde al hijo izquierdo, por ende el hijo izquierdo pasa a ejecutar lo siguiente
            //Aumenta la cantidad de nodos en el nivel respectivo
            array[ longitudArray + nivelActual ]++;

            //mientras la cantidad de nodos no sea la maxima, el proceso queda ejecutando este bucle, retrasando la creacion
            //de sus procesos hijos
            while( array[ longitudArray + nivelActual ] < pow(2, nivelActual));

            //Una vez que todos los procesos hijos correspondientes al nivel fueron creados, entonces
            sortSubArray(array, low, middle1, nivelActual + 1); // first half

            // terminar el proceso
            _exit(0);
        }
        else
        {
            //impresion de comprobacion
            //imprimirArray(array, longitudArray, longitudArray + nivelesArbol - 1);

            //creacion del nodo hijo derecho
            rpid = fork();
            if (rpid<0)
            {
                // si retorno negativo el fork, entonces no se creo el hijo derecho
                perror("Right Child Proc. not created\n");
                _exit(-1);
            }
            else if(rpid==0)
            {
                //si el rpid es 0, corresponde al proceso hijo derecho, por ende pasa a ejecutar lo siguiente
                //Aumentamos la cantidad de nodos de su nivel respectivo
                array[ longitudArray + nivelActual ]++;
                //mientras que la cantidad de nodos en ese nivel no llegue al maximo, seguir el bucle
                while( array[ longitudArray + nivelActual ] < pow(2, nivelActual));
                //una vez que haya alcanzado la cantidad maxima de hijos en el nivel, ejecutar lo siguiente
                sortSubArray(array, middle2, high, nivelActual + 1);
                //terminacion del proceso
                _exit(0);
            }
        }

        int status;

        // Esperando por los hijos izquierdo y derecho del nodo actual o proceso padre actual
        waitpid(lpid, &status, 0);
        waitpid(rpid, &status, 0);

        //union de los resultados de cada hijo
        merge(array, low, middle1, middle2, high);
    }
}
void mergeSort(int array[])
{
    //impresion de prueba
    //imprimirArray(array, 0, longitudArray - 1);
    //primera llamada a la ordenacion, se le pasa el array, su indice maximo y el nivel correspondiente al siguiente
    sortSubArray(array, 0, longitudArray - 1, 1);
}
