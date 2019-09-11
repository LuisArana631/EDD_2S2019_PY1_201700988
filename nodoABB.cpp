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

        archivo<<"node"<<arbol->nombre<<"[label = \"<f0> |<f1> "<<arbol->nombre<<"\\nimage, h: "<<arbol->listaCapas->imageHeight<<", w: "<<arbol->listaCapas->imageWidth<<"\\npixel, h: "<<arbol->listaCapas->pixelHeight<<", w: "<<arbol->listaCapas->pixelHeight<<"|<f2> \"];"<<endl;

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

void nodoABB::graficarInOrden(nodoABB* arbol){
    if(arbol!=NULL){
        nodoABB* inicio =  arbol;

        ofstream archivo;
        archivo.open("ABBInOrden.dot",ios::out);

        if(archivo.fail()){
            cout<<"No se puede abrir el archivo"<<endl;
            return;
        }

        archivo<<"digraph ArbolInOrden{"<<endl;
        archivo<<"rankdir = \"LR\""<<endl;
        archivo<<"node [shape=record, height=.1];"<<endl;
        archivo<<"InOrden";

        archivo.close();

        mostrarInOrden(arbol, inicio, 0);

        archivo.open("ABBInOrden.dot",ios::app);

        if(archivo.fail()){
            cout<<"No se puede abrir el archivo"<<endl;
            return;
        }

        archivo<<""<<endl;

        archivo<<"label = \"ABB recorrido InOrden\";"<<endl;
        archivo<<"}"<<endl;

        archivo.close();

        system("dot -Tpng ABBInOrden.dot -o ABBInOrden.png");
        system("ABBInOrden.png");

    }
}

void nodoABB::mostrarInOrden(nodoABB* arbol, nodoABB* inicio, int moves){
    if(arbol!=NULL){

        mostrarInOrden(arbol->izquierda,inicio, moves);

        ofstream archivo;
        archivo.open("ABBInOrden.dot",ios::app);

        if(archivo.fail()){
            cout<<"No se puede abrir el archivo"<<endl;
            return;
        }

        archivo<<" -> "<<arbol->nombre;



        archivo.close();

        mostrarInOrden(arbol->derecha,inicio, moves);


    }else{
        return;
    }
}

void nodoABB::graficarPreOrden(nodoABB* arbol){
    if(arbol!=NULL){
        nodoABB* inicio =  arbol;

        ofstream archivo;
        archivo.open("ABBPreOrden.dot",ios::out);

        if(archivo.fail()){
            cout<<"No se puede abrir el archivo"<<endl;
            return;
        }

        archivo<<"digraph ArbolPreOrden{"<<endl;
        archivo<<"rankdir = \"LR\""<<endl;
        archivo<<"node [shape=record, height=.1];"<<endl;

        archivo.close();

        mostrarPreOrden(arbol, inicio);

        archivo.open("ABBPreOrden.dot",ios::app);

        if(archivo.fail()){
            cout<<"No se puede abrir el archivo"<<endl;
            return;
        }

        archivo<<""<<endl;

        archivo<<"label = \"ABB recorrido PreOrden\";"<<endl;
        archivo<<"}"<<endl;

        archivo.close();

        system("dot -Tpng ABBPreOrden.dot -o ABBPreOrden.png");
        system("ABBPreOrden.png");

    }
}

void nodoABB::mostrarPreOrden(nodoABB* arbol, nodoABB* inicio){
    if(arbol!=NULL){

        ofstream archivo;
        archivo.open("ABBPreOrden.dot",ios::app);

        if(archivo.fail()){
            cout<<"No se puede abrir el archivo"<<endl;
            return;
        }

        if(arbol!=inicio){
            archivo<<" -> ";
        }

        archivo<<arbol->nombre;

        archivo.close();

        mostrarPreOrden(arbol->izquierda,inicio);
        mostrarPreOrden(arbol->derecha,inicio);


    }else{
        return;
    }
}

void nodoABB::graficarPostOrden(nodoABB* arbol){
    if(arbol!=NULL){
        nodoABB* inicio =  arbol;

        ofstream archivo;
        archivo.open("ABBPostOrden.dot",ios::out);

        if(archivo.fail()){
            cout<<"No se puede abrir el archivo"<<endl;
            return;
        }

        archivo<<"digraph ArbolPostOrden{"<<endl;
        archivo<<"rankdir = \"LR\""<<endl;
        archivo<<"node [shape=record, height=.1];"<<endl;

        archivo.close();

        mostrarPostOrden(arbol, inicio);

        archivo.open("ABBPostOrden.dot",ios::app);

        if(archivo.fail()){
            cout<<"No se puede abrir el archivo"<<endl;
            return;
        }

        archivo<<""<<endl;

        archivo<<"label = \"ABB recorrido PostOrden\";"<<endl;
        archivo<<"}"<<endl;

        archivo.close();

        system("dot -Tpng ABBPostOrden.dot -o ABBPostOrden.png");
        system("ABBPostOrden.png");

    }
}

void nodoABB::mostrarPostOrden(nodoABB* arbol, nodoABB* inicio){
    if(arbol!=NULL){

        mostrarPostOrden(arbol->izquierda,inicio);
        mostrarPostOrden(arbol->derecha,inicio);

        ofstream archivo;
        archivo.open("ABBPostOrden.dot",ios::app);

        if(archivo.fail()){
            cout<<"No se puede abrir el archivo"<<endl;
            return;
        }

        archivo<<arbol->nombre;

        if(arbol!=inicio){
            archivo<<" -> ";
        }

        archivo.close();

    }else{
        return;
    }
}

void nodoABB::mostrarListaArbol(nodoABB* arbol){
    if(arbol == NULL){
        return;
    }else{
        mostrarListaArbol(arbol->izquierda);
        cout<<" + "<<arbol->nombre<<endl;
        mostrarListaArbol(arbol->derecha);
    }
}

bool nodoABB::existeImagen(nodoABB* arbol, int valNombre){
    if(arbol == NULL){
        return false;
    }else if(arbol->valNombre == valNombre){
        cout<<"Imagen encontrada"<<endl;
        return true;
    }else if(valNombre < arbol->valNombre){
        return existeImagen(arbol->izquierda, valNombre);
    }else{
        return existeImagen(arbol->derecha, valNombre);
    }
}

nodoABB* nodoABB::extraerImagen(nodoABB* arbol, int valNombre){
    if(arbol == NULL){
        nodoABB* ret = NULL;
        return ret;
    }else if(arbol->valNombre == valNombre){
        cout<<"Imagen encontrada"<<endl;
        return arbol;
    }else if(valNombre < arbol->valNombre){
        return extraerImagen(arbol->izquierda, valNombre);
    }else{
        return extraerImagen(arbol->derecha, valNombre);
    }
}

