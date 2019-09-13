#ifndef NODOABB_H
#define NODOABB_H

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "imagen.h"

using namespace std;

class nodoABB{
public:
    string nombre;
    int valNombre;
    nodoABB* derecha = NULL;
    nodoABB* izquierda = NULL;
    imagen* listaCapas;

    nodoABB* crearImagen(string, imagen*&, int);
    void insertar(nodoABB*&, string, int, imagen*&);
    void graficarArbol(nodoABB*);
    void mostrarArbol(nodoABB*);
    void graficarInOrden(nodoABB*);
    void mostrarInOrden(nodoABB*, nodoABB*, int);
    void graficarPreOrden(nodoABB*);
    void mostrarPreOrden(nodoABB*, nodoABB*);
    void graficarPostOrden(nodoABB*);
    void mostrarPostOrden(nodoABB*, nodoABB*);
    void mostrarListaArbol(nodoABB*);
    bool existeImagen(nodoABB*, int);
    nodoABB* extraerImagen(nodoABB*, string);
};

#endif // NODOABB_H
