#include <iterator>
#include <functional>
#include <cstdlib> //rand()
#include <iostream>
#include <fstream>
#include <vector>
#include <iostream>
#include <random>


#define d_int int
using namespace std;
typedef unsigned long long ull;

/*Función para generar los sets de datos para los experimentos.  
Se le puede pasar la semilla o 0. Si se pasa 0, se usa una semilla fija.
i es el parámetro del exponente que tendrá el máximo elemento potencia de 2*/
vector <ull>generateTestData(int sd, int i) {
    int debug = 0;
    /* Se inicializa srand */
    unsigned int seed;
    if (sd != 0)
        seed = 31415;
    else 
        seed = sd;
    srand(seed);

    /* Limites distribuciones */
    int n_arreglo = 100000000;
    int lanzamientos = 100;
    /* Inicializar conjunto  del universo u*/
    ull max = (ull)pow(2,i+1);
    ull nArr[max];
    for (int u = 0; u<max; u++) {
        nArr[u] = 1 + u;
        cout<< "Elemento creado: "<<nArr[u]<<endl;
    }
    /* Inicializar arreglo  que se utilizará para uno de los experimentos para un cierto n*/
    vector <ull> ulongTest;
    for (n_arreglo != 0; n_arreglo--;){
        ull index = rand()%max; //se elige un índice entre 0 y exponente-1
        ull number = nArr[index];
        ulongTest.push_back(number);
        if (n_arreglo%1000000 == 0){
            cout<< "Elementos creados: "<<ulongTest.size()<<" Último insertado: ";
            cout<<number<< " Indice del insertado en u: "<< index<< endl;
        } 
    }
    
    return ulongTest;
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

