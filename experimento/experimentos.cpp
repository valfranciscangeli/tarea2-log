#include <stdlib.h>
#include <string.h>
#include "../auxiliares.cpp"
#include <sstream>


#define N_max 64
#define REPS 2 //100


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
        //creación nombre del archivo
        char archivoFilename[50];
        //creación de archivos  con resultados
        sprintf(archivoFilename, "resultados_n^%d.csv",exp+1);
        FILE * results_ptr;
        results_ptr = fopen(archivoFilename, "w");
        //se inicializa la línea de encabezados
        char encabezado[] = "s_name, i,t\n";
        fwrite(encabezado, 1, strlen(encabezado), results_ptr);

        //variables de tiempo
        clock_t start, end;
        double tempo;
        // 100 repeticiones para cada n, usando diferentes semillas
        for(tests = 0; tests < REPS; tests ++){
            
            //se inicializa línea de resultados
            char resultRow1[50];
            char resultRow2[50];

            // Se genera uno de los arreglos
            data = generateTestData(rand(),exp);
            start = clock();
            // Llamada a Quicksort
            end = clock();
            tempo = (double)(end -start) / CLOCKS_PER_SEC;
            // registro resultados quicksort
            sprintf(resultRow1,"quick,%d,%.7f\n",tests,tempo);
            
            start = clock();
            // Llamada a Radixsort
            end = clock();
            tempo = (double)(end -start) / CLOCKS_PER_SEC;
            sprintf(resultRow2,"radix,%d,%.7f\n",tests,tempo);
            
            // Registro de resultados
            fwrite(resultRow1,1,strlen(resultRow1),results_ptr);
            fwrite(resultRow2,1,strlen(resultRow1),results_ptr);

        }
        fclose(results_ptr);
    }
    return 0;
 }