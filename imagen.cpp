#include "imagen.h"

using namespace std;

imagen::imagen(string id, int imageHeight, int imageWidth, int pixelHeight, int pixelWidth){
    imagen::id = id;
    imagen::inicio  = NULL;
    imagen::fin = NULL;
    imagen::listaFiltros = new filtro();
    imagen::imageWidth = imageWidth;
    imagen::imageHeight = imageHeight;
    imagen::pixelHeight = pixelHeight;
    imagen::pixelWidth = pixelWidth;
}

bool imagen::vacia(){
    return (imagen::inicio==NULL)? true:false;
}

void imagen::insertarCapa(matrizDispersa* insertar, int val, string nombre){
    capa* nueva = new capa(insertar, val, nombre);
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
        cout<<aux->z<<" - "<<aux->nombre<<endl;
        aux = aux -> siguiente;
    }
}

capa* imagen::extraerCapa(int z){

    capa* aux = imagen::inicio;

    while(aux!=NULL){
        if(aux->z == z){
            return aux;
        }
        aux = aux -> siguiente;
    }
    return false;
}

void imagen::crearCSSOriginal(string dir){

    int maxX = 0;
    int maxY = 0;

    capa* auxDeCapa = NULL;
    if(imagen::listaFiltros->inicio != NULL){
        cout<<"usando la del filtro"<<endl;
        auxDeCapa = imagen::listaFiltros->fin->inicio;
    }else{
        auxDeCapa = imagen::inicio;
    }



    while(auxDeCapa!=NULL){
        if(auxDeCapa->matriz->indiceX->maximoX() > maxX)
            maxX = auxDeCapa->matriz->indiceX->maximoX();

        if(auxDeCapa->matriz->indiceY->maximoY() > maxY)
            maxY = auxDeCapa->matriz->indiceY->maximoY();

        auxDeCapa = auxDeCapa->siguiente;
    }

    dir = dir + "\\" + imagen::id +".css";
    ofstream archivo;
    archivo.open(dir.c_str(),ios::out);

    if(archivo.fail()){
        cout<<"No se puede crear css"<<endl;
        return;
    }

    //Escribir codigo CSS para pintar cuadricula
    archivo<<"body{"<<endl;
    archivo<<"background: #fff;"<<endl;
    archivo<<"height: 100vh;"<<endl;
    archivo<<"display: flex;"<<endl;
    archivo<<"justify-content: center;"<<endl;
    archivo<<"align-items: center;"<<endl;
    archivo<<"}"<<endl;

    archivo<<".canvas{"<<endl;
    archivo<<"width: "<<imagen::pixelWidth*maxX<<"px;"<<endl;
    archivo<<"height: "<<imagen::pixelHeight*maxY<<"px;"<<endl;
    archivo<<"}"<<endl;

    archivo<<".pixel{"<<endl;
    archivo<<"width: "<<imagen::pixelWidth<<"px;"<<endl;
    archivo<<"height: "<<imagen::pixelHeight<<"px;"<<endl;
    //archivo<<"box-shadow: 0px 0px 1px #333;"<<endl;
    archivo<<"float: left;"<<endl;
    archivo<<"}"<<endl;

    archivo.close();

    capa* aux = NULL;
    if(imagen::listaFiltros->inicio != NULL){
        cout<<"usando la del filtro"<<endl;
        aux = imagen::listaFiltros->fin->inicio;
    }else{
        aux = imagen::inicio;
    }


    while(aux!=NULL){
        cout<<"Pintando la capa: "<<aux->z<<endl;
        aux->matriz->pintarCuadro(dir, maxX);
        aux = aux->siguiente;
    }

    archivo.open(dir.c_str(),ios::app);

    if(archivo.fail()){
        cout<<"No se puede crear css"<<endl;
        return;
    }

    archivo.close();
    cout<<"----------------------------------------------"<<endl;
    cout<<"Archivo .css creado."<<endl;
}

void imagen::crearHTML(string dir){
    //Extraer los margenes de la cuadricula
    int maxX = 0;
    int maxY = 0;

    capa* aux = imagen::inicio;

    while(aux!=NULL){
        if(aux->matriz->indiceX->maximoX() > maxX)
            maxX = aux->matriz->indiceX->maximoX();

        if(aux->matriz->indiceY->maximoY() > maxY)
            maxY = aux->matriz->indiceY->maximoY();

        aux = aux->siguiente;

    }

    //Crear el archivo
    dir = dir + "\\" + imagen::id +".html";
    ofstream archivo;
    archivo.open(dir.c_str(),ios::out);

    if(archivo.fail()){
        cout<<"No se puede crear html"<<endl;
        return;
    }

    //Codigo html escrito en el archivo
    archivo<<"<!DOCTYPE html>"<<endl;
    archivo<<"<html>"<<endl;
    archivo<<"<head>"<<endl;
    archivo<<"<link rel=\"stylesheet\" href=\""<<imagen::id<<".css\">"<<endl;
    archivo<<"</head>"<<endl;

    archivo<<"<body>"<<endl;
    archivo<<"<div class=\"canvas\">"<<endl;

    for(int i=0; i<maxY+1;i++){
        for(int j=0; j<maxX+1; j++){
            archivo<<"<div class=\"pixel\"></div>"<<endl;
        }
    }

    archivo<<"</div>"<<endl;

    archivo<<"</body>"<<endl;
    archivo<<"</html>"<<endl;

    archivo.close();

    cout<<"Archivo .html creado."<<endl;

}

void imagen::filtroNegativo(){
    capa* aux = imagen::inicio;

    imagen::listaFiltros->insertar("Negativo");

    while(aux!=NULL){
        //Extraer valores que iran en la capa
        matrizDispersa* copiaMatriz = new matrizDispersa();
        int valorCopia = aux->z;
        string nombreCopia = aux->nombre;

        //Llenar la matriz nueva con el filtro aplicado
        nodoLateral* auxLateral = aux->matriz->indiceY->inicio;

        while(auxLateral!=NULL){
            nodo* auxNodo = auxLateral->fil->inicio;

            while(auxNodo!=NULL){
                int x = auxNodo->x;
                int y = auxNodo->y;
                int R = 255 - auxNodo->R;
                int G = 255 - auxNodo->G;
                int B = 255 - auxNodo->B;

                copiaMatriz->insertar(x,y,R,G,B);
                auxNodo =  auxNodo->derecha;
            }
            auxLateral = auxLateral->abajo;
        }

        imagen::listaFiltros->insertarCapa(copiaMatriz,valorCopia,nombreCopia);
        cout<<"Termino la primera insercion"<<endl;
        aux = aux -> siguiente;
    }

}

void imagen::terminarFiltros(){
    imagen::listaFiltros->inicio = NULL;
    imagen::listaFiltros->fin = NULL;
}

void imagen::filtroGrises(){
    capa* aux = imagen::inicio;

    imagen::listaFiltros->insertar("EscalaGrises");

    while(aux!=NULL){
        //Extraer valores que iran en la capa
        matrizDispersa* copiaMatriz = new matrizDispersa();
        int valorCopia = aux->z;
        string nombreCopia = aux->nombre;

        //Llenar la matriz nueva con el filtro aplicado
        nodoLateral* auxLateral = aux->matriz->indiceY->inicio;

        while(auxLateral!=NULL){
            nodo* auxNodo = auxLateral->fil->inicio;

            while(auxNodo!=NULL){
                int x = auxNodo->x;
                int y = auxNodo->y;
                int R = auxNodo->R;
                int G = auxNodo->G;
                int B = auxNodo->B;
                int gris = (R+G+B)/3;

                copiaMatriz->insertar(x,y,gris,gris,gris);
                auxNodo =  auxNodo->derecha;
            }
            auxLateral = auxLateral->abajo;
        }

        imagen::listaFiltros->insertarCapa(copiaMatriz,valorCopia,nombreCopia);
        cout<<"Termino la primera insercion"<<endl;
        aux = aux -> siguiente;
    }
}

void imagen::filtroNegativoCapa(int z){
    capa* aux = imagen::inicio;

    imagen::listaFiltros->insertar("NegativoCapa");

    while(aux!=NULL){

        if(aux->z == z){
            //Extraer valores que iran en la capa
            matrizDispersa* copiaMatriz = new matrizDispersa();
            int valorCopia = aux->z;
            string nombreCopia = aux->nombre;

            //Llenar la matriz nueva con el filtro aplicado
            nodoLateral* auxLateral = aux->matriz->indiceY->inicio;

            while(auxLateral!=NULL){
                nodo* auxNodo = auxLateral->fil->inicio;

                while(auxNodo!=NULL){
                    int x = auxNodo->x;
                    int y = auxNodo->y;
                    int R = 255 - auxNodo->R;
                    int G = 255 - auxNodo->G;
                    int B = 255 - auxNodo->B;

                    copiaMatriz->insertar(x,y,R,G,B);
                    auxNodo =  auxNodo->derecha;
                }
                auxLateral = auxLateral->abajo;
            }


            imagen::listaFiltros->insertarCapa(copiaMatriz,valorCopia,nombreCopia);
        }else{
            //Extraer valores que iran en la capa
            matrizDispersa* copiaMatriz = new matrizDispersa();
            int valorCopia = aux->z;
            string nombreCopia = aux->nombre;

            //Llenar la matriz nueva con el filtro aplicado
            nodoLateral* auxLateral = aux->matriz->indiceY->inicio;

            while(auxLateral!=NULL){
                nodo* auxNodo = auxLateral->fil->inicio;

                while(auxNodo!=NULL){
                    int x = auxNodo->x;
                    int y = auxNodo->y;
                    int R = auxNodo->R;
                    int G = auxNodo->G;
                    int B = auxNodo->B;

                    copiaMatriz->insertar(x,y,R,G,B);
                    auxNodo =  auxNodo->derecha;
                }
                auxLateral = auxLateral->abajo;
            }

            imagen::listaFiltros->insertarCapa(copiaMatriz,valorCopia,nombreCopia);
        }
        aux = aux -> siguiente;
    }
}

void imagen::filtroGrisesCapa(int z){
    capa* aux = imagen::inicio;

    imagen::listaFiltros->insertar("EscalaGrisesCapa");

    while(aux!=NULL){

        if(aux->z == z){
            //Extraer valores que iran en la capa
            matrizDispersa* copiaMatriz = new matrizDispersa();
            int valorCopia = aux->z;
            string nombreCopia = aux->nombre;

            //Llenar la matriz nueva con el filtro aplicado
            nodoLateral* auxLateral = aux->matriz->indiceY->inicio;

            while(auxLateral!=NULL){
                nodo* auxNodo = auxLateral->fil->inicio;

                while(auxNodo!=NULL){
                int x = auxNodo->x;
                int y = auxNodo->y;
                int R = auxNodo->R;
                int G = auxNodo->G;
                int B = auxNodo->B;
                int gris = (R+G+B)/3;

                copiaMatriz->insertar(x,y,gris,gris,gris);
                auxNodo =  auxNodo->derecha;
            }
            auxLateral = auxLateral->abajo;
            }


            imagen::listaFiltros->insertarCapa(copiaMatriz,valorCopia,nombreCopia);
        }else{
            //Extraer valores que iran en la capa
            matrizDispersa* copiaMatriz = new matrizDispersa();
            int valorCopia = aux->z;
            string nombreCopia = aux->nombre;

            //Llenar la matriz nueva con el filtro aplicado
            nodoLateral* auxLateral = aux->matriz->indiceY->inicio;

            while(auxLateral!=NULL){
                nodo* auxNodo = auxLateral->fil->inicio;

                while(auxNodo!=NULL){
                    int x = auxNodo->x;
                    int y = auxNodo->y;
                    int R = auxNodo->R;
                    int G = auxNodo->G;
                    int B = auxNodo->B;

                    copiaMatriz->insertar(x,y,R,G,B);
                    auxNodo =  auxNodo->derecha;
                }
                auxLateral = auxLateral->abajo;
            }

            imagen::listaFiltros->insertarCapa(copiaMatriz,valorCopia,nombreCopia);
        }
        aux = aux -> siguiente;
    }
}



