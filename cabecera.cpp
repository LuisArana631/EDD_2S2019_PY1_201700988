#include "cabecera.h"

using namespace std;

cabecera::cabecera(){
    cabecera::inicio = NULL;
    cabecera::fin = NULL;
}

bool cabecera::vacio(){
    return (cabecera::inicio == NULL)? true:false;
}

void  cabecera::insertar(nodoCabecera* insertar){
    if(cabecera::vacio()){
        cabecera::inicio = cabecera::fin = insertar;
    }else{
        if(insertar->x < cabecera::inicio->x){
            cabecera::insertarInicio(insertar);
        }else if(insertar->x > cabecera::fin->x){
            cabecera::insertarFin(insertar);
        }else{
            cabecera::insertarMedio(insertar);
        }
    }
}

void cabecera::insertarInicio(nodoCabecera* insertar){
    cabecera::inicio -> anterior = insertar;
    insertar -> siguiente = cabecera::inicio;
    cabecera::inicio = insertar;
}

void cabecera::insertarFin(nodoCabecera* insertar){
    cabecera::fin -> siguiente = insertar;
    insertar -> anterior = cabecera::fin;
    cabecera::fin = insertar;
}

void cabecera::insertarMedio(nodoCabecera* insertar){
    nodoCabecera* temp;
    nodoCabecera* temp2;
    temp = cabecera::inicio;

    while(temp->x < insertar->x){
        temp = temp -> siguiente;
    }

    temp2 = temp -> anterior;
    temp2 -> siguiente = insertar;
    temp -> anterior = insertar;
    insertar -> siguiente = temp;
    insertar -> anterior =  temp2;
}

void cabecera::mostrar(){
    if(cabecera::vacio()){
        cout<<"Cabecera  vacia"<<endl;
    }else{
        nodoCabecera* temp = cabecera::inicio;
        while(temp !=  NULL){
            cout<<temp->x<<" ";
            temp = temp -> siguiente;
        }
    }
}

nodoCabecera* cabecera::buscar(int x){
   if(cabecera::existeCabecera(x)){
        nodoCabecera* temp;
        temp = cabecera::inicio;
        while(temp->x!=x){
            temp = temp -> siguiente;
        }
        return temp;
   }else{
        return (new nodoCabecera(-1));
   }
}

bool cabecera::existeCabecera(int x){
    if(cabecera::vacio()){
        return false;
    }else{
        nodoCabecera* temp;
        temp = cabecera::inicio;
        while(temp!=NULL){
            if(temp->x == x){
                return true;
            }else if(temp->siguiente == NULL){
                return false;
            }else{
                temp = temp -> siguiente;
            }
        }
    }
}

int cabecera::maximoX(){
    if(vacio()){
        return -1;
    }else{
        nodoCabecera* temp;
        temp = cabecera::fin;
        return temp->x;
    }
}


void cabecera::pintarCabecera(){
    ofstream archivo;
    archivo.open("MatrizDispersa.dot", ios::app);

    if(archivo.fail()){
        cout<<"No se puede abrir el archivo"<<endl;
        return;
    }

    nodoCabecera* aux = cabecera::inicio;

    while(aux!=NULL){
        archivo<<"nodoC"<<aux->x<<"[label=\"C"<<aux->x<<"\" group=C"<<aux->x<<"];"<<endl;
        aux = aux->siguiente;
    }

    aux = cabecera::inicio;

    archivo<<"{ rank=same nodoInicio ";

    while(aux!=NULL){
        archivo<<" nodoC"<<aux->x;
        aux = aux -> siguiente;
    }

    archivo<<"}"<<endl;

    aux = cabecera::inicio;

    archivo<<"nodoInicio -> nodoC"<<aux->x<<";"<<endl;
    archivo<<"nodoInicio -> nodoC"<<aux->x<<"[dir=back];"<<endl;

    while(aux!=NULL){
        if(aux->siguiente!=NULL){
            archivo<<"nodoC"<<aux->x<<" -> nodoC"<<aux->siguiente->x<<";"<<endl;
            archivo<<"nodoC"<<aux->x<<" -> nodoC"<<aux->siguiente->x<<"[dir=back];"<<endl;
        }
        aux = aux->siguiente;
    }

    archivo.close();
}


void cabecera::pintarColumnas(){
    ofstream archivo;
        archivo.open("MatrizDispersa.dot", ios::app);

        if(archivo.fail()){
            cout<<"No se puede abrir el archivo"<<endl;
            return;
        }

        nodoCabecera* aux = cabecera::inicio;

        while(aux!=NULL){
            nodo* temp = aux->col->inicio;

            archivo<<"nodoC"<<aux->x<<" -> nodo"<<temp->x<<temp->y<<";"<<endl;
            archivo<<"nodoC"<<aux->x<<" -> nodo"<<temp->x<<temp->y<<"[dir=back];"<<endl;


            while(temp!=NULL){
                if(temp->abajo!=NULL){
                    archivo<<"nodo"<<temp->x<<temp->y<<" -> nodo"<<temp->abajo->x<<temp->abajo->y<<";"<<endl;
                    archivo<<"nodo"<<temp->x<<temp->y<<" -> nodo"<<temp->abajo->x<<temp->abajo->y<<"[dir=back];"<<endl;
                }
                temp = temp->abajo;
            }

            aux = aux->siguiente;
        }

        archivo.close();
}
