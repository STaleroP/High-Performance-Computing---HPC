/* Copyright (C) 2022 Raul Torres raultorrescarvajal@gmail.com */

#include <stdio.h>
// pista: se debe incluir una cabecera que permita
// enlazar las funciones del runtime

int main(){
    /* calcula C como la resta de las matrices A y B más un offset.
       (- distribuye las iteraciones del bucle en bloques de 
          5 elementos de manera estática
        - imprime en pantalla el número de hilo con cada resultado) */

    // pista: las siguientes variables pueden accederse 
    // desde cualquier hilo
    int A[4][4]= { {0 , 1, 2, 3},{ 4, 5, 6, 7},{8, 9,10,11},{12,13,14,15} };
    int B[4][4]= { {15,14,13,12},{11,10, 9, 8},{7, 6, 5, 4},{ 3, 2, 1, 0} };
    int C[4][4]= { {},{},{},{} };

    // pista: cada iteración debe tener su propia copia de offset
    int offset=33;

    // pista: debemos imprimir el valor de thisOffset de la última iteración
    int thisOffset=0;

    // pista: podemos usar una directiva con una cláusula que paraleliza 
    // ambos bucles como si fueran uno solo
    for(int i=0;i<4;i++){
    	for(int j=0;j<4;j++){
            thisOffset = offset * (i*4 + j);  
            C[i][j] = A[i][j] - B[i][j] + thisOffset;
            printf("C[%d][%d]=%d, thisOffset=%d\n", i, j, C[i][j], thisOffset);
            }
    }

    printf("thisOffset=%d\n", thisOffset);
}
