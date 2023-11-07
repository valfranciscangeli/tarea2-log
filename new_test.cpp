#include <iostream>

unsigned long long extractBits(unsigned long long n, int inicio, int fin) {
    if (inicio < 0 || fin < inicio || fin >= 64) {
        // Verificar si los índices son válidos
        std::cerr << "Índices no válidos." << std::endl;
        return 0;
    }

    unsigned long long mask = (1ULL << (fin - inicio + 1)) - 1;
    return (n >> inicio) & mask;
}

int main() {
    unsigned long long n = 0b1101011010101010;  // Ejemplo: 56394 en decimal
    int inicio = 0;
    int fin = 3;

    unsigned long long resultado = extractBits(n, inicio, fin);
    std::cout << "Bits desde la posición " << inicio << " hasta " << fin << ": " << resultado << std::endl;


    int ull_bits = sizeof(unsigned long long) * 8;

    std::cout << ull_bits << std::endl;

    return 0;
}
