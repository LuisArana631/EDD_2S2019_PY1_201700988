#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include "nodoFiltro.h"

using namespace std;

class filtro{
public:
    nodoFiltro* inicio;
    nodoFiltro* fin;

    filtro();
    bool vacia();
    void insertar(string);
    void graficar();
    void descartarFiltro();
};
