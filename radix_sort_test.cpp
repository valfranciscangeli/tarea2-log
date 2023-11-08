#include "radix_sort.cpp"

int main()
{

    // vector<vector<ull>> test = {{1, 1042833746082220333},
    //                             {0, 15469111748355623932},
    //                             {0, 13895158232237021234},
    //                             {0, 2308042319049997580},
    //                             {0, 12490343978346861738},
    //                             {0, 10029179319439415190},
    //                             {0, 16025845623925501348},
    //                             {1, 8135785063435569109}};
    // vector<ull> resultado = transform_vector(test);

    // for (ull value : resultado)
    // {
    //     cout << value << endl;
    // }

    random_device rd;     // Genera una semilla aleatoria desde el dispositivo
    mt19937_64 gen(rd()); // Generador de números aleatorios de 64 bits
    ull max_value = static_cast<ull>(pow(2, 64)) - 1;
    uniform_int_distribution<ull> distribution(1, max_value);

    int vectorSize = 1e8; // cantidad de valores en el vector
    vector<ull> randomVector;

    for (int i = 0; i < vectorSize; i++)
    {
        ull randomValue = distribution(gen); // genera un número aleatorio en el rango de la distribucion

        randomVector.push_back(randomValue);
    }

    vector<ull> copia;
    copia = randomVector;
    sort(copia.begin(), copia.end());
    cout << "inicio, ¿ordenado?: \n"
         << (copia == randomVector) << endl;

    // imprimimos el vector original
    cout << "vector original...\n"
         << endl;
    for (ull valor : randomVector)
    {
        cout << valor << "\n";
    }

    radix_sort(randomVector,28);
    // imprimimos el vector ordenado
    cout << "vector ordenado... \n"
         << endl;
    for (ull valor : randomVector)
    {
        cout << valor << "\n";
    }
    cout << "fin \n"
         << endl;

    cout << "prueba final, ¿ordenado?: \n"
         << (copia == randomVector) << endl;

    return 0;
}