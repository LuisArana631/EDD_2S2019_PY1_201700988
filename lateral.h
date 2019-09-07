#ifndef LATERAL_H
#define LATERAL_H

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "nodoLateral.h"

using namespace std;

class lateral{
public:
    nodoLateral* inicio;
    nodoLateral* fin;

    lateral();
    bool vacio();
    void insertar(nodoLateral*);
    void insertarInicio(nodoLateral*);
    void insertarFin(nodoLateral*);
    void insertarMedio(nodoLateral*);
    void mostrar();
    nodoLateral* buscar(int);
    bool existeLateral(int);
    int maximoY();
    void pintarLateral();
    void pintarFilas();
};

#endif // LATERAL_H
