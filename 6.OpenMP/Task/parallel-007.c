/* Copyright (C) 2022 Raul Torres raultorrescarvajal@gmail.com */

#include <stdio.h>
#include <omp.h>

int max(int a, int b){
    return a >= b ? a : b;
}

int main(){
    /* determina el número máximo comparando entre pares de números 
       (imprime en pantalla el número de hilo con cada resultado) */

    int a=40, b=20, c=30, d=50;
    int w=25, x=73, y=99, z=5;
    int max_0=0, max_1=0, max_2=0, max_3=0, max_4=0, max_5=0;
    int final_max=0;

    #pragma omp parallel
    {
        #pragma omp single
        {
            // Grupo de tareas para primera capa de comparaciones
            #pragma omp taskgroup
            {
                #pragma omp task
                {
                    max_0 = max(a, b);
                    printf("max_0=%d (thread %d)\n", max_0, omp_get_thread_num());
                }
                
                #pragma omp task
                {
                    max_1 = max(c, d);
                    printf("max_1=%d (thread %d)\n", max_1, omp_get_thread_num());
                }
            }

            // Grupo de tareas para segunda capa de comparaciones
            #pragma omp taskgroup
            {
                #pragma omp task
                {
                    max_2 = max(w, x);
                    printf("max_2=%d (thread %d)\n", max_2, omp_get_thread_num());
                }
                
                #pragma omp task
                {
                    max_3 = max(y, z);
                    printf("max_3=%d (thread %d)\n", max_3, omp_get_thread_num());
                }
            }

            // Grupo de tareas para tercera capa de comparaciones
            #pragma omp taskgroup
            {
                #pragma omp task
                {
                    max_4 = max(max_0, max_1);
                    printf("max_4=%d (thread %d)\n", max_4, omp_get_thread_num());
                }
                
                #pragma omp task
                {
                    max_5 = max(max_2, max_3);
                    printf("max_5=%d (thread %d)\n", max_5, omp_get_thread_num());
                }
            }

            // Resultado final
            final_max = max(max_4, max_5);
            printf("final_max=%d (thread %d)\n", final_max, omp_get_thread_num());
        }
    }
}
