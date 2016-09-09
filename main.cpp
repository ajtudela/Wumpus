/*
    main.cpp - Wumpus Main
    Created by Alberto Tudela, June 23 2011
    Under license GPLv3
*/

#include "CTablero.hpp"
#include "CAgente.hpp"
#include "Tipos.h"

#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

void delay(int secs) {
for(int i = (time(NULL) + secs); time(NULL) != i; time(NULL));
}

int menu(){
int sel;
cout<<endl;
cout<<"     ##      ## ##     ## ##     ## ########  ##     ##  ######  "<<endl;
cout<<"     ##  ##  ## ##     ## ###   ### ##     ## ##     ## ##    ## "<<endl;
cout<<"     ##  ##  ## ##     ## #### #### ##     ## ##     ## ##       "<<endl;
cout<<"     ##  ##  ## ##     ## ## ### ## ########  ##     ##  ######  "<<endl;
cout<<"     ##  ##  ## ##     ## ##     ## ##        ##     ##       ## "<<endl;
cout<<"     ##  ##  ## ##     ## ##     ## ##        ##     ## ##    ## "<<endl;
cout<<"      ###  ###   #######  ##     ## ##         #######   ######  "<<endl<<endl;
cout<<"------ Menu ------"<<endl;
cout<<"0. Salir"<<endl;
cout<<"1. Paso a paso"<<endl;
cout<<"2. Paso a paso (rapido)"<<endl;
cout<<"3. Modo Debug"<<endl;
cout<<"Opcion: [_]\r";
cout<<"Opcion: [";
cin>>sel;
cin.ignore(5000,'\n');
cin.clear();
return sel;
}

int main(){
int seleccion;
CAgente agente;
seleccion=1;
while(seleccion!=0){
    agente.Reiniciar();
	seleccion= menu();
	switch (seleccion){
		case 0:
            system("cls");
			cout<<"Adios!"<<endl;
			return 0;
		case 1:
            system("cls");
            agente.Percepcion(); agente.Analizar();
            agente.tablero.Mostrar(agente.tablero.tablero_real);
            delay(1); system("cls");
            while(agente.rendimiento==0){
                agente.Avanzar();
                agente.tablero.Mostrar(agente.tablero.tablero_real);
                delay(1);
                system("cls");
            }
            switch(agente.rendimiento){
               case 1000:
                    cout<<"Nuestro afortunado agente ha encontrado el oro y se ha hecho rico!"<<endl;
                    break;
               case 2000:
                    cout<<"Nuestro valeroso agente ha matado a la bestia Wumpus!"<<endl;
                    break;
               case -1000:
                    cout<<"El agente se ha caido en el hoyo!"<<endl;
                    break;
               case -100:
                    cout<<"Nuestro prudente agente, incapaz de continuar su camino sin arriesgar su vida, ha vuelto a casa con las manos vacias."<<endl;
                    break;
            }
            break;
      case 2:
            system("cls");
            agente.Percepcion(); agente.Analizar();
            agente.tablero.Mostrar(agente.tablero.tablero_real);
            delay(1); system("cls");
            while(agente.rendimiento==0){
                agente.Avanzar();
                agente.tablero.Mostrar(agente.tablero.tablero_real);
                system("cls");
            }
            switch(agente.rendimiento){
               case 1000:
                    cout<<"Nuestro afortunado agente ha encontrado el oro y se ha hecho rico!"<<endl;
                    break;
               case 2000:
                    cout<<"Nuestro valeroso agente ha matado a la bestia Wumpus!"<<endl;
                    break;
               case -1000:
                    cout<<"El agente se ha caido en el hoyo!"<<endl;
                    break;
               case -100:
                    cout<<"Nuestro prudente agente, incapaz de continuar su camino sin arriesgar su vida, ha vuelto a casa con las manos vacias."<<endl;
                    break;
            }
            break;
        case 3:
            system("cls");
            agente.Percepcion(); agente.Analizar();
            agente.tablero.Mostrar(agente.tablero.tablero_real);
            delay(1); system("cls");
            while(agente.rendimiento==0){
                agente.Avanzar();
                agente.tablero.Mostrar_Todo();
                delay(1); system("cls");
            }
            switch(agente.rendimiento){
               case 1000:
                    cout<<"Nuestro afortunado agente ha encontrado el oro y se ha hecho rico!"<<endl;
                    break;
               case 2000:
                    cout<<"Nuestro valeroso agente ha matado a la bestia Wumpus!"<<endl;
                    break;
               case -1000:
                    cout<<"El agente se ha caido en el hoyo!"<<endl;
                    break;
               case -100:
                    cout<<"Nuestro prudente agente, incapaz de continuar su camino sin arriesgar su vida, ha vuelto a casa con las manos vacias."<<endl;
                    break;
            }
			break;
	}
}
}


//agente.Avanzar(); agente.Avanzar();
//agente.tablero.Mostrar(agente.tablero.tablero_real);
//agente.tablero.Mostrar(agente.tablero.tablero_conocido);
//agente.tablero.Mostrar(agente.tablero.tablero_visitado);
//
////agente.Avanzar();
////agente.tablero.Mostrar(agente.tablero.tablero_real);
////agente.tablero.Mostrar(agente.tablero.tablero_conocido);
////agente.tablero.Mostrar(agente.tablero.tablero_visitado);
//
//agente.Avanzar();
//agente.tablero.Mostrar(agente.tablero.tablero_real);
//agente.tablero.Mostrar(agente.tablero.tablero_conocido);
//agente.tablero.Mostrar(agente.tablero.tablero_visitado);

//cout<<"Brisa= "<<agente.sensaciones[0]<<" .\n";
//cout<<"Hedor= "<<agente.sensaciones[1]<<" .\n";
//cout<<"Resplandor= "<<agente.sensaciones[2]<<" .\n";

