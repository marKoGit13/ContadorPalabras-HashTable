#pragma once

#include <string>
#include <vector>
#include <utility> //para std::pair

// Se crea un nodo 
struct Nodo {
    std::string palabra;    // la palabra a evualar
    int contador;           // la cantidad de veces que aparece en el txt 
    Nodo* siguiente;         // puntero al siguiente nodo

    Nodo(const std::string &p);                 //Constructor

};

class TablaHash{

    private:
        Nodo** tabla;   // puntero a un array de punteros
        int capacidad;
        int numElementos;
        unsigned int funcionHash(const std::string& palabra) const;
        void rehash();
        static constexpr double UMBRAL_CARGA = 0.75;

    public:
        TablaHash(int cap);
        ~TablaHash();   

        void insertar(const std::string& palabra);
        int buscar(const std::string& palabra) const;
        void mostrarTabla() const;
        void reporteFrecuencias() const;
        void reporteTopN(unsigned n = 20) const;
};