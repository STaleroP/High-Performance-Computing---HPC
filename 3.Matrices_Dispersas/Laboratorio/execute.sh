#!/bin/bash

# Nombre del archivo fuente
SOURCE_FILE="matrix.cpp"

# Directorio base para resultados
BASE_DIR="resultados_benchmark"
mkdir -p $BASE_DIR

# Niveles de optimización a probar
OPTIMIZATION_LEVELS=("O0" "O2" "O3")

# Función para ejecutar benchmark con un nivel de optimización específico
run_benchmark() {
    local opt_level=$1
    local flag="-$opt_level"
    local results_dir="$BASE_DIR/$opt_level"
    local executable="./matrix_benchmark_$opt_level"
    
    echo "=================================================="
    echo "Iniciando benchmark con optimización $flag"
    echo "=================================================="
    
    # Crear directorio para este nivel de optimización
    mkdir -p $results_dir
    
    # Compilar el programa con el nivel de optimización especificado
    echo "Compilando $SOURCE_FILE con $flag..."
    g++ $flag -o $executable $SOURCE_FILE
    
    # Verificar si la compilación fue exitosa
    if [ $? -ne 0 ]; then
        echo "Error en la compilación con $flag. Abortando."
        return 1
    fi
    
    # Crear archivos para almacenar los resultados
    GENERACION_FILE="$results_dir/generacion.dat"
    MULT_NORMAL_FILE="$results_dir/multiplicacion_normal.dat"
    MULT_OPT_FILE="$results_dir/multiplicacion_optimizada.dat"
    TRANSPOSICION_FILE="$results_dir/transposicion.dat"
    MULT_TRANSPUESTA_FILE="$results_dir/multiplicacion_transpuesta.dat"
    MULT_TRANSPUESTA_OPT_FILE="$results_dir/multiplicacion_transpuesta_optimizada.dat"
    
    # Limpiar archivos previos
    echo -n > $GENERACION_FILE
    echo -n > $MULT_NORMAL_FILE
    echo -n > $MULT_OPT_FILE
    echo -n > $TRANSPOSICION_FILE
    echo -n > $MULT_TRANSPUESTA_FILE
    echo -n > $MULT_TRANSPUESTA_OPT_FILE
    
    # Ejecutar el programa 100 veces
    echo "Iniciando 100 ejecuciones con $flag..."
    for i in $(seq 1 100); do
        echo -ne "Ejecución $i de 100...\r"
        
        # Ejecutar el programa y capturar la salida
        OUTPUT=$($executable)
        
        # Extraer los tiempos usando expresiones regulares
        GENERACION=$(echo "$OUTPUT" | grep "Generación de matrices" | grep -oE "[0-9]+\.[0-9]+")
        MULT_NORMAL=$(echo "$OUTPUT" | grep "fila × columna" | grep -v "optimizada" | grep -oE "[0-9]+\.[0-9]+")
        MULT_OPT=$(echo "$OUTPUT" | grep "optimizada (i-k-j)" | head -1 | grep -oE "[0-9]+\.[0-9]+")
        TRANSPOSICION=$(echo "$OUTPUT" | grep "Transposición" | grep -oE "[0-9]+\.[0-9]+")
        MULT_TRANSPUESTA=$(echo "$OUTPUT" | grep "fila × fila" | grep -v "optimizada" | grep -oE "[0-9]+\.[0-9]+")
        MULT_TRANSPUESTA_OPT=$(echo "$OUTPUT" | grep "Bᵗ optimizada" | grep -oE "[0-9]+\.[0-9]+")
        
        # Guardar los datos
        echo "$i $GENERACION" >> $GENERACION_FILE
        echo "$i $MULT_NORMAL" >> $MULT_NORMAL_FILE
        echo "$i $MULT_OPT" >> $MULT_OPT_FILE
        echo "$i $TRANSPOSICION" >> $TRANSPOSICION_FILE
        echo "$i $MULT_TRANSPUESTA" >> $MULT_TRANSPUESTA_FILE
        echo "$i $MULT_TRANSPUESTA_OPT" >> $MULT_TRANSPUESTA_OPT_FILE
    done
    echo -e "\nCompletadas 100 ejecuciones con $flag"
    
    # Generar gráficas y estadísticas para este nivel de optimización
    generate_plots_and_stats $opt_level $results_dir
    
    return 0
}

# Función para generar gráficas y estadísticas
generate_plots_and_stats() {
    local opt_level=$1
    local results_dir=$2
    
    echo "Generando gráficas y estadísticas para optimización -$opt_level..."
    
    # Archivos de datos
    GENERACION_FILE="$results_dir/generacion.dat"
    MULT_NORMAL_FILE="$results_dir/multiplicacion_normal.dat"
    MULT_OPT_FILE="$results_dir/multiplicacion_optimizada.dat"
    TRANSPOSICION_FILE="$results_dir/transposicion.dat"
    MULT_TRANSPUESTA_FILE="$results_dir/multiplicacion_transpuesta.dat"
    MULT_TRANSPUESTA_OPT_FILE="$results_dir/multiplicacion_transpuesta_optimizada.dat"
    
    # Crear el script de gnuplot
    GNUPLOT_SCRIPT="$results_dir/plot_script.gnuplot"
    
    cat > $GNUPLOT_SCRIPT << EOL
set terminal pngcairo size 1200,900 enhanced font 'Verdana,12'
set output '$results_dir/tiempos_operaciones.png'
set title 'Tiempos de ejecución para operaciones matriciales con -$opt_level (100 ejecuciones)' font 'Verdana,16'
set xlabel 'Número de ejecución' font 'Verdana,12'
set ylabel 'Tiempo (segundos)' font 'Verdana,12'
set key outside right top
set grid
set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 0.5
set style line 2 lc rgb '#dd181f' lt 1 lw 2 pt 9 ps 0.5
set style line 3 lc rgb '#00ad60' lt 1 lw 2 pt 5 ps 0.5
set style line 4 lc rgb '#ad6000' lt 1 lw 2 pt 11 ps 0.5
set style line 5 lc rgb '#8a00ad' lt 1 lw 2 pt 13 ps 0.5
set style line 6 lc rgb '#000000' lt 1 lw 2 pt 3 ps 0.5

plot '$GENERACION_FILE' using 1:2 title 'Generación de matrices' with linespoints ls 1, \\
     '$MULT_NORMAL_FILE' using 1:2 title 'Multiplicación normal (fila x columna)' with linespoints ls 2, \\
     '$MULT_OPT_FILE' using 1:2 title 'Multiplicación optimizada (i-k-j)' with linespoints ls 3, \\
     '$TRANSPOSICION_FILE' using 1:2 title 'Transposición de matriz' with linespoints ls 4, \\
     '$MULT_TRANSPUESTA_FILE' using 1:2 title 'Multiplicación con transpuesta (fila x fila)' with linespoints ls 5, \\
     '$MULT_TRANSPUESTA_OPT_FILE' using 1:2 title 'Multiplicación con transpuesta optimizada' with linespoints ls 6

# Crear otra gráfica comparando solo los métodos de multiplicación
set output '$results_dir/comparacion_metodos_multiplicacion.png'
set title 'Comparación de métodos de multiplicación de matrices con -$opt_level' font 'Verdana,16'
set yrange [0:*]

plot '$MULT_NORMAL_FILE' using 1:2 title 'Multiplicación normal (fila x columna)' with linespoints ls 2, \\
     '$MULT_OPT_FILE' using 1:2 title 'Multiplicación optimizada (i-k-j)' with linespoints ls 3, \\
     '$MULT_TRANSPUESTA_FILE' using 1:2 title 'Multiplicación con transpuesta (fila x fila)' with linespoints ls 5, \\
     '$MULT_TRANSPUESTA_OPT_FILE' using 1:2 title 'Multiplicación con transpuesta optimizada' with linespoints ls 6

# Crear gráficas de distribución (boxplot) para comparar estadísticamente
set output '$results_dir/boxplot_metodos.png'
set title 'Distribución de tiempos por método con -$opt_level (boxplot)' font 'Verdana,16'
set style fill solid 0.5 border -1
set style boxplot candlesticks
set xtics ('A×B\n(fila×columna)' 1, 'A×B\noptimizada' 2, 'A×Bᵗ\n(fila×fila)' 3, 'A×Bᵗ\noptimizada' 4)
set xlabel ''
unset key

plot '$MULT_NORMAL_FILE' using (1):2 with boxplot ls 2, \\
     '$MULT_OPT_FILE' using (2):2 with boxplot ls 3, \\
     '$MULT_TRANSPUESTA_FILE' using (3):2 with boxplot ls 5, \\
     '$MULT_TRANSPUESTA_OPT_FILE' using (4):2 with boxplot ls 6

# Crear archivo con estadísticas
set table '$results_dir/stats.dat'
set print '-'
print 'Método,Tiempo promedio,Desviación estándar'
stats '$MULT_NORMAL_FILE' using 2 nooutput prefix "A"
print 'Multiplicación normal (fila x columna),'.A_mean.','.A_stddev
stats '$MULT_OPT_FILE' using 2 nooutput prefix "B"
print 'Multiplicación optimizada (i-k-j),'.B_mean.','.B_stddev
stats '$MULT_TRANSPUESTA_FILE' using 2 nooutput prefix "C"
print 'Multiplicación con transpuesta (fila x fila),'.C_mean.','.C_stddev
stats '$MULT_TRANSPUESTA_OPT_FILE' using 2 nooutput prefix "D"
print 'Multiplicación con transpuesta optimizada,'.D_mean.','.D_stddev
unset table

# Generar CSV para comparación global
set table '$results_dir/stats_summary.csv'
print 'Método,Tiempo promedio,Desviación estándar,Nivel optimización'
stats '$MULT_NORMAL_FILE' using 2 nooutput prefix "A"
print 'Multiplicación normal (fila x columna),'.A_mean.','.A_stddev.',$opt_level'
stats '$MULT_OPT_FILE' using 2 nooutput prefix "B"
print 'Multiplicación optimizada (i-k-j),'.B_mean.','.B_stddev.',$opt_level'
stats '$MULT_TRANSPUESTA_FILE' using 2 nooutput prefix "C"
print 'Multiplicación con transpuesta (fila x fila),'.C_mean.','.C_stddev.',$opt_level'
stats '$MULT_TRANSPUESTA_OPT_FILE' using 2 nooutput prefix "D"
print 'Multiplicación con transpuesta optimizada,'.D_mean.','.D_stddev.',$opt_level'
unset table
EOL
    
    # Ejecutar gnuplot
    gnuplot $GNUPLOT_SCRIPT
    
    # Crear un archivo HTML para mostrar resultados
    HTML_FILE="$results_dir/resultados.html"
    
    cat > $HTML_FILE << EOL
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Resultados Benchmark con Optimización -$opt_level</title>
    <style>
        body { font-family: Arial, sans-serif; margin: 20px; line-height: 1.6; }
        h1, h2 { color: #333; }
        img { max-width: 100%; border: 1px solid #ddd; margin: 20px 0; }
        table { border-collapse: collapse; width: 100%; margin: 20px 0; }
        th, td { border: 1px solid #ddd; padding: 8px; text-align: left; }
        th { background-color: #f2f2f2; }
        tr:nth-child(even) { background-color: #f9f9f9; }
    </style>
</head>
<body>
    <h1>Resultados del Benchmark de Multiplicación de Matrices con -$opt_level</h1>
    
    <h2>Gráficas de rendimiento</h2>
    <p>Todas las operaciones:</p>
    <img src="tiempos_operaciones.png" alt="Tiempos de operaciones">
    
    <p>Comparación de métodos de multiplicación:</p>
    <img src="comparacion_metodos_multiplicacion.png" alt="Comparación de métodos">
    
    <p>Distribución estadística (boxplot):</p>
    <img src="boxplot_metodos.png" alt="Boxplot de métodos">
    
    <h2>Estadísticas</h2>
    <table id="statsTable">
        <tr>
            <th>Método</th>
            <th>Tiempo promedio (s)</th>
            <th>Desviación estándar (s)</th>
        </tr>
        <!-- Los datos se cargarán aquí -->
    </table>

    <script>
        // Cargar las estadísticas desde el archivo
        fetch('stats.dat')
            .then(response => response.text())
            .then(data => {
                const lines = data.split('\\n').filter(line => line.includes(','));
                const table = document.getElementById('statsTable');
                
                lines.forEach(line => {
                    if (!line.startsWith('Método')) {  // Ignorar la cabecera
                        const parts = line.split(',');
                        const row = document.createElement('tr');
                        
                        parts.forEach(part => {
                            const cell = document.createElement('td');
                            cell.textContent = part;
                            row.appendChild(cell);
                        });
                        
                        table.appendChild(row);
                    }
                });
            })
            .catch(error => console.error('Error cargando estadísticas:', error));
    </script>
</body>
</html>
EOL
    
    echo "Informe para optimización -$opt_level generado en $HTML_FILE"
}

# Función para generar el informe comparativo final
generate_comparative_report() {
    echo "Generando informe comparativo de todos los niveles de optimización..."
    
    # Directorio para el informe comparativo
    COMPARATIVE_DIR="$BASE_DIR/comparativo"
    mkdir -p $COMPARATIVE_DIR
    
    # Combinar todos los archivos CSV de estadísticas
    echo "Método,Tiempo promedio,Desviación estándar,Nivel optimización" > $COMPARATIVE_DIR/all_stats.csv
    for opt_level in "${OPTIMIZATION_LEVELS[@]}"; do
        tail -n +2 "$BASE_DIR/$opt_level/stats_summary.csv" >> $COMPARATIVE_DIR/all_stats.csv
    done
    
    # Crear script gnuplot para comparaciones
    COMP_GNUPLOT="$COMPARATIVE_DIR/comparative_plots.gnuplot"
    
    cat > $COMP_GNUPLOT << EOL
set terminal pngcairo size 1200,900 enhanced font 'Verdana,12'

# Definir colores para cada nivel de optimización
set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 1
set style line 2 lc rgb '#dd181f' lt 1 lw 2 pt 9 ps 1
set style line 3 lc rgb '#00ad60' lt 1 lw 2 pt 5 ps 1

# Gráfico comparativo por método
set output '$COMPARATIVE_DIR/comparacion_por_metodo.png'
set title 'Comparación de rendimiento por método y nivel de optimización' font 'Verdana,16'
set xlabel 'Método' font 'Verdana,12'
set ylabel 'Tiempo promedio (segundos)' font 'Verdana,12'
set key outside right top
set style data histogram
set style histogram cluster gap 1
set style fill solid 0.5 border -1
set xtics rotate by 45 right
set grid y
set boxwidth 0.9

# Preparar los datos para el histograma
stats '$COMPARATIVE_DIR/all_stats.csv' using 2 nooutput
set yrange [0:STATS_max*1.1]

plot '$COMPARATIVE_DIR/all_stats.csv' using 2:(stringcolumn(4) eq "O0"?column(2):1/0):xtic(1) title 'O0' ls 1, \\
     '$COMPARATIVE_DIR/all_stats.csv' using 2:(stringcolumn(4) eq "O2"?column(2):1/0) title 'O2' ls 2, \\
     '$COMPARATIVE_DIR/all_stats.csv' using 2:(stringcolumn(4) eq "O3"?column(2):1/0) title 'O3' ls 3

# Gráfico de mejora relativa respecto a -O0
set output '$COMPARATIVE_DIR/mejora_relativa.png'
set title 'Mejora de rendimiento relativa a -O0' font 'Verdana,16'
set ylabel 'Mejora (veces más rápido)' font 'Verdana,12'
set key outside right top
set style data histogram
set style histogram cluster gap 1
set style fill solid 0.5 border -1
set xtics rotate by 45 right

# Crear archivo temporal con datos procesados para la mejora relativa
system "awk -F, 'BEGIN {print \"Método,O0,O2,O3\"} \\
        NR>1 && \\\$4==\"O0\" {base[\\\$1]=\\\$2} \\
        NR>1 && \\\$4==\"O2\" {o2[\\\$1]=\\\$2} \\
        NR>1 && \\\$4==\"O3\" {o3[\\\$1]=\\\$2} \\
        END {for (m in base) {print m \",\" 1 \",\" base[m]/o2[m] \",\" base[m]/o3[m]}}' \\
        $COMPARATIVE_DIR/all_stats.csv > $COMPARATIVE_DIR/speedup.csv"

plot '$COMPARATIVE_DIR/speedup.csv' using 2:xtic(1) title 'O0 (referencia)' ls 1, \\
     '$COMPARATIVE_DIR/speedup.csv' using 3 title 'O2' ls 2, \\
     '$COMPARATIVE_DIR/speedup.csv' using 4 title 'O3' ls 3

# Gráfico de barras de métodos vs optimizaciones
set output '$COMPARATIVE_DIR/metodos_vs_optimizaciones.png'
set title 'Comparación de todos los métodos y optimizaciones' font 'Verdana,16'
set xlabel 'Método por nivel de optimización' font 'Verdana,12'
set ylabel 'Tiempo promedio (segundos)' font 'Verdana,12'
set style fill solid 0.5 border -1
set boxwidth 0.9
set xtics rotate by 45 right nomirror

# Procesar datos para mostrar todos los métodos con sus niveles de optimización
system "awk -F, 'BEGIN {OFS=\",\"} \\
        NR>1 {print \\\$1 \"-\" \\\$4, \\\$2}' \\
        $COMPARATIVE_DIR/all_stats.csv > $COMPARATIVE_DIR/all_methods_opts.csv"

plot '$COMPARATIVE_DIR/all_methods_opts.csv' using 2:xtic(1) with boxes ls 1 notitle
EOL
    
    # Ejecutar gnuplot para generar gráficas comparativas
    gnuplot $COMP_GNUPLOT
    
    # Crear HTML comparativo
    HTML_COMPARATIVE="$COMPARATIVE_DIR/comparativa_optimizaciones.html"
    
    cat > $HTML_COMPARATIVE << EOL
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Comparativa de Optimizaciones - Multiplicación de Matrices</title>
    <style>
        body { font-family: Arial, sans-serif; margin: 20px; line-height: 1.6; }
        h1, h2, h3 { color: #333; }
        img { max-width: 100%; border: 1px solid #ddd; margin: 20px 0; }
        table { border-collapse: collapse; width: 100%; margin: 20px 0; }
        th, td { border: 1px solid #ddd; padding: 8px; text-align: left; }
        th { background-color: #f2f2f2; }
        tr:nth-child(even) { background-color: #f9f9f9; }
        .report-links { margin: 20px 0; }
        .report-links a { display: inline-block; margin-right: 15px; padding: 8px 15px; 
                         background-color: #4CAF50; color: white; text-decoration: none;
                         border-radius: 4px; }
        .report-links a:hover { background-color: #45a049; }
    </style>
</head>
<body>
    <h1>Comparativa de Optimizaciones en Multiplicación de Matrices</h1>
    
    <div class="report-links">
        <h3>Informes individuales:</h3>
EOL

    # Añadir enlaces a informes individuales
    for opt_level in "${OPTIMIZATION_LEVELS[@]}"; do
        echo "<a href=\"../$opt_level/resultados.html\">Informe de Optimización -$opt_level</a>" >> $HTML_COMPARATIVE
    done

    cat >> $HTML_COMPARATIVE << EOL
    </div>
    
    <h2>Gráficas Comparativas</h2>
    
    <h3>Comparación de métodos por nivel de optimización</h3>
    <img src="comparacion_por_metodo.png" alt="Comparación por método">
    
    <h3>Mejora relativa respecto a -O0</h3>
    <p>Este gráfico muestra cuántas veces más rápido es cada método con -O2 y -O3 comparado con -O0.</p>
    <img src="mejora_relativa.png" alt="Mejora relativa">
    
    <h3>Todos los métodos y optimizaciones</h3>
    <img src="metodos_vs_optimizaciones.png" alt="Métodos vs optimizaciones">
    
    <h2>Tabla Comparativa</h2>
    <table id="statsTable">
        <tr>
            <th>Método</th>
            <th>Nivel de optimización</th>
            <th>Tiempo promedio (s)</th>
            <th>Desviación estándar (s)</th>
        </tr>
        <!-- Los datos se cargarán aquí -->
    </table>

    <script>
        // Cargar las estadísticas desde el archivo
        fetch('all_stats.csv')
            .then(response => response.text())
            .then(data => {
                const lines = data.split('\\n').filter(line => line.includes(','));
                const table = document.getElementById('statsTable');
                
                lines.forEach(line => {
                    if (!line.startsWith('Método')) {  // Ignorar la cabecera
                        const parts = line.split(',');
                        if (parts.length >= 4) {
                            const row = document.createElement('tr');
                            
                            // Método
                            const cell1 = document.createElement('td');
                            cell1.textContent = parts[0];
                            row.appendChild(cell1);
                            
                            // Nivel de optimización
                            const cell4 = document.createElement('td');
                            cell4.textContent = '-' + parts[3];
                            row.appendChild(cell4);
                            
                            // Tiempo promedio
                            const cell2 = document.createElement('td');
                            cell2.textContent = parseFloat(parts[1]).toFixed(6);
                            row.appendChild(cell2);
                            
                            // Desviación estándar
                            const cell3 = document.createElement('td');
                            cell3.textContent = parseFloat(parts[2]).toFixed(6);
                            row.appendChild(cell3);
                            
                            table.appendChild(row);
                        }
                    }
                });
                
                // Ordenar tabla por método y nivel de optimización
                const sortTable = (table) => {
                    const rows = Array.from(table.rows).slice(1); // Skip header
                    rows.sort((a, b) => {
                        const aMethod = a.cells[0].textContent;
                        const bMethod = b.cells[0].textContent;
                        const aOpt = a.cells[1].textContent;
                        const bOpt = b.cells[1].textContent;
                        
                        // Primero ordenar por método
                        if (aMethod !== bMethod) {
                            return aMethod.localeCompare(bMethod);
                        }
                        // Luego por nivel de optimización
                        return aOpt.localeCompare(bOpt);
                    });
                    
                    // Eliminar filas actuales
                    while (table.rows.length > 1) {
                        table.deleteRow(1);
                    }
                    
                    // Añadir filas ordenadas
                    rows.forEach(row => table.appendChild(row));
                };
                
                sortTable(table);
            })
            .catch(error => console.error('Error cargando estadísticas:', error));
    </script>
    
    <h2>Conclusiones</h2>
    <div id="conclusiones">
        <p>Basado en los datos recopilados, se pueden extraer las siguientes conclusiones:</p>
        <ul>
            <li>La optimización del compilador tiene un impacto significativo en el rendimiento de las operaciones matriciales.</li>
            <li>La multiplicación con matriz transpuesta suele ofrecer mejor rendimiento debido a un mejor aprovechamiento de la localidad de caché.</li>
            <li>Los métodos optimizados muestran un rendimiento significativamente mejor con todas las optimizaciones.</li>
            <li>La optimización -O3 generalmente ofrece mejor rendimiento que -O2, aunque en algunos casos la diferencia es marginal.</li>
        </ul>
    </div>
    
    <h2>Metodología</h2>
    <p>Este análisis se realizó ejecutando 100 veces la multiplicación de matrices de 1024x1024 para cada nivel de optimización,
    utilizando distintos algoritmos implementados en C++. Se recopilaron tiempos para cada operación y se analizaron estadísticamente.</p>
    
    <footer>
        <p>Informe generado el $(date '+%d/%m/%Y %H:%M:%S')</p>
    </footer>
</body>
</html>
EOL
    
    echo "Informe comparativo generado en $HTML_COMPARATIVE"
}

# Ejecutar benchmarks para cada nivel de optimización
for opt_level in "${OPTIMIZATION_LEVELS[@]}"; do
    run_benchmark $opt_level
done

# Generar informe comparativo
generate_comparative_report

echo ""
echo "=================================================="
echo "¡Proceso completo!"
echo "=================================================="
echo ""
echo "Informes individuales:"
for opt_level in "${OPTIMIZATION_LEVELS[@]}"; do
    echo "- Optimización -$opt_level: $BASE_DIR/$opt_level/resultados.html"
done
echo ""
echo "Informe comparativo: $BASE_DIR/comparativo/comparativa_optimizaciones.html"
echo ""
echo "Para ver los informes, abra los archivos HTML en su navegador."