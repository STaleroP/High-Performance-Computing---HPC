# Configuración básica
MAKEFLAGS += --no-print-directory
CC = g++
CFLAGS = -fopenmp
SRC_DIR = src
BIN_DIR = bin
DATA_DIR = data
IMAG_DIR = imag
REPORT_DIR = report
PLOT_SCRIPT = generate_stats_plots.py
PLOT_SOL_SCRIPT = plot_results.py
COMMON_PREFIX = poisson_

# Regla principal
all: compile

# Compilación de todos los archivos
compile:
	@mkdir -p $(BIN_DIR)
	@for src_file in $(SRC_DIR)/*.cpp; do \
		base_name=$$(basename $$src_file .cpp); \
		echo "Compilando $$base_name..."; \
		$(CC) $(CFLAGS) -o $(BIN_DIR)/$$base_name $$src_file; \
	done
	@echo "Compilación completada."


# Ejecuta binarios en modo normal
run:
ifeq ($(ALL),yes)
	@echo "Ejecutando todos los archivos en modo normal..."
	@mkdir -p $(BIN_DIR)
	@for src_file in $(SRC_DIR)/$(COMMON_PREFIX)*.cpp; do \
		base_name=$$(basename $$src_file .cpp); \
		if [ ! -f $(BIN_DIR)/$$base_name ]; then \
			echo "Compilando $$base_name..."; \
			$(CC) $(CFLAGS) $$src_file -o $(BIN_DIR)/$$base_name; \
		fi; \
		echo "Ejecutando $$base_name..."; \
		$(BIN_DIR)/$$base_name; \
	done

else ifdef VERSION
	@mkdir -p $(BIN_DIR)
	@exec_name="$(COMMON_PREFIX)$(VERSION)"; \
	if [ ! -f "$(BIN_DIR)/$$exec_name" ]; then \
		echo "Compilando $$exec_name..."; \
		$(CC) $(CFLAGS) "$(SRC_DIR)/$$exec_name.cpp" -o "$(BIN_DIR)/$$exec_name"; \
	fi; \
	echo "Ejecutando $$exec_name..."; \
	"$(BIN_DIR)/$$exec_name"

else
	$(error Debes usar VERSION=nombre o ALL=yes)
endif

# Ejecuta binarios en modo "report"
report:
ifeq ($(ALL),yes)
	@echo "Ejecutando todos los archivos en modo reporte..."
	@mkdir -p $(BIN_DIR)
	@versions=""
	@for src_file in $(SRC_DIR)/$(COMMON_PREFIX)*.cpp; do \
		base_name=$$(basename $$src_file .cpp); \
		version=$${base_name#$(COMMON_PREFIX)}; \
		versions="$$versions,$$version"; \
		if [ ! -f $(BIN_DIR)/$$base_name ]; then \
			echo "Compilando $$base_name..."; \
			$(CC) $(CFLAGS) $$src_file -o $(BIN_DIR)/$$base_name; \
		fi; \
		echo "Ejecutando $$base_name --report..."; \
		$(BIN_DIR)/$$base_name --report; \
	done
ifneq ($(PLOT),)
ifeq ($(PLOT),yes)
	@$(MAKE) plot_stats ALL=yes
else
	@IFS=','; for version in $$(echo $$versions | sed 's/^,//'); do \
		$(MAKE) plot_stats VERSION=$$version; \
	done
endif
endif

else ifdef VERSION
	@mkdir -p $(BIN_DIR)
	@exec_name="$(COMMON_PREFIX)$(VERSION)"; \
	if [ ! -f "$(BIN_DIR)/$$exec_name" ]; then \
		echo "Compilando $$exec_name..."; \
		$(CC) $(CFLAGS) "$(SRC_DIR)/$$exec_name.cpp" -o "$(BIN_DIR)/$$exec_name"; \
	fi; \
	echo "Ejecutando $$exec_name --report..."; \
	"$(BIN_DIR)/$$exec_name" --report; \
	if [ "$(PLOT)" = "yes" ]; then \
		$(MAKE) plot_stats VERSION=$(VERSION); \
	fi

else
	$(error Debes usar VERSION=nombre o ALL=yes)
endif
	@echo "Ejecución completada."

# Generación de gráficas estadísticas
plot_stats:
ifeq ($(ALL),yes)
	@echo "Generando gráficas estadísticas para todas las versiones..."
	@for dir in $(REPORT_DIR)/*/ ; do \
		version=$$(basename $$dir); \
		mkdir -p $(REPORT_DIR)/$$version/imag; \
		python3 $(REPORT_DIR)/$(PLOT_SCRIPT) $(REPORT_DIR)/$$version/data $(REPORT_DIR)/$$version/imag $$version; \
		echo "Gráficas generadas en $(REPORT_DIR)/$$version/imag/"; \
	done

else ifdef VERSION
	@echo "Generando gráficas estadísticas para $(VERSION)..."
	@mkdir -p $(REPORT_DIR)/$(VERSION)/imag
	@python3 $(REPORT_DIR)/$(PLOT_SCRIPT) $(REPORT_DIR)/$(VERSION)/data $(REPORT_DIR)/$(VERSION)/imag $(VERSION)
	@echo "Gráficas generadas en $(REPORT_DIR)/$(VERSION)/imag/"

else
	$(error Debes usar VERSION=nombre o ALL=yes)
endif

# Generación de gráficas de los datos
plot:
	@echo "Generando gráficas desde data/... en imag/..."
	@python3 $(PLOT_SOL_SCRIPT) data imag

# Limpieza total de los archivos generados
clean:
	@echo "Limpiando archivos generados..."
	@rm -rf $(BIN_DIR) $(DATA_DIR) $(IMAG_DIR)
	@find $(REPORT_DIR) -mindepth 1 ! -name "$(PLOT_SCRIPT)" -exec rm -rf {} +
	@echo "Limpieza completada."

.PHONY: all compile report run plot plot_stats clean