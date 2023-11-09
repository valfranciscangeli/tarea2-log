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
#include "../quick_sort.cpp"
#include "../radix_sort.cpp"
#include "../auxiliares.cpp"

#define N_max 64
#define REPS 100 // 100
#define dbg 0    // cambiar a 1 para debugear
// Definición de tipos de datos
typedef unsigned long long ull;



// arreglo de k's elegido
vector<ull> ks = {2, 3, 4, 5, 6, 6, 8, 9, 8, 11, 12, 13, 14, 13, 16, 16, 18, 19, 16, 16, 22, 23, 23, 22, 22, 24, 22, 22, 22, 22, 23, 23, 23, 23, 23, 27, 29, 22, 24, 26, 23, 22, 29, 22, 26, 22, 29, 22, 22, 22, 22, 22, 23, 24, 22, 26, 22, 23, 22, 22, 30, 28, 22, 28};

int main()
{
   
    random_device rd; // Genera una semilla aleatoria desde el dispositivo

    int tests = 0;
    vector<ull> data;

    // Tests para ambos algoritmos. Para n de 1 a 64
    for (int exp = 33; exp <= N_max; exp++)
    {
        cout << "Pruebas para universo 2^" << exp << " en curso..." << endl;
        // Creación del nombre del archivo
        char archivoFilename[50];
        // Creación de archivos con resultados
        sprintf(archivoFilename, "resultados_2^%d.csv", exp);
        FILE *results_ptr;
        results_ptr = fopen(archivoFilename, "w");
        // se inicializa la línea de encabezados: algoritmo, iteración, tiempo de generación de datos, tiempo ordenamiento
        char encabezado[] = "s_name,repeticion,gen_time(s),sort_time(us),cantidad_valores_en_arreglo\n";
        fwrite(encabezado, 1, strlen(encabezado), results_ptr);

        // Variables de tiempo
        clock_t start, end;
        double tempo1, tempo2; // Tiempos de generación de datos y ordenamiento

        // 100 repeticiones para cada n, usando diferentes semillas
        for (tests = 0; tests < REPS; tests++)
        {
            cout << "Repeticion: " << tests + 1;
            // Inicialización de línea de resultados
            char resultRow1[50];
            char resultRow2[50];

            // Se genera uno de los arreglos
            // Llama a la función generateTestData aquí si está definida.

            cout << " Generando Data..." << endl;
            auto start = chrono::high_resolution_clock::now();
            generateTestData(data, rand(), exp, dbg, cantidad_de_valores);
            auto end = chrono::high_resolution_clock::now();
            auto tempo1 = chrono::duration_cast<chrono::microseconds>(end - start);

            // Llamada a Quicksort
            cout << " Llamando a QuickSort..." << endl;
            vector<ull> copia_de_data1(data); // copiamos la data
            start = chrono::high_resolution_clock::now();
            quick_sort(copia_de_data1);
            end = chrono::high_resolution_clock::now();
            auto tempo2 = chrono::duration_cast<chrono::microseconds>(end - start);
            // registro resultados quicksort
            sprintf(resultRow1, "quick,%d,%.7f,%d,%d\n", tests + 1, (double)tempo1.count() / 1000000,
                    (long int)tempo2.count(), cantidad_de_valores);

            // Llamada a Radixsort
            cout << " LLamando a RadixSort..." << endl;
            vector<ull> copia_de_data2(data); // copiamos la data
            start = chrono::high_resolution_clock::now();
            // extraer el k del arreglo de k's
            ull k = ks[exp - 1];
            cout << "k a usar: " << k << endl;
            radix_sort(copia_de_data2, k);
            end = chrono::high_resolution_clock::now();
            tempo2 = chrono::duration_cast<chrono::microseconds>(end - start);
            // registro resultados radixsort
            sprintf(resultRow2, "radix,%d,%.7f,%d,%d\n", tests + 1, (double)tempo1.count() / 1000000,
                    (long int)tempo2.count(), cantidad_de_valores);

            // Registro de resultados
            fwrite(resultRow1, 1, strlen(resultRow1), results_ptr);
            fwrite(resultRow2, 1, strlen(resultRow2), results_ptr);

            // Reset de data anterior
            data.clear();
        }
        fclose(results_ptr);
    }
    return 0;
}
