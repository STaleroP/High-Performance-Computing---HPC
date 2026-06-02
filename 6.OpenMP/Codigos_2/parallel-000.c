/* Copyright (C) 2022 Raul Torres raultorrescarvajal@gmail.com */

#include <stdio.h>
#include <omp.h>

int main(){
    int m = omp_get_thread_num();
    printf("thread=%d in serial region\n", m);
    
    #pragma omp parallel 
    {
        int t = omp_get_thread_num();
        printf("thread=%d in parallel region\n", t);
    } // implicit barrier here
    
    m = omp_get_thread_num();
    printf("thread=%d in serial region\n", m);
}
