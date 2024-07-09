#ifndef BUSCADORES_H
#define BUSCADORES_H
#include <iostream>
#include <map>
#include <string>
#include <vector>
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

int busquedaBinaria(int* arreglo, int inicio, int fin, int objetivo);
int binarySearchSample(int sample[], int size, int valor);
int encuentraIndice(int gaps[], int size, int ini_indice, int valor, int sample_valor);
void calcularFrecuencia(int gaps[], int size, std::map<int, int> &frecuencia);
int descomprimirGap(char compressedGap, std::map<int, std::string> &huffmanCode);
int encuentraIndiceHuffman(int original[], char gapsComprimidos[], int size, int ini_indice, int valor, std::map<int, std::string> &huffmanCode);
#endif