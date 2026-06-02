/* Copyright (C) 2022 Raul Torres raultorrescarvajal@gmail.com */

#include <stdio.h>
#include <omp.h>

int main(){
    int m = omp_get_thread_num();
    printf("master thread=%d in serial region\n", m);
    
    #pragma omp parallel shared(m)
    {
        int t = omp_get_thread_num();
        if(t==m)
			printf("master thread=%d in parallel region\n", m);
		else
			printf("thread=%d in parallel region\n", t);
    }
    
    printf("master thread=%d in serial region\n", m);
}
