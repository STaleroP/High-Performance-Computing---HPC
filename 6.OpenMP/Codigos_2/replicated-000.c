/* Copyright (C) 2022 Raul Torres raultorrescarvajal@gmail.com */

#include <stdio.h>

int main(){
    #pragma omp parallel
    {
        printf("Step 1\n");
        printf("Step 2\n");
        printf("Step 3\n");
        printf("Step 4\n");
    }
}