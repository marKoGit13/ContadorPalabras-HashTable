#include <iostream>
#include <fstream>  // Para leer archivos (ifstream)
#include <string>
#include <vector>   // para vectores
#include "TextUtil.h"
#include "HashTable.h"


int main(int argc, char *argv[]){

    if (argc < 2) {
        // argc cuenta el nombre del programa, así que necesitamos al menos 2 argumentos
        std::cerr << "Error: Por favor, especifica el nombre del archivo de entrada." << std::endl;
        std::cerr << "Uso: " << argv[0] << " input.txt " << std::endl;
        return 1; // Salir con error
    }

    TablaHash miTabla(10000);

    std::string nombreArchivo = argv[1]; // obtener el nombre del archivo desde los argumentos
    std::ifstream archivo(nombreArchivo);   // abrir el archivo para lectura

    //verificar que se pueda abrir
    if(!archivo.is_open()){
        std::cerr <<"Error: No se pudo abrir el archivo" << nombreArchivo << std::endl;
        return 1;
    }

    std::string palabraLeida; // variable para almacenar cada palabra leida

    //procesar cada palabra del archivo
    while(archivo >> palabraLeida){
        std::string palabraLimpia = limpiarPalabra(palabraLeida);
        miTabla.insertar(palabraLimpia);
    }

    std::cout << "Lectura de archivo '" << nombreArchivo << "' completada." << std::endl;

    // mostrar los buckets con sus listas
    miTabla.mostrarTabla();     

    // mostrar el reporte de frecuencias
    miTabla.reporteFrecuencias();

    //Búsquedas de prueba
    std::vector<std::string> palabrasBusqueda = {"la", "guerra", "injusta", "y", "paz", "amor", "odio"};
    for(const std::string& palabra : palabrasBusqueda){
        int frecuencia = miTabla.buscar(palabra);
        std::cout << "La palabra '" << palabra << "' aparece " << frecuencia << " veces." << std::endl;
    }
    
    //cerrar archivo
    archivo.close();

    return 0;
}
