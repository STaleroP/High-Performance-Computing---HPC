/* Copyright (C) 2022 Raul Torres raultorrescarvajal@gmail.com */

#include <stdio.h>
#include <omp.h>

int main(){
    int m = omp_get_thread_num();
    printf("master thread=%d in serial region\n", m);
    
    #pragma omp parallel master
    {
        int t = omp_get_thread_num();
        printf("thread=%d in parallel region\n", t);
        
        #pragma omp task
        {
            int s = omp_get_thread_num();
            printf("thread=%d in task region\n", s);
        }
        #pragma omp task
        {
            int s = omp_get_thread_num();
            printf("thread=%d in task region\n", s);
        }
        #pragma omp task
        {
            int s = omp_get_thread_num();
            printf("thread=%d in task region\n", s);
        }
    } // implicit barrier here
    
    printf("master thread=%d in serial region\n", m);
}
