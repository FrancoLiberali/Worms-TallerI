#ifndef _WORM_MOVE_COMMAND_H
#define _WORM_MOVE_COMMAND_H

#include "ClientCommand.h"

/**
* @class WormMoveCommand
* Comando de cambio en la posición de un gusano.
*/

class WormMoveCommand : public ClientCommand{
private:
    int  idJugador;
    int dir;
public:
    WormMoveCommand(int idJugador, const int dir);
    void send(ProxyClient& proxy);
};

#endif