#include "auxiliares.cpp"
using namespace std;
typedef unsigned long long ull;
int ull_bits = sizeof(ull) * 8;

bool extractKBit(ull num, int k)
{
    // Crea una máscara para aislar el bit k menos significativo
    ull mask = 1ULL << k;

    // Aplica una operación AND con la máscara y verifica si el bit k es 1 o 0
    return (num & mask) != 0;
}

ull obtenerBitsMenosSignificativos(ull n, ull k)
{
    // Máscara para obtener los k bits menos significativos
    ull mascara = (1ULL << k) - 1ULL;

    // Aplicar la máscara para obtener los bits
    ull bitsMenosSignificativos = n & mascara;

    return bitsMenosSignificativos;
}

// extraer los bits de n desde un indice inicio a fin contando el indice
// 0 como el bit menos significativo
// el resultado incluye el bit final
ull extractBits(ull n, int inicio, int fin)
{
    if (inicio < 0 || fin < inicio)
    {
        // Verificar si los índices son válidos
        cerr << "Índices no válidos." << endl;
        return 0;
    }
    else if (fin >= ull_bits)
    {
        fin = ull_bits-1;
    }

    ull mask = (1ULL << (fin - inicio + 1)) - 1;
    return (n >> inicio) & mask;
}