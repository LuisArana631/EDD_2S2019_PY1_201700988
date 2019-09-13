#ifndef MATRIZDISPERSA_H
#define MATRIZDISPERSA_H

#include <iostream>
#include <stdlib.h>
#include <fstream>
#include "nodo.h"
#include "cabecera.h"
#include "lateral.h"

using namespace std;

class matrizDispersa{
public:
    cabecera* indiceX;
    lateral* indiceY;

    matrizDispersa();
    void insertar(int, int, int, int, int);
    void graficarMatriz();
    void linealizarFilas();
    void linealizarColumnas();
    void pintarCuadro(string, int);
};

#endif // MATRIZDISPERSA_H
