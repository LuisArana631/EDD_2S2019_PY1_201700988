#ifndef COLUMNA_H
#define COLUMNA_H

#include <iostream>
#include <stdlib.h>
#include "nodo.h"

using namespace std;

class columna{
public:
    nodo* inicio;
    nodo* fin;

    columna();
    bool vacia();
    void insertar(nodo*);
    void insertarInicio(nodo*);
    void insertarFin(nodo*);
    void insertarMedio(nodo*);
    void mostrar();
};

#endif // COLUMNA_H
