#include "lateral.h"

using namespace std;

lateral::lateral(){
    lateral::inicio = NULL;
    lateral::fin = NULL;
}

bool lateral::vacio(){
    return (lateral::inicio == NULL)? true:false;
}

void lateral::insertar(nodoLateral* insertar){
    if(lateral::vacio()){
        lateral::inicio = lateral::fin = insertar;
    }else{
        if(insertar -> y < lateral::inicio -> y){
            lateral::insertarInicio(insertar);
        }else if(insertar -> y > lateral::fin -> y){
            lateral::insertarFin(insertar);
        }else{
            lateral::insertarMedio(insertar);
        }
    }
}

void lateral::insertarInicio(nodoLateral* insertar){
    lateral::inicio -> arriba = insertar;
    insertar -> abajo = lateral::inicio;
    lateral::inicio = insertar;
}

void lateral::insertarFin(nodoLateral* insertar){
    lateral::fin -> abajo = insertar;
    insertar -> arriba  = lateral::fin;
    lateral::fin = insertar;
}

void lateral::insertarMedio(nodoLateral* insertar){
    nodoLateral* temp;
    nodoLateral* temp2;
    temp = lateral::inicio;

    while(temp->y < insertar->y){
        temp = temp -> abajo;
    }

    temp2 = temp -> arriba;
    temp2 -> abajo = insertar;
    temp -> arriba = insertar;
    insertar -> abajo = temp;
    insertar -> arriba = temp2;
}

void lateral::mostrar(){
    if(lateral::vacio()){
        cout<<"Lateral vacio"<<endl;
    }else{
        nodoLateral* temp = lateral::inicio;
        while(temp!=NULL){
            cout<<temp->y<<" ";
            temp = temp -> abajo;
        }
    }
}

nodoLateral* lateral::buscar(int y){
    if(lateral::existeLateral(y)){
        nodoLateral* temp;
        temp = lateral::inicio;
        while(temp->y!=y){
            temp = temp -> abajo;
        }
        return temp;
    }else{
        return (new nodoLateral(-1));
    }
}

bool lateral::existeLateral(int y){
    if(lateral::vacio()){
        return false;
    }else{
        nodoLateral* temp;
        temp = lateral::inicio;
        while(temp!=NULL){
            if(temp->y == y){
                return true;
            }else if(temp -> abajo == NULL){
                return false;
            }else{
                temp = temp -> abajo;
            }
        }
    }
}

int lateral::maximoY(){
    if(lateral::vacio()){
        return -1;
    }else{
        nodoLateral* temp;
        temp = lateral::fin;
        return temp->y;
    }
}

void lateral::pintarLateral(){
    ofstream archivo;
    archivo.open("MatrizDispersa.dot", ios::app);

    if(archivo.fail()){
        cout<<"No se puede abrir el archivo"<<endl;
    }

    nodoLateral* aux = lateral::inicio;

    while(aux!=NULL){
        archivo<<"nodoF"<<aux->y<<"[label = \"F"<<aux->y<<"\" group=Inicio];"<<endl;
        aux = aux -> abajo;
    }

    aux = lateral::inicio;

    archivo<<"nodoInicio -> nodoF"<<aux->y<<";"<<endl;

    while(aux!=NULL){
        if(aux->abajo!=NULL){
            archivo<<"nodoF"<<aux->y<<" -> nodoF"<<aux->abajo->y<<";"<<endl;
        }
        aux = aux -> abajo;
    }

    aux = lateral::fin;

    while(aux!=NULL){
        if(aux->arriba!=NULL){
            archivo<<"nodoF"<<aux->y<<" -> nodoF"<<aux->arriba->y<<";"<<endl;
        }
        aux = aux -> arriba;
    }

    archivo<<"nodoF"<<lateral::inicio->y<<" -> nodoInicio;"<<endl;

    archivo.close();
}

void lateral::pintarFilas(){
    ofstream archivo;
    archivo.open("MatrizDispersa.dot", ios::app);

    if(archivo.fail()){
        cout<<"No se puede abrir el archivo"<<endl;
    }

    nodoLateral* aux = lateral::inicio;

    while(aux!=NULL){
        nodo* temp = aux->fil->inicio;

        while(temp!=NULL){
            archivo<<"nodo"<<temp->x<<temp->y<<"[label=\""<<temp->R<<"-"<<temp->G<<"-"<<temp->B<<"\" group=C"<<temp->x<<"];"<<endl;
            temp = temp -> derecha;
        }

        temp = aux->fil->inicio;

        archivo<<"{rank=same nodoF"<<aux->y;

        while(temp!=NULL){
            archivo<<" nodo"<<temp->x<<temp->y;
            temp = temp -> derecha;
        }

        archivo<<"};"<<endl;

        temp = aux->fil->inicio;

        archivo<<"nodoF"<<aux->y<<" -> nodo"<<temp->x<<temp->y<<";"<<endl;

        while(temp!=NULL){
            if(temp->derecha!=NULL){
                archivo<<"nodo"<<temp->x<<temp->y<<" -> nodo"<<temp->derecha->x<<temp->derecha->y<<";"<<endl;
            }
            temp = temp -> derecha;
        }

        temp = aux->fil->fin;

        while(temp!=NULL){
            if(temp->izquierda!=NULL){
                archivo<<"nodo"<<temp->x<<temp->y<<" -> nodo"<<temp->izquierda->x<<temp->izquierda->y<<";"<<endl;
            }
            temp = temp -> izquierda;
        }

        archivo<<"nodo"<<aux->fil->inicio->x<<aux->fil->inicio->y<<" -> nodoF"<<aux->y<<";"<<endl;

        aux = aux -> abajo;
    }

    archivo.close();

}

