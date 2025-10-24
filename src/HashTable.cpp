#include "HashTable.h"
#include <iostream>

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
    if(palabra.empty()) return;
}

