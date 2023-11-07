#include <iterator>
#include <functional>
#include <cstdlib> //rand()
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

#define d_int int

using namespace std;
typedef unsigned long long ull;

/*Función para generar los sets de datos para los experimentos.
Se le pasa pasa un vector vacío data
Se le puede pasar la semilla o 0. Si se pasa 0, se usa una semilla fija.
i es el parámetro del exponente que tendrá el máximo elemento potencia de 2*/
void generateTestData(vector<ull> data, int sd, ull i, int debug)
{
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
    ull max = (ull)pow(2, i); // el máximo  : 2^i
    if (debug)
        cout << "\nmáximo calculado: " << max << endl;
    /*Deprecado: generar vector universo de tamaño 2^i
    vector <ull> Universo;
    for (ull u = 0; u<max; u++) {
        Universo.push_back(1 + u);
        if (debug)
            cout<< "Elemento creado: "<<Universo[u] << endl;
    }*/

    ull ind = 0;
    for (n_arreglo > 0; n_arreglo--;)
    {
        ull number = rand() % (max + 1); // se elige un índice entre 0 y el máximo
        data.push_back(number);
        if ((n_arreglo + 1) % 1000000 == 0 && debug)
        {
            cout << "Elementos creados: " << data.size() << " Último insertado: ";
            cout << data[ind] << " Indice del insertado " << ind << endl;
        }
        ind++;
    }
    cout << "Vector listo" << endl;
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
            fputc(' ', arch);
        }

        cout << "Archivo '" << fileName << "' creado y datos escritos con éxito." << endl;
    }
    else
    {
        cerr << "No se pudo abrir el archivo '" << fileName << "'." << endl;
    }
    fclose(arch);
}
