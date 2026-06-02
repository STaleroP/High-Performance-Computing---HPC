/* Copyright (C) 2022 Raul Torres raultorrescarvajal@gmail.com */

#include <stdio.h>
#include <omp.h>

int main(){
    int m = omp_get_thread_num();
    printf("thread=%d in serial region\n", m);
    
    #pragma omp parallel 
    {
        #pragma omp single
        {
            int g = omp_get_thread_num();
            printf("thread=%d in single region is creating tasks\n", g);

            int p=0,q=0,r=0,s=0,t=0;
            #pragma omp task depend(out: p)
            {
                p = omp_get_thread_num();
                printf("thread=%d executed task A\n", p);
            }

            #pragma omp task
            {
                q= omp_get_thread_num();
                printf("thread=%d executed task B\n", q);
            }

            #pragma omp task depend(out: r)
            {
                r= omp_get_thread_num();
                printf("thread=%d executed task C\n", r);
            }

            #pragma omp task depend(in: p, r)
            {
                s = omp_get_thread_num();
                printf("thread=%d executed task D\n", s);
            }

            #pragma omp task
            {
                t = omp_get_thread_num();
                printf("thread=%d executed task E\n", t);
            }
        } // implicit barrier here
    } // implicit barrier here
    
    m = omp_get_thread_num();
    printf("thread=%d in serial region\n", m);
}