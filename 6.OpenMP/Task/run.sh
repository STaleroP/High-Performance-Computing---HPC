
#!/bin/bash

# Función para extraer los tiempos de la salida del comando time
get_times() {
    real=$(echo "$1" | grep "real" | awk '{split($2,a,"m"); print a[1]*60 + substr(a[2],1,length(a[2])-1)}')
    user=$(echo "$1" | grep "user" | awk '{split($2,a,"m"); print a[1]*60 + substr(a[2],1,length(a[2])-1)}')
    sys=$(echo "$1" | grep "sys" | awk '{split($2,a,"m"); print a[1]*60 + substr(a[2],1,length(a[2])-1)}')
    echo "$real $user $sys"
}

# Compilar todos los archivos
echo "Compilando archivos..."
for i in {5..7}; do
    g++ -fopenmp -o serie-00$i serie-00$i.c
    g++ -fopenmp -o parallel-00$i parallel-00$i.c
done

# Para cada par de archivos
for i in {5..7}; do
    echo "Ejecutando pruebas para serie-00$i y parallel-00$i..."

    # Crear archivos para almacenar tiempos
    echo "Ejecucion Real User Sys" > tiempos_serie_00$i.txt
    echo "Ejecucion Real User Sys" > tiempos_parallel_00$i.txt

    # Arrays para almacenar tiempos
    declare -a serie_real_times
    declare -a serie_user_times
    declare -a serie_sys_times
    declare -a parallel_real_times
    declare -a parallel_user_times
    declare -a parallel_sys_times

    # Realizar 100 ejecuciones
    for ((j=1; j<=100; j++)); do
        # Ejecutar serie y capturar tiempos
        serie_output=$({ time ./serie-00$i; } 2>&1)
        read real user sys <<< $(get_times "$serie_output")
        serie_real_times[$j]=$real
        serie_user_times[$j]=$user
        serie_sys_times[$j]=$sys
        echo "$j $real $user $sys" >> tiempos_serie_00$i.txt

        # Ejecutar parallel y capturar tiempos
        parallel_output=$({ time ./parallel-00$i; } 2>&1)
        read real user sys <<< $(get_times "$parallel_output")
        parallel_real_times[$j]=$real
        parallel_user_times[$j]=$user
        parallel_sys_times[$j]=$sys
        echo "$j $real $user $sys" >> tiempos_parallel_00$i.txt

        echo -ne "\rProgreso: $j/100"
    done
    echo ""

    # Calcular promedios
    serie_real_avg=$(awk '{ sum += $2 } END { print sum/(NR-1) }' tiempos_serie_00$i.txt)
    serie_user_avg=$(awk '{ sum += $3 } END { print sum/(NR-1) }' tiempos_serie_00$i.txt)
    serie_sys_avg=$(awk '{ sum += $4 } END { print sum/(NR-1) }' tiempos_serie_00$i.txt)
    parallel_real_avg=$(awk '{ sum += $2 } END { print sum/(NR-1) }' tiempos_parallel_00$i.txt)
    parallel_user_avg=$(awk '{ sum += $3 } END { print sum/(NR-1) }' tiempos_parallel_00$i.txt)
    parallel_sys_avg=$(awk '{ sum += $4 } END { print sum/(NR-1) }' tiempos_parallel_00$i.txt)

    echo "Resultados para el par 00$i:"
    echo "Serie-00$i promedios:"
    echo "  Tiempo real: $serie_real_avg segundos"
    echo "  Tiempo usuario: $serie_user_avg segundos"
    echo "  Tiempo sistema: $serie_sys_avg segundos"
    echo "Parallel-00$i promedios:"
    echo "  Tiempo real: $parallel_real_avg segundos"
    echo "  Tiempo usuario: $parallel_user_avg segundos"
    echo "  Tiempo sistema: $parallel_sys_avg segundos"
    echo "----------------------------------------"
done
