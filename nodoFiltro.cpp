#include "nodoFiltro.h"

using namespace std;

nodoFiltro::nodoFiltro(string filtro){
    nodoFiltro::nameFiltro = filtro;
    nodoFiltro::inicio = NULL;
    nodoFiltro::fin = NULL;
    nodoFiltro::siguiente = NULL;
    nodoFiltro::anterior = NULL;
}

bool nodoFiltro::vacia(){
    return (nodoFiltro::inicio == NULL)? true:false;
}

void nodoFiltro::insertarFiltro(matrizDispersa* insertar, int val, string nombre){
    capa* nueva = new capa(insertar, val, nombre);
    if(nodoFiltro::vacia()){
        nodoFiltro::inicio = nodoFiltro::fin = nueva;
    }else{
        nodoFiltro::fin  -> siguiente = nueva;
        nueva -> anterior = nodoFiltro::fin;
        nodoFiltro::fin = nueva;
    }
}

capa* nodoFiltro::extraerCapa(int z){
    capa* aux = nodoFiltro::inicio;

    while(aux!=NULL){
        if(aux->z == z){
            return aux;
        }
        aux = aux -> siguiente;
    }

    return false;
}
