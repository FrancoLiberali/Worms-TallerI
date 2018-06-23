#ifndef _WORM_MOVE_COMMAND_H
#define _WORM_MOVE_COMMAND_H

#include "ClientCommand.h"

class WormMoveCommand : public ClientCommand{
private:
    int  idJugador;
    int dir;
public:
    WormMoveCommand(int idJugador, const int dir);
    void send(ProxyClient& proxy);
};

#endif