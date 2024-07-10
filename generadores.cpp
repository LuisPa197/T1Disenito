#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <chrono>
#include <algorithm>
#include <random>
#include <map>
#include <string>
#include <vector>
#include "generadores.h"

using namespace std;

int* inicializarArregloLineal(int* arreglo, int n) {
    arreglo[0] = rand() % 10; // Valor inicial aleatorio entre 0 y 99
    for (int i = 1; i < n; i++) {
        arreglo[i] = arreglo[i - 1] + (rand() % 10); // Siguiente valor aleatorio entre 0 y 9
    }

    return arreglo;
}

int* inicializarArregloNormal(int* arreglo, int n, double media, double desviacion) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> d(media, desviacion);

    for (int i = 0; i < n; i++)
    {
        do
        {
            arreglo[i] = round(d(gen));
        } while (arreglo[i] < 0);
    }

    return arreglo;
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

NodoHuffman *construirArbolHuffman(vector<pair<int, int>> &frecuenciasOrdenadas){
    priority_queue<NodoHuffman *, vector<NodoHuffman *>, CompararNodos> minHeap;

    for (auto pair : frecuenciasOrdenadas)
    {
        minHeap.push(new NodoHuffman(pair.first, pair.second));
    }

    while (minHeap.size() != 1)
    {
        NodoHuffman *izq = minHeap.top();
        minHeap.pop();
        NodoHuffman *der = minHeap.top();
        minHeap.pop();

        NodoHuffman *suma = new NodoHuffman(-1, izq->frecuencia + der->frecuencia);
        suma->izq = izq;
        suma->der = der;
        minHeap.push(suma);
    }

    return minHeap.top();
}

void generarCodigosHuffman(NodoHuffman *raiz, string codigo, map<int, string> &huffmanCode){
    if (!raiz)
        return;

    if (raiz->valor != -1)
    {
        huffmanCode[raiz->valor] = codigo;
    }

    generarCodigosHuffman(raiz->izq, codigo + "0", huffmanCode);
    generarCodigosHuffman(raiz->der, codigo + "1", huffmanCode);
}

void codificarBits(vector<pair<int, string>> &huffmanCode, char charCode[], vector<pair<int, int>> frecuenciasOrdenadas)
{
    for (int i = 0; i < huffmanCode.size(); ++i)
    {
        char c = 0;
        int k = 7;
        for (int j = huffmanCode[i].second.size() - 1; j >= 0; j--)
        {
            if (huffmanCode[i].second[j] == '1')
                c |= (1 << k);
            k--;
        }
        charCode[i] = c;
    }
}

void codificarGaps(int size, char charCode[], int gaps[], char gapsComprimidos[]){
    for(int i = 0; i < size; i++){
        gapsComprimidos[i] = charCode[gaps[i]];
    }
}

