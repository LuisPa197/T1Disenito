#ifndef GENERADORES_H
#define GENERADORES_H
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <queue>
#include "nodo_huffman.h"

int* inicializarArregloLineal(int* arreglo, int n);
int* inicializarArregloNormal(int* arreglo, int n, double media, double desviacion);
void generarGaps(int arr[], int gaps[], int size);
void generarSample(int arr[], int sample[], int size, int m, int b);
NodoHuffman *construirArbolHuffman(std::vector<std::pair<int, int>> &frecuenciasOrdenadas);
void generarCodigosHuffman(NodoHuffman *raiz, std::string codigo, std::map<int, std::string> &huffmanCode);
void codificarBits(std::vector<std::pair<int, std::string>> &huffmanCode, char charCode[], std::vector<std::pair<int, int>> frecuenciasOrdenadas);
void codificarGaps(int size, char charCode[], int gaps[], char gapsComprimidos[]);
#endif