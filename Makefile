# --- Regla Principal ---
# Permite compilar escribiendo solo 'make'
all: build

# --- Regla de Compilación ---
# Sigue la estructura que pediste, cambiando c++23 por c++17
build:
	@echo "Creando directorios bin/ y build/..."
	@mkdir -p build bin
	@echo "Compilando archivos fuente de src/..."
	g++ -Wall -Wextra -std=c++17 -g -Iinclude -c src/*.cpp
	@echo "Moviendo archivos objeto (.o) a build/..."
	mv *.o build/
	@echo "Enlazando para crear el ejecutable en bin/contador..."
	g++ build/*.o -o bin/contador
	@echo "Compilación completada."

# --- Regla de Ejecución (Implementando Mejora 1) ---
# Crea subcarpetas en 'reporte/' y procesa todos los .txt de 'input/'
run:
	@echo "Creando directorios de reporte..."
	@mkdir -p reporte/reporteBooks
	@mkdir -p reporte/reporteSpam
	@mkdir -p reporte/reporteNoSpam

	@echo "Procesando archivos de input/Books/..."
	@for file in input/Books/*.txt; do \
		echo "  Generando reporte para $$file..."; \
		./bin/contador $$file > reporte/reporteBooks/reporte_$$(basename $$file); \
	done

	@echo "Procesando archivos de input/Spam/..."
	@for file in input/Spam/*.txt; do \
		echo "  Generando reporte para $$file..."; \
		./bin/contador $$file > reporte/reporteSpam/reporte_$$(basename $$file); \
	done

	@echo "Procesando archivos de input/NoSpam/..."
	@for file in input/NoSpam/*.txt; do \
		echo "  Generando reporte para $$file..."; \
		./bin/contador $$file > reporte/reporteNoSpam/reporte_$$(basename $$file); \
	done
	
	@echo "Todos los reportes han sido generados en la carpeta reporte/."

# --- Regla de Limpieza ---
# Modificada para borrar la carpeta 'reporte' completa
clean:
	@echo "Limpiando directorios build/, bin/ y reporte/..."
	rm -rf build bin reporte
	@echo "Limpieza completada."

# --- Declaración de Reglas Ficticias ---
.PHONY: all build run clean