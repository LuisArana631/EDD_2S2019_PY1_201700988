#include "nodo.h"

using namespace std;

nodo::nodo(int x, int y, int R, int G, int B){
    nodo::R = R;
    nodo::G = G;
    nodo::B = B;
    nodo::x = x;
    nodo::y = y;
    nodo::arriba = NULL;
    nodo::abajo = NULL;
    nodo::izquierda = NULL;
    nodo::derecha = NULL;
}
