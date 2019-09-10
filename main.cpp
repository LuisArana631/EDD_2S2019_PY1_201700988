#include <iostream>
#include <stdlib.h>
#include <string.h>
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
void cargarImagen(string dir);

nodoABB* arbolImagenes;

matrizDispersa* mat =  new matrizDispersa();
matrizDispersa* mat2 =  new matrizDispersa();
matrizDispersa* mat3 = new matrizDispersa();
imagen* img = new imagen("R",30,30,5,5);
imagen* img2 = new imagen("Cuadro",30,30,5,5);
nodoABB* arbol;

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
            break;
        case 2:
            //Select image
            mat->insertar(2,7,102,255,102);
            mat->insertar(3,7,102,255,102);
            mat->insertar(2,9,102,255,102);
            mat->insertar(3,10,102,255,102);
            mat->insertar(4,11,102,255,102);

            //mat->graficarMatriz();
            //mat->linealizarColumnas();
            //mat->linealizarFilas();

            cout<<"-------------------------------"<<endl;

            mat2->insertar(1,2,102,255,102);
            mat2->insertar(1,3,102,255,102);
            mat2->insertar(1,4,102,255,102);
            mat2->insertar(1,5,102,255,102);
            mat2->insertar(1,6,102,255,102);
            mat2->insertar(1,7,102,255,102);
            mat2->insertar(1,8,102,255,102);
            mat2->insertar(1,9,102,255,102);
            mat2->insertar(1,10,102,255,102);
            mat2->insertar(1,11,102,255,102);
            mat2->insertar(2,2,102,255,102);
            mat2->insertar(3,2,102,255,102);
            mat2->insertar(4,3,102,255,102);
            mat2->insertar(4,4,102,255,102);
            mat2->insertar(4,5,102,255,102);
            mat2->insertar(4,6,102,255,102);

            //mat2->graficarMatriz();

            cout<<"-------------------------------"<<endl;

            mat3->insertar(1,1,102,255,102);
            mat3->insertar(1,2,102,255,102);
            mat3->insertar(1,3,102,255,102);
            mat3->insertar(2,1,102,255,102);
            mat3->insertar(2,2,102,255,102);
            mat3->insertar(2,3,102,255,102);
            mat3->insertar(3,1,102,255,102);
            mat3->insertar(3,2,102,255,102);
            mat3->insertar(3,3,102,255,102);

            cout<<"-------------------------------"<<endl;

            img->insertarCapa(mat, 1);
            img->insertarCapa(mat2, 2);
            img2->insertarCapa(mat3, 1);

            arbol->insertar(arbol,"R",5,img);
            arbol->insertar(arbol,"Cuadro",3,img2);
            arbol->insertar(arbol,"Bebesita",1,img);

            arbol->graficarArbol(arbol);

            arbol->listaCapas->mostrarCapas();
            //arbol->listaCapas->inicio->matriz->graficarMatriz();
            cout<<"-------------------------------"<<endl;
            arbol->graficarInOrden(arbol);
            //arbol->graficarPreOrden(arbol);
            //arbol->graficarPostOrden(arbol);
            break;
        case 3:
            //Apply filters

            break;
        case 4:
            //Manual editing

            break;
        case  5:
            //Export image

            break;
        case 6:
            //Reports

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
        Sleep(700);
        return;
    }else{
        cout<<"Cargando archivo inicial..."<<endl;
        cout<<"----------------------------------------------"<<endl;
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
                            config = nameCapa;
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
        Sleep(700);
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
    int auxValImg = 0;
    string  nombreImg = "";
    int r = dir.length();
    char nombreImgC[r+1];
    strcpy(nombreImgC, dir.c_str());

    for(int i=0; i<r; i++){
        if(nombreImgC[i]!=46){
            nombreImg = nombreImg + nombreImgC[i];
            auxValImg = nombreImgC[i];
            valNombreImg = valNombreImg + auxValImg;
        }else{
            break;
        }
    }

    imagen* nueva = new imagen(nombreImg,heightImagen, widthImagen, heightPixel, widthPixel);
    arbolImagenes->insertar(arbolImagenes, nombreImg, valNombreImg, nueva);

    cout<<"Width Image: "<<widthImagen<<endl;
    cout<<"Height Image: "<<heightImagen<<endl;
    cout<<"Width Pixel: "<<widthPixel<<endl;
    cout<<"Height Pixel: "<<heightPixel<<endl;
    cout<<"----------------------------------------------"<<endl;
    cout<<"Archivo configuracion cargado con exito."<<endl;
    cout<<"----------------------------------------------"<<endl;

    cout<<"Texto capas: "<<capas<<endl;

    //Cargar las capas
    int m = capas.length();
    char capasC[m+1];
    strcpy(capasC, capas.c_str());
    string direccionCapa = "";
    int x = 0;
    int y = 0;
    int z = 0;
    int R = 0;
    int G = 0;
    int B = 0;
    bool BnumCapa = true;
    bool BdirCapa = false;

    for(int i=0; i<m; i++){
        if(isalpha(capasC[i]) || capasC[i]  == 46 || capasC[i]  == 95 || capasC[i]  == 45 || isdigit(capasC[i])){
            direccionCapa = direccionCapa + capasC[i];
        }else if(capasC[i] == 44){
            if(BnumCapa)
        }else if(capasC[i] == 59){

        }else{
            //Nada
        }
    }

}

int main()
{
    menu();
    return 0;
}




