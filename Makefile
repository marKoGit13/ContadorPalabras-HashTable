build:
	@echo "Creando directorios bin/ y build/..."
	mkdir -p build bin
	@echo "Compilando archivos fuente de src/..."
	g++ -Wall -Wextra -std=c++17 -g -Iinclude -c src/*.cpp
	@echo "Moviendo archivos objeto (.o) a build/..."
	mv *.o build/
	@echo "Enlazando para crear el ejecutable en bin/contador..."
	g++ build/*.o -o bin/contador -mconsole
	@echo "Compilación completada."

run: 
	@echo "Creando directorios de reporte..."
	@mkdir -p reporte/reporteBooks
	@mkdir -p reporte/reporteSpam
	@mkdir -p reporte/reporteNoSpam
	@mkdir -p reporte/libroEspanol

	@echo "Procesando archivos de input/Books/..."
	@for file in input/Books/*.txt; do \
		echo "  Generando reporte para $$file..."; \
		./bin/contador $$file input/stop_words_en.txt > reporte/reporteBooks/reporte_$$(basename $$file); \
	done

	@echo "Procesando archivos de input/Spam/..."
	@for file in input/Spam/*.txt; do \
		echo "  Generando reporte para $$file..."; \
		./bin/contador $$file input/stop_words_en.txt > reporte/reporteSpam/reporte_$$(basename $$file); \
	done

	@echo "Procesando archivos de input/NoSpam/..."
	@for file in input/NoSpam/*.txt; do \
		echo "  Generando reporte para $$file..."; \
		./bin/contador $$file input/stop_words_en.txt > reporte/reporteNoSpam/reporte_$$(basename $$file); \
	done

	@echo "Procesando archivos de input/LaGuerraInjusta.txt..."
	@for file in input/LaGuerraInjusta.txt; do \
		echo "  Generando reporte para $$file..."; \
		./bin/contador $$file input/stop_words_es.txt > reporte/libroEspanol/reporte_$$(basename $$file); \
	done
	
	@echo "Todos los reportes han sido generados en la carpeta reporte/."

clean:
	@echo "Limpiando directorios build/, bin/ y reporte/..."
	rm -rf build bin reporte
	@echo "Limpieza completada."

.PHONY: all build run clean