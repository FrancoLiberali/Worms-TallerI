#include "GameControllerProxy.h"
#include "WormMoveCommand.h"
#include "WormJumpCommand.h"
#include "WormWeaponCommand.h"
#include "ChangeAimCommand.h"


GameControllerProxy::GameControllerProxy(Queue<ClientCommand *> &queue)
    : queue(queue) {}

void GameControllerProxy::move(const int idJugador, const int direccion) {
  queue.push(new WormMoveCommand(idJugador, direccion));
}

void GameControllerProxy::jump(const int idJugador, const int direccion) {
  queue.push(new WormJumpCommand(idJugador, direccion));
}

void GameControllerProxy::weapon(const int idJugador, const int idWeapon){
  queue.push(new WormWeaponCommand(idJugador, idWeapon));
}

void GameControllerProxy::aimAngle(const int idJugador, const int delta){
  queue.push(new ChangeAimCommand(idJugador, delta));
}


GameControllerProxy::~GameControllerProxy(){}