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
            return;
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

        archivo<<"label = \"Matriz Dispersa\";"<<endl;
        archivo<<"}"<<endl;

        archivo.close();
        system("dot -Tpng MatrizDispersa.dot -o MatrizDispersa.png");
        system("MatrizDispersa.png");
    }else{
        cout<<"Capa se encuentra vacía"<<endl;
    }
}

void matrizDispersa::linealizarColumnas(){
    if(matrizDispersa::indiceX  != NULL){
        ofstream archivo;
        archivo.open("LinealizacionColumna.dot", ios::out);

        if(archivo.fail()){
            cout<<"No se puede abrir el archivo"<<endl;
            return;
        }

        archivo<<"digraph LinealizacionColumna{"<<endl;
        archivo<<"rankdir=LR;"<<endl;
        archivo<<"node [shape=record];"<<endl;

        nodoCabecera* aux = matrizDispersa::indiceX->inicio;

        archivo<<"nodoInicio[label=\"Inicio\"];"<<endl;
        archivo<<"nodoInicio -> nodo"<<aux->col->inicio->x<<aux->col->inicio->y<<";"<<endl;

        while(aux!=NULL){
            nodo* temp = aux->col->inicio;
            while(temp!=NULL){
                archivo<<"nodo"<<temp->x<<temp->y<<"[label=\"("<<temp->x<<","<<temp->y<<")"<<temp->R<<"-"<<temp->G<<"-"<<temp->B<<"\"];"<<endl;
                if(temp->abajo != NULL){
                    archivo<<"nodo"<<temp->x<<temp->y<<" -> nodo"<<temp->abajo->x<<temp->abajo->y<<";"<<endl;
                }

                temp = temp -> abajo;
            }
            if(aux->siguiente != NULL)
                archivo<<"nodo"<<aux->col->fin->x<<aux->col->fin->y<<" -> nodo"<<aux->siguiente->col->inicio->x<<aux->siguiente->col->inicio->y<<";"<<endl;

            aux = aux -> siguiente;
        }

        archivo<<"label = \"Linealizacion por Columnas\";"<<endl;
        archivo<<"}"<<endl;

        archivo.close();

        system("dot -Tpng LinealizacionColumna.dot -o LinealizacionColumna.png");
        system("LinealizacionColumna.png");
    }else{
        cout<<"Capa se encuentra vacía"<<endl;
    }
}

void matrizDispersa::linealizarFilas(){
    if(matrizDispersa::indiceX  != NULL){
        ofstream archivo;
        archivo.open("LinealizacionFila.dot", ios::out);

        if(archivo.fail()){
            cout<<"No se puede abrir el archivo"<<endl;
            return;
        }

        archivo<<"digraph LinealizacionFila{"<<endl;
        archivo<<"rankdir=LR;"<<endl;
        archivo<<"node [shape=record];"<<endl;

        nodoLateral* aux = matrizDispersa::indiceY->inicio;

        archivo<<"nodoInicio[label=\"Inicio\"];"<<endl;
        archivo<<"nodoInicio -> nodo"<<aux->fil->inicio->x<<aux->fil->inicio->y<<";"<<endl;

        while(aux!=NULL){
            nodo* temp = aux->fil->inicio;
            while(temp!=NULL){
                archivo<<"nodo"<<temp->x<<temp->y<<"[label=\"("<<temp->x<<","<<temp->y<<")"<<temp->R<<"-"<<temp->G<<"-"<<temp->B<<"\"];"<<endl;
                if(temp->derecha != NULL){
                    archivo<<"nodo"<<temp->x<<temp->y<<" -> nodo"<<temp->derecha->x<<temp->derecha->y<<";"<<endl;
                }

                temp = temp -> derecha;
            }
            if(aux->abajo != NULL)
                archivo<<"nodo"<<aux->fil->fin->x<<aux->fil->fin->y<<" -> nodo"<<aux->abajo->fil->inicio->x<<aux->abajo->fil->inicio->y<<";"<<endl;

            aux = aux -> abajo;
        }

        archivo<<"label = \"Linealizacion por Filas\";"<<endl;
        archivo<<"}"<<endl;

        archivo.close();

        system("dot -Tpng LinealizacionFila.dot -o LinealizacionFila.png");
        system("LinealizacionFila.png");

    }else{
        cout<<"Capa se encuentra vacía"<<endl;
    }
}

void matrizDispersa::pintarCuadro(string dir, int maxX){
    ofstream archivo;
    archivo.open(dir.c_str(), ios::app);

    if(archivo.fail()){
        cout<<"No se puede crear css"<<endl;
        return;
    }

    // Pintar
    nodoLateral* auxIndice = matrizDispersa::indiceY->inicio;

    int linealizacion = 0;
    while(auxIndice!=NULL){
        nodo* aux = auxIndice->fil->inicio;
        while(aux!=NULL){
            linealizacion = (aux->y-1)*(maxX)+aux->x;
            cout<<"Linealizacion de: x: "<<aux->x<<", y: "<<aux->y<<" es "<<linealizacion<<endl;
            archivo<<".pixel:nth-child("<<linealizacion<<"){background: rgb("<<aux->R<<", "<<aux->G<<", "<<aux->B<<");}"<<endl;
            aux = aux -> derecha;
        }
        auxIndice = auxIndice ->abajo;
    }

    archivo.close();

}

void matrizDispersa::filtroNegativo(){
    nodoLateral* auxLateral = matrizDispersa::indiceY->inicio;
    while(auxLateral!=NULL){
        nodo* aux = auxLateral->fil->inicio;
        while(aux!=NULL){
            cout<<"Antiguo valor, R: "<<aux->R<<", G: "<<aux->G<<", B: "<<aux->B<<endl;
            aux->R = 255 - aux->R;
            aux->G = 255 - aux->G;
            aux->B = 255 - aux->B;
            cout<<"Nuevo valor, R: "<<aux->R<<", G: "<<aux->G<<", B: "<<aux->B<<endl;

            aux = aux ->derecha;
        }
        auxLateral = auxLateral->abajo;
    }

    nodoCabecera* auxCabecera = matrizDispersa::indiceX->inicio;
    while(auxCabecera!=NULL){
        nodo* aux = auxCabecera->col->inicio;
        while(aux!=NULL){
            aux->R = 255 - aux->R;
            aux->G = 255 - aux->G;
            aux->B = 255 - aux->B;

            aux = aux ->abajo;
        }

        auxCabecera = auxCabecera->siguiente;
    }

}
