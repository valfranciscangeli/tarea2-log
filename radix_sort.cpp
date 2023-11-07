#include "bucket_sort.cpp"

// radix sort implementado como en el apunte, con el cambio
// de que ordena en bucket sort con la clave = secuencia de k bits
void radix_sort(vector<ull> &datos, ull k = 1)
{

    ull vectorSize = datos.size();
    vector<vector<ull>> newVector;

    for (ull inicio = 0; inicio < ull_bits; inicio += k)
    {
        // cout << "inicio: " << inicio << endl;
        ull final = inicio + k - 1;

        // cout << "final: " << final << endl;

        for (ull i = 0; i < vectorSize; i++)
        {

            vector<ull> subVector(2);
            subVector[0] = extractBits(datos[i], inicio, final);
            subVector[1] = datos[i];

            newVector.push_back(subVector);
        }
        datos = transform_vector(bucket_sort(newVector));
        newVector.clear();
    }
}
