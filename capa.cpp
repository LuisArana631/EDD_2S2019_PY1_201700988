#include "capa.h"

using namespace std;

capa::capa(matrizDispersa* matriz, int z, string nombre){
    capa::z = z;
    capa::nombre = nombre;
    capa::matriz = matriz;
    capa::siguiente = NULL;
    capa::anterior = NULL;
}
