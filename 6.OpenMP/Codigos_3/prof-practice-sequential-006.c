/* Copyright (C) 2022 Raul Torres raultorrescarvajal@gmail.com */

#include <stdio.h>
// pista: se debe incluir una cabecera que permita
// enlazar las funciones del runtime

int main(){
    /* usa tareas para calcular C como la suma de los vectores A y B,
       y luego suma todos los elementos de C.
       (- establece un número mínimo de 3 iteraciones del bucle 
          por cada tarea generada.
        - imprime en pantalla el número de hilo con cada resultado) */

    // pista: las siguientes variables pueden accederse 
    // desde cualquier hilo
    int A[16]= {0 , 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15};
    int B[16]= {15,14,13,12,11,10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    int C[16]= {};

    // pista: esta variable acumula el valor de la operación +
    // en cada iteración
    int total=0;

    // pista: podemos usar una directiva que cree un tarea
    // por cada iteración del bucle y así
    // paralelizarlo sin escribir mucho código
    for(int i=0;i<16;i++){
        C[i] = A[i] + B[i];
        printf("C[%d]=%d\n", i, C[i]);
        total += C[i];
    }

    printf("total=%d\n", total);
}
