/* Copyright (C) 2022 Raul Torres raultorrescarvajal@gmail.com */

#include <stdio.h>
#include <omp.h>

int main(){
    int m = omp_get_thread_num();
    printf("master thread=%d in serial region\n", m);
    
    int p = -1;
    printf("p=%d in serial region\n", p);

    #pragma omp parallel for lastprivate(p)
    for(int i=0; i<16 ; i++){
        int f = omp_get_thread_num();
        p = f;
        printf("p=%d modified by thread=%d\n", p, f);
    } // implicit barrier here
    
    printf("master thread=%d in serial region\n", m);
    printf("p=%d in serial region\n", p);
}