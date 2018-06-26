#include "EventFactory.h"
#include <iostream>

#include "event/WormMoveEvent.h"
#include "event/WormChangeStateEvent.h"
#include "event/WormWeaponEvent.h"
#include "event/WormChangeLifeEvent.h"
#include "event/BackgroundEvent.h"
#include "event/CreateVigaEvent.h"
#include "event/CreateWormEvent.h"
#include "event/CreateMissileEvent.h"
#include "event/CreateStageEvent.h"
#include "event/MissileMoveEvent.h"
#include "event/MissileExploteEvent.h"
#include "event/StartTurnEvent.h"
#include "event/PlayerOffEvent.h"
#include "event/PlayerLoseEvent.h"
#include "event/WormChangeAimEvent.h"
#include "event/GameWinnerEvent.h"
#include "event/WeaponDoneEvent.h"
#include "event/RightTargertEvent.h"
#include "event/SecondEvent.h"
#include "event/WindChangedEvent.h"


Event* EventFactory::createEvent(const EventType& type, ProxyClient& proxy){
  switch (type) {
    case BACKGROUND_STAGE:{
      std::string name = proxy.receiveName();
      return new BackgroundEvent(name);
    }
    case CREATE_VIGA:{
      int posx = proxy.receivePosX();
      int posy = proxy.receivePosY();
      int angle = proxy.receiveAngle();
      return new CreateVigaEvent(posx, posy, angle);
    }
    case CREATE_STAGE:{
      int widht = proxy.receiveWidht();
      int height = proxy.receiveHeight();
      return new CreateStageEvent(widht, height) ;
    }
    case CREATE_WORM:{
      int idWorm = proxy.receiveInt();
      int idOwner = proxy.receiveInt();
      int posx = proxy.receivePosX();
      int posy = proxy.receivePosY();
      int dir = proxy.receiveInt();
      int angle = proxy.receiveAngle();
      return new CreateWormEvent(idWorm, idOwner, posx, posy, dir, angle);
    }
    case START_TURN:{
      int currPlayer = proxy.receiveInt();
      int idWorm = proxy.receiveInt();
      return new StartTurnEvent(currPlayer, idWorm);
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
      return new CreateMissileEvent(idMissile, idWeapon, dir, posx, posy, angle);
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
      return new WormWeaponEvent(idWeapon);
    }
    case W_CUR_AIM: {
      int curAimAngle = proxy.receiveInt(); //+1 -1
      return new WormChangeAimEvent(curAimAngle);
    }
    case W_CHANGE_LIFE: {
      int idWorm = proxy.receiveInt();
      int newLife = proxy.receiveInt();
      return new WormChangeLifeEvent(idWorm, newLife);
    }
    case A_PLAYER_OFF: {
      int idPlayer = proxy.receiveInt();
      return new PlayerOffEvent(idPlayer);
    }
    case A_PLAYER_LOSE:{
      int idPlayer = proxy.receiveInt();
      return new PlayerLoseEvent(idPlayer);
    }
    case A_PLAYER_WIN:{
      int idPlayer = proxy.receiveInt();
      return new GameWinnerEvent(idPlayer);
    }
    case WEAPON_DONE:{
      int idWeapon = proxy.receiveInt();
      return new WeaponDoneEvent(idWeapon);
    }
    case RIGHT_TARGET:{
      int idWeapon = proxy.receiveInt();
      return new RightTargertEvent(idWeapon);
    }
    case SECOND:{
      return new SecondEvent();
    }
    case WIND_CHANGED:{
      int windSpeed = proxy.receiveInt();
      return new WindChangedEvent(windSpeed);
    }
  }
  printf("Error\n");
  return nullptr; //nunca deberia llegar todos los casos cubiertos
}
