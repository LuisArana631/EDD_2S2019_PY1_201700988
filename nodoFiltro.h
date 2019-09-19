#ifndef NODOFILTRO_H
#define NODOFILTRO_H

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "capa.h"

using namespace std;

class nodoFiltro{
public:
    string nameFiltro;
    capa* inicio;
    capa* fin;
    nodoFiltro* siguiente;
    nodoFiltro* anterior;

    nodoFiltro(string);
    void insertarFiltro(matrizDispersa*, int, string);
    bool vacia();
    capa* extraerCapa(int);
};

#endif // NODOFILTRO_H
