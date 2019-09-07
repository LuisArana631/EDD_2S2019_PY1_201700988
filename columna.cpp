#include "columna.h"

using namespace std;

columna::columna(){
    columna::inicio = NULL;
    columna::fin = NULL;
}

bool columna::vacia(){
    return(columna::inicio==NULL)? true:false;
}

void columna::insertar(nodo* insertar){
    if(columna::vacia()){
        columna::inicio = columna::fin = insertar;
    }else{
        if(insertar -> y < columna::inicio -> y){
            columna::insertarInicio(insertar);
        }else if(insertar -> y > columna::fin -> y){
            columna::insertarFin(insertar);
        }else{
            columna::insertarMedio(insertar);
        }
    }
}

void columna::insertarInicio(nodo* insertar){
    columna::inicio -> arriba = insertar;
    insertar -> abajo = columna::inicio;
    columna::inicio = insertar;
}

void columna::insertarFin(nodo* insertar){
    columna::fin -> abajo = insertar;
    insertar -> arriba = columna::fin;
    columna::fin = insertar;
}

void columna::insertarMedio(nodo* insertar){
    nodo* aux1;
    nodo* aux2;

    aux1 = columna::inicio;

    while(aux1 -> y < insertar -> y){
        aux1 = aux1 -> abajo;
    }

    if(aux1->y == insertar->y)
        return;

    aux2 = aux1 -> arriba;
    aux2 -> abajo = insertar;
    aux1 -> arriba = insertar;
    insertar -> abajo = aux1;
    insertar -> arriba = aux2;
}

void columna::mostrar(){
    if(columna::vacia()){
        cout<<"Columna vacia"<<endl;
    }else{
        nodo* temp = columna::inicio;
        while(temp != NULL){
            cout<<"Y: "<<temp->y<<" | ";
            cout<<"R: "<<temp->R<<" G: "<<temp->G<<" B: "<<temp->B<<" | "<<endl;
            temp = temp -> abajo;
        }
        cout<<endl;
    }
}
