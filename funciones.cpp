#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <chrono>
#include <algorithm>
#include "funciones.h"

using namespace std;

void inicializarArregloLineal(int* arreglo, int n) {
    arreglo[0] = rand() % 10; // Valor inicial aleatorio entre 0 y 99
    for (int i = 1; i < n; i++) {
        arreglo[i] = arreglo[i - 1] + (rand() % 10); // Siguiente valor aleatorio entre 0 y 9
    }
}

void inicializarArregloNormal(int* arreglo, int n, double media, double desviacion) {
    for (int i = 0; i < n; i++) {
        double u1 = ((double) rand() / RAND_MAX); // Generar número aleatorio entre 0 y 1
        double u2 = ((double) rand() / RAND_MAX); // Generar número aleatorio entre 0 y 1
        double z = sqrt(-2 * log(u1)) * cos(2 * M_PI * u2); // Transformación de Box-Muller
        arreglo[i] = round(media + desviacion * z); // Valor normalmente distribuido
    }
}

//para arreglos explicitos
int busquedaBinaria(int* arreglo, int inicio, int fin, int objetivo) {
    if (inicio <= fin) {
        int medio = inicio + (fin - inicio) / 2;
        if (arreglo[medio] == objetivo) {
            return medio;
        } else if (arreglo[medio] < objetivo) {
            return busquedaBinaria(arreglo, medio + 1, fin, objetivo);
        } else {
            return busquedaBinaria(arreglo, inicio, medio - 1, objetivo);
        }
    }
    return -1; // El objetivo no se encontró en el arreglo
}

void generarGaps(int arr[], int gaps[], int size) {
    if (size > 0) {
        gaps[0] = arr[0]; // El primer elemento es el mismo que el original
        for (int i = 1; i < size; ++i) {
            gaps[i] = arr[i] - arr[i - 1];
        }
    }
}

void generarSample(int arr[], int sample[], int size, int m, int b) {
    for (int i = 0; i < m; ++i) {
        int indice = i * b;
        if (indice < size) {
            sample[i] = arr[indice];
        }
    }
}

int binarySearchSample(int sample[], int size, int valor) {
    int izq = 0;
    int der = size - 1;
    while (izq <= der) {
        int medio = izq + (der - izq) / 2;
        if (sample[medio] == valor) {
            return medio;
        }
        if (sample[medio] < valor) {
            izq = medio + 1;
        } else {
            der = medio - 1;
        }
    }
    return der; // Retornar el índice más cercano por debajo del valor
}

int encuentraIndice(int original[], int gaps[], int size, int ini_indice, int valor) {
    int indice_actual = ini_indice;
    int valor_actual = original[ini_indice];
    while (indice_actual < size && valor_actual < valor) {
        valor_actual += gaps[indice_actual+1];
        indice_actual++;
    }
    if (valor_actual == valor) {
        return indice_actual;
    } else {
        return -1; // No encontrado
    }
}

