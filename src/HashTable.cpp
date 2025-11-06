#include "HashTable.h"
#include <iostream>
#include <vector>

// implementación de nuestro constructor de nodo
Nodo::Nodo(const std::string& p){   
    palabra = p;
    contador = 1;       // siempre el contador empieza el 1
    siguiente = nullptr;
}

// implementación del constructor de tablaHash
TablaHash::TablaHash(int cap){
    capacidad = cap;
    tabla = new Nodo*[capacidad]; // creamos un array dinámicamente con la capacidad ingresada

    for(int i = 0; i < capacidad; i++){
        tabla[i] = nullptr; // inicializamos todos los punteros a nulo
    }
}

TablaHash::~TablaHash(){
    for(int i = 0; i<capacidad ;i++){
        Nodo* actual = tabla[i];
        while(actual != nullptr){
            Nodo* temp = actual;
            actual = actual->siguiente;
            delete temp;    //borramos cada nodo de la lista
        }
    }
    delete[] tabla; // borramos el array principal de punteros
}

unsigned int TablaHash::funcionHash(const std::string& palabra) const{ 
    unsigned long hash = 0;
    for(size_t i = 0; i<palabra.length(); i++){
        hash = (hash * 31 + palabra[i]) % capacidad;
    }
    return hash;
}

void TablaHash::insertar(const std::string& palabra) {

    // no insertar si la palabra está vacía luego de limpiar
    if(palabra.empty()) return;

    unsigned int indice = funcionHash(palabra);
    Nodo* actual = tabla[indice];

    //buscar si ya existe
    while(actual != nullptr){
        if(actual->palabra == palabra){ //enocontrado
            actual->contador++; //aumentamos la cant de palabra
            return;
        }
        actual = actual->siguiente;
    }

    // si no existe, la creamos al inicio
    Nodo* nuevoNodo = new Nodo(palabra);
    nuevoNodo->siguiente = tabla[indice];
    tabla[indice] = nuevoNodo;
    
}

int TablaHash::buscar(const std::string& palabra) const{
    unsigned int indice = funcionHash(palabra);
    Nodo* actual = tabla[indice];
    
    //recorremos la lista de ese indice
    while(actual!=nullptr){
        if(actual->palabra == palabra){
            return actual->contador; //devuelve el conteo
        }
        actual = actual->siguiente;
    }

    // si no existe
    return 0;
}

void TablaHash::mostrarTabla() const {
    std::cout << "\n--- Estructura Interna de la Tabla Hash ---" << std::endl;
    for (int i = 0; i < capacidad; i++) {
        // Imprimir el índice del bucket
        std::cout << "Bucket " << i << ": ";
        
        // Recorrer la lista enlazada en este bucket
        Nodo* actual = tabla[i];
        if (actual == nullptr) {
            std::cout << "nullptr" << std::endl; // Si está vacío
        } else {
            while (actual != nullptr) {
                // Imprimir cada nodo de la lista
                std::cout << "[" << actual->palabra << ": " << actual->contador << "] -> ";
                actual = actual->siguiente;
            }
            std::cout << "nullptr" << std::endl; // Marcar el final de la lista
        }
    }
    std::cout << "-------------------------------------------\n" << std::endl;
}

void TablaHash::reporteFrecuencias() const {
    std::cout << "\n--- Reporte de Frecuencia de Palabras ---" << std::endl;
    int palabrasUnicas = 0; // Para contar cuántas palabras diferentes encontramos

    // Iteramos sobre cada bucket (índice) de la tabla
    for (int i = 0; i < capacidad; i++) {
        // Recorremos la lista enlazada en este bucket
        Nodo* actual = tabla[i];
        while (actual != nullptr) {
            // Imprimimos la palabra y su contador
            std::cout << "'" << actual->palabra << "': " << actual->contador << std::endl;
            palabrasUnicas++; // Incrementamos el contador de palabras únicas
            actual = actual->siguiente;
        }
        // No imprimimos nada si el bucket está vacío
    }

    std::cout << "------------------------------------------" << std::endl;
    std::cout << "Total de palabras unicas encontradas: " << palabrasUnicas << std::endl;
    std::cout << "------------------------------------------\n" << std::endl;
}
