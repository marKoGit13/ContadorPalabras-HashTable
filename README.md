# Contador de Frecuencia de Palabras con Tabla Hash

[![Lenguaje](https://img.shields.io/badge/Lenguaje-C%2B%2B-blue.svg)](https://isocpp.org/)
[![Licencia](https://img.shields.io/badge/Licencia-MIT-green.svg)](LICENSE)

Implementación de una Tabla Hash con Encadenamiento Separado (Chaining) en C++ para contar eficientemente la frecuencia de palabras en un archivo de texto.

## Índice

* [Instalación](#instalación)
* [Uso](#uso)
* [Estructura del Proyecto](#estructura-del-proyecto)
* [Cómo Funciona](#cómo-funciona)
* [Contribución](#contribución)
* [Licencia](#licencia)
* [Contacto](#contacto)

---

## Instalación

Para compilar y ejecutar este proyecto, necesitas:

1.  **Un compilador de C++:** Compatible con C++11 o superior (ej. g++, Clang).
2.  **Make:** La utilidad `make` para automatizar la compilación.
3.  **Clonar el repositorio:**
    ```bash
    git clone [https://github.com/tu_usuario/ContadorPalabras-HashTable.git](https://github.com/tu_usuario/ContadorPalabras-HashTable.git)
    cd ContadorPalabras-HashTable
    ```

---

## Uso

El proyecto utiliza un `Makefile` para simplificar la compilación y ejecución. Abre una terminal en la raíz del proyecto y usa los siguientes comandos:

1.  **Compilar el proyecto:**
    ```bash
    make
    ```
    Esto creará el ejecutable en la carpeta `bin/`.

2.  **Ejecutar el programa:**
    ```bash
    make run
    ```
    Esto ejecutará el programa usando el archivo `input/LaGuerraInjusta.txt` por defecto y guardará el reporte de frecuencias en `reporte/reporte_frecuencias.txt`.

    * **Para usar otro archivo de entrada:** Puedes modificar la variable `INPUT_FILE` en el `Makefile` o ejecutar manualmente:
        ```bash
        ./bin/contador ruta/a/tu/archivo.txt > reporte/otro_reporte.txt
        ```

3.  **Limpiar archivos generados:**
    ```bash
    make clean
    ```
    Esto eliminará las carpetas `bin/`, `build/` y los archivos de reporte generados.

---

## Estructura del Proyecto

/ContadorPalabras-HashTable/ |-- Makefile |-- README.md |-- include/ # Archivos de cabecera (.h) | |-- HashTable.h | |-- TextUtil.h |-- src/ # Archivos de implementación (.cpp) | |-- HashTable.cpp | |-- TextUtil.cpp | |-- main.cpp |-- input/ # Archivos de texto de entrada | |-- LaGuerraInjusta.txt |-- reporte/ # Archivos de salida (reporte de frecuencias) |-- bin/ # Ejecutable compilado |-- build/ # Archivos objeto temporales (.o)


---

## Cómo Funciona

1.  **Lectura y Limpieza:** El programa lee un archivo de texto palabra por palabra. Cada palabra se "limpia" (convierte a minúsculas y se eliminan caracteres no alfabéticos) usando las funciones en `TextUtil`.
2.  **Hashing:** La palabra limpia se pasa a una **función de hash polinomial** implementada en `HashTable` para calcular un índice (bucket).
3.  **Inserción/Conteo:** Se accede al bucket correspondiente. Si la palabra ya existe en la lista enlazada (colisión), se incrementa su contador. Si no existe, se añade un nuevo nodo al inicio de la lista con contador 1.
4.  **Búsqueda y Reporte:** Se puede buscar la frecuencia de una palabra específica o generar un reporte completo (`reporteFrecuencias`) que recorre toda la tabla.

---

## Contribución

Este es un proyecto académico. Por el momento, no se buscan contribuciones externas.

---

## Licencia

Este proyecto está bajo la Licencia MIT. Consulta el archivo `LICENSE` para más detalles.
*(Nota: Deberás crear un archivo llamado `LICENSE` y pegar el texto de la licencia MIT allí).*

---

## Contacto

Si tienes alguna pregunta o sugerencia, puedes contactar a:

* **[Tu Nombre]** - [tu_email@ejemplo.com]
* **[Nombre Compañero 1 (si aplica)]** - [email_compañero1@ejemplo.com]
* *(Añade más compañeros si es necesario)*

*(Reemplaza los placeholders con tu información real).*