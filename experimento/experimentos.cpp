#include <stdlib.h>
#include <string.h>
#include "../quick_sort.cpp"
#include <sstream>
#include <chrono>

#define MAX 9999999999
#define N_max 64
#define REPS 2 // 100
#define dbg 0  // cambiar a 1 para debugear

/*Funcion auxiliar para obtener el k óptimo: recibe un un valor máximo que representa el
tamaño del universo y su máximo, y un 0 o 1 para indicar si se debería o no guardar un registro
estadístico de los k utilizados*/
int kOptimo(int u, vector<ull> &test)
{
    int k = 1;
    vector<double> k_times;

    // creación de archivo de resultados para k si no existe
    FILE *results;
        results= fopen("Registro de tiempos por cada k.csv", "a");
     for (int log = 1; log < log2(u)+1; log++){
        vector<ull> arreglo(test);                              //Se copia eltest facilitado
        auto start = chrono::high_resolution_clock::now();
        radix_sort(arreglo,log);                                //Se ordena el arreglo
        auto end =  chrono::high_resolution_clock::now();
        auto us = chrono::duration_cast<chrono::microseconds>(end - start);
        k_times.push_back((double)us.count()); // se caclula el tiempo
        char linea[50];
        sprintf(linea, "%d,%d,%d\n", u, log, (int)us.count());
        fwrite(linea, 1,strlen(linea), results);
    }
    fclose(results);
    double min = MAX;
    int counter = 0;
    // se elije el k con menor tiempo
    for (double tiempos : k_times){
        counter ++;
        if (tiempos < min){
            k = counter;
            min = tiempos;
        }
    }

    return k;
}

int main()
{
    random_device rd;     // Genera una semilla aleatoria desde el dispositivo

    int tests = 0;
    vector<ull> data;
    // Test genérico para probar generación de arreglo
    if (dbg == 1)
    {
        generateTestData(data, 0, 5, 1);
        cout << "Vector " << tests + 1 << "de largo " << data.size() << " generado con éxito " << endl;
        // se guarda el vector en un archivo
        // char *archivo = "test_base.txt";
        // grabarVector(data,archivo);
    }
    // generación de archivos que registren los tiempos de  ordenamiento de radixSort para k en cada universo
    FILE *k_times;
    k_times = fopen ("Registro de tiempos por cada k.csv", "w");
    char linea1[] = "n_universo, k, tiempo (micro segundos)\n";
    fwrite(linea1, 1,strlen(linea1), k_times);
    fclose(k_times);
    // Tests para ambos algoritmos. Para n de 1 a 64
    for (int exp = 0; exp < N_max; exp++)
    {
        cout << "Pruebas para universo 2^" << exp + 1 << " en curso..." << endl;
        // creación nombre del archivo
        char archivoFilename[50];
        // creación de archivos  con resultados
        sprintf(archivoFilename, "resultados_2^%d.csv", exp + 1);
        FILE *results_ptr;
        results_ptr = fopen(archivoFilename, "w");
        // se inicializa la línea de encabezados: algoritmo, iteración, tiempo de generación de datos, tiempo ordenamiento
        char encabezado[] = "s_name,repeticion,gen_time(s),sort_time(us)\n";
        fwrite(encabezado, 1, strlen(encabezado), results_ptr);

        // se calcula el k óptimo para el universo u
        vector<ull> arreglo;
        generateTestData(arreglo, rand(), exp + 1, 0);
        int k = kOptimo(exp + 1, arreglo);

        // variables de tiempo
        clock_t start, end;
        double tempo1, tempo2; // tiempos de generación de data y ordenamiento
        // 100 repeticiones para cada n, usando diferentes semillas
        for (tests = 0; tests < REPS; tests++)
        {
            cout << "Repeticion: " << tests + 1;
            // se inicializa línea de resultados
            char resultRow1[50];
            char resultRow2[50];

            // Se genera uno de los arreglos

            cout <<" Generando Data...";
            auto start = chrono::high_resolution_clock::now();
            generateTestData(data, rand(), exp + 1, dbg);
            auto end =  chrono::high_resolution_clock::now();
            auto tempo1 = chrono::duration_cast<chrono::microseconds>(end - start);

            // Llamada a Quicksort
            cout << " Llamando a QuickSort...";
            vector<ull> copia_de_data1(data); // copiamos la data
            start = chrono::high_resolution_clock::now();
            quick_sort(copia_de_data1);
            end = chrono::high_resolution_clock::now();
            auto tempo2 = chrono::duration_cast<chrono::microseconds>(end - start);
            // registro resultados quicksort
            sprintf(resultRow1, "quick,%d,%.7f,%d\n", tests + 1, (double)tempo1.count()/1000000, 
                                                                 (long int)tempo2.count());

            
            // Llamada a Radixsort
            cout<<" LLamando a RadixSort..."<<endl;
            vector<ull> copia_de_data2(data);// copiamos la data
            start = chrono::high_resolution_clock::now();
            radix_sort(copia_de_data2, k);
            end = chrono::high_resolution_clock::now();
            tempo2 = chrono::duration_cast<chrono::microseconds>(end - start);
            sprintf(resultRow2, "radix,%d,%.7f,%d\n", tests + 1, (double)tempo1.count()/1000000, 
                                                                 (long int)tempo2.count());

            // Registro de resultados
            fwrite(resultRow1, 1, strlen(resultRow1), results_ptr);
            fwrite(resultRow2, 1, strlen(resultRow2), results_ptr);

            // reseto data anterior
            data.clear();
        }
        fclose(results_ptr);
    }
    return 0;
}
