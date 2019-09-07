#ifndef NODOLATERAL_H
#define NODOLATERAL_H

#include <stdlib.h>
#include "fila.h"

using namespace std;

class nodoLateral{
public:
    int y;
    nodoLateral* arriba;
    nodoLateral* abajo;
    fila* fil;

    nodoLateral(int);
};

#endif // NODOLATERAL_H
