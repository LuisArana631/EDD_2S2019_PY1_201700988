#include "nodoFiltro.h"

using namespace std;

nodoFiltro::nodoFiltro(string filtro){
    nodoFiltro::nameFiltro = filtro;
    nodoFiltro::siguiente = NULL;
    nodoFiltro::anterior = NULL;
}
