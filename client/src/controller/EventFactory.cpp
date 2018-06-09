#include "EventFactory.h"
#include <iostream>

#include "WormMoveEvent.h"
#include "WormChangeStateEvent.h"
#include "WormWeaponEvent.h"



Event *EventFactory::createEvent(const EventType& type, std::stringstream& ss, Model& model) {
  switch (type) {
    case W_CHANGE_STATE:{
      int id = 0, state = 0;
      ss >> id; ss >> state;
      return new WormChangeStateEvent(id, state);
    }
    case W_MOVE: {
      /*segun el protocolo la secuencia despues del tipo es*/
      int idJugador = 0, idWorm = 0, posx =  0, posy = 0, dir = 0, angle = 0;
      ss >> idWorm; ss >> posx; ss >> posy; ss >> dir; ss >> angle;
      return new WormMoveEvent(idWorm, posx, posy, dir, angle);
    }
    case START_TURN: {
      return nullptr;
    }
    case B_POS: {      
      return nullptr;
    }
    case B_EXPLOTE: {
      return nullptr;
    }
    case W_CUR_WEAPON: {
      int id = 0; 
      ss >> id;
      //WeaponId idWeapon = getWeaponId(idWeapon);
      std::cout<<"Change Weapon " << id << std::endl; 
      //break;
      return new WormWeaponEvent(model.getIdWormSelected(), id);
    }
    case W_CUR_AIM: {
      return nullptr;
    }
    case G_ENDGAME: {
      return nullptr;
    }

  }
  return nullptr; //nunca deberia llegar todos los casos cubiertos
}

Event* EventFactory::createEvent(const EventType& type, ProxyClient& proxy, Model& model){
  switch (type) {
    case W_CHANGE_STATE:{
      int id = proxy.receiveInt(); 
      int state = proxy.receiveInt();
      return new WormChangeStateEvent(id, state);

    }
    case W_MOVE: {
      /*segun el protocolo la secuencia despues del tipo es*/
      int id = proxy.receiveInt();
      int posx = proxy.receiveInt();
      int posy = proxy.receiveInt();
      int dir = proxy.receiveInt();
      int angle = proxy.receiveInt();
      return new WormMoveEvent(id, posx, posy, dir, angle);
    }
  }
  return nullptr; //nunca deberia llegar todos los casos cubiertos
}
