#include <stdio.h>

int main()
{
    int mat[3][3]={{2,0,-78},{4,5,97},{2,20,0}};
    int f, j ,i,n;
    int vec[3];
    for (i=0; i<3-1; i++)
    {
        for (j=i+1; j<3; j++)
        {
           
            if(mat[i][2]>mat[j][2])
            {
                printf("\nEL PRIMERO FUE MAYOR\n");
                for(n=0;n<3;n++)
                {
                    vec[n]=mat[i][n];
                }
                for(n=0;n<3;n++)
                {
                    mat[i][n]=mat[j][n];
                }
                for(n=0;n<3;n++)
                {
                    mat[j][n]=vec[n];
                }
               
            }
        }
    }
   printf("\nLa matriz ordenada es: \n");
   for(i=0;i<3;i++)
    {
        printf("\n");
        for(j=0;j<3;j++)
        {
            printf("%i", mat[i][j]);
            printf(" ");
        }
    }  
}