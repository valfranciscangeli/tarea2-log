#include "bucket_sort.cpp"

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

void radix_sort(vector<ull> &datos, ull k = 1)
{

    ull vectorSize = datos.size();
    vector<vector<ull>> newVector;

    for (int inicio = 0; inicio < ull_bits; inicio += k)
    {
        cout << "inicio: " << inicio << endl;
        ull final = inicio + k - 1;

        cout << "final: " << final << endl;

        for (int i = 0; i < vectorSize; i++)
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
