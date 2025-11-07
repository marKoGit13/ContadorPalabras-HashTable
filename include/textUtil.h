#pragma once

#include <string>
#include <fstream>
#include "HashTable.h"  // Para TablaHash

class TextProcessor {
private:
    TablaHash stopWords; // TablaHash interna para las stop words
    void cargarStopWords(const std::string& rutaArchivo);

public:
    // Constructor: recibe la RUTA al archivo de stop words
    TextProcessor(const std::string& rutaStopWords);

    // Metodo para limpiar 
    std::string limpiarPalabra(const std::string& palabra) const;

    // Metodo para verificar si es una stop word
    bool esStopWord(const std::string& palabra) const;
};