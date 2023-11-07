#include <iostream>
#include <vector>
#include <ctime>
#include <cstdio>
#include <cmath>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <sstream>
#include "../quick_sort.cpp" 
#include "../radix_sort.cpp"

#define MAX 9999999999
#define N_max 64
#define REPS 100 // 100
#define dbg 0  // cambiar a 1 para debugear

// Definición de tipos de datos
typedef unsigned long long ull;

/* Función auxiliar para obtener el k óptimo: recibe un valor máximo que representa el tamaño del universo y su máximo,
   y un 0 o 1 para indicar si se debería o no guardar un registro estadístico de los k utilizados */
int kOptimo(int u, vector<ull> &test)
{
    int k = 1;
    vector<double> k_times;
    clock_t start, end;
    // Creación de archivo de resultados para k si no existe
    FILE *results;
    results = fopen("Registro_de_tiempos_por_cada_k.csv", "a");
    for (int log = 1; log <= log2(u) + 1; log++)
    {
        vector<ull> arreglo(test); // Se copia el test facilitado
        start = clock();
        radix_sort(arreglo, log); // Se ordena el arreglo
        end = clock();
        k_times.push_back(static_cast<double>(end - start) / CLOCKS_PER_SEC); // Se calcula el tiempo
        char linea[50];
        sprintf(linea, "%d,%d,%.7f\n", u, log, k_times[log - 1]);
        fwrite(linea, 1, strlen(linea), results);
    }
    fclose(results);
    double min = MAX;
    int counter = 0;
    // Se elige el k con menor tiempo
    for (int i = 0; i < k_times.size(); i++)
    {
        counter++;
        if (k_times[i] < min)
        {
            min = k_times[i];
            k = counter;
        }
    }

    return k;
}

int main()
{
    int tests = 0;
    vector<ull> data;

    // Test genérico para probar generación de arreglo
    if (dbg == 1)
    {
      generateTestData(data, 0, 5, 1);
        cout << "Vector " << tests + 1 << " de largo " << data.size() << " generado con éxito." << endl;
   }

    // Generación de archivos que registren los tiempos de ordenamiento de radixSort para k en cada universo
    FILE *k_times;
    k_times = fopen("Registro_de_tiempos_por_cada_k.csv", "w");
    char linea1[] = "n_universo, k, tiempo";
    fwrite(linea1, 1, strlen(linea1), k_times);
    fclose(k_times);

    // Tests para ambos algoritmos. Para n de 1 a 64
    for (int exp = 0; exp < N_max; exp++)
    {
        cout << "Pruebas para universo 2^" << exp + 1 << " en curso..." << endl;
        // Creación del nombre del archivo
        char archivoFilename[50];
        // Creación de archivos con resultados
        sprintf(archivoFilename, "resultados_2^%d.csv", exp + 1);
        FILE *results_ptr;
        results_ptr = fopen(archivoFilename, "w");
        // Inicialización de la línea de encabezados: algoritmo, iteración, tiempo de generación de datos, tiempo ordenamiento
        char encabezado[] = "s_name,repeticion,gen_time,sort_time\n";
        fwrite(encabezado, 1, strlen(encabezado), results_ptr);

        // Se calcula el k óptimo para el universo u
        vector<ull> arreglo;
        generateTestData(arreglo, rand(), exp + 1, 0);
        int k = kOptimo(exp + 1, arreglo);

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

            cout << " Generando Data...";
            start = clock();
            generateTestData(data, rand(), exp + 1, dbg);
            end = clock();
            tempo1 = (double)(end - start) / CLOCKS_PER_SEC;

            // Llamada a Quicksort
            cout << " Llamando a QuickSort...";
            vector<ull> copia_de_data1(data); // Copiamos la data
            start = clock();
            quick_sort(copia_de_data1);
            end = clock();
            tempo2 = static_cast<double>(end - start) / CLOCKS_PER_SEC;
            // Registro resultados quicksort
            sprintf(resultRow1, "quick,%d,%.7f,%f\n", tests + 1, tempo1, tempo2);

            // Llamada a Radixsort
            cout << " Llamando a RadixSort..." << endl;
            vector<ull> copia_de_data2(data); // Copiamos la data
            start = clock();
            radix_sort(copia_de_data2, k);
            end = clock();
            tempo2 = static_cast<double>(end - start) / CLOCKS_PER_SEC;
            sprintf(resultRow2, "radix,%d,%.7f,%f\n", tests + 1, tempo1, tempo2);

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
