#include "EventFactory.h"
#include <iostream>

#include "WormMoveEvent.h"
#include "WormChangeStateEvent.h"
#include "WormWeaponEvent.h"
#include "WormChangeLifeEvent.h"
#include "PlayerIdEvent.h"
#include "PlayerConnectEvent.h"
#include "CreateVigaEvent.h"
#include "CreateWormEvent.h"
#include "CreateMissileEvent.h"
#include "CreateStageEvent.h"
#include "MissileMoveEvent.h"
#include "MissileExploteEvent.h"
#include "StartTurnEvent.h"
#include "PlayerOffEvent.h"
#include "WormChangeAimEvent.h"
#include "GameWinnerEvent.h"

Event* EventFactory::createEvent(const EventType& type, ProxyClient& proxy, Model& model, mainView& view){
  std::cout << "hay evento " << (EventType)type << std::endl;
  switch (type) {
    case ID_PLAYER:{
      int id = proxy.receiveInt();
      return new PlayerIdEvent(id, model, proxy);
    }
    case PLAYER_CONECT:{
      int id = proxy.receiveInt();
      std::string name = proxy.receiveName();
      return new PlayerConnectEvent(id, name, model);
    }
    case CREATE_VIGA:{
      int posx = proxy.receivePosX();
      int posy = proxy.receivePosY();
      int angle = proxy.receiveAngle();
      return new CreateVigaEvent(posx, posy, angle, view);
    }
    case CREATE_STAGE:{
      int widht = proxy.receiveWidht();
      int height = proxy.receiveHeight();
      printf("DIMENSIONES %i, %i", widht, height);
      return new CreateStageEvent(widht, height) ;
    }
    case CREATE_WORM:{
      int idWorm = proxy.receiveInt();
      int idOwner = proxy.receiveInt();
      int posx = proxy.receivePosX();
      int posy = proxy.receivePosY();
      int dir = proxy.receiveInt();
      int angle = proxy.receiveAngle();
      return new CreateWormEvent(idWorm, idOwner, posx, posy, dir, angle, model, view);
    }
    case START_TURN:{
      int currPlayer = proxy.receiveInt();
      int idWorm = proxy.receiveInt();
      return new StartTurnEvent(currPlayer, idWorm, model, view);
    }
     case W_MOVE: {
      int idWorm = proxy.receiveInt();
      int posx = proxy.receivePosX();
      int posy = proxy.receivePosY();
      int dir = proxy.receiveInt();
      int angle = proxy.receiveAngle();
      return new WormMoveEvent(idWorm, posx, posy, dir, angle);
    }
    case W_CHANGE_STATE:{
      int idWorm = proxy.receiveInt(); 
      int newState = proxy.receiveInt();
      return new WormChangeStateEvent(idWorm, newState);
    }
    case M_CREATE:{
      int idMissile = proxy.receiveInt(); 
      int idWeapon = proxy.receiveInt();
      int dir = proxy.receiveInt();
      int posx = proxy.receivePosX();
      int posy = proxy.receivePosY();
      int angle = proxy.receiveAngle();
      return new CreateMissileEvent(idMissile, idWeapon, dir, posx, posy, angle, view);
    }
    case M_POS: {
      int idMissile = proxy.receiveInt();
      int posx = proxy.receivePosX();
      int posy = proxy.receivePosY();
      int angle = proxy.receiveAngle();
      return new MissileMoveEvent(idMissile, posx, posy, angle);
    }
    case M_EXPLOTE: {
      int idMissile = proxy.receiveInt();
      return new MissileExploteEvent(idMissile);
    }
    case W_CUR_WEAPON: {
      int idWeapon = proxy.receiveInt();
      return new WormWeaponEvent(model.getIdWormSelected(), idWeapon);
    }
    case W_CUR_AIM: {
      int curAimAngle = proxy.receiveInt(); //+1 -1
      return new WormChangeAimEvent(model.getIdWormSelected(), curAimAngle);
    }
    case W_CHANGE_LIFE: {
      int idWorm = proxy.receiveInt();
      int newLife = proxy.receiveInt();
      return new WormChangeLifeEvent(idWorm, newLife);
    }
    case G_PLAYER_OFF: {
      int idPlayer = proxy.receiveInt();
      return new PlayerOffEvent(idPlayer, model, view);
    }
    case G_PLAYER_WIN:{
      int idPlayer = proxy.receiveInt();
      return new GameWinnerEvent(idPlayer, model, view);
    }
  }
  return nullptr; //nunca deberia llegar todos los casos cubiertos
}
