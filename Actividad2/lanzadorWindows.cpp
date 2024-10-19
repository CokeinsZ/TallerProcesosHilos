#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <windows.h>

#define MAX_NAME_LENGTH 100

// Función para ordenar nombres en orden alfabético descendente
void ordenar_nombres(std::vector<std::string>& nombres) {
    std::sort(nombres.begin(), nombres.end(), std::greater<std::string>());
}

// Función para crear un proceso hijo
void crear_proceso(LPSTR nombre_programa) {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Crear el proceso
    if (!CreateProcess(NULL, nombre_programa, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        std::cerr << "Fallo al crear el proceso: " << nombre_programa << std::endl;
        return;
    }

    // Esperar a que el proceso termine
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Cerrar los handles
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

int main() {
    std::ifstream archivo("nombres.txt");
    if (!archivo) {
        std::cerr << "Error al abrir el archivo\n";
        return 1;
    }

    std::vector<std::string> nombres;
    std::string nombre;

    // Leer los nombres del archivo
    while (std::getline(archivo, nombre, ',')) {
        nombres.push_back(nombre);
    }
    archivo.close();

    // Ordenar los nombres en orden alfabético descendente (Tarea del padre)
    ordenar_nombres(nombres);
    std::cout << "Nombres ordenados: ";
    for (size_t i = 0; i < nombres.size(); ++i) {
        std::cout << nombres[i];
        if (i < nombres.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "\n";

    // Crear procesos hijos
    // Proceso 1: Encontrar nombres con longitud mínima y máxima
    crear_proceso((LPSTR)"proceso_min_max.exe");

    // Proceso 2: Imprimir nombres con longitud par
    crear_proceso((LPSTR)"proceso_pares.exe");

    // Proceso 3: Imprimir nombres con longitud impar
    crear_proceso((LPSTR)"proceso_impares.exe");

    return 0;
}
