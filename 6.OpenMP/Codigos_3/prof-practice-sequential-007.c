/* Copyright (C) 2022 Raul Torres raultorrescarvajal@gmail.com */

#include <stdio.h>
// pista: se debe incluir una cabecera que permite enlazar las funciones del runtime

int max(int a, int b){
    return a >= b ? a : b;
}

int main(){
    /* determina el número máximo comparando entre pares de números 
       (imprime en pantalla el número de hilo con cada resultado) */

    // pista: las siguientes variables son de solo lectura
    int a=40, b=20, c=30, d=50;
    int w=25, x=73, y=99, z=5;

    // pista: las siguientes variables se escriben y se leen una sola vez 
    int max_0=0, max_1=0, max_2=0, max_3=0, max_4=0, max_5=0;
    
    // pista: la siguiente variable solo se escribe una sola vez
    int final_max=0;
    
    // pista: las siguientes 2 líneas son independientes entre sí
    max_0 = max(a, b); printf("max_0=%d\n", max_0);
    max_1 = max(c, d); printf("max_1=%d\n", max_1);
    
    // pista: la siguiente línea depende de los dos resultados anteriores
    max_4 = max(max_0, max_1); printf("max_4=%d\n", max_4);
    
    // pista: las siguientes 2 líneas son independientes entre sí,
    // y también lo son de las anteriores 3 operaciones con máximos 
    max_2 = max(w, x); printf("max_2=%d\n", max_2);
    max_3 = max(y, z); printf("max_3=%d\n", max_3);

    // pista: la siguiente línea depende de los dos resultados anteriores
    max_5 = max(max_2, max_3); printf("max_5=%d\n", max_5);

    // pista: la siguiente línea depende de dos máximos anteriores
    final_max = max(max_4, max_5); printf("final_max_6=%d\n", final_max);
}
