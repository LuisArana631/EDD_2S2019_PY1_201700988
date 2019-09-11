#ifndef CAPA_H
#define CAPA_H

#include <iostream>
#include <stdlib.h>
#include "matrizDispersa.h"

using namespace std;

class capa{
public:
    int z;
    string nombre;
    matrizDispersa* matriz;
    capa* siguiente;
    capa* anterior;

    capa(matrizDispersa*, int, string);
};

#endif // CAPA_H
