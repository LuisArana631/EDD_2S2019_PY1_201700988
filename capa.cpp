#include "capa.h"

using namespace std;

capa::capa(matrizDispersa* matriz, int z){
    capa::z = z;
    capa::matriz = matriz;
    capa::siguiente = NULL;
    capa::anterior = NULL;
}
