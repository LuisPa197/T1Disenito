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
#include "buscadores.h"
#include "generadores.h"
#include "nodo_huffman.h"

using namespace std;
using namespace std::chrono;

void printBinary(char c) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (c >> i) & 1);
    }
}

int main()
{
    srand(static_cast<unsigned int>(time(0)));
    int size;
    cout << "Ingrese cantidad de elementos en los arreglos [n]: ";
    cin >> size;

    double media, desviacion;
    cout << "Ingrese la media para la generación del arreglo normal: ";
    cin >> media;
    cout << "Ingrese la desviación para la generación del arreglo normal: ";
    cin >> desviacion;

    int* arregloLineal = new int[size];
    int* arregloNormal = new int[size];

    inicializarArregloLineal(arregloLineal, size);
    inicializarArregloNormal(arregloNormal, size, media, desviacion);
    sort(arregloNormal, arregloNormal + size);

    int m = size / 2;
    int b = size / m;

    int* gaps_lineal = new int[size];
    generarGaps(arregloLineal, gaps_lineal, size);
    int* gaps_normal = new int[size];
    generarGaps(arregloNormal, gaps_normal, size);

    int* sample_lineal = new int[m];
    generarSample(arregloLineal, sample_lineal, size, m, b);
    int* sample_normal = new int[m];
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

    char charCode_lineal[huffmanCode_lineal.size()];
    codificarBits(gaps_lineal, size, huffmanCode_lineal, charCode_lineal, frecuenciasOrdenadas_lineal);
    char charCode_normal[huffmanCode_normal.size()];
    codificarBits(gaps_normal, size, huffmanCode_normal, charCode_normal, frecuenciasOrdenadas_normal);

    char gapsComprimidos_lineal[size];
    codificarGaps(size, charCode_lineal, gaps_lineal, gapsComprimidos_lineal);
    char gapsComprimidos_normal[size];
    codificarGaps(size, charCode_normal, gaps_normal, gapsComprimidos_normal);

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
    for (auto pair : frecuenciasOrdenadas_lineal)
    {
        cout << pair.first << ": "; 
        printBinary(charCode_lineal[pair.first]);
        cout << " (frecuencia: " << pair.second << ")" << endl;
    }

    cout << "Arreglo de Gaps Lineal comprimido: ";
    for(auto c : gapsComprimidos_lineal){
        cout << " ";
        printBinary(c);
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
    for (auto pair : frecuenciasOrdenadas_normal)
    {
        cout << pair.first << ": "; 
        printBinary(charCode_normal[pair.first]);
        cout << " (frecuencia: " << pair.second << ")" << endl;
    }

    cout << "Arreglo de Gaps Normal comprimido: ";
    for(auto c : gapsComprimidos_normal){
        cout << " ";
        printBinary(c);
    }
    cout << endl;

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

    if (indice_encontrado_lineal != -1) {
        cout << "Valor encontrado en el índice: " << indice_encontrado_lineal << endl;
    } else {
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

    if (indice_encontrado_normal != -1) {
        cout << "Valor encontrado en el índice: " << indice_encontrado_normal << endl;
    } else {
        cout << "Valor no encontrado." << endl;
    }
    cout << "Tiempo transcurrido en el arreglo normal: " << duration.count() << " segundos" << endl;

    delete[] arregloLineal;
    delete[] arregloNormal;
    delete[] gaps_lineal;
    delete[] gaps_normal;
    delete[] sample_lineal;
    delete[] sample_normal;

    return 0;
}