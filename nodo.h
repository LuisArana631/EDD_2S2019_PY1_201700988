#ifndef NODO_H
#define NODO_H

#include <stdlib.h>

using namespace std;

class nodo{
public:
    int x;
    int y;
    int R;
    int G;
    int B;
    nodo* arriba;
    nodo* abajo;
    nodo* derecha;
    nodo* izquierda;

    nodo(int, int, int, int, int);
};

#endif // NODO_H
