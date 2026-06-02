/* Copyright (C) 2022 Raul Torres raultorrescarvajal@gmail.com */

#include <stdio.h>
#include <omp.h>

int main(){
    int m = omp_get_thread_num();
    printf("master thread=%d in serial region\n", m);
    
    #pragma omp parallel for schedule(static,2)
    for(int i=0; i<16 ; i++){
        int f = omp_get_thread_num();
        printf("i=%d processed by thread=%d\n", i, f);
    } // implicit barrier here
    
    printf("master thread=%d in serial region\n", m);
}