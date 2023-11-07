#include <iterator>
#include <functional>
#include <cstdlib> //rand()
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

#define d_int int

using namespace std;
typedef unsigned long long ull;

int ull_bits = sizeof(ull) * 8;

// transformar vector de claves,valores a solo valores
vector<ull> transform_vector(vector<vector<ull>> old_data)
{
    ull vectorSize = old_data.size();
    vector<ull> finalVector;

    for (int i = 0; i < vectorSize; i++)
    {

        finalVector.push_back(old_data[i][1]);
    }

    return finalVector;
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
        fin = ull_bits - 1;
    }

    ull mask = (1ULL << (fin - inicio + 1)) - 1;
    return (n >> inicio) & mask;
}