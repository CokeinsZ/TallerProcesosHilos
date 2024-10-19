#include <iostream>
#include <fstream>
#include <string>
#include <vector>

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

    std::cout << "Nombres con número par de caracteres:\n";
    for (const auto& nombre : nombres) {
        if (nombre.size() % 2 == 0) {
            std::cout << nombre << " (" << nombre.size() << " caracteres)\n";
        }
    }

    return 0;
}
