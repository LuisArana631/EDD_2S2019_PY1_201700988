#include <iostream>
#include <stdlib.h>
#include <string.h>
//Pruebas
#include "matrizDispersa.h"
#include "imagen.h"
#include "nodoABB.h"
using namespace std;

void menu();
bool validarEntrada(string);
void insertarImagen();
void cargarImagen(string dir);

matrizDispersa* mat =  new matrizDispersa();
matrizDispersa* mat2 =  new matrizDispersa();
matrizDispersa* mat3 = new matrizDispersa();
imagen* img = new imagen("LetraR");
imagen* img2 = new imagen("Cuadro");
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
            cout<<"La opcion "<<e<<" no es valida."<<endl;
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
            mat->insertar(2,7,102,255,102);
            mat->insertar(3,7,102,255,102);
            mat->insertar(2,9,102,255,102);
            mat->insertar(3,10,102,255,102);
            mat->insertar(4,11,102,255,102);

            mat->graficarMatriz();
            mat->linealizarColumnas();
            mat->linealizarFilas();

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

            mat2->graficarMatriz();

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
            arbol->insertar(arbol,"Cuadro",1,img2);

            arbol->graficarArbol(arbol);

            arbol->listaCapas->mostrarCapas();
            cout<<"-------------------------------"<<endl;
            arbol->listaCapas->inicio->matriz->graficarMatriz();

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
    string dir;

    system("cls");
    cout<<"----------------------------------------------"<<endl;
    cout<<"-------------------PHOTGEN++------------------"<<endl;
    cout<<"----------------------------------------------"<<endl;
    cout<<"-----------------INSERT IMAGE-----------------"<<endl;
    cout<<"----------------------------------------------"<<endl;
    cout<<"Direccion del archivo: ";
    getline(cin,dir);
}

int main()
{
    menu();
    return 0;
}




