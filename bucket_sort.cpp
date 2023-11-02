#include "utils.cpp"

using namespace std;
typedef unsigned long long ull;


// bucket sort se basa en el algoritmo descrito en el Apunte,
// considerando un valor mínimo en base al arreglo y no fijo en 1 por defecto
// vector A contiene como elementos una (clave, contenido), esto se modificó para
// poder aplicar el algoritmo de Radix Sort
vector<vector<ull>> bucket_sort(vector<vector<ull>> A, bool init1 = false)
{
    ull minimo, maximo;
    minimo = numeric_limits<ull>::max();
    maximo = numeric_limits<ull>::min();

    for (vector<ull> elem : A)
    {
        ull clave = elem[0];
        if (!init1)
        {
            minimo = min(clave, minimo);
        }
        maximo = max(clave, maximo);
    }

    vector<ull> C(maximo - minimo + 1, 0);

    for (int i = 0; i < A.size(); i++)
    {
        ull A_i = A[i][0];    // la clave
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

    return B;
}

