#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <ctype.h>

//Pruebas
#include "matrizDispersa.h"
#include "imagen.h"
#include "nodoABB.h"

using namespace std;

void menu();
bool validarEntrada(string);
void insertarImagen();
void menuReportes();
void traversalReport();
void selectImage();
void selectCapa();
void linearReport();
void exportImage();
void menuFiltros();
int aplicarFiltro();
int numCapa();
void mirrorMenu();

//Estructuras globales
nodoABB* arbolImagenes;
imagen* trabajo = NULL;
capa* capaTrabajar;
int Rx = 0;
int Ry = 0;

void menu(){
    string Opcion;
    bool entradaValida = false;

    while(!entradaValida){
        try{
            system("cls");
            cout<<"----------------------------------------------"<<endl;
            cout<<"-------------------PHOTGEN++------------------"<<endl;
            cout<<"----------------------------------------------"<<endl;
            cout<<"---------------------MENU---------------------"<<endl;
            cout<<"----------------------------------------------"<<endl;
            cout<<"1 - Insert image."<<endl;
            cout<<"2 - Select image."<<endl;
            cout<<"3 - Apply filters."<<endl;
            cout<<"4 - Manual editing."<<endl;
            cout<<"5 - Export image."<<endl;
            cout<<"6 - Reports."<<endl;
            cout<<"7 - Exit."<<endl;
            cout<<"----------------------------------------------"<<endl;
            cout<<"Option: ";
            getline(cin,Opcion);
            entradaValida = validarEntrada(Opcion);
            cout<<"----------------------------------------------"<<endl;
            if(!entradaValida)
                throw Opcion;
        }catch(string e){
            cout<<"---------------Opcion no existe---------------"<<endl;
            cout<<"----------------------------------------------"<<endl;
            Sleep(500);
        }
    }

    int OpcionEntera = atoi(Opcion.c_str());

    switch(OpcionEntera){
        case 1:
            //Insert image
            insertarImagen();
            menu();
            break;
        case 2:
            //Select image
            selectImage();
            menu();
            break;
        case 3:
            //Apply filters
            if(trabajo!=NULL){
                menuFiltros();
            }else{
                cout<<"No has seleccionado una imagen."<<endl;
                cout<<"----------------------------------------------"<<endl;
                cout<<"Pulsa una tecla para continuar."<<endl;
                getch();
            }
            menu();
            break;
        case 4:
            //Manual editing
            return;
            break;
        case  5:
            //Export image
            exportImage();
            menu();
            break;
        case 6:
            //Reports
            menuReportes();
            menu();
            break;
        case 7:
            //Exit
            exit(0);
            break;
        default:
            //Cuando es un numero incorrecto
            cout<<"---------------Opcion no existe---------------"<<endl;
            cout<<"----------------------------------------------"<<endl;
            Sleep(500);
            menu();
    }
}

bool validarOpcion(string Opcion){
    bool opcionValida =  true;
    for(int i=0; i<Opcion.length(); i++){
        if(!isalpha(Opcion[i])){
            if(Opcion[i] != 95){
                opcionValida = false;
            }
        }
    }
    return opcionValida;
}

bool validarEntrada(string Opcion){
    int i;
    int inicio = 0;

    if(Opcion.length() == 0)
        return false;

    if(Opcion[0] == '+' || Opcion[0] == '-'){
        inicio = 1;
        if(Opcion.length() == 1)
            return false;
    }

    for(i = inicio; i<Opcion.length(); i++){
        if(!isdigit(Opcion[i]))
            return false;
    }

    return true;
}

void insertarImagen(){
    ifstream archivo;
    string dir, texto, capas, config;

    system("cls");
    cout<<"----------------------------------------------"<<endl;
    cout<<"-------------------PHOTGEN++------------------"<<endl;
    cout<<"----------------------------------------------"<<endl;
    cout<<"-----------------INSERT IMAGE-----------------"<<endl;
    cout<<"----------------------------------------------"<<endl;
    cout<<"Direccion del archivo: ";
    getline(cin,dir);
    cout<<"----------------------------------------------"<<endl;

    //Cargando archivo inicial
    archivo.open(dir.c_str(),ios::in);

    if(archivo.fail()){
        cout<<"No se pudo abrir archivo inicial."<<endl;
        cout<<"----------------------------------------------"<<endl;
        cout<<"Pulsa una tecla para continuar."<<endl;
        getch();
        return;
    }else{
        cout<<"Cargando archivo inicial..."<<endl;
        cout<<"----------------------------------------------"<<endl;
    }

    //ExtraerNombreCarpeta
    int lenCarpeta = dir.length();
    char NombreCarpeta[lenCarpeta+1];
    strcpy(NombreCarpeta, dir.c_str());
    string nombreImagenes = "";
    for(int i=0; i<lenCarpeta;i++){
        if(NombreCarpeta[i] == 92 || NombreCarpeta[i] == 47){
            break;
        }else{
            nombreImagenes = nombreImagenes + NombreCarpeta[i];
        }
    }

    //Variables del archivo Inicial
    int lineas = 0;
    string dirCapa = "";
    string nameCapa = "";
    string numCapa = "";
    bool insertCapa = false;
    bool insertNum = true;

    //Extraer datos del archivo inicial
    while(!archivo.eof()){
        getline(archivo,texto);
        if(lineas != 0){
            int n = texto.length();
            char caracteres[n+2];
            strcpy(caracteres, texto.c_str());

            for(int i=0; i<n+1; i++){
                if(isdigit(caracteres[i])){
                    if(insertNum){
                        numCapa = numCapa + caracteres[i];
                    }else if(insertCapa){
                        nameCapa = nameCapa + caracteres[i];
                    }
                }else if(isalpha(caracteres[i]) || caracteres[i]  == 46 || caracteres[i]  == 95 || caracteres[i]  == 45){
                    nameCapa = nameCapa  + caracteres[i];
                }else if(caracteres[i] == 44 || caracteres[i] == 59 || caracteres[i] == 00){
                    if(insertNum){
                        insertCapa = true;
                        insertNum = false;
                    }else if(insertCapa){
                        if(numCapa == "0"){
                            config = nombreImagenes + "\\" + nameCapa;
                        }else{
                            capas = capas + numCapa + "," + nameCapa + ";";
                        }
                            numCapa = "";
                            nameCapa = "";
                            insertCapa = false;
                            insertNum = true;
                    }
                }else{
                    //Nada
                }
            }
        }
        lineas ++;
    }

    archivo.close();

    cout<<"Archivo inicial cargado con exito."<<endl;
    cout<<"----------------------------------------------"<<endl;



    //Extraer valores de config
    archivo.open(config.c_str(),ios::in);

    if(archivo.fail()){
        cout<<"No se pudo abrir archivo de configuracion."<<endl;
        cout<<"----------------------------------------------"<<endl;
        cout<<"Pulsa una tecla para continuar."<<endl;
        getch();
        return;
    }else{
        cout<<"Cargando configuracion de la imagen..."<<endl;
        cout<<"----------------------------------------------"<<endl;
    }

    int heightImagen = 0;
    int widthImagen = 0;
    int heightPixel = 0;
    int widthPixel = 0;

    lineas = 0;
    string Tconfig = "";
    string Tvalue = "";
    bool Bconfig = true;
    bool Bvalue = false;

    while(!archivo.eof()){
        getline(archivo,texto);
        if(lineas != 0){
            int n = texto.length();
            char caracteres[n+2];
            strcpy(caracteres, texto.c_str());

            for(int i=0; i<n+1; i++){
                if(isalpha(caracteres[i]) || caracteres[i] == 95){
                    caracteres[i] = tolower(caracteres[i]);
                    Tconfig = Tconfig + caracteres[i];
                }else if(isdigit(caracteres[i])){
                    Tvalue = Tvalue + caracteres[i];
                }else if(caracteres[i] == 44 || caracteres[i] == 59 || caracteres[i] == 00){
                    if(Bconfig){
                        Bvalue = true;
                        Bconfig = false;
                    }else if(Bvalue){
                        if(Tconfig == "image_width"){
                            widthImagen = atoi(Tvalue.c_str());
                        }else if(Tconfig == "image_height"){
                            heightImagen = atoi(Tvalue.c_str());
                        }else if(Tconfig == "pixel_width"){
                            widthPixel = atoi(Tvalue.c_str());
                        }else if(Tconfig == "pixel_height"){
                            heightPixel = atoi(Tvalue.c_str());
                        }
                        Tconfig = "";
                        Tvalue = "";
                        Bvalue = false;
                        Bconfig = true;
                    }
                }else{
                    //Nada
                }
            }
        }
        lineas++;
    }

    archivo.close();

    int valNombreImg = 0;
    int auxValNombre = 0;
    string  nombreImg = "";
    int r = dir.length();
    char nombreImgC[r+1];
    strcpy(nombreImgC, dir.c_str());

    for(int i=0; i<r; i++){
        if(nombreImgC[i]!=46){
            auxValNombre = nombreImgC[i];
        }else{
            break;
        }
    }
    imagen* nueva = new imagen(nombreImagenes,heightImagen, widthImagen, heightPixel, widthPixel);
    arbolImagenes->insertar(arbolImagenes, nombreImagenes, valNombreImg, nueva);


    cout<<"Width Image: "<<widthImagen<<endl;
    cout<<"Height Image: "<<heightImagen<<endl;
    cout<<"Width Pixel: "<<widthPixel<<endl;
    cout<<"Height Pixel: "<<heightPixel<<endl;
    cout<<"----------------------------------------------"<<endl;
    cout<<"Archivo configuracion cargado con exito."<<endl;
    cout<<"----------------------------------------------"<<endl;

    //Cargar las capas
    //Lectura de archivo
    int m = capas.length();
    char capasC[m+1];
    strcpy(capasC, capas.c_str());
    string direccionCapa = "";
    string tNumCapa = "";
    string nombreCapa = "";
    //Variables de Carga
    int z = 0;
    string tNum = "";
    int R = 0;
    int G = 0;
    int B = 0;
    //Variables de Recorrido
    int nCol = 1;
    int nFil = 1;
    bool BnumCapa = true;
    bool BdirCapa = false;
    bool BR = true;
    bool BG = false;
    bool BB = false;

    //Lectura de cada archivo
    for(int i=0; i<m; i++){
        if(isalpha(capasC[i]) || capasC[i]  == 46 || capasC[i]  == 95 || capasC[i]  == 45 || isdigit(capasC[i])){
            if(capasC[i]  == 46){
                nombreCapa = direccionCapa;
            }
            if(BnumCapa){
                tNumCapa = tNumCapa + capas[i];
            }else{
                direccionCapa = direccionCapa + capasC[i];
            }
        }else if(capasC[i] == 44){
            BnumCapa = false;
            BdirCapa =  true;
            z = atoi(tNumCapa.c_str());
        }else if(capasC[i] == 59){
            //Cargar matrizDispersa
            direccionCapa = nombreImagenes + "\\" + direccionCapa;
            archivo.open(direccionCapa.c_str(),ios::in);

            if(archivo.fail()){
                cout<<"No se pudo abrir "<<direccionCapa<<"."<<endl;
                cout<<"----------------------------------------------"<<endl;
                cout<<"Pulsa una tecla para continuar."<<endl;

                getch();
                return;
            }else{
                cout<<"Cargando la capa "<<direccionCapa<<"..."<<endl;
                cout<<"----------------------------------------------"<<endl;
            }

            matrizDispersa* newMatriz = new matrizDispersa();

            //Lectura de archivo
            while(!archivo.eof()){
                getline(archivo,texto);
                int n = texto.length();
                char car[n+1];
                strcpy(car, texto.c_str());

                for(int i=0; i<n+1; i++){
                    //Conteo de columnas
                    if(car[i] == 59 || car[i] == 44){
                        if(BB){
                            B = atoi(tNum.c_str());
                            tNum = "";
                            //Guardar nodo
                            newMatriz->insertar(nCol,nFil,R,G,B);
                            R = 0;
                            G = 0;
                            B = 0;
                            BB = false;
                            BR = true;
                        }
                        nCol++;
                    }
                    //Conteo de filas
                    if(car[i] == 00){
                        nCol++;
                        if(BB){
                            B = atoi(tNum.c_str());
                            tNum = "";
                            //Guardar nodo
                            newMatriz->insertar(nCol,nFil,R,G,B);
                            R = 0;
                            G = 0;
                            B = 0;
                            BB = false;
                            BR = true;
                        }
                        nFil++;
                        nCol = 1;
                    }

                    //Insercion de los nodos
                    //Concatenar
                    if(isdigit(car[i])){
                        tNum = tNum + car[i];
                    }

                    if(car[i] == 45){
                        if(BR){
                            R = atoi(tNum.c_str());
                            tNum = "";
                            BR = false;
                            BG = true;
                        }else if(BG){
                            G = atoi(tNum.c_str());
                            tNum = "";
                            BG = false;
                            BB = true;
                        }else if(BB){
                            B = atoi(tNum.c_str());
                            tNum = "";
                            //Guardar nodo
                            newMatriz->insertar(nCol,nFil,R,G,B);
                            R = 0;
                            G = 0;
                            B = 0;
                            BB = false;
                            BR = true;
                        }
                    }
                }

            }

            nueva->insertarCapa(newMatriz,z,nombreCapa);

            cout<<"----------------------------------------------"<<endl;
            cout<<direccionCapa<<" cargado con exito."<<endl;
            cout<<"----------------------------------------------"<<endl;

            archivo.close();

            direccionCapa = "";
            tNumCapa = "";
            BnumCapa = true;
            BdirCapa = false;
            nCol = 1;
            nFil = 1;
        }else{
            //Nada
        }
    }
    cout<<"Pulsa una tecla para continuar."<<endl;
    getch();
    //Fin de la inserción de las matrices
}

void menuReportes(){
    string Opcion;
    bool entradaValida = false;

    while(!entradaValida){
        try{
            system("cls");
            cout<<"----------------------------------------------"<<endl;
            cout<<"-------------------PHOTGEN++------------------"<<endl;
            cout<<"----------------------------------------------"<<endl;
            cout<<"--------------------REPORTS-------------------"<<endl;
            cout<<"----------------------------------------------"<<endl;
            cout<<"1 - Imported images report."<<endl;
            cout<<"2 - Image layer report."<<endl;
            cout<<"3 - Linear matrix report."<<endl;
            cout<<"4 - Traversal report."<<endl;
            cout<<"5 - Filters Report."<<endl;
            cout<<"6 - Return."<<endl;
            cout<<"----------------------------------------------"<<endl;
            cout<<"Option: ";
            getline(cin,Opcion);
            entradaValida = validarEntrada(Opcion);
            cout<<"----------------------------------------------"<<endl;
            if(!entradaValida)
                throw Opcion;
        }catch(string e){
            cout<<"---------------Opcion no existe---------------"<<endl;
            cout<<"----------------------------------------------"<<endl;
            Sleep(500);
        }
    }

    int OpcionEntera = atoi(Opcion.c_str());

    switch(OpcionEntera){
        case 1:
            //Imported images report
            arbolImagenes ->graficarArbol(arbolImagenes);
            menuReportes();
            break;
        case 2:
            //Image layer report
            if(trabajo==NULL){
                selectImage();
            }
            selectCapa();
            if(capaTrabajar!=NULL)
                capaTrabajar->matriz->graficarMatriz();
            menuReportes();
            break;
        case 3:
            //Linear matrix report
            selectImage();
            selectCapa();
            linearReport();
            menuReportes();
            break;
        case 4:
            //Traversal report
            traversalReport();
            menuReportes();
            break;
        case 5:
            //Filters report
            if(trabajo!=NULL){
                if(trabajo->listaFiltros->inicio!=NULL){
                    trabajo->listaFiltros->graficar();
                }else{
                    cout<<"No hay filtros aplicados"<<endl;
                    cout<<"----------------------------------------------"<<endl;
                    cout<<"Pulsa una tecla para continuar..."<<endl;
                    getch();
                }
            }else{
                cout<<"No has seleccionado imagen"<<endl;
                cout<<"----------------------------------------------"<<endl;
                        cout<<"Pulsa una tecla para continuar..."<<endl;
                        getch();
            }

            break;
        case 6:
            //Return
            return;
            break;
        default:
            //Cuando es un numero incorrecto
            cout<<"---------------Opcion no existe---------------"<<endl;
            cout<<"----------------------------------------------"<<endl;
            Sleep(500);
            menuReportes();
            break;
    }

}

void traversalReport(){
    string Opcion;
    bool entradaValida = false;

    while(!entradaValida){
        try{
            system("cls");
            cout<<"----------------------------------------------"<<endl;
            cout<<"-------------------PHOTGEN++------------------"<<endl;
            cout<<"----------------------------------------------"<<endl;
            cout<<"---------------TRAVERSAL REPORT---------------"<<endl;
            cout<<"----------------------------------------------"<<endl;
            cout<<"1 - Inorder traversal."<<endl;
            cout<<"2 - Postorder traversal."<<endl;
            cout<<"3 - Preorder traversal."<<endl;
            cout<<"4 - Return."<<endl;
            cout<<"----------------------------------------------"<<endl;
            cout<<"Option: ";
            getline(cin,Opcion);
            entradaValida = validarEntrada(Opcion);
            cout<<"----------------------------------------------"<<endl;
            if(!entradaValida)
                throw Opcion;
        }catch(string e){
            cout<<"---------------Opcion no existe---------------"<<endl;
            cout<<"----------------------------------------------"<<endl;
            Sleep(500);
        }
    }

        int OpcionEntera = atoi(Opcion.c_str());

        switch(OpcionEntera){
            case 1:
                //Inorden  traversal
                arbolImagenes->graficarInOrden(arbolImagenes);
                traversalReport();
                break;
            case 2:
                //Postorder traversal
                arbolImagenes->graficarPostOrden(arbolImagenes);
                traversalReport();
                break;
            case 3:
                //Preorder traversal
                arbolImagenes->graficarPreOrden(arbolImagenes);
                traversalReport();
                break;
            case 4:
                //Return
                return;
                break;
            default:
                //Cuando es un numero incorrecto
                cout<<"---------------Opcion no existe---------------"<<endl;
                cout<<"----------------------------------------------"<<endl;
                Sleep(500);
                traversalReport();
                break;
        }
}

void selectImage(){
    string Opcion = "";
    bool opcionValida = false;

    if(trabajo!=NULL){
        trabajo->terminarFiltros();
    }

    while(!opcionValida){
        try{
            system("cls");
            cout<<"----------------------------------------------"<<endl;
            cout<<"-------------------PHOTGEN++------------------"<<endl;
            cout<<"----------------------------------------------"<<endl;
            cout<<"-----------------SELECT IMAGE-----------------"<<endl;
            cout<<"----------------------------------------------"<<endl;
            if(arbolImagenes!=NULL){
                arbolImagenes->mostrarListaArbol(arbolImagenes);
                cout<<"----------------------------------------------"<<endl;
                cout<<"Ingresa el nombre de la imagen: ";
                getline(cin,Opcion);
                opcionValida = validarOpcion(Opcion);
                cout<<"----------------------------------------------"<<endl;
                if(!opcionValida)
                    throw Opcion;
            }else{
                cout<<"No hay imagenes cargadas aun, carga un archivo."<<endl;
                cout<<"----------------------------------------------"<<endl;
                cout<<"Pulsa una tecla para continuar."<<endl;
                getch();
                return;
            }
        }catch(string e){
            cout<<"---------------Opcion no existe---------------"<<endl;
            cout<<"----------------------------------------------"<<endl;
            Sleep(500);
        }
    }

    nodoABB* aux = arbolImagenes -> extraerImagen(arbolImagenes,Opcion);

    if(aux == NULL){
        cout<<"---------------Opcion no existe---------------"<<endl;
        cout<<"----------------------------------------------"<<endl;
        cout<<"Pulsa una tecla para continuar."<<endl;
        getch();
        return;
    }

    trabajo = aux->listaCapas;


    cout<<"----------------------------------------------"<<endl;
    cout<<"Pulsa una tecla para continuar."<<endl;
    Opcion = "";
    getch();
}

void selectCapa(){
    string Opcion;
    capaTrabajar = NULL;

    bool opcionValida = false;

    while(!opcionValida){
        try{
            system("cls");
            cout<<"----------------------------------------------"<<endl;
            cout<<"-------------------PHOTGEN++------------------"<<endl;
            cout<<"----------------------------------------------"<<endl;
            cout<<"------------------SELECT CAP------------------"<<endl;
            cout<<"----------------------------------------------"<<endl;
            if(trabajo!=NULL){
                trabajo->mostrarCapas();
                cout<<"----------------------------------------------"<<endl;
                cout<<"Selecciona la capa: ";
                getline(cin,Opcion);
                opcionValida = validarEntrada(Opcion);
                cout<<"----------------------------------------------"<<endl;
                if(!opcionValida)
                    throw Opcion;
            }else{
                cout<<"No existen capas."<<endl;
                cout<<"----------------------------------------------"<<endl;
                cout<<"Pulsa una tecla para continuar."<<endl;
                getch();
                return;
            }

        }catch(string e){
            cout<<"---------------Opcion no existe---------------"<<endl;
            cout<<"----------------------------------------------"<<endl;
            Sleep(500);
        }
    }

    int capaSelect = atoi(Opcion.c_str());

    if(trabajo->listaFiltros->inicio!=NULL){
        capaTrabajar = trabajo->listaFiltros->fin->extraerCapa(capaSelect);
    }else{
        capaTrabajar = trabajo->extraerCapa(capaSelect);
    }

    if(capaTrabajar==NULL){
        cout<<"---------------Opcion no existe---------------"<<endl;
        cout<<"----------------------------------------------"<<endl;
        cout<<"Pulsa una tecla para continuar."<<endl;
        getch();
        return;
    }

    cout<<"----------------------------------------------"<<endl;
    cout<<"Pulsa una tecla para continuar."<<endl;

    getch();

}

void linearReport(){
    string Opcion;
    bool entradaValida = false;

    while(!entradaValida){
        try{
            system("cls");
            cout<<"----------------------------------------------"<<endl;
            cout<<"-------------------PHOTGEN++------------------"<<endl;
            cout<<"----------------------------------------------"<<endl;
            cout<<"-----------------LINEAR REPORT----------------"<<endl;
            cout<<"----------------------------------------------"<<endl;
            cout<<"1 - Linearize by column."<<endl;
            cout<<"2 - Linearize by row."<<endl;
            cout<<"3 - Return."<<endl;
            cout<<"----------------------------------------------"<<endl;
            cout<<"Option: ";
            getline(cin,Opcion);
            entradaValida = validarEntrada(Opcion);
            cout<<"----------------------------------------------"<<endl;
            if(!entradaValida)
                throw Opcion;
        }catch(string e){
            cout<<"---------------Opcion no existe---------------"<<endl;
            cout<<"----------------------------------------------"<<endl;
            Sleep(500);
        }
    }

    int OpcionEntera = atoi(Opcion.c_str());

    switch(OpcionEntera){
            case 1:
                //Column
                if(capaTrabajar!=NULL){
                    capaTrabajar->matriz->linealizarColumnas();
                }else{
                    cout<<"No se encontro la capa."<<endl;
                    return;
                }
                linearReport();
                break;
            case 2:
                //Row
                if(capaTrabajar!=NULL){
                    capaTrabajar->matriz->linealizarFilas();
                }else{
                    cout<<"No se encontro la capa."<<endl;
                    return;
                }
                linearReport();
                break;
            case 3:
                //Return
                return;
                break;
            default:
                //Cuando es un numero incorrecto
                cout<<"---------------Opcion no existe---------------"<<endl;
                cout<<"----------------------------------------------"<<endl;
                Sleep(500);
                traversalReport();
                break;
        }
}

void exportImage(){
    if(trabajo!=NULL){
        string dirCarpeta = "C:\\Users\\luara\\Desktop\\Exports";
        mkdir(dirCarpeta.c_str());
        dirCarpeta = dirCarpeta + "\\" + trabajo->id;
        mkdir(dirCarpeta.c_str());

        trabajo->crearHTML(dirCarpeta);
        trabajo->crearCSSOriginal(dirCarpeta);

        dirCarpeta = dirCarpeta + "\\" + trabajo->id + ".html";
        dirCarpeta = "start \"\" \"" + dirCarpeta +"\"";
        cout<<"Dir: "<<dirCarpeta<<endl;
        system(dirCarpeta.c_str());
        cout<<"----------------------------------------------"<<endl;
        cout<<"Pulsa una tecla para continuar."<<endl;
        getch();
    }else{
        cout<<"No hay imagen seleccionada"<<endl;
        cout<<"----------------------------------------------"<<endl;
        cout<<"Pulsa una tecla para continuar."<<endl;
        getch();
    }
}

int main(){
    menu();
    return 0;
}

void menuFiltros(){
    string Opcion;
    bool entradaValida = false;

    while(!entradaValida){
        try{
            system("cls");
            cout<<"----------------------------------------------"<<endl;
            cout<<"-------------------PHOTGEN++------------------"<<endl;
            cout<<"----------------------------------------------"<<endl;
            cout<<"-----------------APPLY FILTERS----------------"<<endl;
            cout<<"----------------------------------------------"<<endl;
            cout<<"1 - Negative."<<endl;
            cout<<"2 - Grayscale."<<endl;
            cout<<"3 - Mirror."<<endl;
            cout<<"4 - Collage."<<endl;
            cout<<"5 - Mosaic."<<endl;
            cout<<"6 - Return."<<endl;
            cout<<"----------------------------------------------"<<endl;
            cout<<"Option: ";
            getline(cin,Opcion);
            entradaValida = validarEntrada(Opcion);
            cout<<"----------------------------------------------"<<endl;
            if(!entradaValida)
                throw Opcion;
        }catch(string e){
            cout<<"---------------Opcion no existe---------------"<<endl;
            cout<<"----------------------------------------------"<<endl;
            Sleep(500);
        }
    }

    int OpcionEntera = atoi(Opcion.c_str());
    int aplicacion = 0;
    int capa = 0;

    switch(OpcionEntera){
        case 1:
            //Negative
            aplicacion = aplicarFiltro();
            if(aplicacion == 1){
                trabajo->filtroNegativo();
            }else{
                capa = numCapa();
                trabajo->filtroNegativoCapa(capa);
            }
            cout<<"----------------------------------------------"<<endl;
            cout<<"---------------Filtro aplicado----------------"<<endl;
            cout<<"----------------------------------------------"<<endl;
            cout<<"Pulsa una tecla para continuar."<<endl;
            getch();
            break;
        case 2:
            //Grayscale
            aplicacion = aplicarFiltro();
            if(aplicacion == 1){
                trabajo->filtroGrises();
            }else{
                capa = numCapa();
                trabajo->filtroGrisesCapa(capa);
            }
            cout<<"----------------------------------------------"<<endl;
            cout<<"---------------Filtro aplicado----------------"<<endl;
            cout<<"----------------------------------------------"<<endl;
            cout<<"Pulsa una tecla para continuar."<<endl;
            getch();
            break;
        case 3:
            //Mirror
            if(trabajo!=NULL){
                mirrorMenu();
            }else{
                cout<<"No has cargado imagenes."<<endl;
                cout<<"----------------------------------------------"<<endl;
                cout<<"Pulsa una tecla para continuar."<<endl;
                getch();
            }
            break;
        case 4:
            //Collage
            if(trabajo!=NULL){
                trabajo->listaFiltros->insertar("Collage");
                cout<<"Filtro aplicado exitosamente."<<endl;
            }else{
                cout<<"No has cargado imagenes."<<endl;
            }
            cout<<"----------------------------------------------"<<endl;
            cout<<"Pulsa una tecla para continuar."<<endl;
            getch();
            break;
        case 5:
            //Mosaic
            if(trabajo!=NULL){
                trabajo->listaFiltros->insertar("Mosaic");
                cout<<"Filtro aplicado exitosamente."<<endl;
            }else{
                cout<<"No has cargado imagenes."<<endl;
            }
            cout<<"----------------------------------------------"<<endl;
            cout<<"Pulsa una tecla para continuar."<<endl;
            getch();
            break;
        case 6:
            //Return
            return;
            break;
        default:
            //Cuando es un numero incorrecto
            cout<<"---------------Opcion no existe---------------"<<endl;
            cout<<"----------------------------------------------"<<endl;
            Sleep(500);
            menuReportes();
            break;
    }
}

int aplicarFiltro(){
    string Opcion;
    bool entradaValida = false;

    while(!entradaValida){
        try{
            system("cls");
            cout<<"----------------------------------------------"<<endl;
            cout<<"-------------------PHOTGEN++------------------"<<endl;
            cout<<"----------------------------------------------"<<endl;
            cout<<"-----------------APPLY FILTERS----------------"<<endl;
            cout<<"----------------------------------------------"<<endl;
            cout<<"1 - Imagen completa."<<endl;
            cout<<"2 - Capa."<<endl;
            cout<<"----------------------------------------------"<<endl;
            cout<<"Option: ";
            getline(cin,Opcion);
            entradaValida = validarEntrada(Opcion);
            cout<<"----------------------------------------------"<<endl;
            if(!entradaValida)
                throw Opcion;
        }catch(string e){
            cout<<"---------------Opcion no existe---------------"<<endl;
            cout<<"----------------------------------------------"<<endl;
            Sleep(500);
        }
    }

    int OpcionEntera = atoi(Opcion.c_str());

    if(OpcionEntera < 1 || OpcionEntera > 2){
        return aplicarFiltro();
    }else{
        return OpcionEntera;
    }
}

int numCapa(){
    string Opcion;
    bool entradaValida = false;

    while(!entradaValida){
        try{
        cout<<"----------------------------------------------"<<endl;
        trabajo->mostrarCapas();
        cout<<"----------------------------------------------"<<endl;
        cout<<"Option: ";
            getline(cin,Opcion);
            entradaValida = validarEntrada(Opcion);
            cout<<"----------------------------------------------"<<endl;
            if(!entradaValida)
                throw Opcion;
        }catch(string e){
            cout<<"---------------Opcion no existe---------------"<<endl;
            cout<<"----------------------------------------------"<<endl;
            Sleep(500);
        }
    }

    int OpcionEntera = atoi(Opcion.c_str());

    return OpcionEntera;
}

void mirrorMenu(){
    string Opcion;
    bool valido = false;

    while(valido!=true){
        try{
            cout<<"----------------------------------------------"<<endl;
            cout<<"1 - X-Mirror"<<endl;
            cout<<"2 - Y-Mirror"<<endl;
            cout<<"3 - Double Mirror"<<endl;
            cout<<"4 - Return"<<endl;
            cout<<"----------------------------------------------"<<endl;
            cout<<"Opcion: ";
            getline(cin,Opcion);
            valido = validarEntrada(Opcion);
            cout<<"----------------------------------------------"<<endl;
            if(!valido)
                throw Opcion;
        }catch (string e){
            cout<<"---------------Opcion no existe---------------"<<endl;
            cout<<"----------------------------------------------"<<endl;
            Sleep(500);
        }
    }

    int OpcionEntera = atoi(Opcion.c_str());
    switch(OpcionEntera){
        case 1:
            //X mirror
            trabajo->filtroXmirror();
            cout<<"----------------------------------------------"<<endl;
            cout<<"---------------Filtro aplicado----------------"<<endl;
            cout<<"----------------------------------------------"<<endl;
            cout<<"Pulsa una tecla para continuar."<<endl;
            getch();
            break;
        case 2:
            //Y mirror
            trabajo->filtroYmirror();
            cout<<"----------------------------------------------"<<endl;
            cout<<"---------------Filtro aplicado----------------"<<endl;
            cout<<"----------------------------------------------"<<endl;
            cout<<"Pulsa una tecla para continuar."<<endl;
            getch();
            break;
        case 3:
            //Double mirror
            trabajo->filtroXYmirror();
            cout<<"----------------------------------------------"<<endl;
            cout<<"---------------Filtro aplicado----------------"<<endl;
            cout<<"----------------------------------------------"<<endl;
            cout<<"Pulsa una tecla para continuar."<<endl;
            getch();
            break;
        case 4:
            //Return
            return;
            break;
        default:
            //Cuando es un numero incorrecto
            cout<<"---------------Opcion no existe---------------"<<endl;
            cout<<"----------------------------------------------"<<endl;
            Sleep(500);
            break;

    }

}




