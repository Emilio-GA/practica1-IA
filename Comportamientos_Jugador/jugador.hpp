#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H

#include "comportamientos/comportamiento.hpp"
using namespace std;

struct state{
  int fil;
  int col;
  Orientacion brujula;
};
struct almacen{
  int fil;
  int col;
  char letra;
  int ciclos;
};

class ComportamientoJugador : public Comportamiento{

  public:
    ComportamientoJugador(unsigned int size) : Comportamiento(size){
      // Constructor de la clase
      // Dar el valor inicial a las variables de estado
     last_action = actIDLE;
     max_size = 198;
     current_state.fil = current_state.col = 99;
     current_state.brujula= norte;
     ultimo_fil=0;
     ultimo_col=0;
     derecha = false;
     bien_situado = false;
     tengo_bikini = false;
     tengo_zapatos = false;
     cont_malasuerte = 5;
     cont = 0;
     brujula_falsa = norte;
     vector<unsigned char> aux(max_size, '?');
     hay_info=false;
     for (unsigned int i = 0; i < max_size; i++)
     {
     mapaPreResultado.push_back(aux);

     }
    }


    

    ComportamientoJugador(const ComportamientoJugador & comport) : Comportamiento(comport){}
    ~ComportamientoJugador(){}

    Action think(Sensores sensores);
    int interact(Action accion, int valor);

  private:
  // Declarar aquí las variables de estado
  Action last_action;
  state current_state;
  bool derecha;
  bool bien_situado;
  bool tengo_bikini;
  bool tengo_zapatos;
  int cont_malasuerte;
  vector <almacen> memori;
  double cont;
  Orientacion brujula_falsa;
  vector< vector< unsigned char> > mapaPreResultado;
  int max_size;
  bool hay_info;
  int ultimo_fil=0;
  int ultimo_col=0;
};
#endif
