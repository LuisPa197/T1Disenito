#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <chrono>
#include <algorithm>
#include <map>
#include <string>
#include <vector>
#include "buscadores.h"


using namespace std;


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

int encuentraIndice(int gaps[], int size, int ini_indice, int valor, int sample_valor) {
    int indice_actual = ini_indice;
    int valor_actual = sample_valor;

    while (indice_actual < size - 1 && valor_actual < valor) {
        indice_actual++;
        valor_actual += gaps[indice_actual];
    }

    if (valor_actual == valor) {
        return indice_actual;
    } else {
        return -1; // No encontrado
    }
}

void calcularFrecuencia(int gaps[], int size, map<int, int> &frecuencia)
{
    for (int i = 0; i < size; ++i)
    {
        frecuencia[gaps[i]]++;
    }
}

int descomprimirGap(char compressedGap, map<int, string> &huffmanCode) {
    for (const auto &pair : huffmanCode) {
        char c = 0;
        int k = 7;
        for (int j = huffmanCode[pair.first].size() - 1; j >= 0; j--) {
            if (huffmanCode[pair.first][j] == '1')
                c |= (1 << k);
            k--;
        }
        if (c == compressedGap) {
            return pair.first;
        }
    }
    return -1; // Si no se encuentra, lo que no debería ocurrir
}

int encuentraIndiceHuffman(int original[], char gapsComprimidos[], int size, int ini_indice, int valor, map<int, string> &huffmanCode) {
    int indice_actual = ini_indice;
    int valor_actual = original[ini_indice];
    while (indice_actual < size && valor_actual < valor) {
        int gap = descomprimirGap(gapsComprimidos[indice_actual + 1], huffmanCode);
        valor_actual += gap;
        indice_actual++;
    }
    if (valor_actual == valor) {
        return indice_actual;
    } else {
        return -1; // No encontrado
    }
}