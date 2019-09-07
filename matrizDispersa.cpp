#include "matrizDispersa.h"

using namespace std;

matrizDispersa::matrizDispersa(){
    matrizDispersa::indiceX = new cabecera();
    matrizDispersa::indiceY = new lateral();
}

void matrizDispersa::insertar(int x, int y, int R, int G, int B){
    nodo* guardar;
    guardar = new nodo(x,y,R,G,B);

    if(matrizDispersa::indiceX->existeCabecera(x) == false){
        matrizDispersa::indiceX->insertar(new nodoCabecera(x));
    }

    if(matrizDispersa::indiceY->existeLateral(y) == false){
        matrizDispersa::indiceY->insertar(new nodoLateral(y));
    }

    nodoCabecera* tempC;
    nodoLateral* tempL;

    tempC = matrizDispersa::indiceX->buscar(x);
    tempL = matrizDispersa::indiceY->buscar(y);

    tempC->col->insertar(guardar);
    tempL->fil->insertar(guardar);

    cout<<"Nodo insertardo: R:"<<guardar->R<<" G:"<<guardar->G<<" B:"<<guardar->B<<", en "<<guardar->x<<", "<<guardar->y<<endl;
}

void matrizDispersa::graficarMatriz(){
    if(matrizDispersa::indiceX!=NULL){
        ofstream archivo;
        archivo.open("MatrizDispersa.dot", ios::out);

        if(archivo.fail()){
            cout<<"No se puede abrir el archivo"<<endl;
        }

        //Genrar el archivo .dot con la matriz

        archivo<<"digraph MatrizDispersa{"<<endl;
        archivo<<"node [shape=record];"<<endl;
        archivo<<"nodoInicio[label=\"Inicio\" group=Inicio];"<<endl;

        archivo.close();

        //Pintar Indice superior
        matrizDispersa::indiceX->pintarCabecera();
        matrizDispersa::indiceY->pintarLateral();
        matrizDispersa::indiceY->pintarFilas();
        matrizDispersa::indiceX->pintarColumnas();
        //Fin del codigo para genera matriz

        archivo.open("MatrizDispersa.dot", ios::app);

        if(archivo.fail()){
            cout<<"No se puede abrir el archivo"<<endl;
        }

        archivo<<"}"<<endl;

        archivo.close();
        system("dot -Tpng MatrizDispersa.dot -o MatrizDispersa.png");
        system("MatrizDispersa.png");
    }
}
