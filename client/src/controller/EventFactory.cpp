#include "EventFactory.h"
#include <iostream>

#include "WormMoveEvent.h"

Event *EventFactory::createEvent(const EventType& type, std::stringstream& ss) {
  std::cout << "fabrico " << ss.str() << std::endl ; 

  switch (type) {
    case W_MOVE: {
      /*segun el protocolo la secuencia despues del tipo es*/
      int id = 0;
      int posx =  0, posy = 0;
      ss >> id;
      ss >> posx;
      ss >> posy;
      std::cout << "fabrico" << posx << "-" << posy <<std::endl ; 

      return new WormMoveEvent(id, posx, posy);
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
