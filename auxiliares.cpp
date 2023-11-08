#include <iterator>
#include <functional>
#include <cstdlib> //rand()
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>

#define d_int int

using namespace std;
typedef unsigned long long ull;

int cantidad_de_valores = 1e8; // poner 1e8 para 100millones

/*Función para generar los sets de datos para los experimentos.
Se le pasa pasa un vector vacío data
Se le puede pasar la semilla o 0. Si se pasa 0, se usa una semilla fija.
i es el parámetro del exponente que tendrá el máximo elemento potencia de 2*/
void generateTestData(vector<ull> data, int sd, ull i, int debug, int n_arreglo)
{
    /* Se inicializa srand */
    unsigned int seed;
    if (sd != 0)
        seed = 31415;
    else
        seed = sd;
    srand(seed);

    // /* Limites distribuciones */
    // int n_arreglo = 100000000;
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

void separar_registros_de_k_por_exp()
{

    // Abre el archivo CSV original para lectura.
    std::ifstream input_file("Registro_de_tiempos_por_cada_k.csv");
    if (!input_file.is_open())
    {
        std::cerr << "No se pudo abrir el archivo CSV." << std::endl;
    }

    // Crea un mapa para almacenar archivos de salida según el valor de n_universo.
    std::map<int, std::ofstream> output_files;

    // Lee la cabecera del archivo original.
    std::string header;
    std::getline(input_file, header);

    // Itera a través de las filas del archivo original.
    std::string line;
    while (std::getline(input_file, line))
    {
        // Parsea la línea para obtener el valor de n_universo.
        std::istringstream ss(line);
        std::string field;
        int n_universo;

        if (std::getline(ss, field, ','))
        {
            n_universo = std::stoi(field);
        }
        else
        {
            std::cerr << "Error al leer el valor de n_universo." << std::endl;
        }

        // Verifica si ya se ha abierto un archivo de salida para este valor de n_universo.
        if (output_files.find(n_universo) == output_files.end())
        {
            // Crea un nuevo archivo de salida para este valor de n_universo.
            std::string output_filename = "registro_de_k_para_2^" + std::to_string(n_universo) + ".csv";
            output_files[n_universo].open(output_filename);

            // Escribe la cabecera en el archivo de salida.
            output_files[n_universo] << header << std::endl;
        }

        // Escribe la línea actual en el archivo de salida correspondiente.
        output_files[n_universo] << line << std::endl;
    }

    // Cierra todos los archivos de salida.
    for (auto &pair : output_files)
    {
        pair.second.close();
    }

    // Cierra el archivo de entrada original.
    input_file.close();
}