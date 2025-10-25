all: build run

build:
	g++ src/main.cpp src/HashTable.cpp src/TextUtil.cpp -o contador

run: 
	./contador	input/LaGuerraInjusta.txt