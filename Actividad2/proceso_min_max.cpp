#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

void encontrar_min_max_nombres(const std::vector<std::string>& nombres) {
    std::string min_nombre = nombres[0];
    std::string max_nombre = nombres[0];

    for (const auto& nombre : nombres) {
        if (nombre.size() < min_nombre.size()) {
            min_nombre = nombre;
        }
        if (nombre.size() > max_nombre.size()) {
            max_nombre = nombre;
        }
    }

    std::cout << "Nombre con menos letras: " << min_nombre 
              << ", Nombre con más letras: " << max_nombre << std::endl;
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

    encontrar_min_max_nombres(nombres);

    return 0;
}
