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
};

class ComportamientoJugador : public Comportamiento{

  public:
    ComportamientoJugador(unsigned int size) : Comportamiento(size){
      // Constructor de la clase
      // Dar el valor inicial a las variables de estado
     last_action = actIDLE;
     current_state.fil = current_state.col = 99;
     current_state.brujula= norte;
     derecha = false;
     bien_situado = false;
     bool tengo_bikini= false;
     bool tengo_zapatos= false;
     int cont_malasuerte = 8;


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
  
};
#endif
