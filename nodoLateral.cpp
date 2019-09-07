#include "nodoLateral.h"

using namespace std;

nodoLateral::nodoLateral(int y){
    nodoLateral::y = y;
    nodoLateral::fil = new fila();
    nodoLateral::arriba = NULL;
    nodoLateral::abajo = NULL;
}
