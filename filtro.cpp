#include "filtro.h"

using namespace std;

filtro::filtro(){
    filtro::inicio = NULL;
    filtro::fin = NULL;
}

bool filtro::vacia(){
    return (filtro::inicio == NULL)? true:false;
}

void filtro::insertar(string filtro){
    nodoFiltro* nuevo = new nodoFiltro(filtro);
    if(filtro::vacia()){
        filtro::inicio = nuevo;
        filtro::fin = nuevo;
    }else{
        filtro::fin -> siguiente = nuevo;
        nuevo -> anterior = filtro::fin;
        filtro::fin = nuevo;
    }
}

void filtro::graficar(){
    if(filtro::vacia()!=true){
        ofstream archivo;
        archivo.open("Filtros.dot", ios::out);

        if(archivo.fail()){
            cout<<"No se puede abrir el archivo"<<endl;
            return;
        }

        archivo<<"digraph ListaFiltros{"<<endl;
        archivo<<"node [shape=record];"<<endl;

        nodoFiltro* aux = filtro::inicio;

        while(aux!=NULL){

            aux = aux -> siguiente;
        }

        archivo<<"}"<<endl;
    }
}
