/* Copyright (C) 2022 Raul Torres raultorrescarvajal@gmail.com */

#include <stdio.h>
#include <omp.h>

int main(){
    #pragma omp parallel for
    for(int i=0;i<16;i++){
        printf("i=%d processed by thread=%d\n", i, omp_get_thread_num());
    }
}
