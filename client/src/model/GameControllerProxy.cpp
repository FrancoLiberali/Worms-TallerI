#include "GameControllerProxy.h"
#include "WormMoveCommand.h"

GameControllerProxy::GameControllerProxy(Queue<ClientCommand *> &queue)
    : queue(queue) {}

void GameControllerProxy::move(const int idWorm, const int direccion) {
  queue.push(new WormMoveCommand(idWorm, direccion));
}

GameControllerProxy::~GameControllerProxy(){}