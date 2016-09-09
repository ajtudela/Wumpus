/*
    CAgente.hpp - Wumpus Agent Class
    Created by Alberto Tudela, June 23 2011
    Under license GPLv3
*/

#ifndef _AGENTE_
#define _AGENTE_

#include "CTablero.hpp"
#include "Tipos.h"

#include <iostream>

using namespace std;

class CAgente{

private:


    TPosicion pos_anterior, pos_actual;
public:

	CAgente();
	~CAgente();
	void Percepcion();
	void Mover(TPosicion posicion);
    void Analizar();
    void Inferir();
    void Agarrar();
    void Matar();
    void Volver_Casa();
    void Reiniciar();
    void Avanzar();

    CTablero tablero;
	int rendimiento;
	int sensaciones[3];     // Sensaciones[Brisa,Hedor,Resplandor]
	char c_anterior, c_actual;

};


CAgente::CAgente(){
    rendimiento=0;               //Inicializa el rendimiento y la base de conocimientos
    c_anterior=c_actual=0;
    for(int i=0; i<=7; i++){
        sensaciones[i]=0;
    }
    pos_actual.x=0; pos_actual.y=7; //Posiciona el agente "abajo del todo"
    tablero.tablero_real[pos_actual.x][pos_actual.y]='A';
}

void CAgente::Percepcion(){  //Almacena en la base de conocimientos lo que percibe el agente
    if(c_actual=='B' || c_actual=='H'){
        sensaciones[0]=1;
    }else if (c_actual=='M' || c_actual=='W'){
        sensaciones[1]=1;
    }else if (c_actual=='R'){
        sensaciones[2]=1;
    }else{
        sensaciones[0]=sensaciones[1]=sensaciones[2]=0;
    }
}

void CAgente::Mover(TPosicion pos_siguiente){        //Mueve el agente a una posicion determinada

    tablero.tablero_real[pos_actual.x][pos_actual.y]=0;
    pos_anterior=pos_actual;  c_anterior=c_actual;
    pos_actual=pos_siguiente; c_actual=tablero.tablero_real[pos_siguiente.x][pos_siguiente.y];

    //Aqui ya me he movido
    Percepcion(); Analizar(); Inferir();
    tablero.Marcar(tablero.tablero_real, pos_actual,'A');
    tablero.Marcar(tablero.tablero_real, pos_anterior,c_anterior);
}

void CAgente::Analizar(){        //Analiza si las casillas adyacentes son seguras

    if(sensaciones[0]==1){      //Si hay Brisa, marca las adyacentes creyendo que hay hoyo
        tablero.Marcar(tablero.tablero_conocido, pos_actual,'S');
        tablero.Marcar_Adyacentes(tablero.tablero_supuesto, pos_actual,'H');

    }else if(sensaciones[2]==1){ //Si hay Oro
        Agarrar();

    }else if(sensaciones[1]==1){ //Si hay un hedor
        tablero.Marcar_Adyacentes(tablero.tablero_supuesto, pos_actual,'W');
        tablero.Marcar(tablero.tablero_supuesto, pos_actual,'W');
    }else{      //Si no hay Brisa, hedor u resplandor
        tablero.Marcar(tablero.tablero_conocido, pos_actual,'S');
        tablero.Marcar_Adyacentes(tablero.tablero_conocido, pos_actual,'S');
    }
}

void CAgente::Inferir(){  //Superpone el conocido con el supuesto (prevalece seguro)
int contador=0;           //Si hay mas de un hoyo, no inferimos nada
TPosicion pos_peligro[4];
pos_peligro[0]=pos_peligro[1]=pos_peligro[2]=pos_peligro[3]={0,0};

    //Marca las casillas que son seguras en el supuesto
    for(int j=0; j<=7;j++){
		for(int i=0; i<=7;i++){
		    if((tablero.tablero_supuesto[i][j]=='H' || tablero.tablero_supuesto[i][j]=='W') && tablero.tablero_conocido[i][j]=='S'){
                tablero.Marcar(tablero.tablero_supuesto, {i,j}, 0);
		    }
		}
    }
    //Cuenta si hay mas de un peligro
    for(int j=0; j<=7;j++){
		for(int i=0; i<=7;i++){
		    if(tablero.tablero_supuesto[i][j]=='H' || tablero.tablero_supuesto[i][j]=='W'){
                contador++; pos_peligro[0]={i,j};
		    }
		}
    }

    //Si hay mas de un peligro, marcamos peligro en conocido
    //Si hay solo uno, marcamos lo que es en conocido
    if(contador==1){
        tablero.tablero_conocido[pos_peligro[0].x][pos_peligro[0].y]=tablero.tablero_supuesto[pos_peligro[0].x][pos_peligro[0].y];
    }else{
        for(int j=0; j<=7;j++){
            for(int i=0; i<=7;i++){
                if(tablero.tablero_supuesto[i][j]=='H' || tablero.tablero_supuesto[i][j]=='W'){
                    tablero.tablero_conocido[i][j]='P';
                }
            }
        }
    }
    tablero.Borrar(tablero.tablero_supuesto);

    if(tablero.Adyacentes(tablero.tablero_conocido, pos_actual, 'W')){
        Matar();
    }
}

void CAgente::Avanzar(){
TPosicion pos_siguiente;
int num_ale1,num_ale2;
num_ale1=-1+rand()%(2+1); num_ale2=-1+rand()%(2+1);
tablero.Marcar(tablero.tablero_visitado, pos_actual,'V');




    if(pos_actual.x==0 && pos_actual.y==0 && tablero.tablero_visitado[pos_actual.x+1][pos_actual.y]=='X' &&
       tablero.tablero_visitado[pos_actual.x][pos_actual.y+1]=='X'){
        Volver_Casa();
    }else if(pos_actual.x==7 && pos_actual.y==7 && tablero.tablero_visitado[pos_actual.x-1][pos_actual.y]=='X' &&
       tablero.tablero_visitado[pos_actual.x][pos_actual.y-1]=='X'){
        Volver_Casa();
    }else if(pos_actual.x==0 && pos_actual.y==7 && tablero.tablero_visitado[pos_actual.x+1][pos_actual.y]=='X' &&
       tablero.tablero_visitado[pos_actual.x][pos_actual.y-1]=='X'){
        Volver_Casa();
    }else if(pos_actual.x==7 && pos_actual.y==0 && tablero.tablero_visitado[pos_actual.x-1][pos_actual.y]=='X' &&
       tablero.tablero_visitado[pos_actual.x][pos_actual.y+1]=='X'){
        Volver_Casa();
    }else if(tablero.tablero_visitado[pos_actual.x+1][pos_actual.y]=='X' &&
             tablero.tablero_visitado[pos_actual.x][pos_actual.y-1]=='X' &&
             tablero.tablero_visitado[pos_actual.x-1][pos_actual.y]=='X' &&
             tablero.tablero_visitado[pos_actual.x][pos_actual.y+1]=='X'){
        Volver_Casa();
    }else if(pos_actual.x==0 && tablero.tablero_visitado[pos_actual.x+1][pos_actual.y]=='X' &&
             tablero.tablero_visitado[pos_actual.x][pos_actual.y-1]=='X' &&
             tablero.tablero_visitado[pos_actual.x][pos_actual.y+1]=='X'){
        Volver_Casa();
    }else if(pos_actual.x==7 && tablero.tablero_visitado[pos_actual.x-1][pos_actual.y]=='X' &&
             tablero.tablero_visitado[pos_actual.x][pos_actual.y-1]=='X' &&
             tablero.tablero_visitado[pos_actual.x][pos_actual.y+1]=='X'){
        Volver_Casa();
    }else if(pos_actual.y==0 && tablero.tablero_visitado[pos_actual.x+1][pos_actual.y]=='X' &&
             tablero.tablero_visitado[pos_actual.x][pos_actual.x-1]=='X' &&
             tablero.tablero_visitado[pos_actual.x][pos_actual.x+1]=='X'){
        Volver_Casa();
    }else if(pos_actual.y==7 && tablero.tablero_visitado[pos_actual.y-1][pos_actual.y]=='X' &&
             tablero.tablero_visitado[pos_actual.x][pos_actual.x-1]=='X' &&
             tablero.tablero_visitado[pos_actual.x][pos_actual.x+1]=='X'){
        Volver_Casa();
    }
//    if(pos_actual.x+num_ale1>=0 && tablero.tablero_conocido[pos_actual.x+num_ale1][pos_actual.y+num_ale2]=='S' &&
//       pos_actual.x+num_ale1<=7 && tablero.tablero_visitado[pos_actual.x+num_ale1][pos_actual.y+num_ale2]!='X' &&
//       pos_actual.y+num_ale2>=0 && pos_actual.y+num_ale2<=7){
//        pos_siguiente={pos_actual.x+num_ale1,pos_actual.y+num_ale2};
//    }else{
//        tablero.tablero_visitado[pos_actual.x][pos_actual.y]='X';
//    }


    if(pos_actual.x+1>=0 && tablero.tablero_conocido[pos_actual.x+1][pos_actual.y]=='S' &&
       pos_actual.x+1<=7 && tablero.tablero_visitado[pos_actual.x+1][pos_actual.y]!='X'){

        pos_siguiente={pos_actual.x+1,pos_actual.y};
    }else{
        tablero.tablero_visitado[pos_actual.x][pos_actual.y]='X';
        if(pos_actual.y-1>=0 && tablero.tablero_conocido[pos_actual.x][pos_actual.y-1]=='S' &&
           pos_actual.y-1<=7 && tablero.tablero_visitado[pos_actual.x][pos_actual.y-1]!='X'){

        pos_siguiente={pos_actual.x,pos_actual.y-1};
        }else{
            tablero.tablero_visitado[pos_actual.x][pos_actual.y]='X';
            if(pos_actual.x-1>=0 && tablero.tablero_conocido[pos_actual.x-1][pos_actual.y]=='S' &&
               pos_actual.x-1<=7 && tablero.tablero_visitado[pos_actual.x-1][pos_actual.y]!='X'){

                pos_siguiente={pos_actual.x-1,pos_actual.y};
            }else{
                tablero.tablero_visitado[pos_actual.x][pos_actual.y]='X';
                if(pos_actual.y+1>=0 && tablero.tablero_conocido[pos_actual.x][pos_actual.y+1]=='S' &&
                   pos_actual.y+1<=7 && tablero.tablero_visitado[pos_actual.x][pos_actual.y+1]!='X'){

                    pos_siguiente={pos_actual.x,pos_actual.y+1};
                }else{
                    tablero.tablero_visitado[pos_actual.x][pos_actual.y]='X';
                    pos_siguiente=pos_anterior;
                }
            }
        }
    }

    Mover(pos_siguiente);
    tablero.Marcar(tablero.tablero_visitado, pos_actual,'V');
}

void CAgente::Reiniciar(){
    tablero.Reiniciar();
    rendimiento=0; c_anterior=c_actual=0;
    for(int i=0; i<=7; i++){
        sensaciones[i]=0;
    }

    pos_actual.x=0; pos_actual.y=7;
    tablero.tablero_real[pos_actual.x][pos_actual.y]='A';
}

void CAgente::Volver_Casa(){
    rendimiento=-100;
}

void CAgente::Agarrar(){
    rendimiento+=1000;
}

void CAgente::Matar(){
    rendimiento+=2000;
}

CAgente::~CAgente(){
}


#endif
