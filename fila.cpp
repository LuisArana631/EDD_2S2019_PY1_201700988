#include "fila.h"

using namespace std;

fila::fila(){
    fila::inicio = NULL;
    fila::fin = NULL;
}

bool fila::vacia(){
    return (fila::inicio==NULL)? true:false;
}

void fila::insertar(nodo* insertar){
    if(fila::vacia()){
        fila::inicio = fila::fin = insertar;
    }else{
        if(insertar->x < fila::inicio->x){
            fila::insertarInicio(insertar);
        }else if(insertar->x > fila::fin->x){
            fila::insertarFin(insertar);
        }else{
            fila::insertarMedio(insertar);
        }
    }
}

void fila::insertarInicio(nodo* insertar){
    fila::inicio -> izquierda = insertar;
    insertar->derecha = fila::inicio;
    fila::inicio = insertar;
}

void fila::insertarFin(nodo* insertar){
    fila::fin->derecha = insertar;
    insertar->izquierda = fila::fin;
    fila::fin = insertar;
}

void fila::insertarMedio(nodo* insertar){
    nodo* aux;
    nodo* aux2;

    aux = fila::inicio;

    while(aux->x < insertar->x){
        aux = aux->derecha;
    }

    if(aux->x == insertar->x)
        return;

    aux2 = aux->izquierda;
    aux2->derecha = insertar;
    aux->izquierda = insertar;
    insertar->derecha = aux;
    insertar->izquierda = aux2;
}

void fila::mostrar(){
    if(fila::vacia()){
        cout<<"Fila vacia"<<endl;
    }else{
        nodo* temp = fila::inicio;
        while(temp!=NULL){
            cout<<"X: "<<temp->x<<" | ";
            cout<<"R: "<<temp->R<<" G: "<<temp->G<<" B: "<<temp->B<<" | "<<endl;
            temp = temp->derecha;
        }
        cout<<endl;
    }
}
