#include "textUtil.h"
#include <string>
#include <iostream>
#include <cctype> // Para isalpha() y tolower()

TextProcessor::TextProcessor(const std::string& rutaStopWords) : stopWords(1000) { // Inicializa la TablaHash interna
    cargarStopWords(rutaStopWords);
}

void TextProcessor::cargarStopWords(const std::string& rutaArchivo) {
    std::ifstream stopFile(rutaArchivo);
    if (!stopFile.is_open()) {
        std::cerr << "ADVERTENCIA: No se pudo abrir el archivo de stop words en " << rutaArchivo << std::endl;
        return;
    }

    std::string stopWord;
    int contador = 0;
    while (stopFile >> stopWord) {
        // Asumimos que las stop words ya están limpias y en minúsculas
        stopWords.insertar(stopWord);
        contador++;
    }
    stopFile.close();
    std::cout << "Se cargaron " << contador << " stop words desde '" << rutaArchivo << "'." << std::endl;
}

// Normalizacion de palabras
std::string TextProcessor::limpiarPalabra(const std::string& palabra) const {
    std::string limpia = "";
    for (char c : palabra) {
        if (std::isalpha(c)) {
            limpia += std::tolower(c);
        }
    }
    return limpia;
}

// --- Implementación de la verificación de Stop Word ---
// Devuelve 'true' si la palabra está en la tabla de stop words
bool TextProcessor::esStopWord(const std::string& palabra) const {
    // buscar() devuelve 0 si no la encuentra (no es stop word)
    // Devuelve > 0 si la encuentra (SÍ es stop word)
    return stopWords.buscar(palabra) > 0;
}