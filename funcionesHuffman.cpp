#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include "nodo_huffman.h"
#include "funcionesHuffman.h"

using namespace std;

bool ordenarHuffmanCode(map<int, string> &huffmanCode, const vector<pair<int, int>> &frecuenciasOrdenadas, vector<pair<int, string>> &huffmanCodeOrdenado)
{
    // Crear un vector de pares para almacenar las claves y los códigos de Huffman
    vector<pair<int, string>> huffmanCodeVector;

    // Recorrer el vector de frecuenciasOrdenadas
    for (const auto &par : frecuenciasOrdenadas)
    {
        int clave = par.first;

        // Verificar si la clave existe en el huffmanCode original
        if (huffmanCode.find(clave) != huffmanCode.end())
        {
            huffmanCodeVector.push_back({clave, huffmanCode[clave]});
        }
        else
        {
            // Si alguna clave no existe en el huffmanCode, retorna false
            cerr << "Error: La clave " << clave << " no existe en huffmanCode." << endl;
            return false;
        }
    }

    // Ordenar el vector de huffmanCode basado en las frecuencias de mayor a menor
    sort(huffmanCodeVector.begin(), huffmanCodeVector.end(), [&frecuenciasOrdenadas](const pair<int, string> &a, const pair<int, string> &b)
        {
        auto itA = find_if(frecuenciasOrdenadas.begin(), frecuenciasOrdenadas.end(), [&a](const pair<int, int> &p) { return p.first == a.first; });
        auto itB = find_if(frecuenciasOrdenadas.begin(), frecuenciasOrdenadas.end(), [&b](const pair<int, int> &p) { return p.first == b.first; });
        return itA->second > itB->second; });

    // Actualizar el huffmanCodeOrdenado con el vector ordenado
    huffmanCodeOrdenado = huffmanCodeVector;

    // Si todas las claves se encontraron y se ordenaron correctamente, retorna true
    return true;
}

void codificarBitsShort(vector<pair<int, string>> &huffmanCode, int shortCode[], const vector<pair<int, int>> &frecuenciasOrdenadas)
{

    for (int i = 0; i < huffmanCode.size() - 1; ++i)
    {
        // cout << "sice huffman "<<huffmanCode.size() << endl;
        int c = 0;
        int k = 31;

        // cout << "tamano .size: " << huffmanCode[frecuenciasOrdenadas[i].first].size() << endl;

        for (int j = huffmanCode[i].second.size() - 1; j >= 0; j--)
        { /*
            cout << "valor en huffmnancode: " << huffmanCode[i] << endl;
            cout<<"valor de j "<<j<<" "<< i <<endl;
            cout<<"bits " <<frecuenciasOrdenadas[i].first<<endl;
            */
            if (huffmanCode[i].second[j] == '1')
                c |= (1 << k);
            k--;
        }
        shortCode[i] = c;
    }
}

void codificarGapsShort(int size, const int *shortCode, const int *gaps, int *gapsComprimidos)
{
    for (int i = 0; i < size; i++)
    {
        gapsComprimidos[i] = shortCode[gaps[i]];
    }
}

int descomprimirGapShort(int compressedGap, const map<int, string> &huffmanCode)
{
    for (const auto &pair : huffmanCode)
    {
        int c = 0;
        int k = 31;
        for (int j = pair.second.size() - 1; j >= 0; j--)
        {
            if (pair.second[j] == '1')
                c |= (1 << k);
            k--;
        }
        if (c == compressedGap)
        {
            return pair.first;
        }
    }
    return -1; // Si no se encuentra, lo que no debería ocurrir
}

int encuentraIndiceHuffmanShort(const int *original, const int *gapsComprimidos, int size, int ini_indice, int valor, const map<int, string> &huffmanCode)
{
    int indice_actual = ini_indice;
    int valor_actual = original[ini_indice];
    while (indice_actual < size && valor_actual < valor)
    {
        int gap = descomprimirGapShort(gapsComprimidos[indice_actual + 1], huffmanCode);
        valor_actual += gap;
        indice_actual++;
    }
    if (valor_actual == valor)
    {
        return indice_actual;
    }
    else
    {
        return -1; // No encontrado
    }
}