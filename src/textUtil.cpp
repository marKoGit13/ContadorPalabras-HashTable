#include "textUtil.h"
#include <string>
#include <cctype> // Para isalpha() y tolower()

std::string limpiarPalabra(const std::string& palabra) {
    std::string limpia = "";
    for (char c : palabra) {
        // Solo incluye caracteres alfabéticos
        if (std::isalpha(c)) {
            limpia += std::tolower(c); // los convierte a minúscula
        }
    }
    return limpia;
}