
#include <stdio.h>
#include <stdlib.h>
int main()
{
  int c,j,i;
  c=0,j=0,i=0;
  char buffer[15];
  FILE *puntero;
  puntero = fopen ( "procesos.txt", "r" );


  //********************************Lectura de archivo y carga de la matriz****************************************
  if (puntero==NULL){//bloque de control de error
    fputs ("File error",stderr);
    exit (1);
  }
  else{
      while (!feof(puntero)){//Mientras no alcancemos el EndOfLine del archivo...
        fscanf(puntero, "%s" ,buffer );
        c++;//contador de lineas de archivo
      } 
      puntero = fopen ( "procesos.txt", "r" );
      c=c/3;
      j=0;
      i=0;

      int matfich[c][3];//definicion de la matriz de carga

      while (!feof(puntero)){//Mientras no alcancemos el EndOfLine del archivo...
        fscanf(puntero, "%s" ,buffer );//lectura de cada palabra del archivo
        matfich[i][j]= 0;//eliminamos cualquier basura de la matriz
        matfich[i][j]= atoi(buffer);//cargamos en la matriz la palabra leida, convirtiendo a int

        if(j<2)//cambiamos los indices de la matriz
        {
          j++;
        }else{
          j=0;
          i++;
        }
      }
      for(i=0;i<c;i++)//impresion de la matriz cargada
      {
        for(j=0;j<3;j++)
        {
          printf("\n");
          printf("\nEl valor de i es   %i , y el valor de j es   %i\n", i, j );
          printf("\n");
          printf("\nLa matriz tiene el valor de:  %i\n", matfich[i][j]);
          printf("\n");
        }
      }   

//******************************ORDENAMIENTO DE LA MATRIZ******************************************************* 
  int vec[3];
  int n;
  for (i=0; i<c-1; i++)
  {
    for (j=i+1; j<3; j++)
    {
      if(matfich[i][2]>matfich[j][2])
      {
        for(n=0;n<3;n++)
        {
          vec[n]=matfich[i][n];
        }
        for(n=0;n<3;n++)
        {
          matfich[i][n]=matfich[j][n];
        }
        for(n=0;n<3;n++)
        {
          matfich[j][n]=vec[n];
        }
      }
    }
  }
  printf("\nLa matriz ordenada es: \n");
  for(i=0;i<c;i++)
  {
    printf("\n");
    for(j=0;j<3;j++)
    {
      printf("%i", matfich[i][j]);
      printf(" ");
    }
  }  

}
  fclose(puntero);
  return 0;
}
