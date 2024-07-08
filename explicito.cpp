#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <chrono>
#include <algorithm>
#include "generadores.h"
#include "buscadores.h"

using namespace std;
using namespace std::chrono;

int main() {

    int n;
    srand(time(nullptr)); // Semilla aleatoria basada en el tiempo actual
    cout << "Ingrese el número de elementos de los arreglos: ";
    cin >> n;
    int* arregloLineal = new int[n];
    int* arregloNormal = new int[n];

    double media, desviacion;
    cout << "Ingrese la media para la generación del arreglo normal: ";
    cin >> media;
    cout << "Ingrese la desviación para la generación del arreglo normal: ";
    cin >> desviacion;

    // Inicializar arreglos con valores aleatorios ordenados
    inicializarArregloLineal(arregloLineal, n);
    inicializarArregloNormal(arregloNormal, n, media, desviacion);

    // Imprimir arreglos
    cout << "Arreglo lineal: ";
    for (int i = 0; i < n; i++) {
        cout << arregloLineal[i] << " ";
    }
    cout << endl;

    cout << "Arreglo normal ordenado: ";
    sort(arregloNormal, arregloNormal + n); // Ordenar arreglo normal
    for (int i = 0; i < n; i++) {
        cout << arregloNormal[i] << " ";
    }
    cout << endl;

    // Pedir al usuario el valor a buscar
    int objetivo;
    cout << "Ingrese el valor a buscar: ";
    cin >> objetivo;

    auto start = high_resolution_clock::now(); 
    int indiceLineal = busquedaBinaria(arregloLineal, 0, n - 1, objetivo);
    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<nanoseconds>(stop - start);
    cout << "Tiempo de búsqueda binaria en el arreglo lineal: " << duration.count() << " nanosegundos" << endl;

    start = high_resolution_clock::now();
    int indiceNormal = busquedaBinaria(arregloNormal, 0, n - 1, objetivo);
    stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop - start);
    cout << "Tiempo de búsqueda binaria en el arreglo normal: " << duration.count() << " nanosegundos" << endl;

    cout << "Índice del objetivo en el arreglo lineal: " << indiceLineal << endl;
    cout << "Índice del objetivo en el arreglo normal: " << indiceNormal << endl;

    delete[] arregloLineal;
    delete[] arregloNormal;

    return 0;
}