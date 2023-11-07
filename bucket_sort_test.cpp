#include "bucket_sort.cpp"

int main()
{
    random_device rd;     // Genera una semilla aleatoria desde el dispositivo
    mt19937_64 gen(rd()); // Generador de números aleatorios de 64 bits
    ull max_value = static_cast<ull>(pow(2, 64)) - 1;
    uniform_int_distribution<ull> distribution(1, max_value);

    int vectorSize = pow(2, 3); // cantidad de valores en el vector
    vector<vector<ull>> randomVector;

    for (int i = 0; i < vectorSize; i++)
    {
        cout << "creando valor..." << endl;
        ull randomValue = distribution(gen); // genera un número aleatorio en el rango de la distribucion
        vector<ull> subVector(2);
        subVector[0] = extractBits(randomValue, 0, 3); // probamos pasando como clave el 1 bit menos significativo
        subVector[1] = randomValue;

        randomVector.push_back(subVector);
    }

    // imprimimos el vector de vectores
    for (const auto &subVector : randomVector)
    {
        cout << "{" << subVector[0] << ", " << subVector[1] << "} ";
    }

    vector<vector<ull>> test = bucket_sort(randomVector);
    // imprimimos el vector de vectores ordenado
    cout << "\nVector ordenado:\n";
    for (const auto &subVector : test)
    {
        cout << "{" << subVector[0] << ", " << subVector[1] << "} ";
    }
    cout << "" << endl;

    return 0;
}
