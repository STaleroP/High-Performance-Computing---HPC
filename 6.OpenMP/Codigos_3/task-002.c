/* Copyright (C) 2022 Raul Torres raultorrescarvajal@gmail.com */

#include <stdio.h>
#include <omp.h>

int main(){
    int m = omp_get_thread_num();
    printf("thread=%d in serial region\n", m);
    
    #pragma omp parallel 
    {
        #pragma omp master
        {
            int s = omp_get_thread_num();
            printf("thread=%d in master region is creating tasks\n", s);

            #pragma omp task
            {
                int t = omp_get_thread_num();
                printf("thread=%d executed task A\n", t);
            }

            #pragma omp task
            {
                int t = omp_get_thread_num();
                printf("thread=%d executed task B\n", t);
            }
        } // no barrier here
        
        int p = omp_get_thread_num();
        printf("thread=%d has arrived\n", p);
    } // implicit barrier here
    
    m = omp_get_thread_num();
    printf("thread=%d in serial region\n", m);
}