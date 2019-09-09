#ifndef CAPA_H
#define CAPA_H

#include <iostream>
#include <stdlib.h>
#include "matrizDispersa.h"

using namespace std;

class capa{
public:
    int z;
    matrizDispersa* matriz;
    capa* siguiente;
    capa* anterior;

    capa(matrizDispersa*, int);
};

#endif // CAPA_H
