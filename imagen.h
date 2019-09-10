#ifndef IMAGEN_H
#define IMAGEN_H

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "capa.h"

using namespace std;

class imagen{
public:
    string id;
    int imageHeight;
    int imageWidth;
    int pixelHeight;
    int pixelWidth;
    capa* inicio;
    capa* fin;

    imagen(string, int, int, int, int);
    bool vacia();
    void insertarCapa(matrizDispersa*, int);
    int valorMaximo();
    void mostrarCapas();
};

#endif // IMAGEN_H
