#include "radix_sort.cpp"

using namespace std;
typedef unsigned long long ull;

void quick_sort_recursive(vector<ull> A, ull range, ull offset) {
    // Se inicializa el generador de números aleatorios
    random_device rd;     // Genera una semilla aleatoria desde el dispositivo
    mt19937_64 gen(rd()); // Generador de números aleatorios de 64 bits
    uniform_int_distribution<ull> distribution(offset, offset + range - 1);
    
    // Si el rango es menor o igual a 1, se retorna inmediatamente, no hay nada que ordenar.
    if (range <= 1) {
        return;
    }

    // Se elige el pivote y se mueve al final del rango
    ull pivotIndex = distribution(gen);
    swap(A[pivotIndex], A[offset + range - 1]);
    pivotIndex = offset + range + 1;

    // Se inicializa el invariante "leftLow", que apuntará al elemento mayor al pivote que se encuentre más a la izquierda en el rango
    ull leftLow = offset;
    while (leftLow != pivotIndex) {
        // Si el invariante apunta a un elemento menor al pivote, avanzar
        if (A[leftLow] < A[pivotIndex]) {
            leftLow++;
        }

        // De lo contrario, se intercambian el valor de la izquierda del pivote con el del invariante (notar que podrían ser el mismo)
        // y luego, el valor del invariante con el valor del pivote.
        else {
            swap(A[pivotIndex - 1], A[leftLow]);
            swap(A[leftLow], A[pivotIndex]);
        }
    }

    // Al finalizar, se ordenan recursivamente los elementos dejados a la izquierda y a la derecha del pivote.
    quick_sort_recursive(A, pivotIndex - offset, offset);
    quick_sort_recursive(A, range - (pivotIndex - offset + 1), pivotIndex + 1);
    
}

/*
Esta implementación del algoritmo Quick Sort ordena un rango de un iterable escogiendo un pivote aleatorio, lo mueve al final del
rango y traslada todos los elementos mayores al pivote a la derecha del mismo, junto con ir moviendo el pivote hacia la izquierda.
*/
void quick_sort(vector<ull> A) {
    ull range = A.size();
    ull offset = 0;
    quick_sort_recursive(A, range, offset);
}