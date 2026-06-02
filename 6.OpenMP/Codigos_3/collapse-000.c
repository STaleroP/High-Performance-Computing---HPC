/* Copyright (C) 2022 Raul Torres raultorrescarvajal@gmail.com */

#include <stdio.h>
#include <omp.h>

int main(){
    int m = omp_get_thread_num();
    printf("master thread=%d in serial region\n", m);
    
    #pragma omp parallel for collapse(2) schedule(static,2)
    for(int i=0; i<4 ; i++){
        for(int j=0; j<4 ; j++){
            int f = omp_get_thread_num();
            printf("i,j=%d,%d processed by thread=%d\n", i, j, f);
        }
    } // implicit barrier here
    
    printf("master thread=%d in serial region\n", m);
}