#include "quick_sort.cpp"

int main()
{

    random_device rd;     // Genera una semilla aleatoria desde el dispositivo
    mt19937_64 gen(rd()); // Generador de números aleatorios de 64 bits
    ull max_value = static_cast<ull>(pow(2, 64)) - 1;
    uniform_int_distribution<ull> distribution(1, max_value);

    int vectorSize = 1e7; // cantidad de valores en el vector
    vector<ull> randomVector;

    for (int i = 0; i < vectorSize; i++)
    {
        ull randomValue = distribution(gen); // genera un número aleatorio en el rango de la distribucion

        randomVector.push_back(randomValue);
    }

    vector<ull> copia;
    copia = randomVector;
    sort(copia.begin(), copia.end());
    cout << "inicio, ordenado?: \n"
         << (copia == randomVector) << endl;

    // imprimimos el vector original
    cout << "vector original...\n"
         << endl;
    for (ull valor : randomVector)
    {
        cout << valor << "\n";
    }

    quick_sort(randomVector);
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