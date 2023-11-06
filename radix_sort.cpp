#include "bucket_sort.cpp"

int ull_bits = sizeof(ull) * 8;

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

void radix_sort(vector<ull> &datos, int k)
{

    ull vectorSize = datos.size();
    vector<vector<ull>> newVector;

    for (int k = 0; k < ull_bits; k++)
    {

        for (int i = 0; i < vectorSize; i++)
        {
            vector<ull> subVector(2);
            subVector[0] = extractKBit(datos[i], k); // vamos ordenando por el bit k menos significativo
            subVector[1] = datos[i];

            newVector.push_back(subVector);
        }
        datos = transform_vector(bucket_sort(newVector));
        newVector.clear();
    }
}
