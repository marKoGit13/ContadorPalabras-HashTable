#include <iostream>
#include <fstream>  // Para leer archivos (ifstream)
#include <string>
#include <vector>   // para vectores
#include <cctype>   // Para tolower() y isalpha()
#include "HashTable.h"

// creamos una funcion limpiador que quita la puntuación 
// y devuelve en minúsculo la palabra

std::string limpiarPalabra(const std::string& palabra){
    std::string limpia = "";
    for(char c : palabra){
        if(std::isalpha(c)){    //solo evaulua caracteres alfabeticos
            limpia += std::tolower(c);
        }
    }
    return limpia;
}

void imprimirResultadoBusqueda(const TablaHash& tabla, const std::string& palabraABuscar) {
    int conteo = tabla.buscar(palabraABuscar);
    std::cout << "'" << palabraABuscar << "': " << conteo << std::endl;
}

void imprimirResultadosPrueba(const TablaHash& tabla, const std::vector<std::string>& palabrasPrueba) {
    std::cout << "\n--- Resultados de la Prueba ---" << std::endl;
    // Itera sobre el vector de palabras
    for (const std::string& palabra : palabrasPrueba) {
        // Llama a la función que ya teníamos para cada palabra
        imprimirResultadoBusqueda(tabla, palabra);
    }
}

int main(int argc, char *argv[]){

    if (argc < 2) {
        // argc cuenta el nombre del programa, así que necesitamos al menos 2 argumentos
        std::cerr << "Error: Por favor, especifica el nombre del archivo de entrada." << std::endl;
        std::cerr << "Uso: " << argv[0] << " input.txt " << std::endl;
        return 1; // Salir con error
    }

    std::string nombreArchivo = argv[1];

    TablaHash miTabla(20);

    std::ifstream archivo(nombreArchivo);

    //verificar que se pueda abrir
    if(!archivo.is_open()){
        std::cerr <<"Error: No se pudo abrir el archivo" << nombreArchivo << std::endl;
        return 1;
    }

    std::string palabraLeida;

    //procesar cada palabra del archivo
    while(archivo >> palabraLeida){
        std::string palabraLimpia = limpiarPalabra(palabraLeida);
        miTabla.insertar(palabraLimpia);
    }

    std::cout << "Lectura de archivo '" << nombreArchivo << "' completada." << std::endl;

    // mostrar los buckets con sus listas
    miTabla.mostrarTabla();

    //cerrar archivo
    archivo.close();

    // --- Definir la lista de palabras a probar ---
    std::vector<std::string> palabrasParaProbar = {
        "hola", "mundo", "estructura", "de", "datos",
        "este", "es", "un", "texto", "prueba", "simple"
    };

    imprimirResultadosPrueba(miTabla, palabrasParaProbar);

    return 0;
}
