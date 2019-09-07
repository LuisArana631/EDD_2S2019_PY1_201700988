#include "nodoCabecera.h"

using namespace std;

nodoCabecera::nodoCabecera(int x){
    nodoCabecera::x = x;
    nodoCabecera::col = new columna();
    nodoCabecera::siguiente = NULL;
    nodoCabecera::anterior = NULL;
}
