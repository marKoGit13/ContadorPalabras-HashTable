# --- Variables ---
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++11 -g
INC_DIR := include
SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin
TARGET_NAME := contador # Solo el nombre base
TARGET := $(BIN_DIR)/$(TARGET_NAME) # Ruta completa al ejecutable

# Fuentes y Objetos
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Archivos de entrada/salida para 'run'
INPUT_FILE := input/LaGuerraInjusta.txt
REPORTE_DIR := reporte
OUTPUT_FILE := $(REPORTE_DIR)/reporte_frecuencias.txt

# --- Reglas ---

# Regla principal: Crear directorios necesarios y luego el ejecutable
all: dirs $(TARGET)

# Regla para enlazar: Crear el ejecutable desde los archivos objeto
$(TARGET): $(OBJS)
	@echo "Enlazando para crear $(TARGET)..."
	$(CXX) $(OBJS) -o $(TARGET)
	@echo "Ejecutable $(TARGET) creado."

# Regla para compilar: Crear archivos objeto desde archivos fuente
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "Compilando $< -> $@"
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

# Regla para ejecutar el programa
run: $(TARGET) | $(REPORTE_DIR) # Asegura que reporte/ exista antes de ejecutar
	@echo "Ejecutando ./$(TARGET) con $(INPUT_FILE)..."
	./$(TARGET) $(INPUT_FILE) > $(OUTPUT_FILE)
	@echo "Ejecución completada. Resultados en $(OUTPUT_FILE)"

# Regla para crear todos los directorios necesarios de una vez
# Usamos .PHONY para que siempre se ejecute si se llama explícitamente
# Y la ponemos como dependencia de 'all'
.PHONY: dirs clean all run
dirs:
	@echo "Asegurando que los directorios build/, bin/, reporte/ existen..."
	@mkdir -p $(BUILD_DIR) $(BIN_DIR) $(REPORTE_DIR)

# Regla para limpiar
clean:
	@echo "Limpiando archivos generados..."
	@rm -rf $(BIN_DIR) $(BUILD_DIR) $(REPORTE_DIR)/*.txt
	@echo "Limpieza completada."