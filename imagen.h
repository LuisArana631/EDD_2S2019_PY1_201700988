#ifndef IMAGEN_H
#define IMAGEN_H

#include <iostream>
#include <fstream>
#include <direct.h>
#include <stdlib.h>
#include <string.h>
#include "capa.h"
#include "filtro.h"

using namespace std;

class imagen{
public:
    string id;
    int imageHeight;
    int imageWidth;
    int pixelHeight;
    int pixelWidth;
    filtro* listaFiltros;
    capa* inicio;
    capa* fin;

    imagen(string, int, int, int, int);
    bool vacia();
    void insertarCapa(matrizDispersa*, int, string);
    int valorMaximo();
    void mostrarCapas();
    capa* extraerCapa(int);
    void crearHTML(string);
    void crearCSSOriginal(string);
    void terminarFiltros();
    void filtroNegativo();
    void filtroGrises();
    void filtroNegativoCapa(int);
    void filtroGrisesCapa(int);
};

#endif // IMAGEN_H
