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
    nodoABB* extraerImagen(nodoABB*, int);
    void graficarInOrden(nodoABB*);
    void graficarPreOrden(nodoABB*);
    void graficarPostOrden(nodoABB*);
    void mostrarArbol(nodoABB*);
};

#endif // NODOABB_H
