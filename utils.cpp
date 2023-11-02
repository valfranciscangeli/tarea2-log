#include "auxiliares.cpp"
using namespace std;
typedef unsigned long long ull;


bool extractKBit(ull num, int k)
{
    // Crea una máscara para aislar el bit k menos significativo
    ull mask = 1ULL << k;

    // Aplica una operación AND con la máscara y verifica si el bit k es 1 o 0
    return (num & mask) != 0;
}