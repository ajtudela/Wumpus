/*
    CTablero.hpp - Wumpus Board Class
    Created by Alberto Tudela, June 23 2011
    Under license GPLv3
*/

#ifndef _TABLERO_
#define _TABLERO_

#include "Tipos.h"

#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

class CTablero{

private:
    int p_rnd1, p_rnd2;
public:

	CTablero();
	~CTablero();
	void Mostrar(TTablero tab);
	void Mostrar_Todo();
	void Borrar(TTablero tab);
	void Marcar(TTablero tab, TPosicion posicion, char letra);
	void Marcar_Adyacentes(TTablero tab, TPosicion posicion, char letra);
	bool Adyacentes(TTablero tab, TPosicion posicion, char letra);
	void Reiniciar();
	void Rellenar_Aleatorio(TTablero tab, int num_veces, char letra);

	TTablero tablero_real, tablero_supuesto, tablero_visitado, tablero_conocido;


};

CTablero::CTablero(){
srand (time(NULL));

for(int j=0; j<=7; j++){			//Rellena el tablero con 0 o casillas vacias
	for(int i=0; i<=7; i++){
		tablero_real[i][j]=0;
		tablero_conocido[i][j]=0;
		tablero_visitado[i][j]=0;
		tablero_supuesto[i][j]=0;
	}
}

Marcar(tablero_real,{3,1},'R');
Marcar(tablero_real,{7,1},'W'); Marcar_Adyacentes(tablero_real,{7,1},'M');
Marcar_Adyacentes(tablero_real,{2,6},'B'); Marcar_Adyacentes(tablero_real,{3,6},'B');
Marcar(tablero_real,{2,6},'H'); Marcar(tablero_real,{3,6},'H');
}

void CTablero::Mostrar(TTablero tab){
cout<<"\t    0   1   2   3   4   5   6   7   "<<endl;			//Muestra el tablero
cout<<"\t   -------------------------------- "<<endl;
for(int j=0; j<=7;j++){
	cout<<"\t "<<j<<"|";
	for(int i=0; i<=7;i++){
		if(tab[i][j]==0){
			cout<<"   |";
		}else{
			cout<<" "<<tab[i][j]<<" |";
        }
	}
	cout<<endl;
	cout<<"\t   -------------------------------- "<<endl;
}
}

void CTablero::Mostrar_Todo(){
cout<<"\t          Tablero Real                        Tablero Conocido       "<<endl<<endl;
cout<<"\t    0   1   2   3   4   5   6   7      0   1   2   3   4   5   6   7 "<<endl;			//Muestra el tablero
cout<<"\t   --------------------------------   --------------------------------"<<endl;
for(int j=0; j<=7;j++){
	cout<<"\t "<<j<<"|";
	for(int i=0; i<=7;i++){
		if(tablero_real[i][j]==0){
			cout<<"   |";
		}else{
			cout<<" "<<tablero_real[i][j]<<" |";
        }
	}

	cout<<" "<<j<<"|";
	for(int i=0; i<=7;i++){
		if(tablero_conocido[i][j]==0){
			cout<<"   |";
		}else{
			cout<<" "<<tablero_conocido[i][j]<<" |";
        }
	}



	cout<<endl;
	cout<<"\t   --------------------------------   --------------------------------"<<endl;
}
cout<<endl<<endl;
cout<<"\t          Tablero Visitado                    Tablero Supuesto       "<<endl<<endl;
cout<<"\t    0   1   2   3   4   5   6   7      0   1   2   3   4   5   6   7 "<<endl;			//Muestra el tablero
cout<<"\t   --------------------------------   --------------------------------"<<endl;
for(int j=0; j<=7;j++){
	cout<<"\t "<<j<<"|";
	for(int i=0; i<=7;i++){
		if(tablero_visitado[i][j]==0){
			cout<<"   |";
		}else{
			cout<<" "<<tablero_visitado[i][j]<<" |";
        }
	}

	cout<<" "<<j<<"|";
	for(int i=0; i<=7;i++){
		if(tablero_supuesto[i][j]==0){
			cout<<"   |";
		}else{
			cout<<" "<<tablero_supuesto[i][j]<<" |";
        }
	}



	cout<<endl;
	cout<<"\t   --------------------------------   --------------------------------"<<endl;
}
}

void CTablero::Marcar(TTablero tab, TPosicion posicion, char letra){
    tab[posicion.x][posicion.y]=letra;
}

void CTablero::Marcar_Adyacentes(TTablero tab, TPosicion posicion, char letra){
    if(posicion.x-1>=0){
        tab[posicion.x-1][posicion.y]=letra;
    }

    if(posicion.x+1<=7){
        tab[posicion.x+1][posicion.y]=letra;
    }

    if(posicion.y-1>=0){
        tab[posicion.x][posicion.y-1]=letra;
    }

    if(posicion.y+1<=7){
        tab[posicion.x][posicion.y+1]=letra;
    }
}

void CTablero::Borrar(TTablero tab){   //Borra el tablero
for(int j=0; j<=7; j++){
	for(int i=0; i<=7; i++){
		tab[i][j]=0;

    }
}
}

//Devuevle true si la casilla esta al lado
bool CTablero::Adyacentes(TTablero tab, TPosicion posicion, char letra){
    if(tab[posicion.x+1][posicion.y]==letra || tab[posicion.x-1][posicion.y]==letra ||
       tab[posicion.x][posicion.y+1]==letra || tab[posicion.x][posicion.y-1]==letra){
       return true;
    }else{
        return false;
    }
}

void CTablero::Rellenar_Aleatorio(TTablero tab, int num_veces, char letra){
    for(int i=0; i<num_veces; i++){
        p_rnd1=rand()%7+1; p_rnd2=rand()%7+1; //Numero aletario entre 1 y 7
        if(p_rnd1!=0 && p_rnd2!=0){
            Marcar(tab,{p_rnd1,p_rnd2},letra);
            if(letra=='W'){
                Marcar_Adyacentes(tab,{p_rnd1,p_rnd2},'M');
            }else if(letra=='H'){
                Marcar_Adyacentes(tab,{p_rnd1,p_rnd2},'B');
            }
        }
    }
}


void CTablero::Reiniciar(){
    Borrar(tablero_real); Borrar(tablero_conocido);
    Borrar(tablero_visitado); Borrar(tablero_supuesto);
    Rellenar_Aleatorio(tablero_real, 2, 'H');
    Rellenar_Aleatorio(tablero_real, 1, 'W');
    Rellenar_Aleatorio(tablero_real, 1, 'R');

//    Marcar(tablero_real,{3,1},'R'); Marcar(tablero_real,{3,1},'R');
//    Marcar(tablero_real,{7,1},'W'); Marcar_Adyacentes(tablero_real,{7,1},'M');
//    Marcar_Adyacentes(tablero_real,{2,6},'B'); Marcar_Adyacentes(tablero_real,{3,6},'B');
//    Marcar(tablero_real,{2,6},'H'); Marcar(tablero_real,{3,6},'H');
}

CTablero::~CTablero(){
}

#endif

