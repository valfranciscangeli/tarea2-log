#include <iostream>
#include <vector>
#include <ctime>
#include <cstdio>
#include <cmath>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <sstream>
#include <chrono>
#include "../auxiliares.cpp"
#include "../radix_sort.cpp"

#define N_max 64
#define REPS 10 // numero de repeticiones por cada u

// Definición de tipos de datos
typedef unsigned long long ull;

/* Función auxiliar para obtener el k óptimo: recibe un valor máximo que representa el tamaño del universo y su máximo,
   y un 0 o 1 para indicar si se debería o no guardar un registro estadístico de los k utilizados */
void kOptimo(int exp)
{
    cout << "universo: [1, 2^" << exp << "]" << endl;

    vector<double> k_times;

    // creación de archivo de resultados para k si no existe
    FILE *results;
    results = fopen("Registro_de_tiempos_por_cada_k.csv", "a");

    vector<ull> test;
    for (int iteracion = 1; iteracion <= REPS; iteracion++)
    {
        cout << "iteracion: " << iteracion << endl;
        // generamos el arreglo para probar
        generateTestData(test, rand(), exp, 0, cantidad_de_valores);

        for (int log = 1; log <= exp + 1; log++)
        {
            cout << "probando k = " << log << endl;
            vector<ull> arreglo(test); // Se copia eltest facilitado
            auto start = chrono::high_resolution_clock::now();
            radix_sort(arreglo, log); // Se ordena el arreglo
            auto end = chrono::high_resolution_clock::now();
            auto us = chrono::duration_cast<chrono::microseconds>(end - start);
            k_times.push_back((double)us.count()); // se caclula el tiempo
            char linea[50];
            sprintf(linea, "%d,%d,%d,%d, %d\n", exp, log, (int)us.count(), iteracion, cantidad_de_valores);
            fwrite(linea, 1, strlen(linea), results);
        }
    }

    fclose(results);
    cout << "resultados registrados ..." << endl;
}

int main()
{
    random_device rd; // Genera una semilla aleatoria desde el dispositivo

    // Generación de archivos que registren los tiempos de ordenamiento de radixSort para k en cada universo
    FILE *k_times;
    k_times = fopen("Registro_de_tiempos_por_cada_k.csv", "w");
    char linea1[] = "n_universo, k, tiempo (micro segundos), iteracion, cantidad_valores_en_arreglo\n";
    fwrite(linea1, 1, strlen(linea1), k_times);
    fclose(k_times);

    // Tests para encontrar k optimo
    for (int exp = 1; exp <= N_max; exp++)
    {
        cout << "Pruebas para universo 2^" << exp << " en curso..." << endl;

        // Se calcula el k óptimo para el universo u
        kOptimo(exp);
    }

    separar_registros_de_k_por_exp();

    return 0;
}
