build:
	mkdir -p build bin
	g++ -Wall -Wextra -std=c++23 -g -Iinclude -c src/*.cpp
	mv *.o build/
	g++ build/*.o -o bin/contador

run: 
	mkdir -p reporte
	./bin/contador input/LaGuerraInjusta.txt > reporte/reporte_HashTable_Frecuencias.txt

clean:
	rm -rf build bin reporte/*.txt