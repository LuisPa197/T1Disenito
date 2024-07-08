#ifndef NODO_HUFFMAN_H
#define NODO_HUFFMAN_H

struct NodoHuffman
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
};

#endif
