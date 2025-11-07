#include <iostream>
#include <fstream>  
#include <string>
#include <vector>   
#include "TextUtil.h"
#include "HashTable.h"


int main(int argc, char *argv[]){

    if (argc < 3) {
        // argc cuenta el nombre del programa, así que necesitamos al menos 3 argumentos
        std::cerr << "Error: Faltan argumentos." << std::endl;
        std::cerr << "Uso: " << argv[0] << " input.txt stop_words.txt " << std::endl;
        return 1; // Salir con error
    }

    // variables de argumento
    std::string nombreArchivo = argv[1];
    std::string stopWordsArchivo = argv[2];

    TextProcessor miProcesador(stopWordsArchivo);

    TablaHash miTabla(73); // un primo grande

    std::ifstream archivo(nombreArchivo);   // abrir el archivo para lectura

    //verificar que se pueda abrir
    if(!archivo.is_open()){
        std::cerr <<"Error: No se pudo abrir el archivo" << nombreArchivo << std::endl;
        return 1;
    }

    std::string palabraLeida; // variable para almacenar cada palabra leida
    std::cout << "Procesando archivo '" << nombreArchivo << "'..." << std::endl;

    //procesar cada palabra del archivo
    while(archivo >> palabraLeida){
        // Limpiamos la palabra usando el método del procesador
        std::string palabraLimpia = miProcesador.limpiarPalabra(palabraLeida);
        // Verificamos que no esté vacía Y que no sea una stop word
        if (!palabraLimpia.empty() && !miProcesador.esStopWord(palabraLimpia)) {
            miTabla.insertar(palabraLimpia);
        }
    }

    archivo.close();
    std::cout << "Lectura de archivo completada." << std::endl;


    // mostrar los buckets con sus listas
    miTabla.mostrarTabla();     

    // mostrar el reporte de frecuencias
    miTabla.reporteFrecuencias();
    miTabla.reporteTopN(20);
    return 0;
}
