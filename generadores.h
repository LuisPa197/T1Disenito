#ifndef GENERADORES_H
#define GENERADORES_H
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <queue>
#include "nodo_huffman.h"

/*struct NodoHuffman
{
    int valor;
    int frecuencia;
    NodoHuffman *izq;
    NodoHuffman *der;

    NodoHuffman(int v, int f) : valor(v), frecuencia(f), izq(nullptr), der(nullptr) {}
};

struct CompararNodos
{
    bool operator()(NodoHuffman *izq, NodoHuffman *der)
    {
        return izq->frecuencia > der->frecuencia;
    }
};*/

int* inicializarArregloLineal(int* arreglo, int n);
int* inicializarArregloNormal(int* arreglo, int n, double media, double desviacion);
void generarGaps(int arr[], int gaps[], int size);
void generarSample(int arr[], int sample[], int size, int m, int b);
NodoHuffman *construirArbolHuffman(std::vector<std::pair<int, int>> &frecuenciasOrdenadas);
void generarCodigosHuffman(NodoHuffman *raiz, std::string codigo, std::map<int, std::string> &huffmanCode);
void codificarBits(int gaps[], int size, std::map<int, std::string> &huffmanCode, char charCode[], std::vector<std::pair<int, int>> frecuenciasOrdenadas);
void codificarGaps(int size, char charCode[], int gaps[], char gapsComprimidos[]);
#endif