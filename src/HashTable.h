#pragma once

#include <string>

// Se crea un nodo que contendrá:
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
        unsigned int funcionHash(const std::string& palabra) const;

    public:
        TablaHash(int cap = 100);
        ~TablaHash();

        void insertar(const std::string& palabra);
        int buscar(const std::string& palabra) const;
        void mostrarTabla() const;
};