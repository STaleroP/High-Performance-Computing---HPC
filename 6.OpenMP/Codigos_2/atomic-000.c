/* Copyright (C) 2022 Raul Torres raultorrescarvajal@gmail.com */

#include <stdio.h>
#include <omp.h>

int main(){
    int m = omp_get_thread_num();
    printf("master thread=%d in serial region\n", m);
    int count = 0;

    #pragma omp parallel
    {
        int t = omp_get_thread_num();
        printf("thread=%d in parallel region\n", t);
        
        #pragma omp atomic
        count++;
        
        printf("thread=%d says goodbye\n", t);
    } // implicit barrier here
    
    printf("master thread=%d in serial region\n", m);
    printf("count=%d\n", count);
}