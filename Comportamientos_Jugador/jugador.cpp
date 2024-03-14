#include "../Comportamientos_Jugador/jugador.hpp"
#include <iostream>
#include "../include/motorlib/entidad.hpp"
using namespace std;

Action ComportamientoJugador::think(Sensores sensores)
{
	
	Action accion = actIDLE;

	// Actualización del mundo
	
	cout << "ACTUALIZACIÓN"<< endl;
	if (bien_situado == false && sensores.reset ==true ){
		perdidos_dos = true;
	}

	if(sensores.reset ==true){
		cout << "ME CHOCO Y NO SE DONDE ESTOY" << endl;
		bien_situado=false;
		current_state.fil=current_state.col = 99;
	}




	//cout << "CONT = " << (int)cont << endl;
	vector<unsigned char> aux(max_size, '?');

	int contfil= 0,contcol = 0;
	bool valido = false;
	bool pasa_esquina =false;
	int  encontrado=0;
	bool prioridad = false;
	int g=0, k=0, d=0;
	bool g_encontrado= false, k_encontrado= false, d_encontrado= false;
	int  resto_x = 0, resto_y =0;
	int sol_x=0, sol_y=0;
	bool hueco_encontrado = false;
	int ajuste_x=0, ajuste_y=0;
	


	
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
		
	if ((sensores.terreno[0]== 'G' and !bien_situado) or (sensores.nivel==0 and !bien_situado)){
		ultimo_col= current_state.col;
		ultimo_fil=current_state.fil;
		current_state.fil = sensores.posF;
		current_state.col = sensores.posC;
		current_state.brujula = sensores.sentido;
		cout << "Me ubico" << endl;
		bien_situado = true;
	}




   //MEMORIA
	//Brujula falsa

	if(!bien_situado ){
	
	

	switch (last_action){

			case actWALK : 
				switch (brujula_falsa){
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
			brujula_falsa = static_cast<Orientacion>((brujula_falsa+1)%8);
		break;

		case actTURN_L:
			brujula_falsa = static_cast<Orientacion>((brujula_falsa+6)%8);
		break;

	}
		if(perdidos_dos== true){
			brujula_falsa = norte;
		}
	}
	///*
	//Pre guardado
	if(!bien_situado ){

		cout << "DENTRO DE PREGUARDADO"<< endl;

		if(perdidos_dos== true){

    		

			for (unsigned int i = 0; i < max_size; i++)
     		{
     			mapaPreResultado.pop_back();

     		}
    	 	
     		for (unsigned int i = 0; i < max_size; i++)
     		{
     			mapaPreResultado.push_back(aux);

     		}
			perdidos_dos=false;

		}

		hay_info=true;
		for (int i=0; i<sensores.terreno.size(); i++){
			//cout <<  mapaPreResultado[current_state.fil+contfil][current_state.col+contcol] << endl;
			//cout << "DONDE ESTA  " << i << "  DONDE LO GUARDO  " << current_state.fil+contfil<< "   " <<current_state.col+contcol << endl;

				if(mapaPreResultado[current_state.fil+contfil][current_state.col+contcol]  == '?' ){
					mapaPreResultado[current_state.fil+contfil][current_state.col+contcol] = sensores.terreno[i];
				}



			//cout << "LO QUE HAY  " << sensores.terreno[i] << "  LO QUE GUARDO  " << mapaPreResultado[current_state.fil+contfil][current_state.col+contcol] << endl;
			//cout << "DONDE ESTA  " << i << "  DONDE LO GUARDO  " << current_state.fil+contfil<< "   " <<current_state.col+contcol << endl;

				if (i == 0){


					switch (brujula_falsa){
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

					switch (brujula_falsa){
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

					switch (brujula_falsa){
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
					switch (brujula_falsa){
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

		//VOLCADO
		if(bien_situado && hay_info){
			cout << "DENTRO DE volcado"<< endl;

			switch (current_state.brujula){
					case norte: 
						ajuste_x--; 
					break;
					case noreste: 
						ajuste_x--; 
						ajuste_y++;
					break;
					case este: 
						ajuste_y++; 
					break;
					case sureste: 
						ajuste_x++; 
						ajuste_y++;
					break;
					case sur: 
						ajuste_x++;
					
					break;
					case suroeste: 
						ajuste_x++; 
						ajuste_y--; 
					break;
					case oeste: 
						ajuste_y--; 
					break;
					case noroeste: 
						ajuste_x--; 
						ajuste_y--; 
					break;
				}



			cout << ajuste_x<< "	" << ajuste_y<<endl;

			int cambio =(sensores.sentido-brujula_falsa);
			if (cambio<0){
				cambio = cambio+8;
			}
			


			cout <<  "					MIRANDO A " << cambio<<endl;
			
			

			switch (cambio){

				case norte:
				cout << "							brujala al norte  "<<endl;
				for (int x=0; x < mapaPreResultado.size(); x++){
					for(int y =0 ; y < mapaPreResultado[0].size(); y++){
						//cout << "dentro de los for y compruebo esto: "<< mapaPreResultado[x][y] << "en la posicion "<< x<< "  "<<y << endl;
						if(mapaPreResultado[x][y]  != '?' ){
							//cout << "dentro del if" << endl;
							resto_x= x - ultimo_fil-ajuste_x;
							resto_y= y - ultimo_col-ajuste_y;	
							if(mapaResultado[current_state.fil+resto_x][current_state.col+resto_y]  == '?' ){
								//cout << "copio en " << current_state.fil+resto_x<<"  "<<current_state.col+resto_y <<  "  esto: "<< mapaPreResultado[x][y]<<endl;
								mapaResultado[current_state.fil+resto_x][current_state.col+resto_y] = mapaPreResultado[x][y];
							}			
						}
					}
				}	
	
				break;

				
				case noreste: 
				cout << "brujala al noreste "<<endl;
				
				for (int x=0; x < mapaPreResultado.size(); x++){
					for(int y =0 ; y < mapaPreResultado[0].size(); y++){
						//cout << "dentro de los for y compruebo esto: "<< mapaPreResultado[x][y] << "en la posicion "<< x<< "  "<<y << endl;
						if(mapaPreResultado[x][y]  != '?' ){
							//cout << "dentro del if" << endl;
							resto_x= x - ultimo_fil-ajuste_x;
							resto_y= y - ultimo_col-ajuste_y;
							int sol_x=0, sol_y=0;
							while(resto_x != 0 and resto_y != 0){
								if(resto_x<0 && resto_y<0){
									sol_x--;
									resto_x++;
									resto_y++;
								}else if(resto_x>0 && resto_y>0){
									sol_x++;
									resto_x--;
									resto_y--;
								}else if(resto_x<0 && resto_y>0){
									sol_y++;
									resto_x++;
									resto_y--;

								}else if(resto_x>0 && resto_y<0){
									sol_y--;
									resto_x--;
									resto_y++;
								}else if(resto_x==0 && resto_y<0){
									sol_x--;
									sol_y--;
								
									resto_y++;
								}else if(resto_x==0 && resto_y>0){
									sol_x++;

									sol_y++;
									resto_y--;
								}else if(resto_x>0 && resto_y==0){
									sol_x++;
									resto_x--;
									sol_y--;
								}else if(resto_x<0 && resto_y==0){
									sol_x--;
									sol_y++;
									resto_x++;
								
								}
							}

							if(mapaResultado[current_state.fil+sol_x][current_state.col+sol_y]  == '?' ){
								cout << "copio en " << current_state.fil+sol_x<<"  "<<current_state.col+sol_y <<  "  esto: "<< mapaPreResultado[x][y]<<endl;
								mapaResultado[current_state.fil+sol_x][current_state.col+sol_y] = mapaPreResultado[x][y];
							}			
						}
					}
				}					
				
				
				
				
				break;
				
				case este:  
				cout << "				brujala al este "<<endl; 

				for (int x=0; x < mapaPreResultado.size(); x++){
					for(int y =0 ; y < mapaPreResultado[0].size(); y++){
						//cout << "dentro de los for y compruebo esto: "<< mapaPreResultado[x][y] << "en la posicion "<< x<< "  "<<y << endl;
						if(mapaPreResultado[x][y]  != '?' ){
							//cout << "dentro del if" << endl;
							resto_x= x - ultimo_fil+ajuste_x;
							resto_y= y - ultimo_col-ajuste_y;	
							if(mapaResultado[current_state.fil+resto_y][current_state.col+resto_x]  == '?' ){
								//cout << "copio en " << current_state.fil+resto_x<<"  "<<current_state.col+resto_y <<  "  esto: "<< mapaPreResultado[x][y]<<endl;
								mapaResultado[current_state.fil+resto_y][current_state.col+resto_x] = mapaPreResultado[x][y];
							}			
						}
					}
				}					
				
					break;
				case sureste: 
				cout << "brujala al sureste "<<endl;		
				for (int x=0; x < mapaPreResultado.size(); x++){
					for(int y =0 ; y < mapaPreResultado[0].size(); y++){
						//cout << "dentro de los for y compruebo esto: "<< mapaPreResultado[x][y] << "en la posicion "<< x<< "  "<<y << endl;
						if(mapaPreResultado[x][y]  != '?' ){
							//cout << "dentro del if" << endl;
							resto_x= x - ultimo_fil-ajuste_x;
							resto_y= y - ultimo_col-ajuste_y;
							int sol_x=0, sol_y=0;
							while(resto_x != 0 and resto_y != 0){
								if(resto_x<0 && resto_y<0){
									sol_y++;
									resto_x++;
									resto_y++;
								}else if(resto_x>0 && resto_y>0){
									sol_y--;
									resto_x--;
									resto_y--;
								}else if(resto_x<0 && resto_y>0){
									sol_x++;
									resto_x++;
									resto_y--;

								}else if(resto_x>0 && resto_y<0){
									sol_x--;
									resto_x--;
									resto_y++;
								}else if(resto_x==0 && resto_y<0){
									sol_x--;
									sol_y++;
								
									resto_y++;
								}else if(resto_x==0 && resto_y>0){
									sol_x++;
									sol_y--;

									resto_y--;
								}else if(resto_x>0 && resto_y==0){
									sol_x--;
									resto_x--;
									sol_y--;
								}else if(resto_x<0 && resto_y==0){
									sol_x++;
									sol_y++;
									resto_x++;
								
								}
							}

							if(mapaResultado[current_state.fil+sol_x][current_state.col+sol_y]  == '?' ){
								cout << "copio en " << current_state.fil+sol_x<<"  "<<current_state.col+sol_y <<  "  esto: "<< mapaPreResultado[x][y]<<endl;
								mapaResultado[current_state.fil+sol_x][current_state.col+sol_y] = mapaPreResultado[x][y];
							}			
						}
					}
				}					
				
				
				
				break;
				case sur: 
				cout << "		brujala al sur "<<endl;

				for (int x=0; x < mapaPreResultado.size(); x++){
					for(int y =0 ; y < mapaPreResultado[0].size(); y++){
						//cout << "dentro de los for y compruebo esto: "<< mapaPreResultado[x][y] << "en la posicion "<< x<< "  "<<y << endl;
						if(mapaPreResultado[x][y]  != '?' ){
							//cout << "dentro del if" << endl;
							resto_x= (x - ultimo_fil)+ajuste_x;
							resto_y= (y - ultimo_col)+ajuste_y;	
							if(mapaResultado[current_state.fil-resto_x][current_state.col-resto_y]  == '?' ){
								//cout << "copio en " << current_state.fil+resto_x<<"  "<<current_state.col+resto_y <<  "  esto: "<< mapaPreResultado[x][y]<<endl;
								mapaResultado[current_state.fil-resto_x][current_state.col-resto_y] = mapaPreResultado[x][y];
							}			
						}
					}
				}					
				
				
								
				
				
				
				break;
				case suroeste: 
				cout << "brujala al suroeste "<<endl;
				
				for (int x=0; x < mapaPreResultado.size(); x++){
					for(int y =0 ; y < mapaPreResultado[0].size(); y++){
						//cout << "dentro de los for y compruebo esto: "<< mapaPreResultado[x][y] << "en la posicion "<< x<< "  "<<y << endl;
						if(mapaPreResultado[x][y]  != '?' ){
							//cout << "dentro del if" << endl;
							resto_x= x - ultimo_fil-ajuste_x;
							resto_y= y - ultimo_col-ajuste_y;
							int sol_x=0, sol_y=0;
							while(resto_x != 0 and resto_y != 0){
								if(resto_x<0 && resto_y<0){
									sol_x++;
									resto_x++;
									resto_y++;
								}else if(resto_x>0 && resto_y>0){
									sol_x--;
									resto_x--;
									resto_y--;
								}else if(resto_x<0 && resto_y>0){
									sol_y--;
									resto_x++;
									resto_y--;

								}else if(resto_x>0 && resto_y<0){
									sol_y++;
									resto_x--;
									resto_y++;
								}else if(resto_x==0 && resto_y<0){
									sol_x++;
									sol_y++;
								
									resto_y++;
								}else if(resto_x==0 && resto_y>0){
									sol_x--;

									sol_y--;
									resto_y--;
								}else if(resto_x>0 && resto_y==0){
									sol_x--;
									resto_x--;
									sol_y++;
								}else if(resto_x<0 && resto_y==0){
									sol_x++;
									sol_y--;
									resto_x++;
								
								}
							}
							cout << "copio en " << current_state.fil-sol_x<<"  "<<current_state.col+sol_y <<  "  esto: "<< mapaPreResultado[x][y]<<endl;	
							if(mapaResultado[current_state.fil-sol_x][current_state.col-sol_y]  == '?' ){
								
								mapaResultado[current_state.fil-sol_x][current_state.col-sol_y] = mapaPreResultado[x][y];
							}			
						}
					}
				}					
				
				
				
				break;
				case oeste:  
				cout << "					brujala al oeste "<<endl;

				for (int x=0; x < mapaPreResultado.size(); x++){
					for(int y =0 ; y < mapaPreResultado[0].size(); y++){
						//cout << "dentro de los for y compruebo esto: "<< mapaPreResultado[x][y] << "en la posicion "<< x<< "  "<<y << endl;
						if(mapaPreResultado[x][y]  != '?' ){
							//cout << "dentro del if" << endl;
							resto_x= (x - ultimo_fil)+ajuste_x;
							resto_y= (y - ultimo_col)-ajuste_y;	
							//cout << "copio en " << current_state.fil+sol_x<<"  "<<current_state.col+sol_y <<  "  esto: "<< mapaPreResultado[x][y]<<endl;	

							if(mapaResultado[current_state.fil-resto_y][current_state.col+resto_x]  == '?' ){
								//cout << "copio en " << current_state.fil+resto_x<<"  "<<current_state.col+resto_y <<  "  esto: "<< mapaPreResultado[x][y]<<endl;
								mapaResultado[current_state.fil-resto_y][current_state.col+resto_x] = mapaPreResultado[x][y];
							}			
						}
					}
				}					
				
				
								
				
				
				
				break; 
				

				case noroeste:
				/*
				cout << "brujala al noroeste "<<endl;		
				for (int x=0; x < mapaPreResultado.size(); x++){
					for(int y =0 ; y < mapaPreResultado[0].size(); y++){
						//cout << "dentro de los for y compruebo esto: "<< mapaPreResultado[x][y] << "en la posicion "<< x<< "  "<<y << endl;
						if(mapaPreResultado[x][y]  != '?' ){
							//cout << "dentro del if" << endl;
							resto_x= x - ultimo_fil;
							resto_y= y - ultimo_col;
							int sol_x=0, sol_y=0;
							while(resto_x != 0 and resto_y != 0){
								if(resto_x<0 && resto_y<0){
									sol_y--;
									resto_x++;
									resto_y++;
								}else if(resto_x>0 && resto_y>0){
									sol_y++;
									resto_x--;
									resto_y--;
								}else if(resto_x<0 && resto_y>0){
									sol_x--;
									resto_x++;
									resto_y--;

								}else if(resto_x>0 && resto_y<0){
									sol_x++;
									resto_x--;
									resto_y++;
								}else if(resto_x==0 && resto_y<0){
									sol_x++;
									sol_y--;
								
									resto_y++;
								}else if(resto_x==0 && resto_y>0){
									sol_x--;
									sol_y++;

									resto_y--;
								}else if(resto_x>0 && resto_y==0){
									sol_x++;
									resto_x--;
									sol_y++;
								}else if(resto_x<0 && resto_y==0){
									sol_x--;
									sol_y--;
									resto_x++;
								
								}
							}

							if(mapaResultado[current_state.fil+sol_x][current_state.col+sol_y]  == '?' ){
								cout << "copio en " << current_state.fil+sol_x<<"  "<<current_state.col+sol_y <<  "  esto: "<< mapaPreResultado[x][y]<<endl;
								mapaResultado[current_state.fil+sol_x][current_state.col+sol_y] = mapaPreResultado[x][y];
							}			
						}
					}
				}	

				*/

				cout << "brujala al noroeste "<<endl;		
				for (int x=0; x < mapaPreResultado.size(); x++){
					for(int y =0 ; y < mapaPreResultado[0].size(); y++){
						//cout << "dentro de los for y compruebo esto: "<< mapaPreResultado[x][y] << "en la posicion "<< x<< "  "<<y << endl;
						if(mapaPreResultado[x][y]  != '?' ){
							//cout << "dentro del if" << endl;
							resto_x= x - ultimo_fil-ajuste_x;
							resto_y= y - ultimo_col-ajuste_y;
							sol_x=0;
							sol_y=0;
							while(resto_x != 0 and resto_y != 0){
								if(resto_x<0 && resto_y<0){
									sol_y--;
									resto_x++;
									resto_y++;
								}else if(resto_x>0 && resto_y>0){
									sol_y++;
									resto_x--;
									resto_y--;
								}else if(resto_x<0 && resto_y>0){
									sol_x--;
									resto_x++;
									resto_y--;

								}else if(resto_x>0 && resto_y<0){
									sol_x++;
									resto_x--;
									resto_y++;
								}else if(resto_x==0 && resto_y<0){
									sol_x++;
									sol_y--;
								
									resto_y++;
								}else if(resto_x==0 && resto_y>0){
									sol_x--;
									sol_y++;

									resto_y--;
								}else if(resto_x>0 && resto_y==0){
									sol_x++;
									resto_x--;
									sol_y++;
								}else if(resto_x<0 && resto_y==0){
									sol_x--;
									sol_y--;
									resto_x++;
								
								}
							}

							if(mapaResultado[current_state.fil+sol_x][current_state.col+sol_y]  == '?' ){
								cout << "copio en " << current_state.fil+sol_x<<"  "<<current_state.col+sol_y <<  "  esto: "<< mapaPreResultado[x][y]<<endl;
								mapaResultado[current_state.fil+sol_x][current_state.col+sol_y] = mapaPreResultado[x][y];
							}			
						}
					}
				}	
			
				
				
				
				break;	
				
			}
    		

			for (unsigned int i = 0; i < max_size; i++)
     		{
     			mapaPreResultado.pop_back();

     		}
    	 	
     		for (unsigned int i = 0; i < max_size; i++)
     		{
     			mapaPreResultado.push_back(aux);

     		}

			hay_info=false;
			brujula_falsa=norte;
			perdidos_dos=true;


		}

	




	
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
		nuevo.ciclos = 0;
		memori.push_back(nuevo); 
 	}

	




     
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
	int tiempo=9999;
    for (int i = 0; i<memori.size();i++){
		memori[i].ciclos++;
		if ((sensores.terreno[2] == memori[i].letra) && (col_siguiente==memori[i].col) && (fil_siguiente==memori[i].fil)){
			encontrado++;
			
			if (tiempo>memori[i].ciclos){
				tiempo = memori[i].ciclos;
			}
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
		


		//if (((sensores.terreno  == 'M' and sensores.terreno == 'M') or  (sensores.terreno == 'M' and sensores.terreno == 'M' )) and (hueco_encontrado == false) ){

		//}



			



		

	}

	if (sensores.posF == -1 and g_encontrado and  (sensores.terreno[2]!= 'M') and  (sensores.terreno[1]!= 'M')and  (sensores.terreno[3]!= 'M')){
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
			
			and ((encontrado<2 ) or ((cont_malasuerte<=0) and (tiempo > 10)) )	
			){
			//cout << "ANDO NORMAL"<< (bool)tengo_zapatos<< "  "<<  cont_malasuerte<<endl;
			accion = actWALK;
			cont_malasuerte= 3+(rand()%(5-3));
		}/*else if(encontrado >= 1){
			cout << "ENCUENTRO CASILLA REPE"<< endl;
			accion = actTURN_SR;
			if (last_action==actTURN_L){
				accion = actTURN_SR;
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

		}*/ else if (!derecha){
			cout << "GIRO IZQ"<< endl;
			cout << "CONT = " << (int)cont << endl;
			accion= actTURN_L;
			cont++;
			if ((cont >= 2)){
		
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
			/*
			if ((last_action== actTURN_SR) && (cont <= 0)){
				derecha = false;
				//derecha= (rand()%2 ==0);

			
			}
			if ( (cont <= 0)){
				derecha = false;
				//derecha= (rand()%2 ==0);

			
			}*/
			
		
			//derecha= (rand()%2 ==0);
			derecha = false;
			cont_malasuerte--;

		}
	}
	
	//encontrado=false;

	if ( (sensores.bateria < sensores.tiempo) && (sensores.terreno[0]== 'X') ){
		accion = actIDLE;
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