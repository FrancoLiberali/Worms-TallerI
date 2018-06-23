#ifndef _WORM_SHOOT_COMMAND_H
#define _WORM_SHOOT_COMMAND_H

#include "ClientCommand.h"

class WormShootCommand : public ClientCommand{
private:
    int idJugador;
public:
    WormShootCommand(int idJugador);
    void send(ProxyClient& proxy);
};

#endif