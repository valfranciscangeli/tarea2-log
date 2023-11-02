#include "quick_sort.cpp"

int main()
{
    random_device rd;     // Genera una semilla aleatoria desde el dispositivo
    mt19937_64 gen(rd()); // Generador de números aleatorios de 64 bits
    ull max_value = static_cast<ull>(pow(2, 3)) - 1;
    uniform_int_distribution<ull> distribution(1, max_value);

    int vectorSize = 10; // cantidad de valores en el vector
    vector<ull> randomVector;

    for (int i = 0; i < vectorSize; i++) {
        ull randomValue = distribution(gen); // genera un número aleatorio en el rango de la distribucion
        randomVector[i] = randomValue;
    }

    // imprimimos el vector
    for (const ull x : randomVector) {
        cout << x << " ";
    }

    quick_sort(randomVector);
    // imprimimos el vector de vectores ordenado
    cout << "\nVector ordenado:\n";
    for (const ull x : randomVector) {
        cout << x << " ";
    }
    cout << "" << endl;

    return 0;
}
