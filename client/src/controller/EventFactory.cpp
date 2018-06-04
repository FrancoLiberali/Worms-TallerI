#include "EventFactory.h"
#include <iostream>

#include "WormMoveEvent.h"
#include "WormChangeStateEvent.h"

Event *EventFactory::createEvent(const EventType& type, std::stringstream& ss) {
  //std::cout << "fabrico " << ss.str() << std::endl ; 

  switch (type) {
    case W_CHANGE_STATE:{
      std::cout << "W_Change" << std::endl;
      int id = 0, state = 0;
      ss >> id; ss >> state;
      return new WormChangeStateEvent(id, state);

    }
    case W_MOVE: {
      /*segun el protocolo la secuencia despues del tipo es*/
      int id = 0, posx =  0, posy = 0, dir = 0, angle = 0;
      ss >> id; ss >> posx; ss >> posy; ss >> dir; ss >> angle;
      return new WormMoveEvent(id, posx, posy, dir, angle);
    }
    case W_ATTACK: {
      return nullptr;
    }
    case W_JUMP: {      
      return nullptr;
    }
    case W_DEATH: {
      return nullptr;
    }
    case G_ENDGAME: {
      return nullptr;
    }
  }
  return nullptr; //nunca deberia llegar todos los casos cubiertos
}
