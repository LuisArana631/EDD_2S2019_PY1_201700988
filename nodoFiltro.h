#ifndef NODOFILTRO_H
#define NODOFILTRO_H

#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

class nodoFiltro{
public:
    string nameFiltro;
    nodoFiltro* siguiente;
    nodoFiltro* anterior;

    nodoFiltro(string);
};

#endif // NODOFILTRO_H
