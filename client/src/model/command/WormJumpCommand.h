#ifndef _WORM_JUMP_COMMAND_H
#define _WORM_JUMP_COMMAND_H

#include "ClientCommand.h"

/**
* @class WormJumpCommand
* Comando de salto de un gusano.
*/

class WormJumpCommand : public ClientCommand{
private:
    int idJugador;
    int dir;
public:
    WormJumpCommand(int idJugador, const int dir);
    void send(ProxyClient& proxy);
};

#endif