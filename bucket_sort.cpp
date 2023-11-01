#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef unsigned long long ull;

// bucket sort se basa en el algortimo descrito en el Apunte,
// considerando un valor minimo en base al arreglo y no fijo en 1 por defecto
vector<ull> bucket_sort(vector<ull> A, bool init1 = false)
{
    if (A.empty())
    {
        return A; // si el vector está vacío, no hay nada que ordenar.
    }

    ull minimo = *min_element(A.begin(), A.end());
    ull maximo = *max_element(A.begin(), A.end());
    if (init1)
        minimo = 1;

    vector<ull> C(maximo - minimo + 1, 0);

    for (int i = 0; i < A.size(); i++)
    {
        C[A[i] - minimo] += 1; // contamos cuántos valores de cada uno hay en A
    }

    for (int j = 1; j < C.size(); j++)
    {
        C[j] += C[j - 1]; // actualizamos C para que guarde punteros
    }

    vector<ull> B(A.size()); // se crea B

    for (int i = A.size() - 1; i >= 0; i--)
    {
        B[C[A[i] - minimo] - 1] = A[i]; // agregamos en la posicion que dice C en B cada valor de A
        C[A[i] - minimo] -= 1;
    }

    return B;
}

int main()
{
    vector<ull> test = {1, 5, 2, 6, 4, 6, 8, 5, 2, 5, 2, 1, 4, 5, 1, 2, 3, 4, 5, 6, 7, 6, 1, 9, 9, 9, 4, 9, 2, 3};

    test = bucket_sort(test);

    for (ull elem : test)
    {
        cout << elem << "\n";
    }

    return 0;
}
