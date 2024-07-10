#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <chrono>
#include <algorithm>
#include <map>
#include <queue>
#include <vector>
#include <string>
#include <unistd.h>
#include <iomanip>
#include <fstream> 
#include "buscadores.h"
#include "generadores.h"
#include "funcionesHuffman.h"
#include "nodo_huffman.h"

using namespace std;
using namespace std::chrono;

void getMemoryUsage(pid_t pid)
{
    ifstream statusFile("/proc/" + to_string(pid) + "/status");
    string line;

    while (getline(statusFile, line))
    {
        if (line.find("VmRSS:") != string::npos)
        {
            std::cout << line << std::endl;
            break;
        }
    }

    statusFile.close();
}
/*
bool ordenarHuffmanCode(map<int, string> &huffmanCode, const vector<pair<int, int>> &frecuenciasOrdenadas, vector<pair<int, string>> &huffmanCodeOrdenado)
{
    // Crear un vector de pares para almacenar las claves y los códigos de Huffman
    vector<pair<int, string>> huffmanCodeVector;

    // Recorrer el vector de frecuenciasOrdenadas
    for (const auto &par : frecuenciasOrdenadas)
    {
        int clave = par.first;

        // Verificar si la clave existe en el huffmanCode original
        if (huffmanCode.find(clave) != huffmanCode.end())
        {
            huffmanCodeVector.push_back({clave, huffmanCode[clave]});
        }
        else
        {
            // Si alguna clave no existe en el huffmanCode, retorna false
            cerr << "Error: La clave " << clave << " no existe en huffmanCode." << endl;
            return false;
        }
    }

    // Ordenar el vector de huffmanCode basado en las frecuencias de mayor a menor
    sort(huffmanCodeVector.begin(), huffmanCodeVector.end(), [&frecuenciasOrdenadas](const pair<int, string> &a, const pair<int, string> &b)
        {
        auto itA = find_if(frecuenciasOrdenadas.begin(), frecuenciasOrdenadas.end(), [&a](const pair<int, int> &p) { return p.first == a.first; });
        auto itB = find_if(frecuenciasOrdenadas.begin(), frecuenciasOrdenadas.end(), [&b](const pair<int, int> &p) { return p.first == b.first; });
        return itA->second > itB->second; });

    // Actualizar el huffmanCodeOrdenado con el vector ordenado
    huffmanCodeOrdenado = huffmanCodeVector;

    // Si todas las claves se encontraron y se ordenaron correctamente, retorna true
    return true;
}

void codificarBitsShort(vector<pair<int, string>> &huffmanCode, int shortCode[], const vector<pair<int, int>> &frecuenciasOrdenadas)
{

    for (int i = 0; i < huffmanCode.size() - 1; ++i)
    {
        // cout << "sice huffman "<<huffmanCode.size() << endl;
        int c = 0;
        int k = 31;

        // cout << "tamano .size: " << huffmanCode[frecuenciasOrdenadas[i].first].size() << endl;

        for (int j = huffmanCode[i].second.size() - 1; j >= 0; j--)
        {
            cout << "valor en huffmnancode: " << huffmanCode[i] << endl;
            cout<<"valor de j "<<j<<" "<< i <<endl;
            cout<<"bits " <<frecuenciasOrdenadas[i].first<<endl;
            
            if (huffmanCode[i].second[j] == '1')
                c |= (1 << k);
            k--;
        }
        shortCode[i] = c;
    }
}

void codificarGapsShort(int size, const int *shortCode, const int *gaps, int *gapsComprimidos)
{
    for (int i = 0; i < size; i++)
    {
        gapsComprimidos[i] = shortCode[gaps[i]];
    }
}

int descomprimirGapShort(int compressedGap, const map<int, string> &huffmanCode)
{
    for (const auto &pair : huffmanCode)
    {
        int c = 0;
        int k = 31;
        for (int j = pair.second.size() - 1; j >= 0; j--)
        {
            if (pair.second[j] == '1')
                c |= (1 << k);
            k--;
        }
        if (c == compressedGap)
        {
            return pair.first;
        }
    }
    return -1; // Si no se encuentra, lo que no debería ocurrir
}

int encuentraIndiceHuffmanShort(const int *original, const int *gapsComprimidos, int size, int ini_indice, int valor, const map<int, string> &huffmanCode)
{
    int indice_actual = ini_indice;
    int valor_actual = original[ini_indice];
    while (indice_actual < size && valor_actual < valor)
    {
        int gap = descomprimirGapShort(gapsComprimidos[indice_actual + 1], huffmanCode);
        valor_actual += gap;
        indice_actual++;
    }
    if (valor_actual == valor)
    {
        return indice_actual;
    }
    else
    {
        return -1; // No encontrado
    }
}*/

int main()
{
    srand(static_cast<unsigned int>(time(0)));
    pid_t pid = getpid();
    int size;
    cout << "Ingrese cantidad de elementos en los arreglos [n]: ";
    cin >> size;

    double media, desviacion;
    cout << "Ingrese la media para la generación del arreglo normal: ";
    cin >> media;
    cout << "Ingrese la desviación para la generación del arreglo normal: ";
    cin >> desviacion;

    int *arregloLineal = new int[size];
    int *arregloNormal = new int[size];

    inicializarArregloLineal(arregloLineal, size);
    inicializarArregloNormal(arregloNormal, size, media, desviacion);
    sort(arregloNormal, arregloNormal + size);

    int m = size / 2;
    int b = size / m;

    int *gaps_lineal = new int[size];
    generarGaps(arregloLineal, gaps_lineal, size);
    int *gaps_normal = new int[size];
    generarGaps(arregloNormal, gaps_normal, size);

    int *sample_lineal = new int[m];
    generarSample(arregloLineal, sample_lineal, size, m, b);
    int *sample_normal = new int[m];
    generarSample(arregloNormal, sample_normal, size, m, b);

    map<int, int> frecuencia_lineal;
    calcularFrecuencia(gaps_lineal, size, frecuencia_lineal);
    map<int, int> frecuencia_normal;
    calcularFrecuencia(gaps_normal, size, frecuencia_normal);

    vector<pair<int, int>> frecuenciasOrdenadas_lineal(frecuencia_lineal.begin(), frecuencia_lineal.end());
    sort(frecuenciasOrdenadas_lineal.begin(), frecuenciasOrdenadas_lineal.end(), [](const pair<int, int> &a, const pair<int, int> &b)
        { return a.second > b.second; });

    vector<pair<int, int>> frecuenciasOrdenadas_normal(frecuencia_normal.begin(), frecuencia_normal.end());
    sort(frecuenciasOrdenadas_normal.begin(), frecuenciasOrdenadas_normal.end(), [](const pair<int, int> &a, const pair<int, int> &b)
        { return a.second > b.second; });

    NodoHuffman *raiz_lineal = construirArbolHuffman(frecuenciasOrdenadas_lineal);
    NodoHuffman *raiz_normal = construirArbolHuffman(frecuenciasOrdenadas_normal);

    map<int, string> huffmanCode_lineal;
    generarCodigosHuffman(raiz_lineal, "", huffmanCode_lineal);
    map<int, string> huffmanCode_normal;
    generarCodigosHuffman(raiz_normal, "", huffmanCode_normal);

    int codigos_Lineal = 0;
    int codigos_Normal = 0;

    vector<pair<int, string>> huffmanCodeLinealOrdenado;
    if (ordenarHuffmanCode(huffmanCode_lineal, frecuenciasOrdenadas_lineal, huffmanCodeLinealOrdenado))
        cout << "HuffmanCode ordenado correctamente." << endl;
    else
        cout << "Error en la ordenación de HuffmanCode." << endl;
    vector<pair<int, string>> huffmanCodeNormalOrdenado;
    if (ordenarHuffmanCode(huffmanCode_normal, frecuenciasOrdenadas_normal, huffmanCodeNormalOrdenado))
        cout << "HuffmanCode ordenado correctamente." << endl;
    else
        cout << "Error en la ordenación de HuffmanCode." << endl;

    bool largoCode = false;
    for (const auto &code : huffmanCode_normal)
    {
        if (code.second.size() > 8)
            largoCode = true;
    }
    for (const auto &code : huffmanCode_lineal)
    {
        if (code.second.size() > 8)
            largoCode = true;
    }


    if (largoCode)
    {
        cout << "short" << endl;
        int *shortCode_lineal = new int[huffmanCodeLinealOrdenado.size()];
        int *shortCode_normal = new int[huffmanCodeNormalOrdenado.size()];

        codificarBitsShort(huffmanCodeLinealOrdenado, shortCode_lineal, frecuenciasOrdenadas_lineal);
        codificarBitsShort(huffmanCodeNormalOrdenado, shortCode_normal, frecuenciasOrdenadas_normal);

        int *gapsComprimidos_lineal = new int[size];
        int *gapsComprimidos_normal = new int[size];
        codificarGapsShort(size, shortCode_lineal, gaps_lineal, gapsComprimidos_lineal);
        codificarGapsShort(size, shortCode_normal, gaps_normal, gapsComprimidos_normal);

        int valor;
        cout << "Ingrese el valor a buscar en el arreglo original: ";
        cin >> valor;

        // Buscar en el arreglo lineal
        cout << "\nBuscar en el arreglo lineal:\n";
        auto start = high_resolution_clock::now();
        int indiceSample_lineal = binarySearchSample(sample_lineal, m, valor);
        int ini_indice_lineal = indiceSample_lineal * b;
        int indice_encontrado_lineal = encuentraIndiceHuffmanShort(arregloLineal, gapsComprimidos_lineal, size, ini_indice_lineal, valor, huffmanCode_lineal);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);

        if (indice_encontrado_lineal != -1)
        {
            cout << "Valor encontrado en el índice: " << indice_encontrado_lineal << endl;
        }
        else
        {
            cout << "Valor no encontrado." << endl;
        }
        cout << "Tiempo transcurrido en el arreglo lineal: " << duration.count() << " nanosegundos" << endl;

        // Buscar en el arreglo normal
        cout << "\nBuscar en el arreglo normal:\n";
        start = high_resolution_clock::now();
        int indiceSample_normal = binarySearchSample(sample_normal, m, valor);
        int ini_indice_normal = indiceSample_normal * b;
        int indice_encontrado_normal = encuentraIndiceHuffmanShort(arregloNormal, gapsComprimidos_normal, size, ini_indice_normal, valor, huffmanCode_normal);
        stop = high_resolution_clock::now();
        duration = duration_cast<nanoseconds>(stop - start);

        if (indice_encontrado_normal != -1)
        {
            cout << "Valor encontrado en el índice: " << indice_encontrado_normal << endl;
        }
        else
        {
            cout << "Valor no encontrado." << endl;
        }
        cout << "Tiempo transcurrido en el arreglo normal: " << duration.count() << " segundos" << endl;

        delete[] shortCode_lineal;
        delete[] shortCode_normal;
        delete[] gapsComprimidos_normal;
    }
    else
    {
        char *charCode_lineal = new char[huffmanCodeLinealOrdenado.size()];
        codificarBits(huffmanCodeLinealOrdenado, charCode_lineal, frecuenciasOrdenadas_lineal);
        char *charCode_normal = new char[huffmanCodeLinealOrdenado.size()];
        codificarBits(huffmanCodeNormalOrdenado, charCode_normal, frecuenciasOrdenadas_normal);

        char *gapsComprimidos_lineal = new char[size];
        codificarGaps(size, charCode_lineal, gaps_lineal, gapsComprimidos_lineal);
        char *gapsComprimidos_normal = new char[size];
        codificarGaps(size, charCode_normal, gaps_normal, gapsComprimidos_normal);

        /*
        cout << "Arreglo Lineal original: ";
        for (int i = 0; i < size; ++i){
            cout << arregloLineal[i] << " ";
        }
        cout << endl;

        cout << "Gap-Coding del arreglo Lineal: ";
        for (int i = 0; i < size; ++i){
            cout << gaps_lineal[i] << " ";
        }
        cout << endl;

        cout << "Sample del arreglo Lineal: ";
        for (int i = 0; i < m; ++i) {
            cout << sample_lineal[i] << " ";
        }
        cout << endl;

        cout << "Codigos de Huffman del arreglo Lineal: " << endl;
        for (int i = 0 ; i<huffmanCodeLinealOrdenado.size() ; i++)
        {
            cout << huffmanCodeLinealOrdenado[i].first << ": ";
            printBinary(charCode_lineal[i]);
            cout << " (frecuencia: " << huffmanCodeLinealOrdenado[i].second << ")" << endl;
        }

        cout << "Arreglo de Gaps Lineal comprimido: ";
        for(auto c : gapsComprimidos_lineal){
            printBinary(c);
            cout << " ";
        }
        cout << endl;

        cout << "Arreglo Normal original: ";
        for (int i = 0; i < size; ++i){
            cout << arregloNormal[i] << " ";
        }
        cout << endl;

        cout << "Gap-Coding del arreglo Normal: ";
        for (int i = 0; i < size; ++i){
            cout << gaps_normal[i] << " ";
        }
        cout << endl;

        cout << "Sample del arreglo Normal: ";
        for (int i = 0; i < m; ++i) {
            cout << sample_normal[i] << " ";
        }
        cout << endl;

        cout << "Codigos de Huffman del arreglo Normal: " << endl;
        for (int i = 0 ; i<huffmanCodeNormalOrdenado.size() ; i++)
        {
            cout << huffmanCodeNormalOrdenado[i].first << ": ";
            printBinary(charCode_normal[i]);
            cout << " (frecuencia: " << huffmanCodeNormalOrdenado[i].second << ")" << endl;
        }

        cout << "Arreglo de Gaps Normal comprimido: ";
        for(auto c : gapsComprimidos_normal){
            printBinary(c);
            cout << " ";
        }
        cout << endl;
        */
        int valor;
        cout << "Ingrese el valor a buscar en el arreglo original: ";
        cin >> valor;

        // Buscar en el arreglo lineal
        cout << "\nBuscar en el arreglo lineal:\n";
        auto start = high_resolution_clock::now();
        int indiceSample_lineal = binarySearchSample(sample_lineal, m, valor);
        int ini_indice_lineal = indiceSample_lineal * b;
        int indice_encontrado_lineal = encuentraIndiceHuffman(arregloLineal, gapsComprimidos_lineal, size, ini_indice_lineal, valor, huffmanCode_lineal);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);

        if (indice_encontrado_lineal != -1)
        {
            cout << "Valor encontrado en el índice: " << indice_encontrado_lineal << endl;
        }
        else
        {
            cout << "Valor no encontrado." << endl;
        }
        cout << "Tiempo transcurrido en el arreglo lineal: " << duration.count() << " nanosegundos" << endl;

        // Buscar en el arreglo normal
        cout << "\nBuscar en el arreglo normal:\n";
        start = high_resolution_clock::now();
        int indiceSample_normal = binarySearchSample(sample_normal, m, valor);
        int ini_indice_normal = indiceSample_normal * b;
        int indice_encontrado_normal = encuentraIndiceHuffman(arregloNormal, gapsComprimidos_normal, size, ini_indice_normal, valor, huffmanCode_normal);
        stop = high_resolution_clock::now();
        duration = duration_cast<nanoseconds>(stop - start);

        if (indice_encontrado_normal != -1)
        {
            cout << "Valor encontrado en el índice: " << indice_encontrado_normal << endl;
        }
        else
        {
            cout << "Valor no encontrado." << endl;
        }
        cout << "Tiempo transcurrido en el arreglo normal: " << duration.count() << " segundos" << endl;
        delete[] charCode_lineal;
        delete[] charCode_normal;
        delete[] gapsComprimidos_lineal;
    }
    delete[] arregloLineal;
    delete[] arregloNormal;
    delete[] gaps_lineal;
    delete[] gaps_normal;
    delete[] sample_lineal;
    delete[] sample_normal;

    return 0;
}
