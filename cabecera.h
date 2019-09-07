#ifndef CABECERA_H
#define CABECERA_H

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "nodoCabecera.h"

using namespace std;

class cabecera{
public:
    nodoCabecera* inicio;
    nodoCabecera* fin;

    cabecera();
    bool vacio();
    void insertar(nodoCabecera*);
    void insertarInicio(nodoCabecera*);
    void insertarFin(nodoCabecera*);
    void insertarMedio(nodoCabecera*);
    void mostrar();
    nodoCabecera* buscar(int);
    bool existeCabecera(int);
    int maximoX();
    void pintarCabecera();
    void pintarColumnas();
};

#endif // CABECERA_H
