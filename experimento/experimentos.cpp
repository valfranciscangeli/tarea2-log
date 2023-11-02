#include <stdlib.h>
#include <string.h>
#include "../radix_sort.cpp"
//#include "../quick_sort.cpp"
#include <sstream>


#define N_max 64
#define REPS 2 //100
#define dbg 0

 int main(){
    int tests = 0;
    vector <ull> data;
    //Test genérico para probar generación de arreglo
    if (dbg == 1){
        data = generateTestData(0,5,1);
        cout<<"Vector "<<tests +1<< "de largo "<< data.size()<< " generado con éxito "<<endl;
        //se guarda el vector en un archivo
        //char *archivo = "test_base.txt";
        //grabarVector(data,archivo);
    }
    // Tests para ambos algoritmos. Para n de 1 a 64
    for (int exp = 0; exp < N_max; exp++){
        cout << "Pruebas para universo 2^" << exp+1<<" en curso..."<<endl;

        //reseto data anterior
        data.clear();
        //creación nombre del archivo
        char archivoFilename[50];
        //creación de archivos  con resultados
        sprintf(archivoFilename, "resultados_2^%d.csv",exp+1);
        FILE * results_ptr;
        results_ptr = fopen(archivoFilename, "w");
        //se inicializa la línea de encabezados: algoritmo, iteración, tiempo de generación de datos, tiempo ordenamiento
        char encabezado[] = "s_name,repeticion,gen_time,sort_time\n";
        fwrite(encabezado, 1, strlen(encabezado), results_ptr);

        //variables de tiempo
        clock_t start, end;
        double tempo1, tempo2; //tiempos de generación de data y ordenamiento
        // 100 repeticiones para cada n, usando diferentes semillas
        for(tests = 0; tests < REPS; tests ++){
            cout << "Repeticion: "<< tests + 1 <<endl;
            //se inicializa línea de resultados
            char resultRow1[50];
            char resultRow2[50];

            // Se genera uno de los arreglos
            start = clock();
            data = generateTestData(rand(),exp+1,0);
            end = clock();
            tempo1 = (double)(end -start) / CLOCKS_PER_SEC; 

            start = clock();
            // Llamada a Quicksort
            // quickSort(copia_de_data,max);
            end = clock();
            tempo2 = (double)(end -start) / CLOCKS_PER_SEC;
            // registro resultados quicksort
            sprintf(resultRow1, "quick,%d,%.7f,%f\n", tests+1, tempo1, tempo2);
            
            start = clock();
            // Llamada a Radixsort
            // radixSort(copia_de_data,max);
            end = clock();
            tempo2 = (double)(end -start) / CLOCKS_PER_SEC;
            sprintf(resultRow2, "radix,%d,%.7f,%f\n", tests+1, tempo1, tempo2);
            
            // Registro de resultados
            fwrite(resultRow1,1,strlen(resultRow1),results_ptr);
            fwrite(resultRow2,1,strlen(resultRow2),results_ptr);

        }
        fclose(results_ptr);
    }
    return 0;
 }