#include "imagen.h"

using namespace std;

imagen::imagen(string id){
    imagen::id = id;
    imagen::inicio  = NULL;
    imagen::fin = NULL;
}

bool imagen::vacia(){
    return (imagen::inicio==NULL)? true:false;
}

void imagen::insertarCapa(matrizDispersa* insertar, int val){
    capa* nueva = new capa(insertar, val);
    if(imagen::vacia()){
        inicio = fin = nueva;
    }else{
        imagen::fin -> siguiente = nueva;
        nueva -> anterior = imagen::fin;
        imagen::fin = nueva;
    }
}

int imagen::valorMaximo(){
    return imagen::fin->z;
}

void imagen::mostrarCapas(){
    capa* aux = imagen::inicio;
    while(aux!=NULL){
        cout<<"Z: "<<aux->z<<endl;
        aux = aux -> siguiente;
    }
}


