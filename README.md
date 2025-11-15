# Contador de Frecuencia de Palabras con Tabla Hash

[![Lenguaje](https://img.shields.io/badge/Lenguaje-C%2B%2B-blue.svg)](https://isocpp.org/)
[![Build](https://img.shields.io/badge/Build-Makefile-brightgreen.svg)]()

Implementación avanzada de una **Tabla Hash en C++** para el conteo eficiente de frecuencia de palabras (NLP). Incluye **Encadenamiento Separado**, **Re-hashing Dinámico**, filtrado de **Stop Words** y **normalización de palabras**.

## Índice

* [Características Principales](#características-principales)
* [Estructura del Proyecto](#estructura-del-proyecto)
* [Requisitos](#requisitos)
* [Compilación y Uso](#compilación-y-uso)

---

## Características Principales

Este proyecto va más allá de un simple contador e implementa características clave para un análisis de texto robusto:

1.  **Tabla Hash Optimizada:**
    * **Encadenamiento Separado (Chaining):** Implementa listas enlazadas para un manejo eficiente de colisiones.
    * **Hash Polinomial:** Utiliza una función de hash polinomial (`hash * 31 + char`), efectiva para distribuir claves de tipo `std::string`.
2.  **Rendimiento O(1) Amortizado:**
    * **Re-hashing Dinámico:** La tabla monitorea su factor de carga. Si supera el 75%, la tabla se redimensiona automáticamente (duplicando su capacidad) y redistribuye todos los elementos para mantener el rendimiento de inserción y búsqueda en O(1) amortizado.
3.  **Preprocesamiento de Texto (NLP):**
    * **Normalización de Acentos:** La función `limpiarPalabra` normaliza caracteres UTF-8 específicos para un conteo específico y de calidad.
    * **Filtrado de Stop Words:** El programa carga una lista de "stop words" (en español o inglés) en una `TablaHash` separada y las excluye del conteo para centrar el análisis en las palabras más significativas.
4.  **Análisis de Resultados:**
    * **Reporte "Top N":** Incluye una función `reporteTopN()` que ordena los resultados y muestra las N palabras más frecuentes, facilitando el análisis de los datos.
    * **Pruebas Comparativas:** El `Makefile` está configurado para procesar múltiples corpus de texto (Libros, Spam, No-Spam) y generar reportes comparativos.

---

## Estructura del Proyecto

* ContadorPalabras-HashTable/ 
* ├── Makefile # Script de compilación y ejecución
* ├── README.md # Documentación del proyecto 
* ├── include/ # Archivos de cabecera (.h) 
* │ ├── HashTable.h 
* │ └── TextUtil.h 
* ├── src/ # Archivos fuente (.cpp) 
* │ ├── HashTable.cpp 
* │ ├── TextUtil.cpp 
* │ └── main.cpp 
* ├── input/ # Archivos de texto de entrada (pruebas)
* │ └── Books/
* │ └── NoSpam/
* │ └── Spam/
* │ └── LaGuerraInjusta.txt 
* │ └── stop_words_en.txt
* │ └── stop_words_es.txt 
* ├── reporte/ # Archivos de salida (frecuencia de palabras) 
* ├── bin/ # Ejecutable compilado 
* ├── build/ # Archivos objeto temporales (.o)

---

## Requisitos

1.  **Un compilador de C++:** Compatible con C++17 o superior (ej. g++, Clang).
2.  **Make:** La utilidad `make` para automatizar la compilación.
3.  **Sistema (Opcional):** Un entorno tipo Unix (Linux, macOS, o MINGW/MSYS2 en Windows) para que los scripts del `Makefile` funcionen correctamente.

---

## Compilación y Uso

El proyecto utiliza un `Makefile` para simplificar la compilación y ejecución.

1.  **Clonar el repositorio:**
    ```bash
    git clone [https://github.com/tu_usuario/ContadorPalabras-HashTable.git](https://github.com/tu_usuario/ContadorPalabras-HashTable.git)
    cd ContadorPalabras-HashTable
    ```

2.  **Compilar el proyecto:**
    ```bash
    make
    ```
    Esto compilará el código fuente y creará el ejecutable en `bin/contador.exe`.

3.  **Ejecutar todas las pruebas:**
    ```bash
    make run
    ```
    Esto ejecutará el programa para **todos** los archivos `.txt` en las carpetas `input/Books`, `input/Spam` y `input/NoSpam`. Los reportes de salida se guardarán en sus respectivas carpetas dentro de `reporte/`.

4.  **Limpiar archivos generados:**
    ```bash
    make clean
    ```
    Esto eliminará las carpetas `bin/`, `build/` y `reporte/` con todo su contenido.

