#ifndef _GAME_CONTROLLER_PROXY_H
#define _GAME_CONTROLLER_PROXY_H

#include "../common/Queue.h"
#include "ClientCommand.h"

class GameControllerProxy{
private:
    Queue<ClientCommand *> &queue;
public:
    GameControllerProxy(Queue<ClientCommand *> &queue);
    ~GameControllerProxy();
    void move(const int idWorm, const int direccion);
};

#endif