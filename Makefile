all: build run

build:
	g++ src/main.cpp src/HashTable.cpp -o contador

run: 
	./contador	input/entrada.txt