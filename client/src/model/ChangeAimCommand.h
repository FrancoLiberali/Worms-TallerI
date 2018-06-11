#ifndef _CHANGE_AIM_COMMAND_H
#define _CHANGE_AIM_COMMAND_H

#include "ClientCommand.h"

class ChangeAimCommand : public ClientCommand{
private:
    int idJugador;
    int delta;
public:
    ChangeAimCommand(int idJugador, const int delta);
    void send(ProxyClient& proxy);
};

#endif