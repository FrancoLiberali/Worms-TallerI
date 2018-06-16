#ifndef _CHANGE_COUNT_DOWN_COMMAND_H
#define _CHANGE_COUNT_DOWN_COMMAND_H

#include "ClientCommand.h"

class ChangeCountDownCommand : public ClientCommand{
private:
    int idJugador;
    int time;
public:
    ChangeCountDownCommand(int idJugador, const int time);
    void send(ProxyClient& proxy);
};

#endif