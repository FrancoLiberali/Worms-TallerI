#include "GameControllerProxy.h"
#include "WormMoveCommand.h"
#include "WormJumpCommand.h"
#include "WormWeaponCommand.h"
#include "ChangeAimCommand.h"
#include "ChargePowerCommand.h"
#include "WormShootCommand.h"
#include "ChangeCountDownCommand.h"
#include "TeledirigidoCommand.h"

#include <iostream>

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

void GameControllerProxy::chargePower(const int idJugador){
  queue.push(new ChargePowerCommand(idJugador));
}

void GameControllerProxy::shoot(const int idJugador){
  queue.push(new WormShootCommand(idJugador));
}

void GameControllerProxy::countDown(const int idJugador, const int time){
  queue.push(new ChangeCountDownCommand(idJugador, time));
}

void GameControllerProxy::teledirigido(const int idJugador, const int x, const int y){
  queue.push(new TeledirigidoCommand(idJugador, x, y));
}


GameControllerProxy::~GameControllerProxy(){}