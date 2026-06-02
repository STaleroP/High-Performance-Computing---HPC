/* Copyright (C) 2022 Raul Torres raultorrescarvajal@gmail.com */

#include <stdio.h>
#include <omp.h>

int main(){
    #pragma omp parallel
    {
        if(omp_get_thread_num()==0){
            printf("Step 1\n");
        }
        if(omp_get_thread_num()==1){
            printf("Step 2\n");
        }
        if(omp_get_thread_num()==2){
            printf("Step 3\n");
        }
        if(omp_get_thread_num()==3){
            printf("Step 4\n");
        }
    }
}