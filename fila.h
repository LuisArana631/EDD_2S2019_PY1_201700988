#ifndef FILA_H
#define FILA_H

#include <stdlib.h>
#include <iostream>
#include "nodo.h"

using namespace std;

class fila{
public:
    nodo* inicio;
    nodo* fin;

    fila();
    bool vacia();
    void insertar(nodo*);
    void insertarMedio(nodo*);
    void insertarInicio(nodo*);
    void insertarFin(nodo*);
    void mostrar();

};

#endif // FILA_H
