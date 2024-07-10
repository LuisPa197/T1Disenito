#ifndef FUNCIONESHUFFMAN_H
#define FUNCIONESHUFFMAN_H
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>
#include "nodo_huffman.h"

bool ordenarHuffmanCode(std::map<int, std::string> &huffmanCode, const std::vector<std::pair<int, int>> &frecuenciasOrdenadas, std::vector<std::pair<int, std::string>> &huffmanCodeOrdenado);
void codificarBitsShort(std::vector<std::pair<int, std::string>> &huffmanCode, int shortCode[], const std::vector<std::pair<int, int>> &frecuenciasOrdenadas);
void codificarGapsShort(int size, const int *shortCode, const int *gaps, int *gapsComprimidos);
int descomprimirGapShort(int compressedGap, const std::map<int, std::string> &huffmanCode);
int encuentraIndiceHuffmanShort(const int *original, const int *gapsComprimidos, int size, int ini_indice, int valor, const std::map<int, std::string> &huffmanCode);

#endif