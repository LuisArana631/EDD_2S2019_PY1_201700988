#include "imagen.h"

using namespace std;

imagen::imagen(string id, int imageHeight, int imageWidth, int pixelHeight, int pixelWidth){
    imagen::id = id;
    imagen::inicio  = NULL;
    imagen::fin = NULL;
    imagen::copiaInicio = NULL;
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
    capa* aux = NULL;

    if(imagen::copiaInicio!=NULL){
        aux = imagen::copiaInicio;
    }else{
        aux = imagen::inicio;
    }

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

    if(imagen::copiaInicio!=NULL){
        cout<<"Usando copia."<<endl;
        auxDeCapa = imagen::copiaInicio;
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

    if(imagen::copiaInicio!=NULL){
        cout<<"Usando segunda copia"<<endl;
        aux = imagen::copiaInicio;
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

void imagen::inicializarCopia(){
    capa* copia = imagen::fin;

    while(copia!=NULL){
        matrizDispersa* copiaMatriz = copia->matriz;
        int valorCopia = copia->z;
        string nombreCopia = copia->nombre;

        capa* nuevaCopia = new capa(copiaMatriz,valorCopia,nombreCopia);

        nuevaCopia -> siguiente = imagen::copiaInicio;
        imagen::copiaInicio = nuevaCopia;


        copia = copia -> anterior;
    }
}

void imagen::terminarCopia(){
    imagen::copiaInicio = NULL;
}

void imagen::filtroNegativoImg(){
    capa* aux = imagen::copiaInicio;

    while(aux!=NULL){
        cout<<"Capa: "<<aux->nombre<<endl;
        aux->matriz->filtroNegativo();
        cout<<"----------------------------------------------"<<endl;
        aux = aux->siguiente;
    }
}


