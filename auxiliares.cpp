#include <iterator>
#include <functional>
#include <cstdlib> //rand()
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

#define d_int int
#define MAX 9999999999
using namespace std;
typedef unsigned long long ull;
/*Funcion auxiliar para obtener el k óptimo: recibe un un valor máximo que representa el 
tamaño del universo y su máximo, y un 0 o 1 para indicar si se debería o no guardar un registro 
estadístico de los k utilizados*/
int kOptimo(int u, vector<ull> test){
    int k = 1;
    vector<double> k_times;
    clock_t start,end;
    // creación de archivo de resultados para k si no existe
    FILE *results;
        results= fopen("Registro de tiempos por cada k", "a");
     for (int log = 1; log < log2(u)+1; log++){
        vector<ull> arreglo(test);                              //Se copia eltest facilitado
        start = clock();
        radix_sort(arreglo,log);                                //Se ordena el arreglo 
        end = clock();
        k_times.push_back((double)end-start / CLOCKS_PER_SEC); // se caclula el tiempo
        char linea[50];
        sprintf(linea, "%d,%d,%.7f", u,log,k_times[log]);
        fwrite(linea, 1,strlen(linea), results);
    }
    fclose(results);
    double min = MAX;
    int counter = 0;
    // se elije el k con menor tiempo
    for (double tiempos : k_times){
        counter ++;
        if (tiempos < counter){
            counter = k;
        }
    }
    
    return k;
}


/*Función para generar los sets de datos para los experimentos.  
Se le pasa pasa un vector vacío data
Se le puede pasar la semilla o 0. Si se pasa 0, se usa una semilla fija.
i es el parámetro del exponente que tendrá el máximo elemento potencia de 2*/
void generateTestData(vector <ull> data, int sd, ull i, int debug) {
    /* Se inicializa srand */
    unsigned int seed;
    if (sd != 0)
        seed = 31415;
    else 
        seed = sd;
    srand(seed);

    /* Limites distribuciones */
    int n_arreglo = 100000000;
    /* Inicializar conjunto  del universo u*/
    ull max = (ull)pow(2,i);    //el máximo  : 2^i
    if (debug)
        cout <<"\nmáximo calculado: "<< max <<endl; 
    /*Deprecado: generar vector universo de tamaño 2^i
    vector <ull> Universo;
    for (ull u = 0; u<max; u++) {
        Universo.push_back(1 + u);
        if (debug)
            cout<< "Elemento creado: "<<Universo[u] << endl;
    }*/

    ull ind = 0;
    for (n_arreglo > 0; n_arreglo--;){
        ull number = rand()%(max+1); //se elige un índice entre 0 y el máximo
        data.push_back(number);
        if ((n_arreglo+1)%1000000 == 0 && debug){
            cout<< "Elementos creados: "<<data.size()<<" Último insertado: ";
            cout<<data[ind]<< " Indice del insertado "<< ind << endl;
        } 
        ind++;
    }
    cout<< "Vector listo"<< endl;
}

/*Función auxiliar para grabar un vector en memoria */
void grabarVector(vector<ull> vect, char *fileName)
{
    FILE *arch;
    arch = fopen(fileName, "w");
    if (arch)
    {
        cout << "Iniciando escritura ..." << endl;
        for (ull data : vect)
        {
            fwrite(&data, sizeof(ull), 1, arch);
            fputc(' ',arch);
        
        }

        cout << "Archivo '" << fileName << "' creado y datos escritos con éxito." << endl;
    }
    else
    {
        cerr << "No se pudo abrir el archivo '" << fileName << "'." << endl;
    }
    fclose(arch);
}

