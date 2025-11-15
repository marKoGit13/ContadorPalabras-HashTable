#include "HashTable.h"
#include <iostream>
#include <vector>
#include <utility>  //para std::pair
#include <algorithm>    //para std::sort

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
    numElementos = 0;
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
    numElementos++;
    if (static_cast<double>(numElementos) / capacidad > UMBRAL_CARGA) {
        rehash();
    }
}

void TablaHash::rehash() {
    std::cout << "\n--- ¡REHASHING ACTIVADO! --- (Carga: " 
              << static_cast<double>(numElementos) / capacidad << ")" << std::endl;

    //Guardar la tabla vieja y duplicar la capacidad
    int capacidadVieja = capacidad;
    Nodo** tablaVieja = tabla;
    
    capacidad = capacidad * 2; // Duplicamos la capacidad
    
    // Crear la nueva tabla (el puntero tabla ahora apunta a la nueva)
    tabla = new Nodo*[capacidad];
    for (int i = 0; i < capacidad; i++) {
        tabla[i] = nullptr;
    }

    //Recorrer la tabla vieja y re-insertar todos los nodos
    //en la nueva tabla.
    for (int i = 0; i < capacidadVieja; i++) {
        Nodo* actual = tablaVieja[i];
        while (actual != nullptr) {
            Nodo* siguiente = actual->siguiente; // Guardar el siguiente nodo

            //rehash
            // Recalcular el índice con la nueva capacidad
            unsigned int nuevoIndice = funcionHash(actual->palabra); 
            
            // Insertar el nodo actual al inicio de la lista en la nueva tabla
            actual->siguiente = tabla[nuevoIndice];
            tabla[nuevoIndice] = actual;

            // Moverse al siguiente nodo de la lista vieja
            actual = siguiente;
        }
    }

    // 4. Borrar el arreglo viejo, no los nodos
    delete[] tablaVieja;

    std::cout << "--- REHASHING COMPLETADO --- (Nueva Capacidad: " << capacidad << ")" << std::endl;
}

void TablaHash::loadFactor(){
    double Lf = static_cast<double>(numElementos) / capacidad;
    std::cout <<"----------------------------------"<< std::endl;
    std::cout <<"El factor de carga final es: ("<<Lf<<") < ("<<UMBRAL_CARGA<<")"<<  std::endl;
    std::cout <<"----------------------------------"<< std::endl;
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
        std::cout << "Bucket " << i << " :";
        
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

// Esta función le dice a std::sort que ordene los pares
// basándose en el contador de mayor a menor.
bool compararPares(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
    return a.second > b.second;
}

void TablaHash::reporteTopN(unsigned n) const {
    
    //Crear un vector temporal para almacenar todos los pares (palabra, contador)
    std::vector<std::pair<std::string, int>> todasLasPalabras;

    //Recorrer toda la tabla hash 
    for (int i = 0; i < capacidad; i++) {
        Nodo* actual = tabla[i];
        while (actual != nullptr) {
            // Añadir el par (palabra, contador) al vector
            todasLasPalabras.push_back(std::make_pair(actual->palabra, actual->contador));
            actual = actual->siguiente;
        }
    }

    // Ordenar el vector
    // Se usa std::sort con nuestra función de comparación
    // Esta es la parte algorítmicamente más costosa: O(N log N) 
    // donde N es el número de palabras únicas.
    std::sort(todasLasPalabras.begin(), todasLasPalabras.end(), compararPares);

    // Imprimir los primeros n resultados
    std::cout << "\n--- Reporte Top " << n << " Palabras Mas Frecuentes ---" << std::endl;
    for (unsigned i = 0; i < n && i < todasLasPalabras.size(); i++) {
        std::cout << (i + 1) << ". '" << todasLasPalabras[i].first 
                  << "': " << todasLasPalabras[i].second << " veces" << std::endl;
    }
    std::cout << "--------------------------------------------------\n" << std::endl;
}
