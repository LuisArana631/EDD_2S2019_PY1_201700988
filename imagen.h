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
    capa* inicio;
    capa* fin;

    imagen(string);
    bool vacia();
    void insertarCapa(matrizDispersa*, int);
    int valorMaximo();
    void mostrarCapas();
};

#endif // IMAGEN_H
