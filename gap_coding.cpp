#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include "generadores.h"
#include "buscadores.h"

using namespace std;
using namespace std::chrono;

int main() {
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
    cout << "Arreglo lineal: ";
    for (int i = 0; i < size; ++i) {
        cout << arregloLineal[i] << " ";
    }
    cout << endl;

    cout << "Arreglo normal: ";
    for (int i = 0; i < size; ++i) {
        cout << arregloNormal[i] << " ";
    }
    cout << endl;

/*
    cout << "Gap-Coding del arreglo lineal: ";
    for (int i = 0; i < size; ++i) {
        cout << gaps_lineal[i] << " ";
    }
    cout << endl;

    cout << "Gap-Coding del arreglo normal: ";
    for (int i = 0; i < size; ++i) {
        cout << gaps_normal[i] << " ";
    }
    cout << endl;

    cout << "Sample del arreglo lineal: ";
    for (int i = 0; i < m; ++i) {
        cout << sample_lineal[i] << " ";
    }
    cout << endl;

    cout << "Sample del arreglo normal: ";
    for (int i = 0; i < m; ++i) {
        cout << sample_normal[i] << " ";
    }
    cout << endl;
*/
    int valor;
    cout << "Ingrese el valor a buscar en el arreglo original: ";
    cin >> valor;

    // Medir el tiempo lineal
    auto start = high_resolution_clock::now(); 
    int indiceSampleLineal = binarySearchSample(sample_lineal, m, valor);
    int ini_indice_lineal = indiceSampleLineal * b;
    int indice_encontrado_lineal = encuentraIndice(gaps_lineal, size, ini_indice_lineal, valor, sample_lineal[indiceSampleLineal]);
    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<nanoseconds>(stop - start);
    cout << "Tiempo de búsqueda binaria en el arreglo lineal: " << duration.count() << " nanosegundos" << endl;

    // Medir tiempo normal
    start = high_resolution_clock::now(); 
    int indiceSampleNormal = binarySearchSample(sample_normal, m, valor);
    int ini_indice_normal = indiceSampleNormal * b;
    int indice_encontrado_normal = encuentraIndice(gaps_normal, size, ini_indice_normal, valor, sample_normal[indiceSampleNormal]);
    stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop - start);
    cout << "Tiempo de búsqueda binaria en el arreglo lineal: " << duration.count() << " nanosegundos" << endl;

    if (indice_encontrado_lineal != -1) {
        cout << "Valor encontrado en el índice del arreglo lineal: " << indice_encontrado_lineal << endl;
    } else {
        cout << "Valor no encontrado en el arreglo lineal." << endl;
    }

    if (indice_encontrado_normal != -1) {
        cout << "Valor encontrado en el índice del arreglo normal: " << indice_encontrado_normal << endl;
    } else {
        cout << "Valor no encontrado en el arreglo normal." << endl;
    }

    // Liberar memoria dinámica
    delete[] arregloLineal;
    delete[] arregloNormal;
    delete[] gaps_lineal;
    delete[] gaps_normal;
    delete[] sample_lineal;
    delete[] sample_normal;

    return 0;
}
