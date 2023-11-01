#include <stdlib.h>
#include <string.h>
#include "../auxiliares.cpp"
#include <sstream>


#define N_max 64
#define REPS 100


 int main(){
    int tests = 0;
    //Test genérico para probar generación de arreglo
    vector <ull> data= generateTestData(0,10);
    cout<<"Vector "<<tests +1<< "de largo "<< data.size()<< " generado con éxito "<<endl;
    //se guarda el vector en un archivo
    //char *archivo = "test_base.txt";
    //grabarVector(data,archivo);

    // Tests para ambos algoritmos. Para n de 1 a 64
    for (int exp = 0; exp<N_max; exp++){
        // creación de nombre de archivo con resultados
        char *archivoBase = "Resultados_n_E";
        stringstream ss;
        ss << archivoBase << (exp+1)<<".csv";
        char *archivo = const_cast<char *>(ss.str().c_str());
        char archivoFilename[50];

        sprintf(archivoFilename, archivo);
        FILE * results_ptr;
        results_ptr = fopen(archivoBase, "w");
        //se inicializa la línea de encabezados
        char encabezado[] = "i,t\n";
        fwrite(encabezado, 1, strlen(encabezado), results_ptr);


        //variables de tiempo
        clock_t start, end;
        double tempo;
        // 100 repeticiones para cada n, usando diferentes semillas
        for(tests = 0; tests < REPS; tests ++){
            
            //se inicializa línea de resultados
            char resultRow[50];

            // Se genera uno de los arreglos
            data = generateTestData(rand(),exp);
            start = clock();
            //llamada a Quicksort
            end = clock();
            tempo = (double)(end -start) / CLOCKS_PER_SEC;
            //registro resultados para QuickSort
            sprintf(resultRow, archivo);
            
            start = clock();
            //llamada a Radixsort
            end = clock();
            tempo = (double)(end -start) / CLOCKS_PER_SEC;
            //registro resultados para RadixSort

        }
        fclose(resultados);
    }
    return 0;
 }