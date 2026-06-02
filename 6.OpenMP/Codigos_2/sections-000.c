/* Copyright (C) 2022 Raul Torres raultorrescarvajal@gmail.com */

#include <stdio.h>
#include <omp.h>

int main(){
    int m = omp_get_thread_num();
    printf("thread=%d in serial region\n", m);
    
    #pragma omp parallel 
    {
        #pragma omp sections
        {
            #pragma omp section
            {
                int t = omp_get_thread_num();
                printf("Section 0 executed by thread=%d\n", t);
            }

            #pragma omp section
            {
                int t = omp_get_thread_num();
                printf("Section 1 executed by thread=%d\n", t);
            }

            #pragma omp section
            {
                int t = omp_get_thread_num();
                printf("Section 2 executed by thread=%d\n", t);
            }
        } // implicit barrier here
    } 
    
    m = omp_get_thread_num();
    printf("thread=%d in serial region\n", m);
}