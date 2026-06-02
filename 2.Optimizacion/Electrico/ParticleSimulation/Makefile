# Configuración general
CXX = g++
SRC = main.cpp Particle.cpp
TARGET_DEBUG = simulacion_debug
TARGET_RELEASE = simulacion_release

CXXFLAGS_DEBUG = -g -O0
CXXFLAGS_RELEASE = -O3

N = 100

# Compilación en modo Debug
debug:
	$(CXX) $(CXXFLAGS_DEBUG) $(SRC) -o $(TARGET_DEBUG)

# Compilación en modo Release
release:
	$(CXX) $(CXXFLAGS_RELEASE) $(SRC) -o $(TARGET_RELEASE)

# Limpieza
clean:
	rm -f *.o $(TARGET_DEBUG) $(TARGET_RELEASE) \
		particula1.txt particula2.txt \
		tiempos_debug.txt tiempos_release.txt \
		grafica_tiempos.png trayectorias.png temp_time.txt

run_debug:
	@if [ ! -f $(TARGET_DEBUG) ]; then \
		echo "Compilado Debug no encontrado. Compilando..."; \
		$(MAKE) debug; \
	fi
	./$(TARGET_DEBUG)

run_release:
	@if [ ! -f $(TARGET_RELEASE) ]; then \
		echo "Compilado Release no encontrado. Compilando..."; \
		$(MAKE) release; \
	fi
	./$(TARGET_RELEASE)

# Medición de tiempos (extrae el tiempo impreso por el programa)
test_timing: debug release
	@echo "Ejecutando $(N) pruebas en modo Debug..."
	@> tiempos_debug.txt
	@for i in $$(seq 1 $(N)); do \
		TIME=$$(./$(TARGET_DEBUG) | grep -oP 'Tiempo total de simulación: \K\d+\.\d+'); \
		echo "$$TIME" >> tiempos_debug.txt; \
	done

	@echo "Ejecutando $(N) pruebas en modo Release..."
	@> tiempos_release.txt
	@for i in $$(seq 1 $(N)); do \
		TIME=$$(./$(TARGET_RELEASE) | grep -oP 'Tiempo total de simulación: \K\d+\.\d+'); \
		echo "$$TIME" >> tiempos_release.txt; \
	done

# Generar gráfica con promedios
graph: test_timing
	@if command -v gnuplot >/dev/null 2>&1; then \
		echo "Calculando promedios..."; \
		DEBUG_AVG=$$(awk '{ sum += $$1 } END { printf "%.6f", sum/NR }' tiempos_debug.txt); \
		RELEASE_AVG=$$(awk '{ sum += $$1 } END { printf "%.6f", sum/NR }' tiempos_release.txt); \
		echo "Debug avg: $$DEBUG_AVG s"; \
		echo "Release avg: $$RELEASE_AVG s"; \
		echo "Generando gráfica con promedios..."; \
		gnuplot -e " \
			set terminal png size 800,600; \
			set output 'grafica_tiempos.png'; \
			set title 'Comparación de Tiempos (Debug vs Release)'; \
			set xlabel 'Ejecución'; \
			set ylabel 'Tiempo (s)'; \
			set key left top; \
			set grid; \
			plot 'tiempos_debug.txt' with lines title 'Debug (avg: $$DEBUG_AVG s)' lc rgb 'red', \
			     'tiempos_release.txt' with lines title 'Release (avg: $$RELEASE_AVG s)' lc rgb 'blue'; \
		"; \
		echo "Gráfica generada: grafica_tiempos.png"; \
	else \
		echo "ERROR: gnuplot no está instalado."; \
		exit 1; \
	fi

# Graficar trayectorias XY de las dos partículas
plot_positions:
	@echo "Graficando trayectorias de partículas..."
	@gnuplot -e "\
		set terminal png size 800,600; \
		set output 'trayectorias.png'; \
		set title 'Trayectoria de las Partículas'; \
		set xlabel 'x'; \
		set ylabel 'y'; \
		set format x '%.1e'; \
		set format y '%.1e'; \
		set autoscale; \
		set grid; \
		set key top left; \
		plot 'particula1.txt' using 1:2 with points lt rgb 'red' pt 7 ps 0.5 title 'Partícula 1', \
		     'particula2.txt' using 1:2 with points lt rgb 'blue' pt 7 ps 0.5 title 'Partícula 2';"
	@echo "Trayectorias graficadas: trayectorias.png"
