#include <iostream>
#include <assert.h>

using namespace std;
typedef unsigned long long ull;

int ull_bits = sizeof(ull) * 8;

ull obtenerBitsMenosSignificativos(ull n, ull k)
{
    // Máscara para obtener los k bits menos significativos
    ull mascara = (1ULL << k) - 1ULL;

    // Aplicar la máscara para obtener los bits
    ull bitsMenosSignificativos = n & mascara;

    return bitsMenosSignificativos;
}

void modified_radixSort(vector<ull> &A, ull k = 1)
{

    int cantidad_iteraciones = ceil(ull_bits / k);

    // aquí se ejecutará una vez por cada pasada de bucket sort que se necesite
    for (int iter = 0; iter < cantidad_iteraciones; iter++)
    {

        ull minimo, maximo;
        minimo = 0;
        maximo = 1;

        for (vector<ull> elem : A)
        {
            ull clave = obtenerBitsMenosSignificativos(elem, k);
            minimo = min(clave, minimo);
            maximo = max(clave, maximo);
        }

        // inicializamos el vector de contadores C
        vector<ull> C(maximo - minimo + 1, 0);

        // rellenamos el vector C con las ocurrencias de cada clave en A
        for (int i = 0; i < A.size(); i++)
        {
            ull A_i = obtenerBitsMenosSignificativos(A[i], k);    // la clave
            C[A_i - minimo] += 1; // contamos cuántos valores de cada uno hay en A
        }

        for (int j = 1; j < C.size(); j++)
        {
            C[j] += C[j - 1]; // actualizamos C para que guarde punteros
        }

        vector<vector<ull>> B(A.size()); // se crea B

        for (int i = A.size() - 1; i >= 0; i--)
        {
            ull A_i = A[i][0];             // la clave
            B[C[A_i - minimo] - 1] = A[i]; // agregamos en la posición que dice C en B cada valor de A
            C[A_i - minimo] -= 1;
        }
    }

    return;
}

int main()
{

    // pruebas de obtenerBitsMenosSignificativos ====================
    assert(obtenerBitsMenosSignificativos(13783, 4) == 7);
    assert(obtenerBitsMenosSignificativos(0, 2) == 0);
    assert(obtenerBitsMenosSignificativos(46784, 3) == 0);

    return 0;
}
