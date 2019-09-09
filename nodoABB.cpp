#include "nodoABB.h"

using namespace std;

nodoABB* nodoABB::crearImagen(string nombre, imagen*& listaCapas, int valNombre){
    nodoABB *nueva = new nodoABB();

    nueva->nombre = nombre;
    nueva->listaCapas = listaCapas;
    nueva->valNombre = valNombre;
    nueva->derecha = NULL;
    nueva->izquierda = NULL;

    return nueva;
}

void nodoABB::insertar(nodoABB*& arbol, string nombre, int valNombre, imagen*& pixelArt){
    if(arbol == NULL){
        nodoABB* nueva = crearImagen(nombre, pixelArt, valNombre);
        arbol = nueva;
    }else{
        int valRaiz = arbol->valNombre;

        if(valNombre < valRaiz){
            insertar(arbol->izquierda, nombre, valNombre, pixelArt);
        }else if(valNombre > valRaiz){
            insertar(arbol->derecha, nombre, valNombre, pixelArt);
        }else{
            cout<<"Ya existe una imagen con el nombre "<<valNombre<<"."<<endl;
        }
    }
}

void nodoABB::graficarArbol(nodoABB* arbol){
    if(arbol==NULL){
        cout<<"Arbol vacío."<<endl;
    }else{
        ofstream archivo;
        archivo.open("ABBImagenes.dot",ios::out);

        if(archivo.fail()){
            cout<<"No se puede abrir el archivo"<<endl;
            return;
        }

        archivo<<"digraph ArbolImagen{"<<endl;
        archivo<<"node [shape=record, height=.1];"<<endl;

        archivo.close();

        mostrarArbol(arbol);

        archivo.open("ABBImagenes.dot",ios::app);

        if(archivo.fail()){
            cout<<"No se puede abrir el archivo"<<endl;
            return;
        }

        archivo<<"label = \"ABB de Imagenes\";"<<endl;
        archivo<<"}"<<endl;

        archivo.close();

        system("dot -Tpng ABBImagenes.dot -o ABBImagenes.png");
        system("ABBImagenes.png");
    }
}

void nodoABB::mostrarArbol(nodoABB* arbol){
    if(arbol!=NULL){
        ofstream archivo;
        archivo.open("ABBImagenes.dot",ios::app);

        if(archivo.fail()){
            cout<<"No se puede abrir el archivo"<<endl;
            return;
        }

        archivo<<"node"<<arbol->nombre<<"[label = \"<f0> |<f1> "<<arbol->nombre<<"|<f2> \"];"<<endl;

        if(arbol->izquierda!=NULL){
            archivo<<"\"node"<<arbol->nombre<<"\":f0 -> \"node"<<arbol->izquierda->nombre<<"\":f1;"<<endl;
        }

        if(arbol->derecha!=NULL){
            archivo<<"\"node"<<arbol->nombre<<"\":f2 -> \"node"<<arbol->derecha->nombre<<"\":f1;"<<endl;
        }

        archivo.close();

        mostrarArbol(arbol->izquierda);
        mostrarArbol(arbol->derecha);
    }
}


