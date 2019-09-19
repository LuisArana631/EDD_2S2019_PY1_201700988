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
        archivo<<"rankdir = LR;"<<endl;

        nodoFiltro* aux = filtro::inicio;

        while(aux!=NULL){
            archivo<<aux->nameFiltro;
            if (aux->siguiente!=NULL)
                archivo<<" -> ";
            aux = aux -> siguiente;
        }
        archivo<<";"<<endl;

        aux = filtro::fin;
        while(aux!=NULL){
            archivo<<aux->nameFiltro;
            if (aux->anterior!=NULL)
                archivo<<" -> ";
            aux = aux -> anterior;
        }
        archivo<<";"<<endl;

        archivo<<filtro::inicio->nameFiltro<<" -> "<<filtro::fin->nameFiltro<<";"<<endl;
        archivo<<filtro::fin->nameFiltro<<" -> "<<filtro::inicio->nameFiltro<<";"<<endl;

        archivo<<"}"<<endl;

        system("dot -Tpng Filtros.dot -o Filtros.png");
        system("Filtros.png");
    }
}

void filtro::insertarCapa(matrizDispersa* insertar, int val, string nombre){
    filtro::fin->insertarFiltro(insertar,val,nombre);
}
