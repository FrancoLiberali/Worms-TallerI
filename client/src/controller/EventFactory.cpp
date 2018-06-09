#include "EventFactory.h"
#include <iostream>

#include "WormMoveEvent.h"
#include "WormChangeStateEvent.h"
#include "WormWeaponEvent.h"
#include "WormChangeLifeEvent.h"


Event* EventFactory::createEvent(const EventType& type, ProxyClient& proxy, Model& model){
  switch (type) {
    case START_TURN:{
      int currPlayer = proxy.receiveInt();
      int idWorm = proxy.receiveInt();
      return nullptr;
    }
     case W_MOVE: {
      int idWorm = proxy.receiveInt();
      int posx = proxy.receiveInt();
      int posy = proxy.receiveInt();
      int dir = proxy.receiveInt();
      int angle = proxy.receiveInt();
      return new WormMoveEvent(idWorm, posx, posy, dir, angle);
    }
    case W_CHANGE_STATE:{
      int idWorm = proxy.receiveInt(); 
      int newState = proxy.receiveInt();
      return new WormChangeStateEvent(idWorm, newState);
    }
    case B_POS: {
      int idBullet = proxy.receiveInt();
      int idWeapon = proxy.receiveInt();
      int posx = proxy.receiveInt();
      int posy = proxy.receiveInt();
      int dir = proxy.receiveInt();
      int angle = proxy.receiveInt();
      return nullptr;
    }
    case B_EXPLOTE: {
      int idBullet = proxy.receiveInt();
      int posx = proxy.receiveInt();
      int posy = proxy.receiveInt();
      return nullptr;
    }
    case W_CUR_WEAPON: {
      int idWeapon = proxy.receiveInt();
      std::cout<<"Change Weapon " << idWeapon << std::endl; 
      return new WormWeaponEvent(model.getIdWormSelected(), idWeapon);
    }
    case W_CUR_AIM: {
      int curAimAngle = proxy.receiveInt(); //+1 -1
      return nullptr;
    }
    case W_CHANGE_LIFE: {
      int idWorm = proxy.receiveInt();
      int newLife = proxy.receiveInt();
      return new WormChangeLifeEvent(idWorm, newLife);
    }
    case G_PLAYER_OFF: {
      int idPlayer = proxy.receiveInt();
      return nullptr;
    }
    case G_PLAYER_WIN:
      int idPlayer = proxy.receiveInt();
      return nullptr;
  }
  return nullptr; //nunca deberia llegar todos los casos cubiertos
}
