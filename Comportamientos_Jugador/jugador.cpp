#include "../Comportamientos_Jugador/jugador.hpp"
#include <iostream>
#include "../include/motorlib/entidad.hpp"
using namespace std;

Action ComportamientoJugador::think(Sensores sensores)
{
	
	Action accion = actIDLE;

	// Actualización del mundo
	
	cout << "ACTUALIZACIÓN"<< endl;

	if(sensores.reset ==true){
		cout << "ME CHOCO Y NO SE DONDE ESTOY" << endl;
		bien_situado=false;
	}

	//cout << "CONT = " << (int)cont << endl;

	int contfil= 0,contcol = 0;
	bool pasa_esquina =false;
	bool encontrado=false;
	bool prioridad = false;
	int g=0, k=0, d=0;
	bool g_encontrado= false, k_encontrado= false, d_encontrado= false;
	


	
	if(bien_situado){
		switch (last_action){

			case actWALK : 
				switch (current_state.brujula){
					case norte: 
					current_state.fil--; 
					break;
					case noreste: 
						current_state.fil--; 
						current_state.col++;
					break;
					case este: 
						current_state.col++; 
					break;
					case sureste: 
						current_state.fil++; 
						current_state.col++;
					break;
					case sur: 
						current_state.fil++;
					
					break;
					case suroeste: 
						current_state.fil++; 
						current_state.col--; 
					break;
					case oeste: 
						current_state.col--; 
					break;
					case noroeste: 
						current_state.fil--; 
						current_state.col--; 
					break;
				}
			break;

			case actRUN : 
						switch (current_state.brujula){
					case norte: 
						current_state.fil= current_state.fil-2; 
					break;
					case noreste: 
						current_state.fil= current_state.fil-2; 
						current_state.col= current_state.col+2; 
					break;
					case este: 
						current_state.col= current_state.col+2; 
					break;
					case sureste: 
						current_state.fil= current_state.fil+2; 
						current_state.col= current_state.col+2; 
					break;
					case sur: 
						current_state.fil= current_state.fil+2; 
					
					break;
					case suroeste: 
						current_state.fil= current_state.fil+2; 
						current_state.col= current_state.col-2; 
					break;
					case oeste: 
						current_state.col= current_state.col-2; 
					break;
					case noroeste: 
						current_state.fil= current_state.fil-2; 
						current_state.col= current_state.col-2; 
					break;
				}

			break;

			case actTURN_SR:
				current_state.brujula = static_cast<Orientacion>((current_state.brujula+1)%8);
			break;
			case actTURN_L:
				current_state.brujula = static_cast<Orientacion>((current_state.brujula+6)%8);
			break;

			case actIDLE: break;


		}
	}


	 //Memoria
	 if(sensores.terreno[0] == 'K'){
		
		tengo_bikini= true;
	 }

	 if(sensores.terreno[0]== 'D'){
		tengo_zapatos= true;
	 }
     
	if(bien_situado){
		almacen nuevo;
		nuevo.fil = current_state.fil;
		nuevo.col = current_state.col;
		nuevo.letra =sensores.terreno[0];
		memori.push_back(nuevo); 
 	}

	 //Pre guardar el mapa

	





	 
     
	 //Guardar en el mapa
	if (bien_situado){
		for (int i=0; i<sensores.terreno.size(); i++){


			if(mapaResultado[current_state.fil+contfil][current_state.col+contcol]  == '?' ){
				mapaResultado[current_state.fil+contfil][current_state.col+contcol] = sensores.terreno[i];
			}



           //cout << "LO QUE HAY  " << sensores.terreno[i] << "  LO QUE GUARDO  " << mapaResultado[current_state.fil+contfil][current_state.col+contcol] << endl;
		   //cout << "DONDE ESTA  " << i << "  DONDE LO GUARDO  " << current_state.fil+contfil<< "   " <<current_state.col+contcol << endl;

			if (i == 0){

				switch (current_state.brujula){
					case norte:	  contfil = contcol = -1; 	break;
					case noreste: contfil = -1;contcol = 0;pasa_esquina=false;	break;
					case este:    contfil= -1; contcol = +1;	break;
					case sureste: contfil = 0;contcol = +1;pasa_esquina=false;	break;
					case sur:     contfil = contcol = +1; 	break;
					case suroeste:contfil = +1;contcol = 0;pasa_esquina=false;	break;
					case oeste:   contfil= +1; contcol = -1;	break;
					case noroeste:contfil = 0;contcol = -1;pasa_esquina=false;	break;
				}

			}else if (i == 3){

				switch (current_state.brujula){
					case norte:	  contfil = contcol = -2; 	break;
					case noreste: contfil = -2; contcol = 0;pasa_esquina=false;	break;
					case este:    contfil= -2; contcol = +2;	break;
					case sureste: contfil = 0;contcol = +2;pasa_esquina=false;break;
					case sur:     contfil = contcol = +2; 	break;
					case suroeste:contfil = +2;contcol = 0;pasa_esquina=false;	break;
					case oeste:   contfil= +2; contcol = -2;	break;
					case noroeste:contfil = 0;contcol = -2;pasa_esquina=false;	break;
	   			}

			}else if (i == 8){

				switch (current_state.brujula){
					case norte:	  contfil = contcol = -3; 	break;
					case noreste: contfil = -3;contcol = 0;pasa_esquina=false;	break;
					case este:    contfil= -3; contcol = +3;	break;
					case sureste: contfil = 0;contcol = +3;pasa_esquina=false;	break;
					case sur:     contfil = contcol = +3;	break;
					case suroeste:contfil = +3;contcol = 0;pasa_esquina=false;	break;
					case oeste:   contfil= +3; contcol = -3;	break;
					case noroeste:contfil = 0;contcol = -3;pasa_esquina=false;	break;
	            }

			}else{
				switch (current_state.brujula){
					case norte:	  contcol++; 	break;
					case noreste: 
						if(abs(contcol)==(abs(contfil)) or pasa_esquina){
							contfil++;
							pasa_esquina=true;
						}else{
							contcol++;
						};
					break;
					case este:    contfil++;	break;
					case sureste: 
						if(abs(contcol)==(abs(contfil)) or pasa_esquina){
							contcol--;
							pasa_esquina=true;
						}else{
							contfil++;
						};	break;
					case sur:     contcol--; break;
					case suroeste:
						if(abs(contcol)==(abs(contfil)) or pasa_esquina){
					
							contfil--;
							pasa_esquina=true;
						}else{
							contcol--;
							
						};	break;
					case oeste:   contfil--;	break;
					case noroeste:	
						if(abs(contcol)==(abs(contfil)) or pasa_esquina){
							contcol++;
							pasa_esquina=true;
						}else{
							contfil--;
						};	break;
	        	}			
			}

		}
	}


	// Mostrar el valor de los sensores
	cout << "Posicion: fila " << sensores.posF << " columna " << sensores.posC;
	switch (sensores.sentido)
	{
		case norte:	  cout << " Norte\n";	break;
		case noreste: cout << " Noreste\n";	break;
		case este:    cout << " Este\n";	break;
		case sureste: cout << " Sureste\n";	break;
		case sur:     cout << " Sur\n";	break;
		case suroeste:cout << " Suroeste\n";	break;
		case oeste:   cout << " Oeste\n";	break;
		case noroeste:cout << " Noroeste\n";	break;
	}
	cout << "Terreno: ";
	for (int i=0; i<sensores.terreno.size(); i++)
		cout << sensores.terreno[i];

	cout << "  Agentes: ";
	for (int i=0; i<sensores.agentes.size(); i++)
		cout << sensores.agentes[i];

	cout << "\nColision: " << sensores.colision;
	cout << "  Reset: " << sensores.reset;
	cout << "  Vida: " << sensores.vida << endl<< endl;
	
	/*if(sensores.colision ==true){
		bien_situado=false;
	}*/


	//Decidir acción

	//No repetir
	int fil_siguiente=current_state.fil;
	int col_siguiente=current_state.col;

	switch (current_state.brujula){
		case norte: 
			fil_siguiente--; 
		break;
		case noreste: 
			fil_siguiente--; 
			col_siguiente++;
		break;
		case este: 
			col_siguiente++; 
		break;
		case sureste: 
			fil_siguiente++; 
			col_siguiente++;
		break;
		case sur: 
			fil_siguiente++;
					
		break;
		case suroeste: 
			fil_siguiente++; 
			col_siguiente--; 
		break;
		case oeste: 
			col_siguiente--; 
		break;
		case noroeste: 
			fil_siguiente--; 
			col_siguiente--; 
		break;
	}

    for (int i = 0; i<memori.size();i++){
		if ((sensores.terreno[2] == memori[i].letra) && (col_siguiente==memori[i].col) && (fil_siguiente==memori[i].fil)){
			encontrado=true;
		}
	}

	cout << "DECIDIR"<< endl;

	//PRIORIDADES
		cout << "PRIORIDAD"<< endl;
	
    for ( int i=0; i<sensores.terreno.size() ; i++){

		if (sensores.terreno[i] == 'G' and g_encontrado==false){
			g_encontrado= true;
			g=i;
			cout << "veo casilla G"<< endl;
		}
		if (sensores.terreno[i] == 'K' and k_encontrado==false){
			k_encontrado= true;
			k=i;
			cout << "veo casilla K"<< endl;
		}
		if (sensores.terreno[i] == 'D' and d_encontrado==false){
			d_encontrado= true;
			d=i;
			cout << "veo casilla D"<< endl;
		}

	}

	if (current_state.fil == 99 and g_encontrado and  (sensores.terreno[2]!= 'M') and  (sensores.terreno[1]!= 'M')and  (sensores.terreno[3]!= 'M')){
		cout << "VOY casilla G"<< endl;
		switch(g){
			case 1: 
			case 4:
			case 9:
			accion= actTURN_L;
			break;

			case 3: 
			case 8:
			case 15:
			accion= actTURN_SR;
			break;

			case 2: 
			case 5:
			case 6:
			case 7: 
			case 10:
			case 11:
			case 12:
			case 13: 
			case 14:
			if(sensores.agentes[2]== '_'){
				accion= actWALK;
			}else{accion =actIDLE;}
			
			break;


		}
		prioridad=true;
	}

	//cout << "CONDICIONES:  "<< 	tengo_bikini <<"  " <<	prioridad <<"  " 	<< k_encontrado <<"  "<<sensores.terreno[2]  << "  "<<sensores.terreno[1]  << "  "<<sensores.terreno[3]  << "  "  << endl;


	if((tengo_bikini==false) && (prioridad ==false) && (k_encontrado==true) &&  (sensores.terreno[2] != 'M') &&  (sensores.terreno[1] != 'M') && (sensores.terreno[3] != 'M')){
		cout << "VOY casilla k"<< endl;
		switch(k){
			case 1: 
			case 4:
			case 9:
			accion= actTURN_L;
			break;

			case 3: 
			case 8:
			case 15:
			accion= actTURN_SR;
			break;

			case 2: 
			case 5:
			case 6:
			case 7: 
			case 10:
			case 11:
			case 12:
			case 13: 
			case 14:
			if(sensores.agentes[2]== '_' && sensores.terreno[2]!= 'M'){
				accion= actWALK;
			}else{accion =actIDLE;}
			break;

		}
		prioridad=true;
	}
	//cout << "CONDICIONES:  "<< 	tengo_bikini <<"  " <<	prioridad <<"  " 	<< k_encontrado <<"  " << endl;

	if((prioridad == false) && (d_encontrado==true) && (tengo_zapatos==false)and  (sensores.terreno[2]!= 'M')and  (sensores.terreno[1]!= 'M')and  (sensores.terreno[3]!= 'M')){
		cout << "VOY casilla D"<< endl;
		switch(d){
			case 1: 
			case 4:
			case 9:
			accion= actTURN_L;
			break;

			case 3: 
			case 8:
			case 15:
			accion= actTURN_SR;
			break;

			case 2: 
			case 5:
			case 6:
			case 7: 
			case 10:
			case 11:
			case 12:
			case 13: 
			case 14:			
			if(sensores.agentes[2]== '_' ){
				accion= actWALK;
			}else{accion =actIDLE;}
			break;


		}
		prioridad=true;
	}
	
	

	

	

	if(prioridad==false){

		cout << "NO hay prioridad"<< endl;
		if ((sensores.terreno[2] == 'T' or sensores.terreno[2] == 'S' or sensores.terreno[2] == 'G' or sensores.terreno[2] == 'K' or sensores.terreno[2] == 'D' or sensores.terreno[2] == 'X' or
			((sensores.terreno[2] == 'A') and (tengo_bikini==true)) or ((sensores.terreno[2] == 'B') and (tengo_zapatos==true)) or ((cont_malasuerte<=0) and (sensores.terreno[2] != 'P') and (sensores.terreno[2] != 'M') ))
			
			and (sensores.agentes[2]== '_')
			
			and ((encontrado==false) or (cont_malasuerte<=0) )){
			//cout << "ANDO NORMAL"<< (bool)tengo_zapatos<< "  "<<  cont_malasuerte<<endl;
			accion = actWALK;
			cont_malasuerte= 3+(rand()%(5-3));
		}else if(encontrado == true){
			cout << "ENCUENTRO CASILLA REPE"<< endl;
			accion = actTURN_SR;
			if (last_action==actTURN_SR){
				accion = actTURN_L;
				cont++;
				cout << "GIRO A LA IZQ Y CONT = " << cont << endl;
				//if(cont >=2){
			//		accion= actTURN_SR;
			//		cont=0;
			//	}
			}
			if(cont_malasuerte<=0 and sensores.terreno[2] != 'P' and sensores.terreno[2] != 'M'  and sensores.agentes[2]== '_'){
				cout << "ANDO POR LA MALA SUERTE"<< endl;
			accion = actWALK;
			cont_malasuerte= 3+(rand()%(5-3));
			}
			cont_malasuerte--;

		} else if (!derecha){
			cout << "GIRO IZQ"<< endl;
			cout << "CONT = " << (int)cont << endl;
			accion= actTURN_L;
			cont++;
			if ((last_action == actTURN_L) && (cont >= 2)){
		
				derecha = true;
				//derecha= (rand()%2 ==0);
				//cont = 2;
			

			}
			//derecha = (rand()%2 == 0);
			cont_malasuerte--;
		}else{
			cout << "GIRO DER"<< endl;
			accion = actTURN_SR;
			cont= 0;
			if ((last_action== actTURN_SR) && (cont <= 0)){
				derecha == false;
				//derecha= (rand()%2 ==0);

			
			}/*
			if ( (cont <= 0)){
				derecha = false;
				//derecha= (rand()%2 ==0);

			
			}*/
			
		
			//derecha= (rand()%2 ==0);
			cont_malasuerte--;

		}
	}
	
	//encontrado=false;

	if ( (sensores.bateria < sensores.tiempo) && (sensores.terreno[0]== 'X') ){
		accion = actIDLE;
	}
		if ((sensores.terreno[0]== 'G' and !bien_situado) or (sensores.nivel==0 and !bien_situado)){
		current_state.fil = sensores.posF;
		current_state.col = sensores.posC;
		current_state.brujula = sensores.sentido;
		cout << "Me ubico" << endl;
		bien_situado = true;
	}

	//RETURN
	last_action=accion;
	cout << ""<< endl;
	return accion;
}

int ComportamientoJugador::interact(Action accion, int valor)
{
	return false;
}