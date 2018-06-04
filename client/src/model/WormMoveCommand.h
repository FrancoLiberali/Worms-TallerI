#ifndef _WORM_MOVE_COMMAND_H
#define _WORM_MOVE_COMMAND_H

#include "ClientCommand.h"

class WormMoveCommand : public ClientCommand{
private:
    int  idWorm;
    int dir;
public:
    WormMoveCommand(int idWorm, const int dir);
    void send(ProxyClient& proxy);
};

#endif