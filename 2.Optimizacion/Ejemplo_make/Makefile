# Variables
CXX = g++
CXXFLAGS = -Wall -Wextra
TARGET = app
OBJS = main.o funciones.o

# Configuraciones adicionales
DEBUG_FLAGS = -g
RELEASE_FLAGS = -O3 -DNDEBUG

# Regla por defecto
all: $(TARGET)

# Regla para compilación modo debug
debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: clean all

# Regla para compilación modo release
release: CXXFLAGS += $(RELEASE_FLAGS)
release: clean all

# Cómo construir el ejecutable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Regla para compilar objetos
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpiar archivos generados
clean:
	rm -f $(OBJS) $(TARGET)
